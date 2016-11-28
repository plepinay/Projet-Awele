projet : projet.o Outil.c
	gcc projet.o Outil.c -o projet -lm
Outil.o : Outil.c
	gcc -c Outil.c
projet.o : projet.c Outil.h
	gcc -c projet.c Outil.h

