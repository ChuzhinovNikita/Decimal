#include "../decimal.h"

void convertDecimalToBid(decimal value1, big_decimal *value2) {
  value2->b_bits[0] = value1.bits[0];
  value2->b_bits[1] = value1.bits[1];
  value2->b_bits[2] = value1.bits[2];
}
