all: main.o main run clean

main.o: main.c
	gcc -g -Wall -c main.c

main: main.o
	gcc -o main main.o

run:
	./main

clean:
	rm main *.o