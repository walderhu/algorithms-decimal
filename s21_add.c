#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0, sign1 = getSign(value_1), sign2 = getSign(value_2);
  zeroingOut(result);
  s21_decimal_extended ext1 = convertToExtended(value_1);
  s21_decimal_extended ext2 = convertToExtended(value_2);
  bringToACommonDenominator(&ext1, &ext2);
  if (sign1 != sign2) {
    if (isLessExt(ext1, ext2)) {
      swapDecimalExt(&ext1, &ext2);
      sign1 = sign2;
    }
    for (int i = 0; i < 7; i++) ext2.bits[i] = ~ext2.bits[i] & MAXBITS;
    ext2.bits[0]++;
  }
  for (int i = 0; i < 7; i++) {
    ext1.bits[i] += ext2.bits[i];
    if (getOverflow(&ext1)) {
      flag = 1;
      break;
    }
  }
  if ((flag = normalization(&ext1))) {
    if (sign1) flag = 2;
  } else {
    *result = convertFromExtended(ext1);
    setBit(result, 127, sign1);
  }
  return flag;
}
