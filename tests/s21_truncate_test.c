#include "../s21_decimal.h"
#include "s21_decimal_test.h"

START_TEST(test1) {
  s21_decimal a, c;
  int result;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 3219;
  s21_set_scale(&a, 1);
  result = s21_truncate(a, &c);
  ck_assert_int_eq(c.bits[0], 321);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_check_sign(&a), s21_check_sign(&c));
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

START_TEST(test2) {
  s21_decimal a, c;
  int result;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 3219;
  s21_set_scale(&a, 2);
  s21_set_sign(&a, 1);
  result = s21_truncate(a, &c);
  ck_assert_int_eq(c.bits[0], 32);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_check_sign(&a), s21_check_sign(&c));
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

START_TEST(test3) {
  s21_decimal a, c;
  int result;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] = 3219;
  s21_set_scale(&a, 3);
  result = s21_truncate(a, &c);
  ck_assert_int_eq(c.bits[0], 3);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

START_TEST(test4) {
  s21_decimal a, c;
  int result;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] =
      0b11111111111111111111111111111111;  // 39614081257132168796771975167
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b01111111111111111111111111111111;
  s21_set_scale(&a, 24);
  result = s21_truncate(a, &c);
  ck_assert_int_eq(c.bits[0], 39614);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

START_TEST(test5) {
  s21_decimal a, c;
  int result;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] =
      0b11111111111111111111111111111111;  // 39614081257132168796771975167
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b01111111111111111111111111111111;
  s21_set_scale(&a, 28);
  result = s21_truncate(a, &c);
  ck_assert_int_eq(c.bits[0], 3);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

START_TEST(test6) {
  s21_decimal a, c;
  int result;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] =
      0b11111111111111111111111111111111;  // 39614081257132168796771975167
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b01111111111111111111111111111111;
  s21_set_scale(&a, 29);
  result = s21_truncate(a, &c);
  ck_assert_int_eq(c.bits[0], 0);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

START_TEST(test7) {
  s21_decimal a, c, expected_c;
  int result;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  s21_initDecimal(&expected_c);
  a.bits[0] =
      0b11111111111111111111111111111111;  // 39614081257132168796771975167
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b01111111111111111111111111111111;
  s21_set_scale(&a, 0);
  expected_c.bits[0] = 0b11111111111111111111111111111111;
  expected_c.bits[1] = 0b11111111111111111111111111111111;
  expected_c.bits[2] = 0b01111111111111111111111111111111;
  result = s21_truncate(a, &c);
  ck_assert_int_eq(c.bits[0], expected_c.bits[0]);
  ck_assert_int_eq(c.bits[1], expected_c.bits[1]);
  ck_assert_int_eq(c.bits[2], expected_c.bits[2]);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

START_TEST(test8) {
  s21_decimal a, c;
  int result;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] =
      0b11111111111111111111111111111111;  // 79228162514264337593543950335
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  s21_set_scale(&a, 27);
  result = s21_truncate(a, &c);
  ck_assert_int_eq(c.bits[0], 79);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

START_TEST(test9) {
  s21_decimal a, c;
  int result;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] =
      0b11111111111111111111111111111111;  // 79228162514264337593543950335
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  s21_set_scale(&a, 28);
  result = s21_truncate(a, &c);
  ck_assert_int_eq(c.bits[0], 7);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

START_TEST(test10) {
  s21_decimal a, c;
  int result;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] =
      0b11111111111111111111111111111111;  // 79228162514264337593543950335
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  s21_set_scale(&a, 29);
  s21_set_sign(&a, 1);
  result = s21_truncate(a, &c);
  ck_assert_int_eq(c.bits[0], 0);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(s21_check_sign(&a), s21_check_sign(&c));
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

START_TEST(test11) {
  s21_decimal a, c;
  int result;
  s21_initDecimal(&a);
  s21_initDecimal(&c);
  a.bits[0] =
      0b11111111111111111111111111111111;  // 79228162514264337593543950335
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  s21_set_scale(&a, 30);
  result = s21_truncate(a, &c);
  ck_assert_int_eq(c.bits[0], 0);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(s21_check_scale(&c), 0);
}

Suite *s21_truncate_test_suite() {
  Suite *s = suite_create("s21_truncate test");
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
  tcase_add_test(t, test10);
  tcase_add_test(t, test11);
  suite_add_tcase(s, t);
  return s;
}
