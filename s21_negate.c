#include "./s21_decimal.h"

int s21_negate(s21_decimal value,
               s21_decimal *result) {  // 0 - OK 1 - ошибка вычисления
  s21_initDecimal(result);
  s21_copy_decimal(result, value);
  unsigned int u = 1;

  result->bits[3] ^= u << 31;

  return s21_check_bit(&value, 127) == s21_check_bit(result, 127);
}
