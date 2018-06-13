/*
Annie Gorbet
AOS Project 2
Part 2

This is the server for part 2.  It simply contains 5 procedures
that take none, 1, 2, 10, or 400 byte array arguments.  Nothing is
done, the arguments are immediately returned.
 */

#include "rpctime.h"

void *
nullremote1_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	return (void *) &result;
}

int *
nullremote2_1_svc(int *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */

	return &result;
}

twoArgs *
nullremote3_1_svc(twoArgs *argp, struct svc_req *rqstp)
{
	static twoArgs  result;

	/*
	 * insert server code here
	 */

	return &result;
}

tenArgs *
nullremote4_1_svc(tenArgs *argp, struct svc_req *rqstp)
{
	static tenArgs  result;

	/*
	 * insert server code here
	 */

	return &result;
}

arrayArg *
nullremote5_1_svc(arrayArg *argp, struct svc_req *rqstp)
{
	static arrayArg  result;

	/*
	 * insert server code here
	 */

	return &result;
}
