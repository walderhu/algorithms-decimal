#include "../s21_decimal.h"
#include "s21_decimal_test.h"

START_TEST(test1) {
  s21_decimal a, c;
  int result = 0;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 5689874;
  s21_set_scale(&a, 4);
  result = s21_floor(a, &c);
  ck_assert_int_eq(c.bits[0], 568);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_check_sign(&a), s21_check_sign(&a));
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

START_TEST(test2) {
  s21_decimal a, c;
  int result = 0;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 5689874;
  s21_set_scale(&a, 4);
  s21_set_sign(&a, 1);
  result = s21_floor(a, &c);
  ck_assert_int_eq(c.bits[0], 569);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_check_sign(&a), s21_check_sign(&a));
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

START_TEST(test3) {
  s21_decimal a, c;
  int result = 0;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 0;
  s21_set_scale(&a, 4);
  result = s21_floor(a, &c);
  ck_assert_int_eq(c.bits[0], 0);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_check_sign(&a), s21_check_sign(&a));
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

START_TEST(test4) {
  s21_decimal a, c;
  int result = 0;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 1;
  s21_set_scale(&a, 4);
  s21_set_sign(&a, 1);
  result = s21_floor(a, &c);
  ck_assert_int_eq(c.bits[0], 1);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_check_sign(&a), s21_check_sign(&a));
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

START_TEST(test5) {
  s21_decimal a, c;
  int result = 0;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 0;
  s21_set_scale(&a, 4);
  s21_set_sign(&a, 1);
  result = s21_floor(a, &c);
  ck_assert_int_eq(c.bits[0], 0);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_check_sign(&a), s21_check_sign(&a));
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

Suite *s21_floor_test_suite() {
  Suite *s = suite_create("s21_floor test");
  TCase *t = tcase_create("main tcase");
  tcase_add_test(t, test1);
  tcase_add_test(t, test2);
  tcase_add_test(t, test3);
  tcase_add_test(t, test4);
  tcase_add_test(t, test5);
  suite_add_tcase(s, t);
  return s;
}
