#ifndef S21_DECIMAL_TEST_H
#define S21_DECIMAL_TEST_H

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

#define c30 0x1E000000   // scale 30
#define c28 0x1C000000   // scale 28
#define c15 0x0F000000   // scale 15
#define c19 0x13000000   // scale 19
#define m7 0x8E000000    // minus scale 7
#define m6 0x8C000000    // minus scale 6
#define m5 0x8A000000    // minus scale 5
#define c6 0x06000000    // scale 6
#define c1 0x01000000    // scale 1
#define m1 0x81000000    // minus scale 1
#define minus 0x80000000 // minus scale 0
#define TEST_ARITHMETIC_OK 0
#define TEST_ARITHMETIC_BIG 1
#define TEST_ARITHMETIC_SMALL 2
#define TEST_ARITHMETIC_ZERO_DIV 3

void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_mul_fail(s21_decimal decimal1, s21_decimal decimal2, int code_check);
int run_suite(Suite *);

Suite *s21_from_int_to_decimal_suite(void);
Suite *s21_from_decimal_to_int_suite(void);
Suite *s21_from_float_to_decimal_suite(void);
Suite *s21_from_decimal_to_float_suite(void);
Suite *greater_tests();
Suite *less_tests();
Suite *equal_tests();
Suite *sub_tests();
Suite *addition_tests();
Suite *s21_truncate_test_suite();
Suite *s21_floor_test_suite();
Suite *s21_negate_test_suite();
Suite *s21_round_test_suite();
Suite *mul_suite(void);
Suite *s21_div_suite();

void run_tests(void);
int run_testcase(Suite *testcase);

#endif // S21_DECIMAL_TEST_H
