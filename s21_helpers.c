#include "s21_decimal.h"
//ВСПОМОГАТЕЛЬНЫЕ АЛЕКСЕЯ

int round_string(char str[14]) {  //берёт строку типа 123.456 делает из неё
                                  // 123456 и возвращает позицию точки 3
  int position = -1;
  int original_len = strlen(str);
  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] == '.') position = i;
    if (position != -1) str[i] = str[i + 1];
  }
  return position != -1 ? original_len - position - 1 : -1;
}

// проверить значение бита в структуре decimal (0 или 1) на позиции position (от
// 0 до 127)
int s21_check_bit(s21_decimal *value, int position) {
  return ((value->bits[position / 32] & ((1U << (position % 32)))) != 0);
}

// проверить знак числа в структуре decimal (0 плюс, 1 минус)
int s21_check_sign(s21_decimal *value) { return s21_check_bit(value, 127); }

// проверить значение коэффициента масштабирования
int s21_check_scale(s21_decimal *value) {
  int mask = 0b11111111;
  return (mask << 16 & value->bits[3]) >> 16;
}

// установить значение бита bit (0 или 1) в структуре decimal на позиции
// position (от 0 до 127)
void s21_set_bit(s21_decimal *value, int position, int bit) {
  if (bit == 0)
    value->bits[position / 32] =
        value->bits[position / 32] & ~(1U << (position % 32));
  else
    value->bits[position / 32] =
        value->bits[position / 32] | (1U << (position % 32));
}

// установить знак числа sign (0 плюс, 1 минус) в структуре decimal
void s21_set_sign(s21_decimal *value, int sign) {
  if (sign == 0)
    value->bits[3] = value->bits[3] & ~(1U << 31);
  else
    value->bits[3] = value->bits[3] | (1U << 31);
}

// установить значение коэффициента масштабирования
void s21_set_scale(s21_decimal *value, int scale) {
  value->bits[3] =
      ((unsigned int)s21_check_bit(value, 127) << 31) | (scale << 16);
}

// // проверка мантисы на ноль. Если все нули вернет 1, иначе 0. Проверяем
// только
// // мантису, чтобы не попасть в ловушку, когда можем получть -0 != 0
// int s21_is_zero(s21_decimal *value) {
//   int result = TRUE;
//   for (int i = 0; i < 96; i++) {
//     if (s21_check_bit(value, i) != 0) {
//       result = FALSE;
//     }
//   }
//   return result;
// }

// побитовое копирование структуры value по адресу destination
void s21_copy_decimal(s21_decimal *destination, s21_decimal value) {
  for (int i = 127; i >= 0; i--) {
    s21_set_bit(destination, i, s21_check_bit(&value, i));
  }
}

/*
Функция s21_simple_less_or_equal корректно сравнивает 2 целых, неотрицаиельных
децимала. Все тесты проходит успешно - релих Основа для более сложных
конструкций 0 - FALSE 1 - TRUE
*/
int s21_simple_less_or_equal(s21_decimal val1,
                             s21_decimal val2) {  // 0 - FALSE 1 - TRUE
  int result = 0;

  for (int i = 96; i >= 0; i--) {
    int bit1 = s21_check_bit(&val1, i);
    int bit2 = s21_check_bit(&val2, i);
    if (i == 0 && bit1 == bit2)
      result = 1;
    else if (bit1 != bit2) {
      result = bit1 < bit2;
      break;
    };
  }
  return result;
}

/*
Функция s21_simple_sum корректно складывает 2 целых, неотрициательных децимала.
Нет проверки на переполнение числа, предполагается, что сумма чисел заведомо
меньше 96 бит. Все тесты проходит успешно - релиз Основа для более сложных
конструкций
*/
int s21_simple_sum(s21_decimal val1, s21_decimal val2, s21_decimal *result) {
  int overbit = 0;  //бит который запоминаем, если нужно после сложения 1 в
                    //"уме" сохранить
  for (int i = 0; i < 96; i++) {
    if (s21_check_bit(&val1, i) == 1 && s21_check_bit(&val2, i) == 1 &&
        overbit == 0) {
      s21_set_bit(result, i, 0);
      overbit = 1;
    } else if (s21_check_bit(&val1, i) == 1 && s21_check_bit(&val2, i) == 1 &&
               overbit == 1) {
      s21_set_bit(result, i, 1);
      overbit = 1;
    } else if (((s21_check_bit(&val1, i) == 1 &&
                 s21_check_bit(&val2, i) == 0) ||
                (s21_check_bit(&val1, i) == 0 &&
                 s21_check_bit(&val2, i) == 1)) &&
               overbit == 0) {
      s21_set_bit(result, i, 1);
      overbit = 0;
    } else if (((s21_check_bit(&val1, i) == 1 &&
                 s21_check_bit(&val2, i) == 0) ||
                (s21_check_bit(&val1, i) == 0 &&
                 s21_check_bit(&val2, i) == 1)) &&
               overbit == 1) {
      s21_set_bit(result, i, 0);
      overbit = 1;
    } else if (s21_check_bit(&val1, i) == 0 && s21_check_bit(&val2, i) == 0 &&
               overbit == 1) {
      s21_set_bit(result, i, 1);
      overbit = 0;
    } else if (s21_check_bit(&val1, i) == 0 && s21_check_bit(&val2, i) == 0 &&
               overbit == 0) {
      s21_set_bit(result, i, 0);
      overbit = 0;
    }
  }
  return 0;
}

