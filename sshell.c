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

int processToArgs(char* commandLine, char** arguments);

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

  // number of arguments in *args[]. Do we need this? can we just check the size of args[]?
  int ctr;



  ///////////////
  // Main Loop //
  ///////////////

  while (should_run) {

    // prompt user for a shell argument
    printf("osh>");
    fflush(stdout);

    // retrieve command line and put into the char[] str // check for error !!!
    if (fgets(str, MAX_LINE, stdin) == NULL)
      fprintf(stderr,"Failed to read command line");

    // for testing
    printf(" executing argument: '%s'", str);
    //


    // process command line input into arguments
    ctr = processToArgs(str, args);


    /*  TESING IF IT WORKED */

    for (int i = 0; i < ctr; i++){
      printf("you entered:args[%d] : %s \n", i, args[i]);
    }

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
      fprintf(stderr, "Fork Failed");
      return 1;
    }
    else if (pid == 0) { // pid = 0 within the child process
      execvp(args[0], args);
    }
    else { // parent process
      // parent will wait for the child to complete
      pid = wait(NULL);
      printf("Child Complete\n");
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
    printf("Reading char: % \n", commandLine[i]);
    // if we are reading space or a new-line(end of the command line)
    if (commandLine[i] == ' ' || commandLine[i] == '\n'){
      printf("    we reached some white space!\n");
      // if we've actually been reading some chars (not a double space, ignore spaces at the start)
      if (i != j) {
        printf("    we've read some chars! let's set argmuent ");
        // allocate an array of chars of size i-j
        arguments[argNum] = (char *) malloc((i - j) * sizeof(char));

        // fill up the argument array with the chars
        printf("%d to ", argNum);
        for (int k = 0; k < (i - j); k++){
          printf("%c",commandLine[j+k]);
      	   arguments[argNum][k] = commandLine[j + k];
        }
        printf("\n");
        // completed this argument, on to the next one
        argNum++;
        j = i;

      // if we havent read anything new, its some other whitespace so we'll ignore
      } else {
        printf("    but we haven't read any chars... skip!\n");
        i++;
        j++;
      }

    // the char we're at is in the middle of a word, keep reading
    } else {
      printf("    its not white space! keep reading...\n");
      i++;
    }
  }
  // the last argument with content will be an end of file char to signal to stop reading arguments
  printf("Read an ending character. Setting last arg to EOF\n");
  arguments[argNum] = '\0';
  return argNum+1;
}
