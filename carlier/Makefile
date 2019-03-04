__start__: carlier.out
	./carlier.out

carlier.out: main.o Carlier.o Zadanie.o 
	g++ main.o Carlier.o Zadanie.o

main.o: main.cpp Carlier.h Zadanie.h
	g++ -c -Wall -pedantic main.cpp

Carlier.o: Carlier.h Carlier.cpp
	g++ -c -Wall -pedantic Carlier.cpp

Zadanie.o: Zadanie.h Zadanie.cpp
	g++ -c -Wall -pedantic Zadanie.cpp
