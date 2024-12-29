#include "./s21_decimal.h"

int s21_round(s21_decimal value,
              s21_decimal *result) {  // 0 - OK 1 - ошибка вычисления
  s21_decimal truncated_value, just_number_one;
  int fnac = s21_getFNAC(value);

  s21_initDecimal(result);
  s21_initDecimal(&truncated_value);
  s21_initDecimal(&just_number_one);
  just_number_one.bits[0] = 1;

  s21_truncate(value, &truncated_value);

  if (fnac >= 5)
    s21_simple_sum(truncated_value, just_number_one, result);
  else
    s21_copy_decimal(result, truncated_value);
  return 0;
}
