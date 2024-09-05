#include "../decimal.h"

int dec_round(decimal value, decimal *result) {
  int ret = 0;
  decimal temp = value;

  if (result == NULL) {
    ret = 1;
  }else{
    int scale = get_scale(&value);
    int sign = get_sign(&value);

    if (scale == 0) {
      *result = value;
      ret = 0;
    }else{
      unsigned remainder = 0;

      while (scale > 1) {
        divide_by_10(&temp, &remainder);
        scale--;
      }

      divide_by_10(&temp, &remainder);

      if (remainder >= 5) {
        int carry = 1;
        for (int i = 0; i < 96 && carry; i++) {
          int bit = get_bit(temp, i);
          if (bit == 0) {
            set_bit(&temp, i, 1);
            carry = 0;
          } else {
            set_bit(&temp, i, 0);
          }
        }

        if (carry) {
          ret = 2;
        }
      }
    }

    *result = temp;
    set_sign(result, sign);
    set_scale(result, 0);
  }

  return ret;
}