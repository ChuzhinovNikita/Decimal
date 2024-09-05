#include "../decimal.h"

int from_int_to_decimal(int src, decimal *dst) {
  int ret = SUCCESS;

  if (dst == NULL) {
    ret = CONVERTING_ERROR;
  }else{
    null_decimal(dst);

    if (src < 0) {
      dst->bits[3] |= SIGN;
      src = -src;
    }

    dst->bits[0] = (unsigned int)src;
  }

  return ret;
}
