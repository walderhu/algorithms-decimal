#include "s21_decimal.h"
// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal intermediate_result, tmp_a, S;
  s21_initDecimal(&intermediate_result);
  s21_initDecimal(&tmp_a);
  s21_initDecimal(&S);
  s21_copy_decimal(&tmp_a, value_1);
  int counter_to_break = 0;

  while (s21_simple_less_or_equal(value_2, tmp_a) == 1) {
    s21_copy_decimal(&intermediate_result, value_2);
    int q = s21_getQ(tmp_a, value_2);
    s21_left_shift(&intermediate_result, q);

    s21_decimal tmp_tmp_a;
    s21_initDecimal(&tmp_tmp_a);
    s21_simple_sub(tmp_a, intermediate_result, &tmp_tmp_a);
    s21_copy_decimal(&tmp_a, tmp_tmp_a);

    s21_decimal digit_one;
    s21_initDecimal(&digit_one);
    digit_one.bits[0] = 1;
    s21_left_shift(&digit_one, q);
    s21_decimal tmp_S;
    s21_initDecimal(&tmp_S);
    s21_simple_sum(S, digit_one, &tmp_S);
    s21_copy_decimal(&S, tmp_S);
    if (counter_to_break > 500) break;
    counter_to_break++;
  }
  s21_copy_decimal(result, S);
  return 0;
}
