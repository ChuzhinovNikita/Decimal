#include "../decimal.h"

int is_equal(decimal dec1, decimal dec2) {
  int sign1 = get_sign(&dec1), sign2 = get_sign(&dec2);
  int result = TRUE, flag = 0, scale = 0;
  big_decimal b_dec1 = {0}, b_dec2 = {0};

  if (sign1 != sign2) {
    result = FALSE;
    flag = 1;
  }

  b_normalize(dec1, dec2, &b_dec1, &b_dec2, &scale);

  if (is_zero(dec1) && is_zero(dec2)) {
    result = TRUE;
    flag = 1;
  } else if ((!is_zero(dec1) || !is_zero(dec2)) && !flag) {
    for (int i = 0; i <= 7 && !flag; i++) {
      if (b_dec1.b_bits[i] != b_dec2.b_bits[i]) {
        result = FALSE;
        flag = 1;
      }
    }
  }
  return result;
}

int b_is_equal(big_decimal dec1, big_decimal dec2) {
  int result = TRUE;
  for (int i = 0; i <= 7; i++) {
    if (dec1.b_bits[i] != dec2.b_bits[i]) {
      result = FALSE;
    }
  }

  return result;
}
