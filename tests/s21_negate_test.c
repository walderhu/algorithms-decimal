#include "../s21_decimal.h"
#include "s21_decimal_test.h"

START_TEST(test1) {
  s21_decimal a, c;
  int result;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[3] = 0b10000000000000100000000000000000;
  result = s21_negate(a, &c);
  ck_assert_int_eq(c.bits[3], 131072);
  ck_assert_int_eq(result, 0);
}

START_TEST(test2) {
  s21_decimal a, c;
  int result;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[3] = 0b11111111111111111111111111111111;
  result = s21_negate(a, &c);
  ck_assert_int_eq(c.bits[3], 2147483647);
  ck_assert_int_eq(result, 0);
}

START_TEST(test3) {
  s21_decimal a, c;
  int result;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[3] = 0b00000000000000000000000000000000;
  result = s21_negate(a, &c);
  ck_assert_int_eq(c.bits[3], 2147483648);
  ck_assert_int_eq(result, 0);
}

Suite *s21_negate_test_suite() {
  Suite *s = suite_create("s21_negate test");
  TCase *t = tcase_create("main tcase");
  tcase_add_test(t, test1);
  tcase_add_test(t, test2);
  tcase_add_test(t, test3);
  suite_add_tcase(s, t);
  return s;
}
