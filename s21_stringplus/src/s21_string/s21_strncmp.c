#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t result = 0;
  for (s21_size_t i = 0; i < n; ++i) {
    if (str1[i] != str2[i]) {
      if (str1[i] < /*(unsigned char*)*/ str2[i])
        result = -1;
      else
        result = 1;
    }
  }
  return result;
}
