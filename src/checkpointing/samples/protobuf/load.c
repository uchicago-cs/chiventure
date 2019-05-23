#include <stdio.h>
#include <string.h>
#include "sample.pb-c.h"
#define MAX_BUF_SIZE 4096


int main (int argc, const char *argv[]) 
{
    Game *file;
    Player *sub1;
    Room *sub2;

    char c;
    int i = 0;
    uint8_t buf[MAX_BUF_SIZE];

    while (fread(&c, 1, 1, stdin) != 0) {
	if (i >= MAX_BUF_SIZE) {
	    fprintf(stderr, "msg too long for allocated buffer\n");
	    return 1;
	}
	buf[i] = c;
	i++;
    }

    file = game__unpack(NULL, i, buf);
    if (file == NULL) {
	fprintf(stderr, "error unpacking incoming message\n");
	return 1;
    }

    sub1 = file->player_info;
    sub2 = file->location;

    printf("Received: \nplayer_info: name = %s\ngender = %d\nlocation = %s\n", 
	   sub1->name, sub1->gender, sub2->r_name);
    if (file->has_discovered == 1) {
	printf("discovered = %d\n", file->discovered);
    }
    
    game__free_unpacked(file, NULL);

    return 0;
}
