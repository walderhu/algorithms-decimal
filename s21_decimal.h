#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINUS 0x80000000
#define SCALE 0x00ff0000
#define MAXBITS 0xffffffff
#define MAXBITSEXT 0xffffffffffffffff

#define S21_NUM_WORDS 4
#define CONVERT_ERROR 1
#define CONVERSION_SUCCESS 0
#define CONVERSION_OVERFLOW 1
#define CONVERSION_UNDERFLOW 2

enum state { FALSE = 0, TRUE = 1 };
enum errors { OK = 0, ERROR = 1 };
enum arithmetic_errors { S21_INF = 1, S21_NEG_INF = 2, S21_NAN = 3 };

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  uint64_t bits[7];
  short scale;
} s21_decimal_extended;

// Другие
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);

// Арифметика
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Конвертация
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Сравнение
int s21_is_less(s21_decimal, s21_decimal);              // <
int s21_is_less_or_equal(s21_decimal, s21_decimal);     // <=
int s21_is_greater(s21_decimal, s21_decimal);           // >
int s21_is_greater_or_equal(s21_decimal, s21_decimal);  // >
int s21_is_equal(s21_decimal, s21_decimal);             // ==
int s21_is_not_equal(s21_decimal, s21_decimal);         //!=

// Функции из Helpers
int s21_check_bit(s21_decimal *value, int position);
int s21_check_sign(s21_decimal *value);
int s21_check_scale(s21_decimal *value);
void s21_set_bit(s21_decimal *value, int position, int bit);
void s21_set_sign(s21_decimal *value, int sign);
void s21_set_scale(s21_decimal *value, int scale);
int s21_is_zero(s21_decimal *value);
void s21_copy_decimal(s21_decimal *destination, s21_decimal value);
void s21_normalize(s21_decimal *value_1, s21_decimal *value_2);

// Вспомогательные GreyBaca
int s21_initDecimal(s21_decimal *dst);
int s21_simple_less_or_equal(s21_decimal val1, s21_decimal val2);
int s21_simple_sum(s21_decimal val1, s21_decimal val2, s21_decimal *result);
void s21_simple_sub(s21_decimal a, s21_decimal b, s21_decimal *result);
void s21_simple_div(s21_decimal a, s21_decimal b, s21_decimal *result);
void s21_left_shift(s21_decimal *dst, int shift);
void s21_right_shift(s21_decimal *dst, int shift);
void s21_printBin(int x);
void s21_print_decimal(s21_decimal decimal);
unsigned long long s21_from_decimal_to_ull(s21_decimal res);
int s21_getQ(s21_decimal a, s21_decimal b);
int s21_getFNAC(s21_decimal value);
int round_string(char str[14]);

//Вспомогательные Арсена
int isLessExt(s21_decimal_extended value1, s21_decimal_extended value2);
int getBit(s21_decimal value, int position);
int getSign(s21_decimal value);
int setBit(s21_decimal *value, int position, int bit);
s21_decimal_extended convertToExtended(s21_decimal value);
s21_decimal convertFromExtended(s21_decimal_extended value);
int getOverflow(s21_decimal_extended *value);
int commaShiftLeft(s21_decimal_extended *value);
int commaShiftRight(s21_decimal_extended *value);
int getScale(s21_decimal value);
void setScale(s21_decimal *value, int scale);
int normalization(s21_decimal_extended *value);
void printInBits(s21_decimal value);
int getBitExtended(s21_decimal_extended, int position);
void printInBitsExtended(s21_decimal_extended value);
void bringToACommonDenominator(s21_decimal_extended *value1,
                               s21_decimal_extended *value2);
int ItIsZero(s21_decimal value);
void swapDecimalExt(s21_decimal_extended *value1, s21_decimal_extended *value2);
void zeroingOut(s21_decimal *value);
int checkForZero(s21_decimal value1, s21_decimal value2, s21_decimal *result);
int equalExt(s21_decimal_extended ext1, s21_decimal_extended ext2);

#endif  // S21_DECIMAL_H
