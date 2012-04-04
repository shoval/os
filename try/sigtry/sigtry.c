#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

#define TOTCHILD 3

int dead;

// Signal handler for when a child exits
void childexit() {
  printf("child has finished\n"); // TODO: remove line
  ++dead;
  // If all children are dead exit the parent too
  if (dead >= TOTCHILD)
    exit(0);
}

// TODO: implement general signal handler for child processes
void ouch() {
  printf("ouch %d\n", getpid());
}

int main(int argc, char *argv[]) {
  char numstr[1];
  int childnum, signum, i;
  pid_t child[TOTCHILD];
  
  dead = 0;
  signal(SIGCHLD, childexit);
  
  for (i=0; i < TOTCHILD; ++i) {
    child[i] = fork();
    if (child[i] == 0) {
      //TODO: insert signal handling here
      //printf("i am child %d, with pid=%d\n", i, getpid());
      signal(4, ouch);
      
      // wait for signals; sleep half a second each iteration
      for(; ;) {
        sleep(0.5);
      }
      
      //sleep(i+3);
      //exit(0);
    }
  }
  
  printf("only parent\n");
  
  for(; ;) {
    // TODO: receive child num and signal, and send the signal to that child
    printf("Enter a child id (0 - 2): ");
    gets(numstr); // needs arg2=1
    childnum = atoi(numstr);
    if (childnum < 0 || childnum >= TOTCHILD)
      continue;
    printf("Which signal to send: ");
    gets(numstr); // needs arg2=1
    signum = atoi(numstr);
    //sigsend(child[childnum], signum); // this isn't working
    //printf("num*2 = %i\n", num*2);
  }
  
  printf("Exiting\n"); // this line is not supposed to be reached
  return 0;
}