#include "../decimal.h"

int from_decimal_to_float(decimal src, float *dst) {
  int ret = SUCCESS;

  if (dst == NULL) {
    ret = CONVERTING_ERROR;
  }else{
    int sign = src.bits[3] & 0x80000000;
    int scale = (src.bits[3] >> 16) & 0xFF;

    double result = 0.0;
    for (int i = 0; i < 96; i++) {
      if (get_bit(src, i)) {
        result += pow(2.0, i);
      }
    }

    while (scale > 0) {
      unsigned rest = 0;
      divide_by_10(&src, &rest);
      result /= 10.0;
      scale--;
    }

    if (sign) {
      result = -result;
    }
    *dst = (float)result;
  }

  return ret;
}