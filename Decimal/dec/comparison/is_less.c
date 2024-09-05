#include "../decimal.h"

int is_less(decimal dec1, decimal dec2) {
  return (is_greater(dec2, dec1));
}