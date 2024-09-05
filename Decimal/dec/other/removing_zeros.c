#include "../decimal.h"

void removing_zeros(decimal *value) {
  decimal c_value = *value;
  int scale = get_scale(&c_value);

  while (scale != 0) {
    if (divide_by_10_dec(c_value) == 0) {
      unsigned b = 0;
      divide_by_10(&c_value, &b);
      scale--;
    } else {
      break;
    }
  }

  set_scale(&c_value, scale);

  *value = c_value;
}
