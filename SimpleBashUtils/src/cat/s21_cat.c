#include "s21_cat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc > 1) {
    checkFlags(argc, argv);
  }
}

void checkFlags(int argc, char **argv) {
  int argFlag[7] = {0};
  memset(argFlag, 0, sizeof(int));
  int curArg = 1;
  int isFlag = 1;
  for (int i = 1; i < argc; i++) {
    if (isFlag) {
      if (!strcmp(argv[i], "-b") || !strcmp(argv[i], "--number-nonblank")) {
        argFlag[B] = 1;
      } else if (!strcmp(argv[i], "-e") || !strcmp(argv[i], "-E")) {
        argFlag[E] = 1;
        if (!strcmp(argv[i], "-e")) {
          argFlag[V] = 1;
        }
      } else if (!strcmp(argv[i], "-n") || !strcmp(argv[i], "--number")) {
        argFlag[N] = 1;
      } else if (!strcmp(argv[i], "-s") ||
                 !strcmp(argv[i], "--squeeze-blank")) {
        argFlag[S] = 1;
      } else if (!strcmp(argv[i], "-t") || !strcmp(argv[i], "-T")) {
        argFlag[T] = 1;
        if (!strcmp(argv[i], "-t")) {
          argFlag[V] = 1;
        }
      } else if (!strcmp(argv[i], "-v")) {
        argFlag[V] = 1;
      } else if (argv[i][0] == '-') {
        argFlag[ERROR] = 1;
      } else {
        curArg = i;
        isFlag = 0;
      }
    }
  }
  if (argFlag[ERROR] != 1) {
    ReadFile(argc, argv, argFlag, curArg);
  } else {
    PrintError();
  }
}

void ReadFile(int argc, char **argv, int *flag, int curArg) {
  char *DIR;
  FILE *fp;
  char str[BUFFER] = {0};
  for (int i = curArg; i < argc; i++) {
    DIR = argv[i];
    if ((fp = fopen(DIR, "r")) == NULL) {
      printf("%s: No such file\n", DIR);
    } else {
      PrintFile(str, flag, fp);
    }
  }
  fclose(fp);
}

void PrintFile(char *str, int *flag, FILE *fp) {
  int curLine = 1;
  int isSpace = 0;
  while (fgets(str, BUFFER, fp) != NULL) {
    if (flag[B] && str[0] != '\n') {
      printf("%6d\t", curLine);
      curLine++;
    }
    if (flag[S]) {
      if (!isSpace && str[0] == '\n') {
        isSpace = 1;
      } else if (isSpace && str[0] == '\n') {
        continue;
      } else if (isSpace && str[0] != '\n') {
        isSpace = 0;
      }
    }
    if (flag[N] && flag[B] != 1) {
      printf("%6d\t", curLine);
      curLine++;
    }
    for (size_t i = 0; i < strlen(str); i++) {
      if (flag[T] && str[i] == '\t') {
        printf("^");
        str[i] += 64;
      }
      if (flag[E] && str[i] == '\n' && flag[B] && i == 0) {
        printf("      \t$");
      } else if (flag[E] && str[i] == '\n') {
        printf("$");
      }
      PrintChar(str[i], flag[V]);
    }
  }
}

void PrintChar(unsigned char symbol, int flagV) {
  if (flagV == 1) {
    if (symbol < 32 && symbol != '\n' && symbol != '\t') {
      symbol += 64;
      printf("^%c", symbol);
    } else if (symbol == 127) {
      printf("^?");
    } else if (symbol > 127 && symbol < 160) {
      symbol -= 64;
      printf("M-^%c", symbol);
    } else {
      printf("%c", symbol);
    }
  } else {
    printf("%c", symbol);
  }
}

void PrintError() { printf("You must write correct flag"); }