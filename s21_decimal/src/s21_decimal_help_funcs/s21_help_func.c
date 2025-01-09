#include "../s21_decimal.h"

int s21_get_scale(s21_decimal value) {
  return (value.bits[3] & SCALE_MASK) >> 16;
}

int s21_get_sign(s21_decimal value) {
  return (value.bits[3] & SIGN_MASK) >> 31;
}

void s21_set_scale(s21_decimal *value, int scale) {
  value->bits[3] &= ~SCALE_MASK;
  value->bits[3] |= (scale & 0xFF) << 16;
}

void s21_set_sign(s21_decimal *value, int sign) {
  if (sign) {
    value->bits[3] |= SIGN_MASK;
  } else {
    value->bits[3] &= ~SIGN_MASK;
  }
}

unsigned int s21_as_uint(int x) { return *((unsigned int *)&x); }

int s21_as_int(unsigned int x) { return *((int *)&x); }

int s21_drop_last_digit(s21_decimal *src) {
  unsigned long long last, div;

  last = s21_as_uint(src->bits[2]);
  div = last % 10;
  src->bits[2] = s21_as_int((unsigned int)(last / 10));

  last = s21_as_uint(src->bits[1]) + div * S21_2IN32;
  div = last % 10;
  src->bits[1] = s21_as_int((unsigned int)(last / 10));

  last = s21_as_uint(src->bits[0]) + div * S21_2IN32;
  div = last % 10;
  src->bits[0] = s21_as_int((unsigned int)(last / 10));
  return (int)div;
}

void s21_copy_decimal(s21_decimal value_1, s21_decimal *value_2) {
  value_2->bits[0] = value_1.bits[0];
  value_2->bits[1] = value_1.bits[1];
  value_2->bits[2] = value_1.bits[2];
  value_2->bits[3] = value_1.bits[3];
}

void s21_set_zero(s21_decimal *value) {
  value->bits[0] = 0;
  value->bits[1] = 0;
  value->bits[2] = 0;
  value->bits[3] = 0;
}

int s21_compare_with_minus(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  for (int i = 2; i >= 0; i--) {
    if (!res) {
      if ((long int)-value_1.bits[i] > (long int)-value_2.bits[i]) res = 1;
      if ((long int)-value_1.bits[i] < (long int)-value_2.bits[i]) res = -1;
    }
  }
  return res;
}

int s21_compare_abs(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  for (int i = 2; i >= 0; i--) {
    if (!res) {
      if (value_1.bits[i] > value_2.bits[i]) res = 1;
      if (value_1.bits[i] < value_2.bits[i]) res = -1;
    }
  }
  return res;
}

void s21_increase_scale(s21_decimal *value) {
  unsigned long temp = 0;
  for (int i = 0; i < 3; i++) {
    temp += (s21_as_uint(value->bits[i]) * 10);
    value->bits[i] = s21_as_int(temp);
    temp >>= 32;
  }

  int scale = s21_get_scale(*value);
  s21_set_scale(value, scale + 1);
}

void s21_equalize_scale(s21_decimal *value_1, s21_decimal *value_2) {
  int scale_1 = s21_get_scale(*value_1);
  int scale_2 = s21_get_scale(*value_2);

  while (scale_1 < scale_2) {
    s21_increase_scale(value_1);
    scale_1++;
  }

  while (scale_2 < scale_1) {
    s21_increase_scale(value_2);
    scale_2++;
  }
}

int s21_is_zero(s21_decimal value) {
  int res = 1;
  for (int i = 0; i < 3; i++) {
    if (value.bits[i] != 0) {
      res = 0;
    }
  }
  return res;
}

int s21_is_max_dec(s21_decimal value) {
  int res = 0;
  if (s21_as_uint(value.bits[0]) == 0xffffffff &&
      s21_as_uint(value.bits[1]) == 0xffffffff &&
      s21_as_uint(value.bits[2]) == 0xffffffff) {
    res = 1;
  }
  return res;
}

void s21_set_bit(s21_decimal *dst, int index, int bit) {
  int mask = 1u << (index % 32);
  if (bit == 0)
    dst->bits[index / 32] = dst->bits[index / 32] & ~mask;
  else
    dst->bits[index / 32] = dst->bits[index / 32] | mask;
}

int s21_get_bit(s21_decimal num, int curBit) {
  int bit;
  if ((num.bits[curBit / 32] & (1 << curBit % 32)) == 0) {
    bit = 0;
  } else {
    bit = 1;
  }

  return bit;
}

int getFloatSign(float *src) { return *(int *)src >> 31; }

int getFloatExp(float *src) { return ((*(int *)src & ~SIGN_MASK) >> 23) - 127; }