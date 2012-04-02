#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

#define CHILDNUM 3

int dead;

// Signal handler for when a child exits
void childexit() {
  printf("child has finished\n");
  ++dead;
  // If all children are dead exit the parent too
  if (dead >= CHILDNUM)
    exit(0);
}

// TODO: implement general signal handler for child processes

int main(int argc, char *argv[]) {
  char numstr[1];
  int num, i;
  pid_t child[CHILDNUM];
  
  dead = 0;
  signal(SIGCHLD, childexit);
  
  for (i=0; i < CHILDNUM; ++i) {
    child[i] = fork();
    if (child[i] == 0) {
      //TODO: insert signal handling here
      printf("i am child %d, with pid=%d\n", i, getpid());
      
      /* TODO: wait for signals; sleep half a second each iteration
      for(; ;) {
        // 
      }
      */
      
      sleep(i+3);
      exit(0);
    }
  }
  
  printf("only parent\n");
  
  for(; ;) {
    // TODO: receive child num and signal, and send the signal to that child
    printf("  enter number: \n");
    gets(numstr); // needs arg2=1
    num = atoi(numstr);
    //printf("num*2 = %i\n", num*2);
  }
  
  printf("exiting\n");
  
  return 0;
}