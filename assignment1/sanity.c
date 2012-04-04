#include "types.h"
#include "stat.h"
#include "user.h"

#define TOTCHILD 3

int dead;

// Signal handler for when a child exits
void childexit() {
  //printf(1, "child has finished\n"); // DEBUG
  ++dead;
  
  // If all children are dead exit the parent too
  if (dead >= TOTCHILD)
    exit();
}

// Handle signal number 4
void ouch() {
  printf(1, "ouch %d\n", getpid());
}

int
main(int argc, char *argv[])
{
  char numstr[1];
  int childnum, signum, i;
  int child[TOTCHILD];
  
  dead = 0; // Number of children that have exited
  signal(17, childexit); // Handel exiting child
  
  // Create TOTCHILD number of child processes
  for (i=0; i < TOTCHILD; ++i) {
    child[i] = fork();
    if (child[i] == 0) {
      signal(4, ouch); // Handle signal 4 as requested
      //TODO: insert signal handling here if needed
      
      //printf(1, "i am child %d, with pid=%d\n", i, getpid()); // DEBUG
      
      // Wait for signals; sleep half a second each iteration
      for(; ;) {
        sleep(0.5);
      }
    }
  }
  
  //printf(1, "only parent\n"); // DEBUG
  
  for(; ;) {
    // Receive child num and signal, and send the signal to that child
    printf(1, "Enter a child id (0 - 2): ");
    gets(numstr, 1);
    childnum = atoi(numstr);
    if (childnum < 0 || childnum >= TOTCHILD) // Verify 0-2
      continue; // If not, ask again
    printf(1, "Which signal to send: ");
    gets(numstr, 1);
    signum = atoi(numstr);
    
    sigsend(child[childnum], signum); // Send the signal
  }
  
  printf(1, "Exiting\n"); // these lines are not supposed to be reached
  exit();             // exit is done via childexit function
}
