all: read_gdl test_camera test_dimensions

read_gdl: read_gdl.c
	gcc -fPIC -g -O2 -Wall -Wextra -O2 -I../../include/ read_gdl.c ../../src/game-state/src/stats.c -o read_gdl -lcriterion

test_camera: test_camera.c read_gdl.c
	cc -fPIC -g -Wall -Wextra -O2 -I../../include/ -L../ -Wl,-rpath,. test_camera.c read_gdl.c ../../src/game-state/src/stats.c -o test_camera -lcriterion

test_dimensions: test_dimensions.c read_gdl.c
	cc -fPIC -g -Wall -Wextra -O2 -I../../include/ -L../ -Wl,-rpath,. test_dimensions.c read_gdl.c ../../src/game-state/src/stats.c -o test_dimensions -lcriterion

clean:
	rm -f read_gdl test_camera test_dimensions
