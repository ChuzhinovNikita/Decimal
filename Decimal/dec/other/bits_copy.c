#include "../decimal.h"

void bits_copy(decimal src, decimal *dest) {
  dest->bits[0] = src.bits[0];
  dest->bits[1] = src.bits[1];
  dest->bits[2] = src.bits[2];
  dest->bits[3] = src.bits[3];
}