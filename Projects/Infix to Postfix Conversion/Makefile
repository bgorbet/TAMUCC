
i2p: i2p.o stringutil.o
	g++ -g -I. i2p.o stringutil.o -o i2p

i2p.o: i2p.cpp Stack.h 
	g++ -g -c -I. i2p.cpp 
	
stringutil.o: stringutil.cpp stringutil.h
	g++ -g -c -I. stringutil.cpp 

clean:
	/bin/rm -f i2p *.o
