#include <msgpack.h>
#include <string.h>
#include <stdio.h>
#include "checkpointing.h"

int main(int argc, char *argv[])
{
  if (argc < 2){
    fprintf(stderr, "Error no input file name give.\n");
    exit(1);
  }

  char *name = argv[1];
  int **arr = malloc(sizeof(int*)*5);
  int count = 0;
  
  /* filling out the 2D array */
  for(int i = 0; i < 5; ++i){
    arr[i] = malloc(sizeof(int)*5);
    for (int j = 0; j < 5; ++j){
      arr[i][j] = count;
      ++count;
    }
  }
  
  int col =  5; // size of col array
  int row =  5; // size of row array

  /* allocating room for game struct and filling out fields */
  game_t *ex = malloc(sizeof(game_t));
  ex->col = col;
  ex->row = row;
  ex->arr = arr;
  ex->desc = "Black Moved Somewhere";
  ex->curr = WHITE;
  
  FILE *save = fopen(name, "w"); // opens the file we are going to write into

  /* initializes all of the variables needed in serializing */
  msgpack_sbuffer sbuf;
  msgpack_sbuffer_init(&sbuf);
  msgpack_packer pk;
  msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

  
  msgpack_pack_array(&pk, (ex->col*ex->row) + 5); // determines size of pack array 

  msgpack_pack_int(&pk, ex->col); // packs the col size of array first
  msgpack_pack_int(&pk, ex->row); // packs the row size of array first

  /* packs the 2D array into the pack array */
  for(int i=0; i<5; ++i)
    for (int j=0; j<5; ++j)
      msgpack_pack_int(&pk, ex->arr[i][j]);

  
  int strlength = strlen(ex->desc); // length of the string description
  msgpack_pack_int(&pk, strlength); // packs length of string
  msgpack_pack_str(&pk, strlength); // packs room for string
  msgpack_pack_str_body(&pk, ex->desc, strlength); // packs the string in
  int player = 0;
  if (ex->curr == 1){
    player = 1;
  } else {
    player = 0;
  }
  msgpack_pack_int(&pk, player); // packs the current turn
 
  fwrite(sbuf.data, sbuf.size, 1, save); // writes the packed array into the file
  
  fclose(save); // closes the file

  // frees each array in the columns
  for(int i=0; i<5; ++i)
    free(arr[i]);

  free(arr); // frees overall array

  free(ex); // free game struct
  
  msgpack_sbuffer_destroy(&sbuf); // frees buffer
  return 0;
}
