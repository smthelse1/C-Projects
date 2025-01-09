#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_copy_decimal(value, result);
  int error = 0;
  if (result == NULL) {
    error = 1;
  }
  if (s21_get_sign(value)) {
    s21_set_sign(result, 0);
  } else {
    s21_set_sign(result, 1);
  }
  return error;
}