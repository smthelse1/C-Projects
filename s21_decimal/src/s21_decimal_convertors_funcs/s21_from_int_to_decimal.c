#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
  int error = 1;
  if (dst) {
    error = 0;
    s21_set_zero(dst);
    if (src < 0) {
      src *= -1;
      s21_set_sign(dst, 1);
    }
    dst->bits[0] = src;
  }
  return error;
}