/*
Функция s21_simple_sub корректно вычитает из числа a, число b, резльтат
записывает в число с. Принимает на вход неотрициательные децималы. Нет проверки
на переполнение числа, предполагается, что сумма чисел заведомо меньше 96 бит.
Все тесты проходит успешно - релиз
Основа для более сложных конструкций
*/
void s21_simple_sub(s21_decimal a, s21_decimal b, s21_decimal *result) {
  int overbit_counter = 0;
  int this_bit_must_be_zero = 0;

  for (int i = 0; i < 96; i++) {
    int b_a = s21_check_bit(&a, i);
    int b_b = s21_check_bit(&b, i);

    if (i != 0 && this_bit_must_be_zero == i) b_a = 0;

    if (b_a == 1 && b_b == 1) {
      s21_set_bit(result, i, 0);
    } else if (b_a == 1 && b_b == 0) {
      s21_set_bit(result, i, 1);
    } else if (b_a == 0 &&
               b_b == 1) {  //если из 0 вычитаем 1, то двигаем влево, ищем 1
      if (overbit_counter == 0) {
        while (s21_check_bit(&a, ++overbit_counter + i) != 1)
          ;
        this_bit_must_be_zero =
            i + overbit_counter--;  //номер бита у которого мы заняли единицу,
                                    //теперь он 0
        s21_set_bit(result, i, 1);
      } else {
        overbit_counter--;
        s21_set_bit(result, i, 0);
      }
    } else if (b_a == 0 && b_b == 0 && overbit_counter != 0) {
      overbit_counter--;
      s21_set_bit(result, i, 1);
    }
  }
}

/*
Функция s21_simple_div корректно делит число a, на число b, резльтат записывает
в число с. Принимает на вход неотрициательные децималы. Нет проверки на
переполнение числа, предполагается, что сумма чисел заведомо меньше 96 бит. Все
тесты проходит успешно - релиз Основа для более сложных конструкций
*/
void s21_simple_div(s21_decimal a, s21_decimal b, s21_decimal *result) {
  s21_decimal intermediate_result, tmp_a, S;
  s21_initDecimal(&intermediate_result);
  s21_initDecimal(&tmp_a);
  s21_initDecimal(&S);
  s21_copy_decimal(&tmp_a, a);
  int counter_to_break = 0;

  while (s21_simple_less_or_equal(b, tmp_a) == 1) {
    s21_copy_decimal(&intermediate_result, b);
    int q = s21_getQ(tmp_a, b);
    s21_left_shift(&intermediate_result, q);

    s21_decimal tmp_tmp_a;
    s21_initDecimal(&tmp_tmp_a);                             // -
    s21_simple_sub(tmp_a, intermediate_result, &tmp_tmp_a);  // -
    s21_copy_decimal(&tmp_a, tmp_tmp_a);  // - вычитаем из А промежуточный
                                          // результат и сохраняем его в А

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
}

void s21_simple_mul(s21_decimal a, s21_decimal b, s21_decimal *c) {
  s21_initDecimal(c);
  for (int i = 0; i < 96; i++) {
    if (s21_check_bit(&a, i) == 1) {
      s21_decimal tmp_c;
      s21_initDecimal(&tmp_c);
      s21_copy_decimal(&tmp_c, *c);
      s21_decimal tmp_b;
      s21_initDecimal(&tmp_b);
      s21_copy_decimal(&tmp_b, b);
      s21_left_shift(&tmp_b, i);
      s21_simple_sum(tmp_c, tmp_b, c);
    }
  }
}

// void s21_printBin(int x) {
//   for (int i = 31; i >= 0; i--) {
//     printf("%d", (x >> i) & 1);
//     if (i % 8 == 0)
//       printf(" ");
//   }
//   printf("\n");
// }

// void s21_print_decimal(s21_decimal decimal) {
//   for (int i = 127; i >= 96; i--) {
//     printf("%d", (decimal.bits[3] >> i) & 1);
//     if (i % 32 == 0)
//       printf(" ");
//   }

//   for (int i = 95; i >= 64; i--) {
//     printf("%d", (decimal.bits[2] >> i) & 1);
//     if (i % 32 == 0)
//       printf(" ");
//   }

//   for (int i = 63; i >= 32; i--) {
//     printf("%d", (decimal.bits[1] >> i) & 1);
//     if (i % 32 == 0)
//       printf(" ");
//   }

//   for (int i = 31; i >= 0; i--) {
//     printf("%d", (decimal.bits[0] >> i) & 1);
//     if (i % 32 == 0)
//       printf(" ");
//   }
// }

int s21_initDecimal(s21_decimal *dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }
  return 0;
}

