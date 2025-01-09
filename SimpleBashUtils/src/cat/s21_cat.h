#ifndef CAT_H
#define CAT_H
#define BUFFER 4096
#include <stdio.h>

typedef enum EFLAGS { B, E, N, S, T, V, ERROR } FLAGS;

void checkFlags(int argc, char **argv);
void ReadFile(int argc, char **argv, int *flag, int curArg);
void PrintFile(char *str, int *flag, FILE *fp);
void PrintChar(unsigned char symbol, int flagV);
void PrintError();

#endif