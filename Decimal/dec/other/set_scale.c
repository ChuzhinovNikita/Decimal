#include "../decimal.h"

void set_scale(decimal *value, int scale) {
  int clearMask = ~(0xFF << 16);
  value->bits[3] &= clearMask;
  int mask = scale << 16;
  value->bits[3] |= mask;
}