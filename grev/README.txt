Start here to solve the grev task.

In this task, you will read a list of integers from the file
"numbers.txt" and write the same integers in reverse order
to the console  (stdout).

The total amount of integers allocated by the program
after main is called should be at most 4 times the 
number of integers in "numbers.txt".

Details: Modify and complete the file grev.c by implementing  
functions read_number() and completing main(). The comments in  
gfileio.c describe each function, and full specifications are as  
follows: 
 
int read_number(FILE *inf, long int *result)  
    read_number() reads a signed long int. The parameters are:
 - inf is an opened file.  The file contains signed decimal integers 
    and white space (including new lines). read_number skips any white 
    space, reads the next integer (delimited by white space or end of 
    file), stores the integer into the address given by result, and 
    returns 1. If no integer is found in the file, read_number() 
    returns 0, leaving the file open. 
 - result is the address of the signed long int that is read  
 
int main()  
    main() ignores any command-line arguments. main() reads integers
    from the file named "numbers.txt" and prints the numbers to stdout
    in reverse order.

You MUST complete the implementation of read_number() in 
grev.c according to the specifications above and in grev.c.

Important: free all allocated memory before your program 
exits. 


----------------- 
Example command:
----------------- 
grev
-----------------------------------
Example input: (in "numbers.txt"):
-----------------------------------
5 
10 
582 
328 
234 
409 
------------------------------------------- 
Example output: (to console, i.e. stdout):
-------------------------------------------
409  
234  
328  
582  
10  
5  
-------------------------------------------

Your solution should reside entirely in grev.c.
You may not introduce additional files. After compiling grev.c, 
it will be run without command-line arguments.

Important: free all allocated memory before your program exits.


DEVELOPING IN A TERMINAL WINDOW
===============================

% make        -- Compile your program
% make run    -- Run your program
% make debug  -- debug your program
% make submit -- submit your program


ADDITIONAL INFORMATION
======================
You may not add new source files, you must change only grev.c.

You may assume signed long integers and arrays do not overflow 
(except for arrays that your own code allocates).

You may assume input always has a valid integers, each one followed by
a newline character.

