#include "../s21_decimal.h"
#include "s21_decimal_test.h"

START_TEST(test1) {
  s21_decimal a, b, c;
  s21_initDecimal(&a);
  s21_initDecimal(&b);
  s21_initDecimal(&c);
  a.bits[0] = 19;
  b.bits[0] = 3;
  s21_div(a, b, &c);
  ck_assert_int_eq(c.bits[0], 6);
}

START_TEST(test2) {
  s21_decimal a, b, c;
  s21_initDecimal(&a);
  s21_initDecimal(&b);
  s21_initDecimal(&c);
  a.bits[0] = 65537;
  b.bits[0] = 10;
  s21_div(a, b, &c);
  ck_assert_int_eq(c.bits[0], 6553);
}

START_TEST(test3) {
  s21_decimal a, b, c;
  s21_initDecimal(&a);
  s21_initDecimal(&b);
  s21_initDecimal(&c);

  for (int i = 1000; i < 10000; i = i + 3) {
    a.bits[0] = i;
    b.bits[0] = 12;
    s21_div(a, b, &c);
    ck_assert_int_eq(c.bits[0], i / 12);
  }
}

START_TEST(test4) {
  s21_decimal a, b, c;
  s21_initDecimal(&a);
  s21_initDecimal(&b);
  s21_initDecimal(&c);

  for (int i = 1000; i < 10000; i = i + 3) {
    a.bits[0] = i;
    b.bits[0] = 3;
    s21_div(a, b, &c);
    ck_assert_int_eq(c.bits[0], i / 3);
  }
}

START_TEST(test5) {
  s21_decimal a, b, fact_c, expected_c;
  s21_initDecimal(&a);
  s21_initDecimal(&b);
  s21_initDecimal(&fact_c);
  s21_initDecimal(&expected_c);

  a.bits[0] = 483923857;
  a.bits[1] = 1839483911;
  a.bits[2] = 0;  // 7900523239747098513
  b.bits[0] = 777;
  expected_c.bits[0] = 0b00101001001110001001111000101101;
  expected_c.bits[1] = 0b00000000001001000001111110111010;
  expected_c.bits[2] = 0;  // 10 167 983 577 538 093
  s21_div(a, b, &fact_c);
  ck_assert_int_eq(fact_c.bits[0], expected_c.bits[0]);
  ck_assert_int_eq(fact_c.bits[1], expected_c.bits[1]);
  ck_assert_int_eq(fact_c.bits[2], expected_c.bits[2]);
}

START_TEST(test6) {
  s21_decimal a, b, c;
  s21_initDecimal(&a);
  s21_initDecimal(&b);
  s21_initDecimal(&c);
  a.bits[0] = 4294967295;
  b.bits[0] = 10;
  s21_div(a, b, &c);
  ck_assert_int_eq(c.bits[0], 429496729);
}

START_TEST(test7) {
  s21_decimal a, b, fact_c, expected_c;
  s21_initDecimal(&a);
  s21_initDecimal(&b);
  s21_initDecimal(&fact_c);
  s21_initDecimal(&expected_c);

  a.bits[0] = 483923857;
  a.bits[1] = 1839483911;
  a.bits[2] = 394873610;  // 7284132433032319977838352273
  b.bits[0] = 777;
  expected_c.bits[0] = 0b00110110101110101100001001101011;
  expected_c.bits[1] = 0b11011000010001100110001110011001;
  expected_c.bits[2] =
      0b00000000000001111100000100101010;  // 9374687816000411811889771 206/777
  s21_div(a, b, &fact_c);
  ck_assert_int_eq(fact_c.bits[0], expected_c.bits[0]);
  ck_assert_int_eq(fact_c.bits[1], expected_c.bits[1]);
  ck_assert_int_eq(fact_c.bits[2], expected_c.bits[2]);
}

START_TEST(test8) {
  s21_decimal a, b, fact_c, expected_c;
  s21_initDecimal(&a);
  s21_initDecimal(&b);
  s21_initDecimal(&fact_c);
  s21_initDecimal(&expected_c);

  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] =
      0b11111111111111111111111111111111;  // 79228162514264337593543950335
  b.bits[0] = 10;
  expected_c.bits[0] = 0b10011001100110011001100110011001;
  expected_c.bits[1] = 0b10011001100110011001100110011001;
  expected_c.bits[2] =
      0b00011001100110011001100110011001;  // 7922816251426433759354395033
  s21_div(a, b, &fact_c);
  ck_assert_int_eq(fact_c.bits[0], expected_c.bits[0]);
  ck_assert_int_eq(fact_c.bits[1], expected_c.bits[1]);
  ck_assert_int_eq(fact_c.bits[2], expected_c.bits[2]);
}

Suite *s21_div_suite() {
  Suite *s = suite_create("s21_div test");
  TCase *t = tcase_create("main tcase");
  tcase_add_test(t, test1);
  tcase_add_test(t, test2);
  tcase_add_test(t, test3);
  tcase_add_test(t, test4);
  tcase_add_test(t, test5);
  tcase_add_test(t, test6);
  tcase_add_test(t, test7);
  tcase_add_test(t, test8);
  suite_add_tcase(s, t);
  return s;
}
