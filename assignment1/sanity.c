#include "types.h"
#include "stat.h"
#include "user.h"

void foo(){

}

int
main(int argc, char *argv[])
{
  int i = 6;
  //sighandler_t handler;
  
  i = signal(10, 0);
  printf(1, "signal returned %d\n", i);
  exit();
}
