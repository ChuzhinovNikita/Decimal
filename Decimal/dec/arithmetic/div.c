#include "../decimal.h"


int dec_div(decimal value_1, decimal value_2, decimal *result) {
  decimal c_result = {0};
  int ret = OK, scale = 0, rem = 0, scale_rem = 0, sign_1 = get_sign(&value_1), sign_2 = get_sign(&value_2), sign = 0;
  int scale_1 = get_scale(&value_1), scale_2 = get_scale(&value_2);
  big_decimal big_value_1 = {0}, big_value_2 = {0}, big_result = {0}, result_rem = {0};

  if (result == NULL || ((scale_1 > 28 || scale_1 < 0) || (scale_2 > 28 || scale_2 < 0))){
    ret = 4;
  }else if (correct_last_bits(value_1) != 1 || correct_last_bits(value_2) != 1) {
    ret = 4;
  }else if(is_zero(value_2)){
    ret = 3;
  }else{
    decimal c_value_1 = value_1;

    if(sign_1 != sign_2) sign = 1; else sign = 0;

    null_decimal(result); 
    b_normalize(value_1, value_2, &big_value_1, &big_value_2, &scale);
    rem = b_div(big_value_1, big_value_2, &big_result);
    scale = 0;
    
    if(rem) scale_rem = remains(big_result, big_value_1, big_value_2, &result_rem, scale);
 
    scale = scale_rem;

    for(int i = scale_rem; i > 0; i--) b_multiplication_by_10(&big_result);
    
    b_add(big_result, result_rem, &big_result);
    ret = convertBigToDecimal(big_result, &c_result, &scale);

    if (ret == 1 && sign == 1) ret = NEGATIVE_INF;
    if (is_zero(value_1)) ret = OK;
    if(!is_zero(c_value_1) && is_zero(value_1) && is_zero(c_result)) ret = NEGATIVE_INF;

    set_scale(&c_result, scale);
    set_sign(&c_result, sign);

    *result = c_result;
  }

  return ret;
}




int b_div(big_decimal value_1, big_decimal value_2, big_decimal *result){
  b_null_decimal(result);

  big_decimal c_result = {0}, sub = value_1;
  int bit_value_2 = 0, bit_value_1 = 0, rem = 0;

  for(int i = 0; i < 256; i++) if(b_get_bit(value_2, i) == 1) bit_value_2 = i;
  for(int i = 0; i < 256; i++) if(b_get_bit(value_1, i) == 1) bit_value_1 = i;
  
  int i = bit_value_1 - bit_value_2, flag = 0;

  for(int y = i; y > 0; y--) b_shift_right(&sub, 1);
  
  while (1){
    if(i < 0) break;
    if(b_is_greater(sub, value_2) || b_is_equal(sub, value_2)){
      b_shift_left(&c_result, 1);
      b_set_bit(&c_result, 0, 1);
      b_sub(sub, value_2, &sub);
      flag = 1;
    }else{
      i--;
      if(flag == 0) b_shift_left(&c_result, 1); else flag = 0;
      b_shift_left(&sub, 1);
      b_set_bit(&sub, 0, b_get_bit(value_1, i));
    }
  }
  
  if(sub.b_bits[0] == 5) rem = 5;
  if(!b_is_zero(sub)) rem = 1;
  if(b_is_greater(value_2, value_1)) rem = 1;
  if(b_is_zero(value_1)) rem = 0;

  *result = c_result;

  return rem;
}

int remains(big_decimal c_result ,big_decimal value_1, big_decimal value_2, big_decimal *result, int scale){
  big_decimal src = {0}, c_res = {0};
  int scale_rem = 0, rem = 1;

  while (rem != 0){
    if(scale + scale_rem == 40) break;
    b_mul(c_result, value_2, &src);
    b_sub(value_1, src, &src);
    b_multiplication_by_10(&src);
    value_1 = src;
    rem = b_div(src, value_2, &src);

    if(!b_is_zero(c_res)){
      b_multiplication_by_10(&c_res);
      b_add(c_res, src, &c_res);
    }else c_res = src;
    
    c_result = src;
    b_null_decimal(&src);
    scale_rem++;
  }

  *result = c_res;

  return scale_rem;
}