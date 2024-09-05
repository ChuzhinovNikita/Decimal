#include "../decimal.h"


int mul(decimal value_1, decimal value_2, decimal *result) {
  decimal c_result = {0};
  big_decimal big_value_1 = {0}, big_value_2 = {0}, big_result = {0};
  int ret = OK, sign_1 = get_sign(&value_1), sign_2 = get_sign(&value_2), sign = 0;
  int scale = 0, scale_1 = get_scale(&value_1), scale_2 = get_scale(&value_2);

  if (result == NULL || ((scale_1 > 28 || scale_1 < 0) || (scale_2 > 28 || scale_2 < 0))){
    ret = 4;
  }else if (correct_last_bits(value_1) != 1 || correct_last_bits(value_2) != 1) {
    ret = 4;
  }else{
    null_decimal(result); 

    if(sign_1 == 1 || sign_2 == 1) sign = 1;
    if(sign_1 == 1 && sign_2 == 1) sign = 0;

    b_normalize(value_1, value_2, &big_value_1, &big_value_2, &scale);

    if(b_is_greater(big_value_2, big_value_1)){
      b_mul(big_value_2, big_value_1, &big_result);
    }else{
      b_mul(big_value_1, big_value_2, &big_result);
    }

    if (scale_1 == scale_2) scale = scale_1;

    scale *= 2; 

    ret = convertBigToDecimal(big_result, &c_result, &scale);

    if (ret == 1 && sign == 1) ret = NEGATIVE_INF;
    if (is_zero(value_1) && is_zero(value_2)) ret = OK;
    if(is_zero(value_1) || is_zero(value_2)) ret = OK;

    set_scale(&c_result, scale);
    set_sign(&c_result, sign);
    removing_zeros(&c_result);

    if(ret == OK) *result = c_result;
  }
  
  return ret;
}


int b_mul(big_decimal value_1, big_decimal value_2, big_decimal *result){
  b_null_decimal(result);

  big_decimal c_result = {0};

  for (int i = 0; i <= 255; i++) {
    if (b_get_bit(value_2, i) != 1) {
      b_shift_left(&value_1, 1);
      continue;
    }

    b_shift_left(&value_1, 1);
    b_add(c_result, value_1, &c_result);
  }

  b_shift_right(&c_result, 1);

  *result = c_result;
  
  return OK;
}