#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_copy_decimal(value, result);
  s21_decimal half = {{5}};
  s21_set_scale(&half, 1);
  s21_set_zero(result);
  int scale = s21_get_scale(value);
  *result = value;
  s21_decimal cpy_value;
  s21_copy_decimal(value, &cpy_value);
  int last_digit = 0;
  if (s21_is_max_dec(value) && scale) {
    last_digit = s21_drop_last_digit(&cpy_value);
  } else if (scale) {
    if (s21_get_sign(value)) {
      s21_sub(value, half, result);  // - 0.5
    } else {
      s21_add(value, half, result);  // + 0.5
    }
  }
  s21_truncate(*result, result);
  if (last_digit >= 5) {
    const s21_decimal one = {{1}};
    s21_add(*result, one, result);
  }
  return 0;
}