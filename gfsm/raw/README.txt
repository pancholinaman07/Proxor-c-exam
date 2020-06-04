Start here to solve the gfsm task.

In this task, you will implement a finite state machine
that parses signed decimal integers. There are four states:
START, INT, FRAC and END, and transitions are shown in the
diagram below (please view this with a fixed-width font).
The labels on the arrows are input characters, e.g. if you
are in the START state and the next input is a '-' character,
or a <digit>, which is any digit from '0' through '9', you
would transition to the INT state.


    +-------+
    | START |----------+
    +-------+-----+    |
        |  ^      |    |
        |  |  <sp>|    |
        |  +------+    |
        |              |
        |'+','-',      |
        |<digit>       |
        V              |
    +-------+          |'.'
 +--|  INT  |-------+  |
 |  +-------+       |  |
 |      |  ^        |  |
 |OTHER |  | <digit>|  |
 |      |  +--------+  |
 |      |              |
 |      |'.'           |
 |      |              |
 |      V              |
 |  +-------+<---------+
 |  | FRAC  |-------+
 |  +-------+       |
 |      |  ^        |
 |      |  | <digit>|
 |      |  +--------+
 |      |
 |      |OTHER
 |      |
 |      V
 |  +-------+
 +->|  END  |-----+
    +-------+     |
        ^         |
        |    <any>|
        +---------+

In addition, update variables sign, output, and significance
as follows: 
   - sign is 1.0 but changes to -1.0 if '-' is parsed.
   - In the INT and FRAC states, output (initially zero) 
     accumulates the value parsed so far, e.g. if the 
     input is '-', '1', '2', then output should have the 
     value -12.0. If the next two inputs are '.', '3', 
     then output will become -12.3.
   - significance denotes the significance of the next digit in
     the FRAC state. It is initialized to 0.1, and after the
     first digit after the decimal point is parsed, significance
     is changed to 0.01, etc.
     
Details: Modify and complete the file gfsm.c by implementing
function fsm_accept(). The comments in gfsm.c give detailed 
specifications for each function.


Example command:
-----------------
gfsm

Example output:
----------------
gfsm has passed some simple tests
----------------
  (Passing this test is necessary but 
   not sufficient for a high score.)

Your solution should reside entirely in gfsm.c.
You may not introduce additional files. After compiling gfsm.c, 
it will be run without command-line arguments.


DEVELOPING IN A TERMINAL WINDOW
===============================

% make        -- Compile your program
% make run    -- Run your program
% make debug  -- debug your program
% make submit -- submit your program


ADDITIONAL INFORMATION
======================
You may not add new source files, you must change only
gfsm.c.

You may assume integers and arrays do not overflow.

The correct value of output after parsing '+', ' ' or 
'-', ' ' or '.', ' ' is zero (0), as indicated by the 
state transition diagram.

You may assume input always has a valid number (with
possibly leading blanks), followed by any string, as
indicated by the state transition diagram.
