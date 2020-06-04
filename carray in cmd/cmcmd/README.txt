cmcmd -- an extensible command processor

Input is sent character-by-character to cmdb_scan(), which copies
input into cmdbuf, indexed by cmdndx until a newline is encountered.

When newline is seen, cmdbuf is copied to lstbuf (last command
buffer) and cmdb_proc() is called to process the input line.

Both backpace (^H) and DEL (delete key) remove the last character
of the command line while typing.

There is special processing of arrow keys, which send a sequence
of characters beginning with ESC (character '\033'). Up arrow
retrieves the saved last command and allows editing and entering
the command. Left arrow is treated as a backspace.

In cmdb_proc(), everything after the first space is copied to 
argstr_buf and the cmdbuf is truncated after the command. 
The command is searched by calling cmdid_search().

Commands are stored in cmd_tble, an array of structs with:
         cmdstr - the command
         subs - the subsystem
         parms - parameters description used by sscanf
         cmddescr - description of the command
         parmdesc - description of the parameters to the command
         function - the address of the command implementation

When a commnand is found, the parms field from the table is
used with sscanf to pull parameter values from argstr_buf. 
Parameters must be either long, unsigned long, or doubles. A
special case is that the parameter may be a single string, in
which case sscanf is not called: the string is already in 
argstr_buf.

After parsing the command, the command is invoked by calling
the function pointer stored in the cmd_tble.

Some special case commands include:
     macro  - the characters after "macro" are stored in a 
                macro buffer
     macros - show the stored macro, if any
     run    - the string stored in the macro buffer is evaluated
                as a command
     quit   - quit the program
     help   - list commands
     exit   - leave a subsystem. Commands can be either global or
                associated with a subsystem. You enter a subsystem
                by typing the subsystem name, as if it is a command.
                Once in the subsystem, new commands for that 
                subsystem become available and are described when 
                you type help. When you type exit, you leave the
                subsystem and then only global commands (including
                typing another subsystem name) are available.

The command interpreter is extensible. You add new commands with
cmdb_add_cmd(), which has the following parameters:
  name -- the name of the command
  subs -- the subsystem containing the command, if any, 
           otherwise "Global". Subsystems themselves are indicated
           by setting subs to the empty string "".
  parms - format string to parse parameters. %s, %g, %c, %ld and %lu 
           are supported. For no parms or for subsystems, use "".
  desc -- description of the command printed by Help
  pdesc - description of the parameters or empty string "".
  func -- implementation of the command. func will be called with no
           parameters when the command is invoked. parms[] contains
           numeric parameters (if any), and argstr_buf contains a
           string parameter. This implementation supports either one
           string parameter or up to 8 long and double parameters.
           For a subsystem, func should be NULL. When func is called,
           access numeric parameters with the macros:
                  CHARPARM(n) for parameters parsed with %c
                  LONGPARM(n) for parameters parsed with %ld
                  ULONGPARM(n) for parameters parsed with %lu
                  DOUBLEPARM(n) parameters parsed with %g
The command returns 1 if successful, 0 if the command table is full.

