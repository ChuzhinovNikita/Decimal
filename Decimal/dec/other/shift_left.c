#include "../decimal.h"

int shift_left(decimal *value, int offset) {
  int res = OK;
  int lastbit = last_bit(*value);
  if (lastbit + offset > 95) {
    res = INF;
  } else {
    for (int i = 0; i < offset; i++) {
      int bit31 = get_bit(*value, 31);
      int bit63 = get_bit(*value, 63);
      value->bits[0] <<= 1;
      value->bits[1] <<= 1;
      value->bits[2] <<= 1;
      
      if (bit31) set_bit(value, 32, 1);
      if (bit63) set_bit(value, 64, 1);
    }
  }

  return res;
}