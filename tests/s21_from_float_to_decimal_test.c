#include "s21_decimal_test.h"

START_TEST(from_float_to_decimal_0) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  float result, value_one_f = -INFINITY;
  s21_from_float_to_decimal(value_one_f, &value_one);
  s21_from_decimal_to_float(value_one, &result);
  ck_assert_float_eq(result, 0);
}

END_TEST

START_TEST(from_float_to_decimal_1) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  float result, value_one_f = 1234.56789123456778;
  s21_from_float_to_decimal(value_one_f, &value_one);
  s21_from_decimal_to_float(value_one, &result);
  ck_assert_float_le(fabs(result) - fabs(value_one_f), 1e-3);
}

END_TEST

START_TEST(from_float_to_decimal_2) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  float result, value_one_f = 85899;
  s21_from_float_to_decimal(value_one_f, &value_one);
  s21_from_decimal_to_float(value_one, &result);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_float_to_decimal_3) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  float result, value_one_f = -1234.56789;
  s21_from_float_to_decimal(value_one_f, &value_one);
  s21_from_decimal_to_float(value_one, &result);
  ck_assert_float_eq_tol(result, value_one_f, 7);
}

END_TEST

START_TEST(from_float_to_decimal_4) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  float result, value_one_f = 4294.967;
  s21_from_float_to_decimal(value_one_f, &value_one);
  s21_from_decimal_to_float(value_one, &result);
  ck_assert_float_eq(result, value_one_f);
}

END_TEST

START_TEST(from_float_to_decimal_5) {
  s21_decimal value_one = {{0, 0, 0, 0}};
  float result, value_one_f = -8589;
  s21_from_float_to_decimal(value_one_f, &value_one);
  s21_from_decimal_to_float(value_one, &result);
  ck_assert_float_eq_tol(result, value_one_f, 6);
}

END_TEST

START_TEST(s21_float_1) {
  float inp = -321.2;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00000C8C, 0, 0, 2147549184}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

Suite *s21_from_float_to_decimal_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("s21_from_float_to_decimal");
  tc = tcase_create("case_from_float_to_decimal");

  tcase_add_test(tc, from_float_to_decimal_0);
  tcase_add_test(tc, from_float_to_decimal_1);
  tcase_add_test(tc, from_float_to_decimal_2);
  tcase_add_test(tc, from_float_to_decimal_3);
  tcase_add_test(tc, from_float_to_decimal_4);
  tcase_add_test(tc, from_float_to_decimal_5);
  tcase_add_test(tc, s21_float_1);

  suite_add_tcase(s, tc);
  return s;
}