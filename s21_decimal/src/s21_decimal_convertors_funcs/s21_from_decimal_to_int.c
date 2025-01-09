#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  if (dst) {
    if (s21_get_sign(src) == 1) {
      *dst = -1 * (int)(src.bits[0] / pow(10, s21_get_scale(src)));
    } else {
      *dst = (int)(src.bits[0] / pow(10, s21_get_scale(src)));
    }
  } else {
    error = 1;
  }
  return error;
}
