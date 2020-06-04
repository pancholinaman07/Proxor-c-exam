Start here to solve the cmath task.

In this task, you will extend the command interpreter
framework by adding a Math subsystem with two 
commands: Add and Mult. 

Details: ../cmcmd contains sources and some documentation
for the command interpreter. You can run make in that
directory to build the command interpreter. However,
for this task you should work in this directory (named
cmath). A partially completed solution is in aduc.c here
for you to alter. Also, Makefile is provided to compile 
aduc.c and link it with the other command interpreter 
sources. The executable is named cmcmd.

You should modify ONLY aduc.c in this directory. No other
files will be used to grade your work.

The Add command should add 2 signed integers, print 
"[Math:Add]" on the first line and the sum on the next line.

The Mult command should multiply 2 signed integers, print 
"[Math:Mult]" on the first line and their product on the
next line.

The Add command should be implemented by the function
cmd_add(). See the comments for this already declared 
function in aduc.c.


EXAMPLE BEHAVIOR [WITH COMMENTS IN BRACKETS]
============================================
CMD> Math        [enter Math subsystem]
Math> Add 2 3    [add 2 numbers]
[Math:Add]
5
Math> Mult 2 3   [multiply 2 numbers]
[Math:Mult] 
6
Math> 


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

Assume that arithmetic overflow will not occur in Add
and Mult.

For full credit, the output must appear exactly as shown
in the example above.

Some DOCUMENTATION for the command interpreter and how
to extend it is provided in ../cmcmd/README.txt. The
complete source code for the command interpreter is
ins ../cmcmd/.
