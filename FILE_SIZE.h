#include<stdio.h>

#ifndef FILE_SIZE
#define FILE_SIZE
#define ZERO_OFFSET 0
float FILE_SIZE(FILE* INPUT_FILE){


int   SIZE;
int   initial;
float AVERAGE;
fseeko(INPUT_FILE,ZERO_OFFSET,SEEK_END);
SIZE    = ftell(INPUT_FILE);
AVERAGE = SIZE;

for(initial = 0; initial < 3; ++initial)
{AVERAGE = (AVERAGE)/(1024.0);}

rewind(INPUT_FILE);
return  AVERAGE;}

#endif
