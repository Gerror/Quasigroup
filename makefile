all: a.out

a.out: IncidenceCube.o Quasigroup.o main.o
	g++ IncidenceCube.o Quasigroup.o main.o -Wall -o a.out

IncidenceCube.o: IncidenceCube.cpp
	g++ -c -Wall IncidenceCube.cpp 

Quasigroup.o: Quasigroup.cpp
	g++ -c -Wall Quasigroup.cpp

main.o: main.cpp
	g++ -c -Wall main.cpp 

clean:
	rm -rf *.o a.out