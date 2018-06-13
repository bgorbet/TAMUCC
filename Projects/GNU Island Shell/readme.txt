README

Contents:

guish.cpp = source code for the shell
guish.l = parser
Makefile

This shell supports basic commands such as:

progname [args]
Runs the program progname with the given, possibly optional, arguments.

exit
The exit internal command causes the shell to exit and print 
out the number of times each interrupt (Ctl C, Ctl \, Ctl Z) was detected.

hist
The hist history internal shell command will display the (up to) 10 most 
recent commands entered from the user.  

r n
The r n internal shell command will execute a command from the history list.  

Also supports I/O redirection in the following forms:

progname [args] > file.out
or > progname [args] file.out
or progname [args] file.out >
Write the standard output of progname to the file file.out.

progname [args] < file.in
or < progname [args] file.in
or progname [args] file.in <
Uses the contents of the file file.in as the standard input to program progname.

Also supports piping:

progname [args] | progname [args]

