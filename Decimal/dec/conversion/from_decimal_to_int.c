#include "../decimal.h"

int from_decimal_to_int(decimal src, int *dst) {
  int ret = SUCCESS;
  
  if (dst == NULL) {
    ret = CONVERTING_ERROR;
  }else{
    int scale = get_scale(&src);
    decimal temp = src;

    for (int i = 0; i < scale; i++) {
      unsigned rest = 0;
      divide_by_10(&temp, &rest);
    }

    if (temp.bits[1] != 0 || temp.bits[2] != 0) {
      ret = CONVERTING_ERROR;
    }

    if (temp.bits[0] > (unsigned)INT_MAX) {
      ret = CONVERTING_ERROR;
    }

    int sign = get_sign(&src);
    *dst = sign ? -(int)temp.bits[0] : (int)temp.bits[0];
  }

  return ret;
}