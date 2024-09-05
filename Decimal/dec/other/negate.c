#include "../decimal.h"

int negate(decimal value, decimal *result) {
  int ret = 0;
  if (result == NULL) {
    ret = 0;
  }else{
    bits_copy(value, result);

    int sign = get_sign(result);

    set_sign(result, !sign);
  }

  return ret;
}