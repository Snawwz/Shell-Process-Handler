/*************************************************************** 
  Team:     Team06
  Members:  Hagar, Bryce
	          Ramirez, Ruben 
  File Name: parse.c
  Assignment number: Project 1 Part 1
  Notes: Read "readme.txt" for notes on project.
  
  This project was created by the sole efforts of the team members listed above. The team possesses a single Linux computer environment which was used for the entirety of the project for ease of compiling & debugging. Our team github repo will reflect that the vast majority of the content was pushed from the Ubuntu- Linux distro. 
***************************************************************/
#include "parse.h"

// initializes variables in struct shellParam //
void initStruct(shellParam *SP){
  int i;
  SP->inputRedirect = NULL;
  SP->outputRedirect = NULL;
  SP->argumentCount = 0;
  for(i=0;i<MAXARGS;i++){
    SP->argumentVector[i]=NULL;
  }
}


// Part 1 of project. Inside of Shell Loop // 
int shellLoop(shellParam *SP, int printFlag, char *line){

  // Prints Prompt for user //
  printf(">>> ");

  // Reads user input in 'line' //
  fgets(line,STRNG_BUFSIZE,stdin);

  // Prepares line for 'parseLine()' //
  line = reconditionInput(line);

  // Checks for invalid input //
  //if(checkInput(line) == INVALID_INPUT){
    //return INVALID_INPUT;
  //}

  // Check to see if 'exit' was entered //
  if(checkForExit(line) == EXIT_LOOP){
    return EXIT_LOOP;
  }

  // Call 'parseLine' to tokenize input & store in struct //
  parseLine(SP, line);

  // Print Paramters if '-Debug' flag set //
  printFlag == 1 ? printParams(SP):NULL;
  
  return 0;
}


// Formats an input string to get it ready to be tokenized/parsed //
char *reconditionInput(char *line){
  int i,indexL=0,indexC=0, flag = 0;
  char *copy = strdup(line);

  // Replace last new line character: '\n' with \0' //
  if(*(line +strlen(line)-1) == '\n'){
      *(line +strlen(line)-1) = '\0';
      *(copy +strlen(copy)-1) = '\0';
   }
  // replace '\t' in line with ' ' //
      for(i=0; i<strlen(line);i++){
        if(*(line+i) == '\t'){
          *(line+i) = ' ';
          *(copy+i) = ' ';
        }
      }

  // Remove repeated spaces //
  while(1){
    if (*(copy+indexC) == '\0'){
      *(line+indexL) = '\0';
      break;
    }
    else if (*(copy+indexC) != ' '){
      *(line+indexL) = *(copy+indexC);
      flag = 0;
      indexC++;
      indexL++;
    }
    else if(*(copy+indexC) == ' ' && flag == 0){
      *(line+indexL) = *(copy+indexC);
      flag = 1;
      indexC++;
      indexL++;
    }
    else{
      indexC++;
    }
  }
  
  free(copy);
  return line;
}


// Check for valid input entry //
int checkInput(char *line){
  int i;
  char *a = line;

  // Check for repeated redirect delimiters //
  for(i=0; i<strlen(line);i++){
    if(a[i] == '<' || a[i] == '>'){
      if(a[i+1]=='<' || a[i+1]=='>'|| a[i+2]=='<' || a[i+2]=='>'){
        return INVALID_INPUT;
      }
    }
  }
  return 0;
}


// Parses input line into tokens //
void parseLine(shellParam *SP, char *line){

  char *copy = strdup(line);
  char *token = strtok(line, TOK_DELIM);
  int delim_index;
  char key = NULL;

  // Tokenize input String //
  while (token != NULL){
    delim_index = token != NULL ? token-copy-1:strlen(copy)-1;

    if(key == '<' || copy[delim_index] == '<' || copy[delim_index-1] == '<'){
      SP->inputRedirect = token;
      }
    else if(key == '>' || copy[delim_index] == '>' || copy[delim_index-1] == '>'){
      SP->outputRedirect = token;
      }
    else{
        SP->argumentVector[SP->argumentCount] = token;
        SP->argumentCount++;      
    }
    key = copy[token-line+strlen(token)];
    token = strtok(NULL, TOK_DELIM);

    // Returns if user has reached the token limit //
    if (SP->argumentCount >= MAXARGS){
      printf("\nOnly first [%d] arguments accepted.\n", MAXARGS);
      free(copy);
      SP->argumentVector[SP->argumentCount] = NULL;
      return; 
    }
  }
  free(copy);
  SP->argumentVector[SP->argumentCount] = NULL; 
}


// Checks for exit in user input //
int checkForExit(char *line){

  if(strcmp(line,"exit")==0){
    return EXIT_LOOP;
  }
  return 0;
}


// Prints struct //
void printParams(shellParam *SP){
  int i;
  char text[5] = "NULL";
  printf("\ninputRedirect:      [%s]", SP->inputRedirect != NULL ? SP->inputRedirect:text);
  printf("\noutputRedirect:     [%s]", SP->outputRedirect != NULL ? SP->outputRedirect:text);
  printf("\nArgumentCount:      [%d]", SP->argumentCount);
  for(i=0;i<SP->argumentCount;i++){
    if(i<=9){
      printf("\nArgumentVector[0%d]: [%s]", i, SP->argumentVector[i]);
    }
    else{
      printf("\nArgumentVector[%d]: [%s]", i, SP->argumentVector[i]);
    }
  }
  printf("\n");
}

// Check for Error Flag //
void checkFlag(int errorFlag, char *line, shellParam *SP){
  // Check for exit //
  if (errorFlag == EXIT_LOOP){
    printf("\nterminating...");
    printf("\nprogram terminated.\n\n");
    garbageCollect(SP,line);
    }

  // Check for invalid input //
  else if(errorFlag == INVALID_INPUT){
    printf("\ninvalid input...");
    printf("\nreinitialize prompt.\n");
    garbageCollect(SP,line);
  }
}


// Garbage Collect //
void garbageCollect(shellParam *SP, char* line){
  free(line);
  free(SP);
}
























