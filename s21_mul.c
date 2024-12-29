#include "./s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0, sign1 = getSign(value_1), sign2 = getSign(value_2);
  zeroingOut(result);
  if (sign1 != sign2)
    sign1 = 1;
  else
    sign1 = 0;
  if (ItIsZero(value_1) || ItIsZero(value_2))
    ;
  else {
    s21_decimal_extended mul = {0};
    s21_decimal_extended ext1 = convertToExtended(value_1);
    s21_decimal_extended ext2 = convertToExtended(value_2);
    mul.bits[0] = ext1.bits[0] * ext2.bits[0];
    getOverflow(&mul);
    mul.bits[1] += ext1.bits[0] * ext2.bits[1];
    getOverflow(&mul);
    mul.bits[1] += ext1.bits[1] * ext2.bits[0];
    getOverflow(&mul);
    mul.bits[2] += ext1.bits[0] * ext2.bits[2];
    getOverflow(&mul);
    mul.bits[2] += ext1.bits[1] * ext2.bits[1];
    getOverflow(&mul);
    mul.bits[2] += ext1.bits[2] * ext2.bits[0];
    getOverflow(&mul);
    mul.bits[3] += ext1.bits[1] * ext2.bits[2];
    getOverflow(&mul);
    mul.bits[3] += ext1.bits[2] * ext2.bits[1];
    getOverflow(&mul);
    mul.bits[4] += ext1.bits[2] * ext2.bits[2];
    mul.scale = ext1.scale + ext2.scale;
    flag = getOverflow(&mul);
    if (!flag) {
      flag = normalization(&mul);
    }
    if (flag) {
      if (sign1) flag = 2;
    } else {
      *result = convertFromExtended(mul);
      setBit(result, 127, sign1);
    }
  }
  return flag;
}
