#include "s21_decimal.h"

int s21_is_equal(s21_decimal value1, s21_decimal value2) {
  int sign1 = getSign(value1), sign2 = getSign(value2);
  int flag = 1;
  if (ItIsZero(value1) && ItIsZero(value2))
    ;
  else if (sign1 != sign2)
    flag = 0;
  else {
    s21_decimal_extended ext1 = convertToExtended(value1);
    s21_decimal_extended ext2 = convertToExtended(value2);
    bringToACommonDenominator(&ext1, &ext2);
    for (int i = 6; i >= 0; i--)
      if (ext1.bits[i] != ext2.bits[i]) {
        flag = 0;
        break;
      }
  }
  return flag;
}
