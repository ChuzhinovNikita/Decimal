#ifndef DECIMAL_H
#define DECIMAL_H

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DECIMAL_MAX_VALUE 79228162514264337593543950335
#define DECIMAL_MIN_VALUE -79228162514264337593543950335
#define BITS_MAX_VALUE 0xFFFFFFFF
#define DECIMAL_PRECISION 28
#define TRUE 1
#define FALSE 0
#define SIGN 0x80000000
#define ERROR (-1)

enum returns { OK, INF, NEGATIVE_INF, DIVISION_BY_ZERO, CONVERSION_ERROR };
enum converts { SUCCESS, CONVERTING_ERROR };


typedef struct decimal {
    unsigned bits[4];
} decimal;

typedef struct {
  unsigned int b_bits[8];
} big_decimal;

int add(decimal value_1, decimal value_2, decimal *result);
int sub(decimal value_1, decimal value_2, decimal *result);
int mul(decimal value_1, decimal value_2, decimal *result);
int dec_div(decimal value_1, decimal value_2, decimal *result);

int is_less(decimal value_1, decimal value_2);
int is_less_or_equal(decimal value_1, decimal value_2);
int is_greater(decimal value_1, decimal value_2);
int is_greater_or_equal(decimal value_1, decimal value_2);
int is_equal(decimal value_1, decimal value_2);
int is_not_equal(decimal value_1, decimal value_2);

int from_int_to_decimal(int src, decimal *dst);
int from_float_to_decimal(float src, decimal *dst);
int from_decimal_to_int(decimal src, int *dst);
int from_decimal_to_float(decimal src, float *dst);

int dec_floor(decimal value, decimal *result);
int dec_round(decimal value, decimal *result);
int truncate(decimal value, decimal *result);
int negate(decimal value, decimal *result);

int is_zero(decimal value);
void null_decimal(decimal *decimal);
int get_sign(const decimal *value);
void set_sign(decimal *num, int sign);
int get_scale(const decimal *value);
void set_scale(decimal *value, int scale);
int get_bit(decimal num, int bit);
void set_bit(decimal *varPtr, int bit, int value);
int last_bit(decimal number);
void clear_bits(decimal *val);
void bits_copy(decimal src, decimal *dest);
void shift_right(decimal *num, int shift);
int shift_left(decimal *value, int offset);
int normalize(decimal *numDec1, decimal *numDec2);
int correct_last_bits(decimal value);

int b_get_bit(const big_decimal value, int bit);
void b_set_bit(big_decimal *varPtr, int bit, int value);
int b_shift_left(big_decimal *value, int offset);
int b_last_bit(big_decimal number);
int b_multiplication_by_10(big_decimal *dst);
void b_null_decimal(big_decimal *decimal);
void b_shift_right(big_decimal *num, int shift);
int b_is_zero(big_decimal value);
void removing_zeros(decimal *value);


int b_normalize(decimal numDec1, decimal numDec2, big_decimal *dec1,
                big_decimal *dec2, int *scale);
int b_add(big_decimal value_1, big_decimal value_2,
              big_decimal *result);
int b_sub(big_decimal value_1, big_decimal value_2,
              big_decimal *result);
int b_mul(big_decimal value_1, big_decimal value_2,
              big_decimal *result);
int b_div(big_decimal value_1, big_decimal value_2,
              big_decimal *result);
int remains(big_decimal c_result, big_decimal value_1,
            big_decimal value_2, big_decimal *result, int scale);
int different_signs_add(big_decimal big_value_1, big_decimal big_value_2, big_decimal *big_result, int sign_1, int sign_2, int *sign);

int multiplication_by_10(decimal *dst);
void divide_by_10(decimal *in, unsigned *rest);
void big_divide_by_10(big_decimal *in, unsigned *rest);

void convertDecimalToBid(decimal value1, big_decimal *value2);
int convertBigToDecimal(big_decimal value, decimal *result, int *scale);
int bank_round(big_decimal *value, big_decimal value2, unsigned iter, unsigned flag);

int big_divide_by_10_rest(big_decimal in);
int divide_by_10_dec(decimal in);

int b_is_greater(big_decimal dec1, big_decimal dec2);
int b_is_equal(big_decimal dec1, big_decimal dec2);

void print_decimal(decimal *dst);
void print_binry(int num); 
void b_print_decimal(big_decimal *dst);

#endif