// unsigned long long s21_from_decimal_to_ull(s21_decimal res) {
//   unsigned long long needed_number = 0;
//   for (int i = 95; i >= 0; i--) {
//     needed_number += s21_check_bit(&res, i) * pow(2, i);
//   }
//   return needed_number;
// }

void s21_left_shift(s21_decimal *dst, int shift) {
  for (int i = 0; i < shift; i++) {
    int bits_32 = s21_check_bit(dst, 31);
    int bits_64 = s21_check_bit(dst, 63);
    int bits_95 = s21_check_bit(dst, 95);
    int bits_96 = s21_check_bit(dst, 96);
    dst->bits[0] <<= 1;
    dst->bits[1] <<= 1;
    dst->bits[2] <<= 1;
    if (bits_32) s21_set_bit(dst, 32, 1);
    if (bits_64) s21_set_bit(dst, 64, 1);
    if (bits_95) s21_set_bit(dst, 96, 1);
    if (bits_96) s21_set_bit(dst, 97, 1);
  }
}

void s21_right_shift(s21_decimal *dst, int shift) {
  for (int i = 0; i < shift; i++) {
    int bits_32 = s21_check_bit(dst, 32);
    int bits_64 = s21_check_bit(dst, 64);
    dst->bits[0] >>= 1;
    dst->bits[1] >>= 1;
    dst->bits[2] >>= 1;
    if (bits_32) s21_set_bit(dst, 31, 1);
    if (bits_64) s21_set_bit(dst, 63, 1);
  }
}

int s21_getQ(s21_decimal a, s21_decimal b) {
  int q = 0;
  for (int i = 0; i < 97; i++) {
    s21_decimal tmp_b = b;
    s21_left_shift(&tmp_b, i);
    if (s21_simple_less_or_equal(tmp_b, a) == 0) break;
    q = i;
  }
  return q;
}

int s21_getFNAC(s21_decimal value) {  // get First Number After Comma
  s21_decimal result, devider, tmp_result, multiplied_result;
  s21_initDecimal(&devider);
  s21_initDecimal(&tmp_result);
  s21_initDecimal(&result);
  s21_initDecimal(&multiplied_result);
  devider.bits[0] = 10;
  int fnac = 0;
  if (s21_check_scale(&value) == 0) {
    fnac = 0;
  } else if (s21_check_scale(&value) == 1) {
    s21_simple_div(value, devider, &tmp_result);
    s21_simple_mul(tmp_result, devider, &result);
    s21_simple_sub(value, result, &tmp_result);
    fnac = tmp_result.bits[0];
  } else {
    s21_copy_decimal(&result, value);

    for (int i = 0; i < s21_check_scale(&value); i++) {
      s21_simple_div(result, devider, &tmp_result);
      s21_copy_decimal(&result, tmp_result);
    }

    for (int i = 0; i < s21_check_scale(&value); i++) {
      s21_simple_mul(tmp_result, devider, &multiplied_result);
      s21_copy_decimal(&tmp_result, multiplied_result);
    }

    s21_simple_sub(value, multiplied_result, &tmp_result);

    for (int i = 0; i < s21_check_scale(&value) - 1; i++) {
      s21_simple_div(tmp_result, devider, &result);
      s21_copy_decimal(&tmp_result, result);
    }
    fnac = result.bits[0];
  }
  return fnac;
}

//ВСПОМОГАТЕЛЬНЫЕ АРСЕНА

int getBit(s21_decimal value, int position) {
  int movement = 1 << (position % 32);
  return (value.bits[position / 32] & movement) >> (position % 32);
}

int getSign(s21_decimal value) { return getBit(value, 127); }

int setBit(s21_decimal *value, int position, int bit) {
  if (bit)
    value->bits[position / 32] |= (1 << (position % 32));
  else
    value->bits[position / 32] &= ~(1 << (position % 32));
  return 0;
}

