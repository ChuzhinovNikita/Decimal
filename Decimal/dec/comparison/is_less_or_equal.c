#include "../decimal.h"

int is_less_or_equal(decimal dec1, decimal dec2) {
  return (is_greater(dec2, dec1) || is_equal(dec1, dec2));
}
