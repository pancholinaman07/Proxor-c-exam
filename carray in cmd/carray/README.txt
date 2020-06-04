Start here to solve the carray task.

In this task, you will extend the command interpreter
framework by adding an Array subsystem with two
commands: Save and Get.

Details: ../cmcmd contains sources and some documentation
for the command interpreter. You can run make in that
directory to build the command interpreter. However,
for this task you should work in this directory (named
carray). A partially completed solution is in aduc.c here
for you to alter. Also, Makefile is provided to compile
aduc.c and link it with the other command interpreter
sources. The executable is named cmcmd.

You should modify ONLY aduc.c in this directory. No other
files will be used to grade your work.

The Save command should take 2 signed integers, an index
and a value. Print "[Array:Save]" on the first line. If
the index is between 0 and 99 inclusive, print the index
and value separated by one space on the next line. If the
index is not in range, print "Out of range: " followed by
the index.

The Get command takes one integer index value and gets
the corresponding value from the array. Print
"[Array:Get]" on the first line. If the index is between
0 and 99 inclusive, print the index and value separated
by one space on the next line. If the index is not in
range, print "Out of range: " followed by the index.

The values should be stored in an array of long int
named array.

The Save command should be implemented by the function
cmd_save(). See the comments for this already declared
function in aduc.c.


EXAMPLE BEHAVIOR [WITH COMMENTS IN BRACKETS]
============================================
CMD> Array       [enter Array subsystem]
Array> Save 2 3    [stores 3 at array index 2]
[Array:Save]
2 3
Array> Save 200 3   [first argument (index) is too big, print error message]
[Array:Save]
Out of range: 200
Array> Get 2
[Array:Get] 
2 3
Array>


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

Some DOCUMENTATION for the command interpreter and how
to extend it is provided in ../cmcmd/README.txt. The
complete source code for the command interpreter is
ins ../cmcmd/.
