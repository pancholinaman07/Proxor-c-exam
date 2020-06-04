Start here to solve the gbitset task.

In this task, you will implement a set of small integers using bits to
indicate members of the set.  Only integers from 0 to MAX_BSET_SIZE - 1
(inclusive) can be elements of a set. MAX_BSET_SIZE is defined in
gbitset.c, and your code should work with different values of
MAX_BSET_SIZE.

Details: Modify and complete the file gbitset.c by implementing type
bset and functions bset_union(), bset_intersection(), bset_insert(),
bset_test() and bset_empty(). The comments in gbitset.c give detailed
specifications for each function.

The function main() will call these functions and perform a
preliminary test. main().

Example output:
----------------
gbitset has passed some simple tests.
----------------
  (Passing this test is necessary but 
   not sufficient for a high score.)

Your solution should reside entirely in gbitset.c.
You may not introduce additional files. After compiling gbitset.c, 
it will be run with no command-line arguments.


DEVELOPING IN A TERMINAL WINDOW
===============================

% make        -- Compile your program
% make run    -- Run your program
% make debug  -- debug your program
% make submit -- submit your program


ADDITIONAL INFORMATION
======================
You may not add new source files, you must change only gbitset.c.

Data of type bset should not be allocated on the heap.  bset should
not be a pointer type. Do not ever call malloc().  Your representation
of bset need not be space efficient.
