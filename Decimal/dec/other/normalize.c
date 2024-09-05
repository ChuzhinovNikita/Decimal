#include "../decimal.h"

int normalize(decimal *numDec1, decimal *numDec2) {
  int exp1 = get_scale(numDec1), exp2 = get_scale(numDec2);
  int diff = exp1 - exp2, ret = OK;

  if (diff == 0){
    ret =  OK;
  }else{
      if (diff > 0) {
      for (int i = 0; i < diff; i++) multiplication_by_10(numDec2);
      set_scale(numDec2, exp1);
    } else if (diff < 0) {
      for (int i = 0; i < -diff; i++) multiplication_by_10(numDec1);
      set_scale(numDec1, exp2);
    }
  }

  return ret;
}

int b_normalize(decimal numDec1, decimal numDec2, big_decimal *dec1,
                big_decimal *dec2, int *scale) {
  int exp1 = get_scale(&numDec1), exp2 = get_scale(&numDec2);
  int diff = exp1 - exp2;
  int c_exp = 0, result = OK;

  big_decimal c_dec1 = *dec1, c_dec2 = *dec2;

  convertDecimalToBid(numDec1, &c_dec1);
  convertDecimalToBid(numDec2, &c_dec2);

  if (diff > 0) {
    for (int i = 0; i < diff; i++) b_multiplication_by_10(&c_dec2);
    c_exp = exp1;
  } else if (diff < 0) {
    for (int i = 0; i < -diff; i++) b_multiplication_by_10(&c_dec1);
    c_exp = exp2;
  }

  *scale = c_exp;
  *dec1 = c_dec1;
  *dec2 = c_dec2;

  return result;
}