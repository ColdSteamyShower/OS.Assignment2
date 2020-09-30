/*
Michael Kulinich
kulinich@chapman.edu

Ayden Best
bbest@chapman.edu

CPSC 380-01
Assignment 2
*/

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The Maximum length command */
extern int errno;

// precondition: arguments has valid size limit
int processToArgs(char* commandLine, char** arguments);
// postcondition: 'arguments' becomes an array of char arrays containing each word from 'commandLine'

int main(void)
{
  ////////////////
  // Initialize //
  ////////////////

  // full command line argument
  char str[MAX_LINE];

  // execution arguments
  char *args[MAX_LINE/2 + 1];

  // flag to determine when to exit
  int should_run = 1;

  // number of arguments in *args[]
  int ctr;

  // flag used to determine if user included an '&'
  int flag;


  ///////////////
  // Main Loop //
  ///////////////
  
  while (should_run) {
    // set flag as 0 (aka no '&') at the start
    flag = 0;
    
    // prompt user for a shell argument
    printf("osh> ");
    fflush(stdout);

    // retrieve command line and put into the char[] str
    if (fgets(str, MAX_LINE, stdin) == NULL)
      fprintf(stderr,"Failed to read command line");

    // for testing
    printf("executing argument: %s", str);
   

    // process command line input into arguments
    ctr = processToArgs(str, args);


    // checks to see if user entered an '&' to
    // determine whether or not the parent process is to wait for child to exit
    if ( ctr > 1 && args[ctr - 2][0] == '&' ){
      flag = 1;
      args[ctr - 2] = NULL;
    }
 
    // skip NULL arguments
    if (args[0] == NULL)
      continue;

    // exit prgram if they meant to
    if (args[0][0] == 'e' && args[0][1] == 'x' && args[0][2] == 'i' && args[0][3] == 't'){
      break;
    }

    ////////////////////////////////
    // Process Fork and Execution //
    ////////////////////////////////

    // fork the process and make an identifier for that child process
    pid_t pid = fork();

    if (pid < 0) { // fork() returns < 0 if error occurred
      fprintf(stderr, "Fork Failed\n");
      return 1;
    }
    else if (pid == 0) { // pid = 0 within the child process
      if (execvp(args[0], args) < 0) 
        printf("Command Execution Failed: unknown command '%s'\n", args[0]);
    }
    else { // parent process
      // parent will wait for the child to complete if no '&' is included
      if (flag != 1){
	pid = wait(NULL);
      }
      // parent doesn't wait for the child to complete because flag == 1
      
      
      printf("\n\nChild Complete\n");
    }
  }

  return 0;
}



// char* commandLine is an array of chars to be read for argmuents
// char** arguments is an array of arguments in the form of nested char arrays
// returns the number of arguments
int processToArgs(char* commandLine, char** arguments) {
  // initialize
  int i = 0; // current char
  int j = 0; // index of first char of an argument
  int argNum = 0; // index of argument within array of arguments

  // keep checking next char in commandLine until we see a char that signals end of line
  // In our case, \0 will come after the \n at the end of the command line input
  ///// [changed this to a while loop to avoid running the last if statement]
  ///// [also now we don't have to declare the iteration ints in global scope!]
  while (commandLine[i] != '\0') {
    // if we are reading space or a new-line(end of the command line)
    if (commandLine[i] == ' ' || commandLine[i] == '\n'){
      // if we've actually been reading some chars (not a double space, ignore spaces at the start)
      if (i != j) {
        // allocate an array of chars of size i-j
        arguments[argNum] = (char *) malloc((i - j) * sizeof(char));

        // fill up the argument array with the chars
        for (int k = 0; k < (i - j); k++){
      	   arguments[argNum][k] = commandLine[j + k];
        }
        // completed this argument, on to the next one
        argNum++;
        j = i;

      // if we havent read anything new, its some other whitespace so we'll ignore
      } else {
        i++;
        j++;
      }

    // the char we're at is in the middle of a word, keep reading
    } else {
      i++;
    }
  }
  // the last argument with content will be an end of file char to signal to stop reading arguments
  arguments[argNum] = '\0';
  return argNum+1;
}
