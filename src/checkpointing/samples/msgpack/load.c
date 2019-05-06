#include <msgpack.h>
#include <stdio.h>
#include <string.h>
#include "checkpointing.h"

int main(int argc, char *argv[])
{
  if (argc < 2){
    fprintf(stderr, "There was no file name given\n");
    exit(1);
  }
  
  int buffsize = 2048;

  char *inbuffer = malloc(buffsize); // space for buffer size

  FILE *reading = fopen(argv[1], "r"); //reading from given file in stdin
  size_t off = 0;
  size_t read = 0;
  msgpack_unpacked unp;
  msgpack_unpacked_init(&unp); // initializing the unpacking

  FILE *write = fopen("loaded.txt", "w");
  /* prints out the data from the file */
  /* source:
  https://stackoverflow.com/questions/43442194/how-do-i-read-and-write-with-msgpack */
  do {    
    read = fread(inbuffer, sizeof(char), buffsize - off, reading);
    off = 0;
    while(msgpack_unpack_next(&unp, inbuffer, read, &off)) {
      msgpack_object_print(write, unp.data); // writes to new write file
      fputc('\n', write);
    }
    memcpy(inbuffer, &(inbuffer[off]), read-off);
    off = read - off;
  } while(read != 0);

 
  free(inbuffer);
    
  fclose(reading); // closes the file that was read
  msgpack_unpacked_destroy(&unp); // frees everything
  fclose(write); // closes the human readable deserialized code

  game_t *ex = malloc(sizeof(game_t));
  ex->col = 0;
  ex->row = 0;
  ex->curr = 0;
  int col = 0, row = 0;
  FILE *load = fopen("loaded.txt", "r"); // opens human-readable deserialized code
  fscanf(load,"[%d, %d,", &col, &row); // gets column and row

  ex->col = col;
  ex->row = row;

  int **arr = malloc(sizeof(int*)*col);
  int temp = 0;
  for(int i=0; i<col; ++i){
    arr[i] = malloc(sizeof(int)*row);
    for (int j=0; j<row; ++j){
      fscanf(load," %d,", &temp); // gets every value in array
      arr[i][j] = temp;
    }
  }

  ex->arr = arr;

  int strlength = 0;
  fscanf(load, " %d,", &strlength);
  char *str = malloc(strlength*2);
  char *pattern = " \"%[^\"]\","; 
  fscanf(load, pattern, str); // gets the string

  ex->desc = str;

  int player = 0;
  fscanf(load," %d]", &player); // gets the current player

  ex->curr = player; 

  /* prints out game struct and values */
  printf("Game Struct Contains\n");
  printf("column size: %d\n", ex->col);
  printf("row size: %d\n", ex->row);
  printf("array values: ");
  for(int i=0; i<ex->col; ++i)
    for(int j=0; j<ex->row; ++j){
      temp = ex->arr[i][j];
      printf("%d ", temp);
    }
  printf("\n");
  printf("description: %s\n", ex->desc);
  printf("current player: %s\n", ex->curr==0?"BLACK":"WHITE");

  /* frees all the loaded structs */
  fclose(load);
  free(str);
  for(int i=0; i<ex->col; ++i)
    free(arr[i]);
  free(arr);
  free(ex);
  remove("loaded.txt");
  
  return 0;
}
