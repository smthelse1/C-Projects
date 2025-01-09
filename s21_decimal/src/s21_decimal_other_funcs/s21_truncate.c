#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_set_zero(result);
  int sign = s21_get_sign(value);
  *result = value;
  int scale = s21_get_scale(value);
  for (int i = 0; i < scale; i++) s21_drop_last_digit(result);
  s21_set_scale(result, 0);
  if (sign) s21_set_sign(result, 1);
  return 0;
}