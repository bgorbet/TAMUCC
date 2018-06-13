Advanced Operating Systems Project 1
Annie Gorbet

Part 2:

Contents:

aosproj1_1.c		source file
aosproj1_1			executable
Makefile				the makefile
aosproj1_1.pdf	jumpshot screenshot
aosproj1_1.xlxs	Excel file 
README.txt			readme file

Explanation:

Given a small two node distributed system, assume that the time needed to send 
an n-byte message can be modeled by the linear equation t = a + n/b. The 
parameter "a" is the message latency. Latency is the time it takes for the first 
bit of the message to arrive at the receiving process after it was sent by the 
sending process. The parameter "n" is the size of the message in bytes. The 
parameter "b" is the bandwidth of the network (typically in bits/second).

Write a C or C++ program using MPI to send a message (repeatedly) between two 
processes "A" and "B". Process "A" will record the current time and send a 
message to process "B". After process "B" receives the message, it immediately 
sends it back to process "A". Process "A" will receive the message and then 
records the current time. The elapsed time divided by two is the average message 
passing time for a message of length "n". (The message is sent and then 
immediately received similar to two people playing a game of ping-pong or table 
tennis.)

Details:

The name of your program must be aosproj1_1.c or aosproj1_1.cpp.
The name of your executable must be aosproj1_1.
The screenshot from jumpshot should be saved as aosproj1_1.pdf (Show this for 
only 1 sample size).
Vary the message size between 0 and 1 MB. (Consider atleast 10 different message 
sizes)
The messages should be sent more than once. It is suggested for a fixed message 
size that you repeat the send and receive at least 10 times to flush out any 
caching effects. Finally compute the average time taken for a given message 
size.
Record the data as a table and create a plot of time vs message size using Excel 
or any other spreadsheet program. Compute the values of "a" and "b" from the 
obtained plot. This can also be done using tools available in your spreadsheet 
program. Name this file as aosproj1_1.xlsx (or any other spreadsheet program 
extension)			

I used an array of integers as my message.  I varied the number of integers
in the array being sent between 0 and 250 integers for a total of 50 different 
messages (with 5 integer intervals) whose sizes varied between 0 and 1 MB. For 
each message size, I sent the message 20 times and calculated the average.  
Initially, I made a mistake by not calculating the average, so the times being 
used were totals and not averages.  This resulted in a scatter plot that was all 
over the place and didn't seem to show any linear relationship.  Once I finally 
caught this error in my code and put in the corrected data, the scatter plot 
cleaned up very well and the data points formed a nice nearly straight line.  I
added a trendline and used the tools available in Excel to display a linear
equation for the trendline (y=2E-7x+7E-6, where y is t and x is n).  From ths 
equation I determined that the latency is 0.000007 seconds and by setting 2E-7n
equal to n/b I was able to calculate that the bandwidth is 5,000,000 bits/s.

Part 3:

Write a C or C++ program using MPI to play a rock-paper-scissors tournament. 
The created processes should play the game in pairs until one processes emerges 
as the winner. The processes participate in contests based on their rank. In 
the first round, the even-numbered nodes each compete with the one-greater odd 
node (0 and 1, 2 and 3, etc.) The winners of these contests compete in pairs, 
left-to-right, until a final winner emerges victorious. For example if I have 8 
processes competing:

    The first round competition would be between 0 - 1, 2 - 3, 4 - 5, and 6 - 7
    If 0, 3, 4, 6 win the first round, then the secound round competition would 
			be between 0 - 3 and 4 - 6
    If 0 and 6 win the secound round, then the last round competion would be 
			between 0 - 6

The competing processes before the start of first round should exchange random 
choices of rock, paper or scissors. The rules of the game are: Rock breaks 
scissors, scissors cuts paper, and paper wraps rock. According to these rules 
the winner can be decided. In case of a tie, simply run the contest until there 
is a winner. Complete each round, and then start a new round with the winners 
from the previous round. For the purpose of simplification, you may assume the 
number of processes to be a power of two (or power of two plus one).

Announce the winner of each competition, and the winner of the whole tournament. 
Here is a sample run:

$mpirun -np 8 aosproj1_3
Process 0 wins over process 1
Process 7 wins over process 6
Process 3 wins over process 2
Process 4 wins over process 5
Process 0 wins over process 3
Process 4 wins over process 7
Process 4 wins over process 0
Process 4 wins the rock, paper, scissors tournament
$

My solution was to have one process (process 0) be a referee process and keep 
track of the winners or each round.  In my program, for the first round the 
even-numbered nodes each compete with the one-greater odd node (0 and 1, 2 and 
3, etc.).  The processes know their opponent already based on their rank (at the 
beginning of subsequent rounds they must receive their opponent from the 
referee).  They then randomly generate a number (1, 2, or 3) and send their 
opponent their number, and then wait on their opponent's number.  When they 
receive their opponent's they compare (1=rock, 2=paper, 3=scissors).  If they 
have won, they send their rank to the referee process. If they have lost, they 
exit.  For simplicity, a tie goes to the process with the higher rank. 
Then, the referee process receives all of the winners and sorts them 
based on their rank. The referee can then send out the opponents for the next 
round. The process repeats until there is only one process left.  The ouput
is as above.  ***I use functions from math.h in my code that require a certain 
flag and linker, so be sure to use the makefile to compile.***
  