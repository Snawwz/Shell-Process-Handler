/*************************************************************** 
  Team:     Team06
  Members:  Hagar, Bryce
            Ramirez, Ruben 
  File Name: parse.h
  Assignment number: Project 1 Part 1
  Notes: Read "readme.txt" for notes on project.
  
  This project was created by the sole efforts of the team members listed above. The team possesses a single Linux computer environment which was used for the entirety of the project for ease of compiling & debugging. Our team github repo will reflect that the vast majority of the content was pushed from the Ubuntu- Linux distro. 
***************************************************************/

#ifndef parse
    #include "structures.h"

//******* Function Prototypes *******//

// Initialize variables in struct shellParam //
void initStruct(shellParam *SP);

// Part 1 of project. Inside of Shell Loop // 
int shellLoop(shellParam *SP, int pringFlag, char *line);

// Formats an input string to get it ready to be tokenized/parsed //
char *reconditionInput(char *line);

// Check for valid input entry //
int checkInput(char *line);

// Parse input line into tokens //
void parseLine(shellParam *SP, char *line);

// Check for exit in user input //
int checkForExit(char *line);

// Print struct //
void printParams(shellParam *SP);

// Check Error Flag //
void checkFlag(int errorFlag, char *line, shellParam *SP);

// Garbage Collect //
void garbageCollect(shellParam *SP, char* line);


#endif









