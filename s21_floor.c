#include "./s21_decimal.h"

int s21_floor(s21_decimal value,
              s21_decimal *result) {  // 0 - OK 1 - ошибка вычисления
  s21_initDecimal(result);
  if (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0) {
    result->bits[3] = value.bits[3];
    s21_set_scale(result, 0);
  } else {
    s21_decimal just_number_one;
    s21_initDecimal(&just_number_one);
    just_number_one.bits[0] = 1;
    s21_truncate(value, result);
    if (s21_check_bit(&value, 127) != 0)
      s21_simple_sum(*result, just_number_one, result);
  }
  return 0;
}
