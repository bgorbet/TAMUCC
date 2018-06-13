/*
Annie Gorbet
AOS Project2
Part 2

This is the client file for part 2.  It makes null remote calls
10000 times for 5 remote procedures ( no arguments, 1 argument,
2 arguments, 10 arguments, and a 400 byte array argument ).
It measures the clicks taken for each call using the clock() 
function, converts this to seconds, then takes the average.
 */

#include "rpctime.h"
#include <stdio.h>
#include <time.h>


void
add_prog_1(char *host)
{
	CLIENT *clnt;
	void  *result_1;
	char *nullremote1_1_arg;
	int  *result_2;
	int  nullremote2_1_arg;
	twoArgs  *result_3;
	twoArgs  nullremote3_1_arg;
	tenArgs  *result_4;
	tenArgs  nullremote4_1_arg;
	arrayArg  *result_5;
	arrayArg  nullremote5_1_arg;
	float sum1=0, sum2=0, sum3=0, sum4=0, sum5=0;
	float avg1, avg2, avg3, avg4, avg5;
	int i;

#ifndef	DEBUG
	clnt = clnt_create (host, ADD_PROG, ADD_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	for( i = 0; i < 10000; i++ ) {

		clock_t t1 = clock();
		result_1 = nullremote1_1((void*)&nullremote1_1_arg, clnt);
		t1 = clock() - t1;

		sum1 += (((float)t1)/CLOCKS_PER_SEC)*1000000;
	}

	avg1 = sum1/10000;

	printf( "avg1: %f\n", avg1 );

	for( i = 0; i < 10000; i++ ) {

		clock_t t2 = clock();
		result_2 = nullremote2_1(&nullremote2_1_arg, clnt);
		t2 = clock() - t2;

		sum2 += (((float)t2)/CLOCKS_PER_SEC)*1000000;
	}

	avg2 = sum2/10000;

	printf( "avg2: %f\n", avg2 );

	for( i = 0; i < 10000; i++ ) {
		
		clock_t t3 = clock();
		result_3 = nullremote3_1(&nullremote3_1_arg, clnt);
		t3 = clock() - t3;

		sum3 += (((float)t3)/CLOCKS_PER_SEC)*1000000;
	}

	avg3 = sum3/10000;

	printf( "avg3: %f\n", avg3 );

	for( i = 0; i < 10000; i++ ) {

		clock_t t4 = clock();
		result_4 = nullremote4_1(&nullremote4_1_arg, clnt);
		t4 = clock() - t4;

		sum4 += (((float)t4)/CLOCKS_PER_SEC)*1000000;
	}

	avg4 = sum4/10000;

	printf( "avg4: %f\n", avg4 );

	for( i = 0; i < 10000; i++ ) {

		clock_t t5 = clock();
		result_5 = nullremote5_1(&nullremote5_1_arg, clnt);
		t5 = clock() - t5;

		sum5 += (((float)t5)/CLOCKS_PER_SEC)*1000000;
	}
	
	avg5 = sum5/10000;

	printf( "avg5: %f\n", avg5 );

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	add_prog_1 (host);
exit (0);
}
