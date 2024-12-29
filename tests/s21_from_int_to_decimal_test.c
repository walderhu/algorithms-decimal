#include "s21_decimal_test.h"

START_TEST(test_from_int_to_decimal) {
  s21_decimal a;
  int value1 = 0;
  int value2 = 2147483647;
  int value3 = -2147483647;
  int value4 = 12312321;
  int value5 = -12312321;
  s21_from_int_to_decimal(value1, &a);
  ck_assert_uint_eq(a.bits[0], 0);
  ck_assert_uint_eq(a.bits[1], 0);
  ck_assert_uint_eq(a.bits[2], 0);
  ck_assert_uint_eq(a.bits[3], 0b00000000000000000000000000000000);

  s21_from_int_to_decimal(value2, &a);
  ck_assert_uint_eq(a.bits[0], 2147483647);
  ck_assert_uint_eq(a.bits[1], 0);
  ck_assert_uint_eq(a.bits[2], 0);
  ck_assert_uint_eq(a.bits[3], 0b00000000000000000000000000000000);

  s21_from_int_to_decimal(value3, &a);
  ck_assert_uint_eq(a.bits[0], 2147483647);
  ck_assert_uint_eq(a.bits[1], 0);
  ck_assert_uint_eq(a.bits[2], 0);
  ck_assert_uint_eq(a.bits[3], 0b10000000000000000000000000000000);

  s21_from_int_to_decimal(value4, &a);
  ck_assert_uint_eq(a.bits[0], 12312321);
  ck_assert_uint_eq(a.bits[1], 0);
  ck_assert_uint_eq(a.bits[2], 0);
  ck_assert_uint_eq(a.bits[3], 0b00000000000000000000000000000000);

  s21_from_int_to_decimal(value5, &a);
  ck_assert_uint_eq(a.bits[0], 12312321);
  ck_assert_uint_eq(a.bits[1], 0);
  ck_assert_uint_eq(a.bits[2], 0);
  ck_assert_uint_eq(a.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

Suite *s21_from_int_to_decimal_suite(void) {
  Suite *s = suite_create("s21_from_int_to_decimal_suite");
  TCase *t = tcase_create("case_from_int_to_decimal");
  tcase_add_test(t, test_from_int_to_decimal);
  suite_add_tcase(s, t);
  return s;
}