CFLAGS = -W -Wall `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf

fic = fichier/fichier
ia = IA/IA
i = interface/interface
j = joueur/joueur
m = moteur/moteur



all: main.o fichier.o IA.o interface.o joueur.o moteur.o main run clean

main: main.o fichier.o IA.o interface.o joueur.o moteur.o
	gcc -o main main.o fichier.o IA.o interface.o joueur.o moteur.o ${LDFLAGS}

main.o: main.c
	gcc -g -Wall -c main.c ${CFLAGS}

fichier.o: ${fic}.c
	gcc -g -Wall -c ${fic}.c ${CFLAGS}

IA.o: ${ia}.c
	gcc -g -Wall -c ${ia}.c ${CFLAGS}

interface.o: ${i}.c
	gcc -g -Wall -c ${i}.c ${CFLAGS}

joueur.o: ${j}.c
	gcc -g -Wall -c ${j}.c ${CFLAGS}

moteur.o: ${m}.c
	gcc -g -Wall -c ${m}.c ${CFLAGS}

run:
	./main

clean:
	rm main *.o