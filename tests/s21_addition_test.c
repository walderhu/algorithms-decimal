#include "s21_decimal_test.h"

START_TEST(add_0) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{987, 654, 321, 0}}, result;
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_1) {
  s21_decimal value_one = {{15, 0, 0, 0}},
              value_two = {{15, 0, 0, ~(UINT_MAX >> 1)}}, result;
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_2) {
  s21_decimal value_one = {{UINT_MAX, 65656, 9876, 0}},
              value_two = {{677, 0, 777, 0}}, result;
  setBit(&value_one, 127, 1);
  setBit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_3) {
  s21_decimal value_one = {{123, 0, UINT_MAX, 0}},
              value_two = {{0, 777, UINT_MAX, 0}}, result;
  s21_set_scale(&value_one, 12);
  s21_set_scale(&value_two, 12);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_4) {
  s21_decimal value_one = {{5677, 0, 12333, 0}}, value_two = {{0, 0, 0, 0}},
              result;
  s21_set_scale(&value_one, 19);
  setBit(&value_two, 86, 1);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_5) {
  s21_decimal value_one = {{UINT_MAX, 456, 789, 0}},
              value_two = {{987, UINT_MAX, 321, 0}}, result;
  s21_set_scale(&value_one, 6);
  s21_set_scale(&value_two, 4);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_6) {
  s21_decimal value_one = {{2, 0, 0, ~(UINT_MAX >> 1)}},
              value_two = {{8, 0, 0, 0}}, result;
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_7) {
  s21_decimal value_one = {0}, value_two = {0}, result;
  setBit(&value_two, 127, 1);
  setBit(&value_two, 33, 1);
  setBit(&value_one, 86, 1);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_8) {
  s21_decimal value_one = {{123, 456, 789, 0}},
              value_two = {{987, 654, 321, ~(UINT_MAX >> 1)}}, result;
  setBit(&value_one, 127, 1);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_9) {
  s21_decimal value_one = {{456, 321, 7777, ~(UINT_MAX >> 1)}}, value_two = {0},
              result;
  setBit(&value_two, 127, 1);
  setBit(&value_two, 77, 1);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_10) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX >> 1)}},
              value_two = {{987, UINT_MAX, 321, 0}}, result;
  s21_set_scale(&value_two, 12);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_11) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{4, 0, 0, ~(UINT_MAX >> 1)}}, result;
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_12) {
  s21_decimal value_one = {{UINT_MAX, 0, 24444444, 0}},
              value_two = {{UINT_MAX, 45666656, 234444, 0}}, result;
  setBit(&value_two, 127, 1);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_13) {
  s21_decimal value_one = {{123, 0, 0, ~(UINT_MAX >> 1)}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result;
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_14) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result;
  s21_set_scale(&value_one, 5);
  s21_set_scale(&value_two, 3);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

START_TEST(add_15) {
  s21_decimal value_one = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}},
              value_two = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}}, result;
  s21_set_scale(&value_one, 5);
  s21_set_scale(&value_two, 3);
  ck_assert_int_eq(0, s21_add(value_one, value_two, &result));
}

END_TEST

Suite *addition_tests() {
  Suite *suite = suite_create("---ADDITION---");
  TCase *tcase = tcase_create("decimal_tc");
  tcase_add_test(tcase, add_0);
  tcase_add_test(tcase, add_1);
  tcase_add_test(tcase, add_2);
  tcase_add_test(tcase, add_3);
  tcase_add_test(tcase, add_4);
  tcase_add_test(tcase, add_5);
  tcase_add_test(tcase, add_6);
  tcase_add_test(tcase, add_7);
  tcase_add_test(tcase, add_8);
  tcase_add_test(tcase, add_9);
  tcase_add_test(tcase, add_10);
  tcase_add_test(tcase, add_11);
  tcase_add_test(tcase, add_12);
  tcase_add_test(tcase, add_13);
  tcase_add_test(tcase, add_14);
  tcase_add_test(tcase, add_15);

  suite_add_tcase(suite, tcase);
  return suite;
}
