Start here to solve the ccvt task.

In this task, you will extend the command interpreter
framework by adding a Cvt (for "Convert") command
that converts between signed decimal, binary and 
hexadecimal number formats. Part of the solution is
implementing the function hex_to_int().

Details: ../cmcmd contains sources and some documentation
for the command interpreter. You can run make in that
directory to build the command interpreter. However,
for this task you should work in this directory (named
ccvt). A partially completed solution is in aduc.c, here
for you to alter. Also, Makefile is provided to compile 
aduc.c and link it with the other command interpreter 
sources. The executable is named cmcmd.

You should modify ONLY aduc.c in this directory. No other
files will be used to grade your work.

Begin by implementing hex_to_int() as described in
comments in aduc.c. You are not required to use this
function, but it must be implemented correctly for
full credit.

The Cvt command should take a single string argument
which can be any of the forms:
    "-1456" or "1456" for a signed decimal integer
    "0b0010101101" for an unsigned binary integer, or
    "0xab105ff" for an unsigned hexadecimal integer.
The command should print "[Convert]" on the first line. 
On the next line print all three forms of the integer:
decimal, binary, and hexadecimal in that order
separated by a single space character.

The Cvt command must be implemented by the function
cmd_cvt(). See the comments for this already declared 
function in aduc.c. You will probably find your 
implementation of hex_to_int() to be useful.

Note that binary and hexadecimal formats are unsigned, 
even though they represent twos-complement signed
integers.

EXAMPLE BEHAVIOR
================
CMD> Cvt 0b11010
[Convert] 
26 0b11010 0x1a
CMD> Cvt -15217
[Convert]
-15217 0b1111111111111111111111111111111111111111111111111100010010001111 0xffffffffffffc48f


DEVELOPING IN A TERMINAL WINDOW
===============================

% make        -- Compile your program
% make run    -- Run your program
% make debug  -- debug your program
% make submit -- submit your program


ADDITIONAL INFORMATION
======================
You may not add new source files, you must change only
aduc.c in this directory.

Modifications/extensions to ../cmcmd will be REMOVED
when Proxor tests your solution.

Do NOT make changes to aduc.c that are not in these
requirements.

Do NOT print debugging information or any extra text.

For full credit, the output must appear exactly as shown
in the example above.

You can assume:
    hex digits 'a' through 'f' are lower case
    signed integers can be represented by long int 
    unsigned integers can be represented by unsigned long int
    The Cvt command output is undefined if a valid integer
        is not typed or if the integer value does not fit into
        a long int or unsigned long int.

Some DOCUMENTATION for the command interpreter and how
to extend it is provided in ../cmcmd/README.txt. The
complete source code for the command interpreter is
ins ../cmcmd/. The Cvt command should be a global command.
