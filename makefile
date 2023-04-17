fic = fichier/fichier
ia = IA/IA
i = interface/interface
j = joueur/joueur
m = moteur/moteur



all: main.o fichier.o IA.o interface.o joueur.o moteur.o main run clean

main: main.o fichier.o IA.o interface.o joueur.o moteur.o
	gcc -o main main.o fichier.o IA.o interface.o joueur.o moteur.o `sdl2-config --libs`

main.o: main.c
	gcc -g -Wall -c main.c

fichier.o: ${fic}.c
	gcc -g -Wall -c ${fic}.c

IA.o: ${ia}.c
	gcc -g -Wall -c ${ia}.c

interface.o: ${i}.c
	gcc -g -Wall -c ${i}.c `sdl2-config --cflags`

joueur.o: ${j}.c
	gcc -g -Wall -c ${j}.c

moteur.o: ${m}.c
	gcc -g -Wall -c ${m}.c

run:
	./main

clean:
	rm main *.o