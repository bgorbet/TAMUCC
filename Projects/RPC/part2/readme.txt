CONTENTS:

rpctime_xdr.c  // XDR file
rpctime_svc.c  // server stub
rpctime_server.c // server source code
rpctime_clnt.c // client stub
rpctime_client.c // client source code
rpctime.xlsx  // Excel file with measurement data
rpctime.x  // IDL file
rpctime.h  // header file
makefile  // make file

Part 2:

Write a C/C++ program using RPC.

Measure the timing performance of
1. A null remote call with zero arguments and zero results.
2. A null remote call with 1 arguments and 1 result.
3. A null remote call with 2 arguments and 2 results.
4. A null remote call with 10 arguments and 10 results.
5. A null remote call with a 400 byte array as argument and a 400 byte array as 
result.
6. A null remote call is where the remote procedure does not do any work, and 
the results are returned immediately.
7. Test your program with RPC server and RPC client existing on the same machine.
8. Test your program with RPC server and RPC client existing on different 
machines. (penguin.tamucc.edu and clst.tamucc.edu)
9. To get a good timing measurement perfom the calls several times (e.g. 1000 
or 10,000 calls or even more).
10. Store the data in a excel file named rpctime.xlsx.

I called each remote procedure 10,000 times in a loop.  I ran the client program
10 times on a local machine (penguin) and 10 time on two machines ( penguin
and clst ).  The data for those runs are in the Excel file.  Strangely, the
calls took longer on the local machine.
