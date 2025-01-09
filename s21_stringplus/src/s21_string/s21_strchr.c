#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *res = '\0';
  c = (char)c;
  for (s21_size_t i = 0; i < s21_strlen(str) + 1; i++) {
    if (str[i] == c) {
      res = (char *)&str[i];
      break;
    }
  }
  return res;
}