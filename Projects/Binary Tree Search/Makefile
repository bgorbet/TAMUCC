concord: concord.o stringutil.o WordRef.o
	g++ -g concord.o stringutil.o WordRef.o -o concord

concord.o: concord.cpp BTree.h
	g++ -c concord.cpp -o concord.o

stringutil.o: stringutil.cpp stringutil.h
	g++ -c stringutil.cpp -o stringutil.o

WordRef.o: WordRef.cpp WordRef.h
	g++ -c WordRef.cpp -o WordRef.o

clean:
	/bin/rm -f concord stringutil WordRef *.o

