CC = gcc

all: noise

noise: noise.o wav.o pink.o white.o

clean:
	rm -f *.o noise
