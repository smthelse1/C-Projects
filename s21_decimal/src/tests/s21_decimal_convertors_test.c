#include "s21_decimal_test.h"

START_TEST(s21_from_decimal_to_int_1) {
  s21_decimal src;
  int result = 0, number = 0;
  src.bits[0] = INT_MAX;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_float_eq(number, 2147483647);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_int_2) {
  s21_decimal src;
  int result = 0, number = 0;
  src.bits[0] = 133141;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 133141);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_int_3) {
  s21_decimal src;
  int result = 0, number = 0;
  src.bits[0] = 2147483647;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  s21_set_sign(&src, 1);
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -2147483647);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_int_4) {
  s21_decimal src;
  int result = 0, number = 0;
  src.bits[0] = 123451234;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 2147483648;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -123451234);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_int_5) {
  s21_decimal src;
  int result = 0, number = 0;
  src.bits[0] = 18;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 2147483648;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -18);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_int_6) {
  s21_decimal src;
  int result = 0, number = 0;
  src.bits[0] = 4294967295;
  src.bits[1] = 4294967295;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0xFFFFFFFFFFFFFFFF);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_int_to_decimal_0) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -2147483648;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_2) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 2147483647;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(s21_from_int_to_decimal_1) {
  s21_decimal val = {0};

  s21_from_int_to_decimal(0, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  s21_set_zero(&val);
  s21_from_int_to_decimal(127, &val);
  ck_assert_int_eq(val.bits[0], 127);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  s21_set_zero(&val);
  s21_from_int_to_decimal(2147483647, &val);
  ck_assert_int_eq(val.bits[0], 2147483647);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_0) {
  int a = 100;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  int add = s21_from_int_to_decimal(a, ptr_b);
  s21_decimal etalon = {{100, 0, 0, 0}};
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_1) {
  int a = 100;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  int add = s21_from_int_to_decimal(a, ptr_b);
  s21_decimal etalon = {{1000, 0, 0, 0}};
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 0);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_2) {
  int a = INT_MAX;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  int add = s21_from_int_to_decimal(a, ptr_b);
  s21_decimal etalon = {{INT_MAX, 0, 0, 0}};
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_3) {
  int a = -INT_MAX;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  int add = s21_from_int_to_decimal(a, ptr_b);  // a записываем в b
  s21_decimal etalon = {{INT_MAX, 0, 0, 0}};
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 0);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_4) {
  int a = -INT_MAX;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  int add = s21_from_int_to_decimal(a, ptr_b);
  s21_decimal etalon = {{INT_MAX, 0, 0, ~(INT_MAX)}};
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(s21_test_from_int_to_decimal_5) {
  int a = 0;
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal *ptr_b = &b;

  int add = s21_from_int_to_decimal(a, ptr_b);
  s21_decimal etalon = {{INT_MAX, 0, 0, ~(INT_MAX)}};
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(b, etalon);
  ck_assert_int_eq(equal, 0);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest1) {
  // 6412
  int src1 = 1;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest2) {
  // 6428
  int src1 = -1;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest3) {
  // 6444
  int src1 = 0;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest4) {
  // 6460
  int src1 = 0;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest5) {
  // 6476
  int src1 = -987879878;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00111010111000011101100111000110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest6) {
  // 6492
  int src1 = -2147483646;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b01111111111111111111111111111110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest7) {
  // 6508
  int src1 = 2147483646;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b01111111111111111111111111111110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest8) {
  // 6524
  int src1 = 796132784;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00101111011101000000010110110000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimalTest9) {
  // 6540
  int src1 = -12345677;
  s21_decimal origin = {0}, result = {0};
  s21_decimal *res = &result;
  s21_from_int_to_decimal(src1, res);
  origin.bits[0] = 0b00000000101111000110000101001101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_float_to_decimal_1) {
  s21_decimal val;

  s21_from_float_to_decimal(0.03, &val);
  ck_assert_int_eq(val.bits[0], 3);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 131072);

  s21_from_float_to_decimal(127.1234, &val);
  ck_assert_int_eq(val.bits[0], 1271234);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 262144);
}
END_TEST

START_TEST(s21_from_float_to_decimal_2) {
  s21_decimal val;
  s21_from_float_to_decimal(-128.023, &val);
  ck_assert_int_eq(val.bits[0], 12802299);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
}

