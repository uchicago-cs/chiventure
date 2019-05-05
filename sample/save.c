#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sample.pb-c.h"

int main (int argc, const char * argv[]) 
{
	Game file = GAME__INIT;
	Player sub1 = PLAYER__INIT;
	Room sub2 = ROOM__INIT;
	void *buf;
	unsigned len;

	if (argc !=3 || argc != 4){
		fprintf(stderr, "usage: game player_info location [discovered]");
		return 1;
	}

	sub1.p_name = atoi(argv[1]);
	file.player_info = &sub1;

	sub2.r_name = atoi(argv[2]);
	file.location = &sub2;

	if (argc == 4) {
		file.has_discovered = 1;
		file.discovered = atoi(argv[3]);
	}

	len = sample__get_packed_size(&file);
	buf = malloc(len);
	sample__pack(&file,buf);

	fprintf(stderr, "Writing %d serialized bytes\n", len);
	fwrite(buf, len, 1, stdout);

	free(buf);
	return 0;
}
