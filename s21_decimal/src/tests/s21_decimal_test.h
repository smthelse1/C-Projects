#ifndef SRC_TESTS_TESTS_SUITCASES_H_
#define SRC_TESTS_TESTS_SUITCASES_H_

#include <check.h>
#include <limits.h>
#include <math.h>
#include <unistd.h>

#define MINUS_SIGN 2147483648
#define EXPONENT_PLUS_1 65536
#define EXPONENT_PLUS_28 1835008

#include "../s21_decimal.h"

Suite *suite_compare();
Suite *init_suite_other();
Suite *convertors_test();
Suite *arithmetic_test();
void run_tests(void);
void run_testcase(Suite *testcase);

#endif