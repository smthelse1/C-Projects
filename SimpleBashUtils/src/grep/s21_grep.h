#ifndef HEADER_H
#define HEADER_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 4096

typedef struct options {
  int e, i, v, c, l, n, h, s, f, o;

  char *pattern;

  int len_pattern;
} opt;

void reader(int argc, char **argv, opt *options, char *templateStr);
void parser(int argc, char *argv[], opt *options, char *templateStr);
void prChar(unsigned char symbol, int v);
void grep(const char *pattern, FILE *file, opt *options, char *DIR, int countf,
          int counts);
void setPattern(char *templateStr, char *templateArg, opt *options);
void printOflag(regex_t *regex, char *line, int countf, char *DIR, int curLine,
                opt *options);
regex_t createRegex(const char *pattern, opt *options);
void printDir(int countf, opt *options, char *DIR, int counts, char *line);
void printSecDIr(int countf, opt *options, char *DIR, int counts, char *line);

#endif