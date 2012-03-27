
#include <stdio.h>
#include <string.h>
#define PWD_SIZE 256

char curdir[PWD_SIZE];

int main(int argc, char *argv[]) {
  sprintf(curdir, "/bla/grr");
  printf("%s\n", curdir);
  if (argc > 1) {
    chdirstr(argv[1]);
  }
  printf("dir: %s\n", curdir); 
  
  return 0;
}

int chdirstr(char* cdstr) {
  char str[PWD_SIZE];
  char tmp[PWD_SIZE];
  int i=0;
  int j=0;
  int len;
  
  // Check reletivity to root
  if (cdstr[0] == '/') {
    cdstr++;
    sprintf(curdir, "/");
  }
  
  //Copy received string
  sprintf(str, "%s", cdstr);
  
  //Append slash at end of curdir
  len = strlen(curdir);
  if (len < PWD_SIZE && curdir[len-1] != '/') {
    curdir[len] = '/';
    curdir[++len] = '\0';
  }
  
  //Append slash at end of str
  len = strlen(str);
  if (len < PWD_SIZE && str[len-1] != '/') {
    str[len] = '/';
    str[++len] = '\0';
  }
  
  //Split str on slashes
  while(i<len) {
    if (str[i] == '/') {
      i++;
      tmp[j] = '\0';
      j=0;
      
      //Change curdir string one step at a time
      if (strcmp(tmp, "..") == 0) {
        int k = strlen(curdir)-1;
        while (k > 0 && curdir[k-1] != '/') k--;
        curdir[k] = '\0';
      } else if (strcmp(tmp, ".") != 0) {
        sprintf(curdir + strlen(curdir), "%s/", tmp);
      }
      printf("%s\n", curdir); 
      continue;
    }
    tmp[j] = str[i];
    i++;
    j++;
  }
  
  //Remove last slash if not in root
  len = strlen(curdir);
  if (len > 1) {
    curdir[len-1] = '\0';
  }
  
  return 1;
}