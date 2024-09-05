#include "../decimal.h"

int is_greater_or_equal(decimal dec1, decimal dec2) {
  return (is_greater(dec1, dec2) || is_equal(dec1, dec2));
}
