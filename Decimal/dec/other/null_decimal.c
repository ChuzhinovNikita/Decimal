#include "../decimal.h"

void null_decimal(decimal *decimal) {
  decimal->bits[0] = 0;
  decimal->bits[1] = 0;
  decimal->bits[2] = 0;
  decimal->bits[3] = 0;
}

void b_null_decimal(big_decimal *decimal) {
  decimal->b_bits[0] = 0;
  decimal->b_bits[1] = 0;
  decimal->b_bits[2] = 0;
  decimal->b_bits[3] = 0;
  decimal->b_bits[4] = 0;
  decimal->b_bits[5] = 0;
  decimal->b_bits[6] = 0;
  decimal->b_bits[7] = 0;
}