#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0, sign2 = getSign(value_2);
  if (sign2)
    setBit(&value_2, 127, 0);
  else {
    setBit(&value_2, 127, 1);
  }
  flag = s21_add(value_1, value_2, result);
  return flag;
}
