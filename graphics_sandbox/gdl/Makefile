read_gdl: read_gdl.c
	gcc -fPIC -g -O2 -Wall -Wextra -O2 -I../../include/ read_gdl.c ../../src/game-state/src/stats.c -o read_gdl -lcriterion

test_camera: test_camera.c
	gcc -fPIC -g -Wall -Wextra -O2 -I../../include/ test_camera.c read_gdl.c ../../src/game-state/src/stats.c -o test_camera -L../ -lcriterion

clean:
	rm -f read_gdl
