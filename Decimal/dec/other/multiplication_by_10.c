#include "../decimal.h"

int multiplication_by_10(decimal *dst) {
  int value = OK;
  decimal c_dst = *dst, c_dst2 = *dst, res = {0};

  if (dst != NULL) {
    shift_left(&c_dst, 3);
    shift_left(&c_dst2, 1);
    add(c_dst, c_dst2, &res);
  } else if (dst != NULL && dst == 0) {
    value = DIVISION_BY_ZERO;
  } else {
    value = CONVERSION_ERROR;
  }

  null_decimal(dst);

  *dst = res;

  return value;
}

int b_multiplication_by_10(big_decimal *dst) {
  int value = OK;
  big_decimal c_dst = *dst, c_dst2 = *dst, res = {0};

  if (dst != NULL) {
    b_shift_left(&c_dst, 3);
    b_shift_left(&c_dst2, 1);
    b_add(c_dst, c_dst2, &res);
  } else if (dst != NULL && dst == 0) {
    value = DIVISION_BY_ZERO;
  } else {
    value = CONVERSION_ERROR;
  }

  b_null_decimal(dst);

  *dst = res;

  return value;
}