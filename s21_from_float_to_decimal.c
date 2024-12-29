#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result = 0;
  s21_initDecimal(dst);
  if (fabs(src) < powl(10.0, -1 * 28)) {
    result = 1;
  } else if (src >= powl(2.0, 96)) {
    result = 1;
  } else if (src < -1 * powl(2.0, 96)) {
    result = 1;
  } else {
    if (src < 0.0) {
      s21_set_sign(dst, 1);
      src *= -1;
    }
  }

  char str[14] = {0};
  sprintf(str, "%.7g", src);
  int i = round_string(str);
  int int_src = 0;
  sscanf(str, "%d", &int_src);

  dst->bits[0] = int_src;
  if (i != -1) s21_set_scale(dst, i);

  return result;
}