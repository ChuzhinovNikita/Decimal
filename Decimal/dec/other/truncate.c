#include "../decimal.h"

int truncate(decimal value, decimal *result) {
  int scale = get_scale(&value);
  int sign = get_sign(&value);

  decimal temp = value;
  unsigned remainder = 0;

  for (int i = 0; i < scale; i++) {
    divide_by_10(&temp, &remainder);
  }

  *result = temp;
  set_sign(result, sign);
  set_scale(result, 0);

  return OK;
}