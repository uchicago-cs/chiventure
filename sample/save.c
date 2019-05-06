#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sample.pb-c.h"

int main (int argc, char * argv[]) 
{
	Game file = GAME__INIT;
	Player sub1 = PLAYER__INIT;
	Room sub2 = ROOM__INIT;
	void *buf;
	unsigned len;

	if (argc != 4 || argc != 5){
		fprintf(stderr, "usage: game player_info location [discovered]");
		return 1;
	}
	sub1.name = argv[1];
	sub1.gender = atoi(argv[2]);
	file.player_info = &sub1;

	sub2.r_name = argv[3];
	file.location = &sub2;

	if (argc == 5) {
		file.has_discovered = 1;
		file.discovered = atoi(argv[4]);
	}

	len = game__get_packed_size(&file);
	buf = malloc(len);
	game__pack(&file,buf);

	fprintf(stderr, "Writing %d serialized bytes\n", len);
	fwrite(buf, len, 1, stdout);

	free(buf);
	return 0;
}
