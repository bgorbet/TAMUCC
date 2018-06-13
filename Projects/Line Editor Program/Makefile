



led: led.o stringutil.o
	g++ -g -I. led.o stringutil.o -o led

led.o: led.cpp ListType.h
	g++ -g -c -I. led.cpp 

stringutil.o: stringutil.cpp stringutil.h
	g++ -g -c -I. stringutil.cpp 

clean:
	/bin/rm -f led *.o 
