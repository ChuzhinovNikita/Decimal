#include "../decimal.h"

int is_greater(decimal dec1, decimal dec2) {
  int sign1 = get_sign(&dec1), sign2 = get_sign(&dec2), result = TRUE, flag = 0;
  int scale = 0, neg_flag = 0;
  big_decimal b_dec1 = {0}, b_dec2 = {0};

  if(sign1 == 1 && sign2 == 1) neg_flag = 1;

  if (is_zero(dec1) && is_zero(dec2)) {
    result = FALSE;
  } else if (sign1 != sign2) {
    if (sign1 == 1) result = FALSE;
    if (sign1 < sign2) flag = 1;
  }

  if(is_equal(dec1, dec2)) result = FALSE;

  b_normalize(dec1, dec2, &b_dec1, &b_dec2, &scale);


  if (result == TRUE && flag == 0) {
    for(int i = 255; i >= 0; i--){
      int a = b_dec1.b_bits[i / 32];
      int b = b_dec2.b_bits[i / 32];
      if (a == b) continue;
      int bit1 = b_get_bit(b_dec1, i);
      int bit2 = b_get_bit(b_dec2, i);
      if (bit1 != bit2){
        if(!neg_flag) result = bit1; else result = bit2;
        break;
      }
    }
      
    result = (result == -1) ? 0 : result;
  }

  return result;
}

int b_is_greater(big_decimal dec1, big_decimal dec2) {
  int result = TRUE;

  for(int i = 255; i >= 0; i--){
    int a = dec1.b_bits[i / 32];
    int b = dec2.b_bits[i / 32];
    if (a == b) continue;
    int bit1 = b_get_bit(dec1, i);
    int bit2 = b_get_bit(dec2, i);
    if (bit1 != bit2){
      result = bit1;
      break;
    }
  }
      
  result = (result == -1) ? 0 : result;
  
  return result;
}