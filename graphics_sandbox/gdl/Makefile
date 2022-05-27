all: read_gdl test_camera test_dimensions

read_gdl: read_gdl.c
	gcc -fPIC -g -O2 -Wall -Wextra -O2 -I../../include/ read_gdl.c ../../src/game-state/src/stats.c -o read_gdl -lcriterion


#<<<<<<< HEAD

#SRCS = read_gdl.c test_dimensions.c test_camera.c 
#OBJS = $(SRCS:.c=.o)

#BINS = read_gdl test

#all: $(BINS)

#.PHONY: clean all

#$(OBJS): %.o:%.c
#	$(CC) $(CFLAGS) $< -c -o $@

#$(BINS): $(OBJS) 
#	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)
#=======
#test_camera: test_camera.c
#	gcc -fPIC -g -Wall -Wextra -O2 -I../../include/ test_camera.c read_gdl.c ../../src/game-state/src/stats.c -o test_camera -L../ -lcriterion
#=======
test_camera: test_camera.c read_gdl.c
	cc -fPIC -g -Wall -Wextra -O2 -I../../include/ -L../ -Wl,-rpath,. test_camera.c read_gdl.c ../../src/game-state/src/stats.c -o test_camera -lcriterion

test_dimensions: test_dimensions.c read_gdl.c
	cc -fPIC -g -Wall -Wextra -O2 -I../../include/ -L../ -Wl,-rpath,. test_dimensions.c read_gdl.c ../../src/game-state/src/stats.c -o test_dimensions -lcriterion
#>>>>>>> 2efcb7fc70672d6173cb188200e38fbd449e31c3

clean:
	rm -f read_gdl test_camera test_dimensions
