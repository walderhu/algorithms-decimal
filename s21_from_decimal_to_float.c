#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result = CONVERSION_SUCCESS;
  if (dst) {
    double num = 0;
    for (int i = 0; i < 96; i++) {
      if (s21_check_bit(&src, i)) {
        num += pow(2.0, i);
      }
    }
    unsigned int scale = s21_check_scale(&src);
    num /= pow(10.0, scale);
    if (s21_check_sign(&src) == 1) {
      num = -num;
    }
    *dst = (float)num;
  } else {
    result = CONVERT_ERROR;
  }
  return result;
}
