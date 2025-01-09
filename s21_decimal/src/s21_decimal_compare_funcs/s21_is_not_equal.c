#include "../s21_decimal.h"

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 1;
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  s21_equalize_scale(&value_1, &value_2);
  if (!sign_1 && !sign_2) {
    int cmp = s21_compare_abs(value_1, value_2);
    if (cmp == 0) {
      res = 0;
    }
  } else if (sign_1 && sign_2) {
    int cmp = s21_compare_with_minus(value_1, value_2);
    if (cmp == 0) {
      res = 0;
    }
  }
  return res;
}