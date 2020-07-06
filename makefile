all: program

program: main.o IncidenceCube.o Quasigroup.o
	g++ main.o IncidenceCube.o Quasigroup.o -o program

main.o: main.cpp
	g++ -c main.cpp

IncidenceCube.o: IncidenceCube.cpp
	g++ -c IncidenceCube.cpp

Quasigroup.o: Quasigroup.cpp
	g++ -c Quasigroup.cpp

clean:
	rm -rf *.o program