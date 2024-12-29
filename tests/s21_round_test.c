#include "../s21_decimal.h"
#include "s21_decimal_test.h"

START_TEST(test1) {
  s21_decimal a, c;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 123456789;
  s21_set_scale(&a, 2);
  s21_round(a, &c);
  ck_assert_int_eq(c.bits[0], 1234568);
}

START_TEST(test2) {
  s21_decimal a, c;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 123456789;
  s21_set_scale(&a, 5);
  s21_round(a, &c);
  ck_assert_int_eq(c.bits[0], 1235);
}

START_TEST(test3) {
  s21_decimal a, c;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 123456789;
  s21_set_scale(&a, 6);
  s21_round(a, &c);
  ck_assert_int_eq(c.bits[0], 123);
}

START_TEST(test4) {
  s21_decimal a, c;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 123456789;
  s21_set_sign(&a, 1);
  s21_set_scale(&a, 2);
  s21_round(a, &c);
  ck_assert_int_eq(c.bits[0], 1234568);
}

START_TEST(test5) {
  s21_decimal a, c;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 123456789;
  s21_set_sign(&a, 1);
  s21_set_scale(&a, 5);
  s21_round(a, &c);
  ck_assert_int_eq(c.bits[0], 1235);
}

START_TEST(test6) {
  s21_decimal a, c;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 123456789;
  s21_set_sign(&a, 1);
  s21_set_scale(&a, 6);
  s21_round(a, &c);
  ck_assert_int_eq(c.bits[0], 123);
}

START_TEST(test7) {
  s21_decimal a, c;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b00111111111111111111111111111111;  // 4611686018427387903
  s21_set_scale(&a, 0);
  s21_round(a, &c);
  ck_assert_int_eq(c.bits[0], 0b11111111111111111111111111111111);
  ck_assert_int_eq(c.bits[1], 0b00111111111111111111111111111111);
}

START_TEST(test8) {
  s21_decimal a, c;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b00111111111111111111111111111111;  // 4611686018427387903
  s21_set_scale(&a, 1);
  s21_round(a, &c);
  ck_assert_int_eq(c.bits[0], 0b01100110011001100110011001100110);
  ck_assert_int_eq(c.bits[1],
                   0b00000110011001100110011001100110);  // 461168601842738790
}

START_TEST(test9) {
  s21_decimal a, c;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b00111111111111111111111111111111;  // 4611686018427387903
  s21_set_scale(&a, 3);
  s21_round(a, &c);
  ck_assert_int_eq(c.bits[0],
                   0b11010010111100011010100111111100);  // 4611686018427388
  ck_assert_int_eq(c.bits[1], 0b00000000000100000110001001001101);
}

Suite *s21_round_test_suite() {
  Suite *s = suite_create("s21_round_test");
  TCase *t = tcase_create("main tcase");
  tcase_add_test(t, test1);
  tcase_add_test(t, test2);
  tcase_add_test(t, test3);
  tcase_add_test(t, test4);
  tcase_add_test(t, test5);
  tcase_add_test(t, test6);
  tcase_add_test(t, test7);
  tcase_add_test(t, test8);
  tcase_add_test(t, test9);
  suite_add_tcase(s, t);
  return s;
}
