.SUFFIXES: .h .c .cpp .l .o

CC = gcc -I.
CPP = g++ -I.-Wall -Wno-deprecated

all: findcc

findcc: findcc.o Grid.o
	$(CPP) findcc.o Grid.o -o findcc

findcc.o: findcc.cpp
	$(CPP) -c findcc.cpp -o findcc.o

Grid.o: Grid.cpp Grid.h
	$(CPP) -c Grid.cpp -o Grid.o

clean:
	/bin/rm -f *.o *~ core* findcc
