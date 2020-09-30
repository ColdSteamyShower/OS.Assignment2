#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#define MAX_LINE 80 /* The Maximum length command */
extern int errno;

int main(void)
{
  /*
  //require user to execute file correctly by using only 3 arguments: filecpy <input file> <output file>
  if (argc != 3) {
    printf("Error: %s <input file> <output file> \n", argv[0]);
    return 0;

  }
  printf("Given Input file: %s\nOutput file: %s\n", argv[1], argv[2]);
  */
  
  char *args[MAX_LINE/2 + 1]; /* command line arguments */
  int should_run = 1; /* flag to determine when to exit program */
  char str[MAX_LINE]; /* Full command line argument */
  //char word[MAX_LINE/2 + 1]; /* each word inside of str that will be put into args[i] */
  int i, j, ctr;
  printf("osh>");
  fflush(stdout);
  fgets(str, MAX_LINE, stdin); /* gets in the command line prompt from user*/  // check for error !!! 

  printf("%s", str);
  
  j = 0; // index of the first letter of a word
  ctr = 0; // index of each word inside for args[]. Its the "rows" for args[][]

  /* We are using a two pointer technique, j is the slow moving one which points to first
     index of the word. i is the current index that we are looking at */
  
  for (i = 0; i < MAX_LINE; i++){
    /*  if the current character is a space, then we have to finish the word followed by NULL char */
    if (str[i] == ' ' || str[i] == '\0'){
      //args[ctr][j] = '\0'; // after the word is done, next char is NULL'
      // word[j] = '\0';
      // args[ctr] = word;
      /* if j is equal to 0 that means that we are still on the first argument (aka the command)  */ 
      if (j == 0) {
	
	args[ctr] = (char *)malloc((i + 1) * sizeof(char)); /* we allocate a char array size of i + 1 
							     ex:  if command is ls, then i is 2 and we
							     need an array of size 2 to fit the word */
	for (int k = 0; k < i; k++){
	  args[ctr][k] = str[k]; /* fill in the args[ctr][] with the necessary chars */
	}
	//args[ctr][i] = '\0'; /* last element will be a */
      }
      /* If we are here,  now we have already done with command, we are on to the arguments following the command 
        we will only be here if the number of args in the command line is greater than 2 (more than 2 words in the input) */
      else {
	args[ctr] = (char *)malloc((i - j) * sizeof(char));
	for (int k = 0; k < (i - j); k++){
	  args[ctr][k] = str[j + k];
	}
	//args[ctr][i] = '\0';
      }
	ctr++; // next word
	j = i + 1; // char index back to zero
      
    }
    /* if the index that we are on is an '\n' end line char
       then we are at the end of the input from the user
       and the word we are on is the last one of the input */
    else if (str[i] == '\n'){
      // args[ctr][j] = '\0';

      // word[j] = '\0';
      //args[ctr] = word;

      args[ctr] = (char *)malloc((i - j) * sizeof(char)); /* allocate an array of chars of size i-j */

      for (int k = 0; k < (i - j); k++){
	args[ctr][k] = str[j + k];
      }
      //args[ctr][i] = '\0';
      
    // printf("Args %d : %s\n", ctr, args[ctr]);

      
      args[++ctr] = NULL; /* make the index following the last word null */
      break;
      
      
    }

    /* If we are here that means that the index we are at
       is part of the word(aka a letter) so we Do nothing */
    else {
      
      //args[ctr][j] = str[i];
      //  word[j] = str[i];
      //printf("Args %d : %s\n", 0, args[0]);
      // j++;
      
    }
  }


  /*  TESING IF IT WORKED */
  
  for (i = 0; i < ctr; i++){
    printf("you entered:args[%d] : %s \n", i, args[i]);
  }




  
  /*
  pid_t pid;
  pid = fork();
  if (pid < 0) { // error occurred 
    fprintf(stderr, "Fork Failed");
    return 1;
  }
  else if (pid == 0) { // child process 
    execlp("/bin/ls","ls",NULL);
  }
  else { // parent process 
    // parent will wait for the child to complete 
    wait(NULL);
    printf("Child Complete");
  }
*/
  return 0;
}