s21_decimal_extended convertToExtended(s21_decimal value) {
  s21_decimal_extended ext;
  for (int i = 0; i < 3; i++) ext.bits[i] = value.bits[i] & MAXBITS;
  for (int i = 3; i < 7; i++) ext.bits[i] = 0;
  ext.scale = getScale(value);
  return ext;
}

void setScale(s21_decimal *value, int scale) {
  value->bits[3] |= scale << 16 & SCALE;
}

s21_decimal convertFromExtended(s21_decimal_extended value) {
  s21_decimal a = {0};
  for (int i = 0; i < 3; i++) a.bits[i] = value.bits[i] & MAXBITS;
  setScale(&a, value.scale);
  return a;
}

int getOverflow(s21_decimal_extended *value) {
  uint64_t overflow = 0;
  for (int i = 0; i < 7; i++) {
    value->bits[i] += overflow;
    overflow = value->bits[i] >> 32;
    value->bits[i] &= MAXBITS;
  }
  if (overflow != 0) overflow = 1;
  return overflow;
}

int commaShiftLeft(s21_decimal_extended *value) {
  int flag = 0;
  s21_decimal_extended tmp = *value;
  for (int i = 0; i < 7; i++) tmp.bits[i] *= 10;
  if (getOverflow(&tmp)) {
    flag = 1;
  }
  tmp.scale++;
  if (flag)
    ;
  else
    *value = tmp;
  return flag;
}

int commaShiftRight(s21_decimal_extended *value) {
  long int rest = 0;
  for (int i = 6; i >= 0; i--) {
    value->bits[i] += rest << 32;
    rest = value->bits[i] % 10;
    value->bits[i] /= 10;
  }
  value->scale--;
  return rest;
}

int getScale(s21_decimal value) { return (value.bits[3] & SCALE) >> 16; }

int normalization(s21_decimal_extended *value) {
  int flag = 0, last_rest = 0, existanceOfRest = 0;
  for (int i = 3; i < 7; i++)
    while (value->bits[i] != 0 && value->scale > 0)
      if ((last_rest = commaShiftRight(value))) existanceOfRest++;
  if (value->scale > 28)
    while (value->scale != 28)
      if ((last_rest = commaShiftRight(value))) existanceOfRest++;
  if (last_rest > 5) {
    value->bits[0] += 1;
    getOverflow(value);
  } else if (last_rest < 5 && last_rest != 0)
    ;
  else if (last_rest == 5 && existanceOfRest > 1) {
    value->bits[0] += 1;
    getOverflow(value);
  } else if (last_rest == 5 && existanceOfRest == 1) {
    if ((value->bits[0] % 10) % 2 != 0) {
      value->bits[0] += 1;
      getOverflow(value);
    }
  }
  if (value->scale == 0 && value->bits[3] != 0)
    flag = 1;
  else if (value->scale == 28 && value->bits[0] == 0 && value->bits[1] == 0 &&
           value->bits[2] == 0)
    flag = 2;
  return flag;
}

void bringToACommonDenominator(s21_decimal_extended *value1,
                               s21_decimal_extended *value2) {
  int flag = 0;
  int cnt = 0;
  if (value1->scale < value2->scale) {
    for (int i = 0; value1->scale != value2->scale; i++, cnt++)
      if ((flag = commaShiftLeft(value1))) break;
  } else if (value1->scale > value2->scale) {
    for (int i = 0; value2->scale != value1->scale; i++, cnt++)
      if ((flag = commaShiftLeft(value2))) break;
  }
  getOverflow(value1);
  getOverflow(value2);
}

int ItIsZero(s21_decimal value) {
  int flag = 1;
  for (int i = 0; i < 96; i++)
    if (getBit(value, i) != 0) flag = 0;
  return flag;
}

void swapDecimalExt(s21_decimal_extended *value1,
                    s21_decimal_extended *value2) {
  s21_decimal_extended tmp;
  tmp = *value1;
  *value1 = *value2;
  *value2 = tmp;
}

void zeroingOut(s21_decimal *value) {
  for (int i = 0; i < 4; i++) value->bits[i] = 0;
}

int isLessExt(s21_decimal_extended value1, s21_decimal_extended value2) {
  int flag = 0;
  for (int i = 6; i >= 0; i--) {
    if (value1.bits[i] < value2.bits[i]) {
      flag = 1;
      break;
    } else if (value1.bits[i] > value2.bits[i]) {
      flag = 0;
      break;
    }
  }

  if (flag)
    if (equalExt(value1, value2)) flag = 0;
  return flag;
}

int equalExt(s21_decimal_extended ext1, s21_decimal_extended ext2) {
  int flag = 1;
  for (int i = 6; i >= 0; i--)
    if (ext1.bits[i] != ext2.bits[i]) flag = 0;
  return flag;
}
