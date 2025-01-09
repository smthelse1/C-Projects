#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  const s21_decimal one = {{1}};
  s21_copy_decimal(value, result);
  s21_truncate(value, result);
  if (s21_get_sign(value) && s21_get_scale(value)) {
    s21_sub(*result, one, result);
  }
  return 0;
}