#include "../decimal.h"

int b_shift_left(big_decimal *value, int offset) {
  int res = OK, lastbit = b_last_bit(*value);
  if (lastbit + offset > 255) {
    res = INF;
  } else {
    for (int i = 0; i < offset; i++) {
      int bit31 = b_get_bit(*value, 31), bit63 = b_get_bit(*value, 63),
          bit95 = b_get_bit(*value, 95);
      int bit127 = b_get_bit(*value, 127), bit159 = b_get_bit(*value, 159),
          bit191 = b_get_bit(*value, 191), bit223 = b_get_bit(*value, 223);

      for (int y = 0; y <= 7; y++) value->b_bits[y] <<= 1;

      if (bit31) b_set_bit(value, 32, 1);
      if (bit63) b_set_bit(value, 64, 1);
      if (bit95) b_set_bit(value, 96, 1);
      if (bit127) b_set_bit(value, 128, 1);
      if (bit159) b_set_bit(value, 160, 1);
      if (bit191) b_set_bit(value, 192, 1);
      if (bit223) b_set_bit(value, 224, 1);
    }
  }
  return res;
}