START_TEST(s21_from_float_to_decimal_3) {
  s21_decimal val;
  s21_from_float_to_decimal(-2.1474836E+09, &val);
  ck_assert_int_eq(val.bits[0], -2147483648);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_from_float_to_decimal_4) {
  s21_decimal val;
  s21_from_float_to_decimal(22.14836E+03, &val);
  ck_assert_int_eq(val.bits[0], 2214836);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 131072);
}
END_TEST

START_TEST(s21_from_float_to_decimal_5) {
  s21_decimal val;
  s21_from_float_to_decimal(1.02E+09, &val);
  ck_assert_int_eq(val.bits[0], 1020000000);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_6) {
  s21_decimal val;
  s21_from_float_to_decimal(-333.2222, &val);
  ck_assert_int_eq(val.bits[0], 3332222);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_7) {
  s21_decimal val;
  float a = 1.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_8) {
  s21_decimal val;
  float a = -1.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_9) {
  s21_decimal val;
  float a = 0.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_1) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 18122;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 2147680256;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -18.122);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_2) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 1812;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 2147483648;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -1812);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_3) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 0XFFFFFF;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, 16777215);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_4) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 23450987;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 2147745792;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -2345.0987);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_5) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 4294967295;
  src.bits[1] = 4294967295;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, 0xFFFFFFFFFFFFFFFF);
  ck_assert_int_eq(result, 0);
}
END_TEST

Suite *convertors_test() {
  Suite *s1 = suite_create("s21_convertors");
  TCase *t1 = tcase_create("s21_convertors");
  suite_add_tcase(s1, t1);

  // FROM_DECIMAL_TO_INT
  tcase_add_test(t1, s21_from_decimal_to_int_1);
  tcase_add_test(t1, s21_from_decimal_to_int_2);
  tcase_add_test(t1, s21_from_decimal_to_int_3);
  tcase_add_test(t1, s21_from_decimal_to_int_4);
  tcase_add_test(t1, s21_from_decimal_to_int_5);
  tcase_add_test(t1, s21_from_decimal_to_int_6);

  // FROM_INT_TO_DECIMAL
  tcase_add_test(t1, from_int_to_decimal_1);
  tcase_add_test(t1, from_int_to_decimal_2);
  tcase_add_test(t1, s21_from_int_to_decimal_1);
  tcase_add_test(t1, s21_test_from_int_to_decimal_0);
  tcase_add_test(t1, s21_test_from_int_to_decimal_1);
  tcase_add_test(t1, s21_test_from_int_to_decimal_2);
  tcase_add_test(t1, s21_test_from_int_to_decimal_3);
  tcase_add_test(t1, s21_test_from_int_to_decimal_4);
  tcase_add_test(t1, s21_test_from_int_to_decimal_5);
  tcase_add_test(t1, s21_from_int_to_decimalTest1);
  tcase_add_test(t1, s21_from_int_to_decimalTest2);
  tcase_add_test(t1, s21_from_int_to_decimalTest3);
  tcase_add_test(t1, s21_from_int_to_decimalTest4);
  tcase_add_test(t1, s21_from_int_to_decimalTest5);
  tcase_add_test(t1, s21_from_int_to_decimalTest6);
  tcase_add_test(t1, s21_from_int_to_decimalTest7);
  tcase_add_test(t1, s21_from_int_to_decimalTest8);
  tcase_add_test(t1, s21_from_int_to_decimalTest9);
  tcase_add_test(t1, from_int_to_decimal_0);
  tcase_add_test(t1, from_int_to_decimal_1);

  tcase_add_test(t1, s21_from_float_to_decimal_1);
  tcase_add_test(t1, s21_from_float_to_decimal_2);
  tcase_add_test(t1, s21_from_float_to_decimal_3);
  tcase_add_test(t1, s21_from_float_to_decimal_4);
  tcase_add_test(t1, s21_from_float_to_decimal_5);
  tcase_add_test(t1, s21_from_float_to_decimal_6);
  tcase_add_test(t1, s21_from_float_to_decimal_7);
  tcase_add_test(t1, s21_from_float_to_decimal_8);
  tcase_add_test(t1, s21_from_float_to_decimal_9);

  tcase_add_test(t1, s21_from_decimal_to_float_1);
  tcase_add_test(t1, s21_from_decimal_to_float_2);
  tcase_add_test(t1, s21_from_decimal_to_float_3);
  tcase_add_test(t1, s21_from_decimal_to_float_4);
  tcase_add_test(t1, s21_from_decimal_to_float_5);

  return s1;
}