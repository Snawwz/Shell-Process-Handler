PROGRAM EXECUTION:
    (1) make
    (2) ./myshell or ./myshell -Debug

**NOTE: Project was copied from a private school git-hub repo, and unforunately, individual commits could not be copied over.

PROGRAM FLOW: 
	Part1: Parse Input
			a.) Displays a propmt on stdout.
			b.) Accepts a command as a string from user.
			c.) Parses the input into tokens.
			d.) Stores the tokens into a structure.
			e.) The contents of the structure are printed whenever myshell is started with the debug option, '-Debug'.
	Part2: Distributed Computing
			a.) The functionality of this shell program is different from that of a production shell such as a c-shell or a bourne shell found in many operating systems because the shell will launch several instances of a program. 
			b.) argumentVector[0]: this element will define the name of a program that must be executed
			argumentVector[1]: this element will define a counter that specifies the number of times the program must be launched as a spearate process/instance
			c.) All other elements in the argument vector are passed to the specified program.
			d.) Upon interpreting the values in the argument vector, myshell launches k instances of the specified program using fork() where k is th enumber specified in argumentVector[1]. A new argument vector is produced for each process. In order for the processes to work cooperatively on solving a proble myshell generates a separate index for each process and passes it to the process in the new argument vector. The specified program will use this index to apply a divide and conquor strategy on the data for solving a problem. 

			Minimally, a user program will need to accept the following arguments in main. 
				(1) argument[1] will be the number of processes user wishes to execute.
				(2) argument[2] will be the updated index number that the specified program accepts.
			

ORGANIZATION NOTES:
    (1) All part 1 functions go into files: parse.c/parse.h
    (2) All part 2 functions go into files: compute.c/compute.h
    (3) All '#define' values are stored in structures.h
    (4) All '#include' libraries are stored in structures.h 

TEST PROGRAMS:
    (1) testInput
        'testInput.txt' stores an arbitrary integer value that can be used in conjunction with
        the program 'testInput' to verify that myshell's inputRedirect works.
    (2) prime
    (3) testme

OUTPUT NOTES: 
    (1) Program will not accept 'testme' or 'prime' without './' preceeding.
    (2) Program will accept delimiters with any amount of spaces/tabs on each side of it. 
    (3) Program will accept user input if there is a redirect delimiter that is not proceeded by a char.
            example: >>> token token >
                Note: outputRedirect == NULL
            example: >>> token token >results.txt >findings.txt
                Note: outputRedirect == findings.txt
    (4) Program will reject consecutive repeated delimiters & reprompt user for input
            example: >>> token > < input
    (5) Program can execute programs with or without an indexValue
            example:          >>> ./prime 2 0 10
                reformats to: >>> ./prime 2 0 10
            example:          >>> ./prime 2 10
                reformats to: >>> ./prime 2 0 10
            example:          >>> ./prime 2 x 10
                reformats to: >>> ./prime 2 0 10
                Note: where 'x' == (any_length_string || integer)
                
TO-DO LIST: 
    NULL

VERIFY COMPLETED:
    NULL
    
COMPLETED: 
    (1-0) Ask professor if [-Debug] is supposed to be stored in the argumentVector[]. (It is not)
    (1-1) Function "parseLine" will need to detect which delimiter is which & store the following string in the appropriate inputRedirect or outputRedirect. ie how do we know the strtok() function read a "<" vs a ">". 
    (1-2) Function "parseLine" will need to filter out '\t' & replace trailing ' ' & '\n' with '\0' from user input.
    (1-3) Check for 'exit' in user input
    (1-4) Don't allow for spaces (ie ' ') to follow after a redirect (ie '<' or '>').
    (1-6) Add -Debug so that struct is only printed when the -Debug option is selected.
    (1-7) Iterate through function "shellLoop" continuously until the user is finished.
    (2-0) Add input/output redirect
    (2-1) Verify program will execute programs with no additional arguments.
    (2-2) Verify how professor wants us to run normal shell programs such as 'ls'.
            ie Does he want us to run it as 'ls' or 'ls 1'

MISC. NOTES: 
    A Shell does 3 things during it's loop
        (1) Read: Read the command from standard input.
        (2) Parse: Separate the command string into a program and arguments.
        (3) Execute: Run the parsed command.

    Ways to get unexpected output:
        (a) NULL


