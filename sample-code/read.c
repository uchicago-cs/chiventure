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

  /* prints out the data from the file */

  do {
    read = fread(inbuffer, sizeof(char), buffsize - off, reading);
    off = 0;
    while(msgpack_unpack_next(&unp, inbuffer, read, &off)) {
      msgpack_object_print(stdout, unp.data);
      puts("");
    }
    memcpy(inbuffer, &(inbuffer[off]), read-off);
    off = read - off;
  } while(read != 0);
  free(inbuffer);
  
  fclose(reading); // closes the file that was read
  
  msgpack_unpacked_destroy(&unp); // frees everything
  
  return 0;
}
