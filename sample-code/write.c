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
  
  int size =  25; // size of 2D Array

  /* allocating room for game struct and filling out fields */
  game_t *ex = malloc(sizeof(game_t));
  ex->size = size;
  ex->arr = arr;
  ex->desc = "Black Moved Somewhere";
  ex->curr = WHITE;
  
  FILE *save = fopen(name, "w"); // opens the file we are going to write into

  /* initializes all of the variables needed in serializing */
  msgpack_sbuffer sbuf;
  msgpack_sbuffer_init(&sbuf);
  msgpack_packer pk;
  msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

  
  msgpack_pack_array(&pk, ex->size + 3); // determins size of pack array 

  msgpack_pack_int(&pk, ex->size); // packs the size of array first

  /* packs the 2D array into the pack array */
  for(int i=0; i<5; ++i)
    for (int j=0; j<5; ++j)
      msgpack_pack_int(&pk, ex->arr[i][j]);

  
  int strlength = strlen(ex->desc); // length of the string description
  msgpack_pack_str(&pk, strlength); // packs room for string
  msgpack_pack_str_body(&pk, ex->desc, strlength); // packs the string in

  msgpack_pack_int(&pk, ex->curr); // packs the current turn
 
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
