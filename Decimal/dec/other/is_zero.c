#include "../decimal.h"

int is_zero(decimal value) {
  return !value.bits[0] && !value.bits[1] && !value.bits[2];
}

int b_is_zero(big_decimal value) {
  return !value.b_bits[0] && !value.b_bits[1] && !value.b_bits[2] &&
         !value.b_bits[3] && !value.b_bits[4] && !value.b_bits[5] &&
         !value.b_bits[6] && !value.b_bits[7];
}