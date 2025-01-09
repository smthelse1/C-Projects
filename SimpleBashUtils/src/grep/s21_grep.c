#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char templateStr[BUFSIZE] = {0};
  opt options = {0};
  parser(argc, argv, &options, templateStr);
  if (!options.e && !options.f) {
    for (int i = optind; i < argc; i++) {
      if (strlen(templateStr) == 0) {
        setPattern(templateStr, argv[i], &options);
      }
    }
  }
  reader(argc, argv, &options, templateStr);
  return 0;
}

void parser(int argc, char *argv[], opt *options, char *templateStr) {
  int opt;

  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
    switch (opt) {
      case 'e':
        options->e = 1;
        setPattern(templateStr, optarg, options);
        break;
      case 'i':
        options->i = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'f':
        options->f = 1;
        setPattern(templateStr, optarg, options);
        break;
      case 'o':
        options->o = 1;
        break;
      default:
        printf("No such arguments");
        break;
    }
  }
}

void reader(int argc, char **argv, opt *options, char *templateStr) {
  char *DIR;
  FILE *f;
  if (!options->e && !options->f) {
    optind++;
  }
  int countf = argc - optind;
  int counts = 0;
  for (int i = optind; i < argc; i++) {
    DIR = argv[i];
    if (argv[i - 1][0] == '-' &&
        (strchr(argv[i - 1], 'e') || (strchr(argv[i - 1], 'f')))) {
      continue;
    }
    if ((f = fopen(DIR, "r")) == NULL && !options->s) {
      printf("grep: %s: No such file or directory", DIR);
    } else if ((f = fopen(DIR, "r")) == NULL && options->s) {
      return;
    } else {
      grep(templateStr, f, options, DIR, countf, counts);
      fclose(f);
    }
  }
}

void grep(const char *pattern, FILE *file, opt *options, char *DIR, int countf,
          int counts) {
  regex_t regex = createRegex(pattern, options);
  int result;
  char line[BUFSIZE];
  int matches_count = 0;

  int has_match = 0;

  while (fgets(line, sizeof(line) - 1, file) != NULL) {
    counts++;
    if (!strchr(line, '\n')) {
      int len = strlen(line);
      line[len] = '\n';
      line[len + 1] = '\0';
    }

    result = regexec(&regex, line, 0, NULL, 0);
    if (result == 0 && !options->v) {
      matches_count++;
      has_match = 1;
      if (!options->l && !options->v && !options->c && !options->o) {
        printDir(countf, options, DIR, counts, line);
      } else if (!options->l && !options->v && !options->c && options->o) {
        printOflag(&regex, line, countf, DIR, counts, options);
      }
    } else if (result == 1 && options->v) {
      matches_count++;
      has_match = 1;
      printSecDIr(countf, options, DIR, counts, line);
    }
  }

  if (options->c) {
    if (countf > 1 && !options->h) {
      printf("%s:", DIR);
    }
    if (options->l) {
      if (has_match) {
        printf("1\n");
      } else {
        printf("0\n");
      }
    } else {
      printf("%d\n", matches_count);
    }
  }

  if (options->l && has_match) {
    printf("%s\n", DIR);
  }

  regfree(&regex);
}

void setPattern(char *templateStr, char *templateArg, opt *options) {
  FILE *file;
  char line[BUFSIZE];

  if (options->f) {
    file = fopen(templateArg, "r");
    if (file == NULL && !options->s) {
      printf("Cannot open file: %s", templateArg);
      return;
    }
    while (fgets(line, BUFSIZE, file) != NULL) {
      size_t len = strlen(line);
      if (line[len - 1] == '\n') {
        line[len - 1] = '\0';
      }
      if (strlen(templateStr) > 0) {
        strcat(templateStr, "|");
      }
      strcat(templateStr, line);
    }
    fclose(file);
  } else {
    if (strlen(templateStr) > 0) {
      strcat(templateStr, "|");
    }
    strcat(templateStr, templateArg);
  }
}

void printOflag(regex_t *regex, char *line, int countf, char *DIR, int curLine,
                opt *options) {
  regmatch_t match;
  char *copy = line;
  while (copy && 0 == (regexec(regex, copy, 1, &match, 0))) {
    if (countf > 1 && !options->h) {
      printf("%s:", DIR);
    }
    if (options->n) {
      printf("%d:", curLine);
    }
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      printf("%c", copy[i]);
    }
    printf("\n");
    copy += match.rm_eo;
  }
}

regex_t createRegex(const char *pattern, opt *options) {
  regex_t regex;
  if (options->i) {
    regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
  } else {
    regcomp(&regex, pattern, REG_EXTENDED);
  }
  return regex;
}

void printDir(int countf, opt *options, char *DIR, int counts, char *line) {
  if (countf > 1 && !options->h) {
    printf("%s:", DIR);
  }
  if (options->n) {
    printf("%d:", counts);
  }
  printf("%s", line);
}

void printSecDIr(int countf, opt *options, char *DIR, int counts, char *line) {
  if (!options->l && options->v && !options->c) {
    if (countf > 1 && !options->h) {
      printf("%s:", DIR);
    }
    if (options->n) {
      printf("%d:", counts);
    }
    printf("%s", line);
  }
}