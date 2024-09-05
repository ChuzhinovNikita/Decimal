#include "../decimal.h"

int convertBigToDecimal(big_decimal value, decimal *result,
                        int *scale) {
  int res = OK, overflow = 0, exp = *scale;
  decimal c_res = {0};
  big_decimal c_value = value;

  if ((value.b_bits[3] != 0 || value.b_bits[4] != 0 || value.b_bits[5] != 0 ||
       value.b_bits[6] != 0 || value.b_bits[7] != 0) &&
      exp == 0)
    res = INF;
  
  if ((value.b_bits[3] != 0 && exp != 0) ||  exp > 28) overflow = 1;

  if (overflow == 0 && res == OK) {
    for (int i = 0; i <= 3; i++) c_res.bits[i] = value.b_bits[i];
  } else if (overflow == 1 && res == OK) {
    unsigned a = 0, iter = 0, flag = 0; 
    while (exp != 0) {
      if (value.b_bits[3] == 0 && exp < 29) break;
      big_divide_by_10(&value, &a);
      if(a > 0) flag++;
      exp--;
      iter++;
    }

    if(flag) flag -= 1;
 
    bank_round(&value, c_value, iter, flag);
    if (value.b_bits[3] == 0)
      for (int i = 0; i <= 2; i++) c_res.bits[i] = value.b_bits[i];
  }
  
  if(is_zero(c_res)) res = INF;
  if(overflow == 1 && b_is_zero(value)) res = NEGATIVE_INF;

  set_scale(&c_res, exp);

  *result = c_res;
  *scale = exp;

  return res;
}

int bank_round(big_decimal *value, big_decimal value2, unsigned iter, unsigned flag) {
  big_decimal c_value = *value, one = {0};
  one.b_bits[0] = 1;
  unsigned a = 0, b = 0;

  for (unsigned i = 0; i < iter; i++) big_divide_by_10(&value2, &a);

  b = big_divide_by_10_rest(c_value);
 
  if(a == 5 && flag > 0) a += 1; 

  if (a == 5) {
    if (b % 2 != 0) b_add(c_value, one, &c_value);
  } else if (a > 5) {
    b_add(c_value, one, &c_value);
  }

  *value = c_value;

  return 0;
}
