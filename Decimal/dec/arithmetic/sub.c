#include "../decimal.h"

int sub(decimal value_1, decimal value_2, decimal *result) {
  decimal c_result = {0};
  big_decimal big_value_1 = {0}, big_value_2 = {0}, big_result = {0};
  int ret = OK, sign_1 = get_sign(&value_1), sign_2 = get_sign(&value_2), sign = 0;
  int scale = 0, scale_1 = get_scale(&value_1), scale_2 = get_scale(&value_2), null_flag = 0;

  if (result == NULL || ((scale_1 > 28 || scale_1 < 0) || (scale_2 > 28 || scale_2 < 0))){
    ret = 4;
  }else if (correct_last_bits(value_1) != 1 || correct_last_bits(value_2) != 1) {
    ret = 4;
  }else{
    null_decimal(result);
    b_normalize(value_1, value_2, &big_value_1, &big_value_2, &scale);  
  
    if (sign_1 != sign_2){
      b_add(big_value_1, big_value_2, &big_result);
      if(sign_1 == 1) sign = 1;
      if(sign_1 == 0) sign = 0;
    }else{
      
      if(b_is_equal(big_value_2, big_value_1)){
        b_sub(big_value_2, big_value_1, &big_result);
        sign = 0;
        null_flag = 1;
      }else if(b_is_greater(big_value_1, big_value_2)){
        b_sub(big_value_1, big_value_2, &big_result);
        sign = sign_1;
      }else if(b_is_greater(big_value_2, big_value_1)){
        b_sub(big_value_2, big_value_1, &big_result);
        sign = !sign_1;
      }
    }

    if (scale_1 == scale_2) scale = scale_1;

    ret = convertBigToDecimal(big_result, &c_result, &scale);

    if (ret == 1 && sign == 1) ret = NEGATIVE_INF;
    if (c_result.bits[2] == 0 && c_result.bits[1] == 0 && c_result.bits[0] == 0 &&
        ret == OK)
      ret = NEGATIVE_INF;
    if (is_zero(value_1) && is_zero(value_2)) ret = OK;
    if (null_flag == 1) ret = OK;
    if((!is_zero(value_1) && !is_zero(value_2)) && sign == 0 && ret == NEGATIVE_INF) ret = INF;

    set_scale(&c_result, scale);
    set_sign(&c_result, sign);
    removing_zeros(&c_result);

    *result = c_result;
  }

  return ret;
}

int b_sub(big_decimal value_1, big_decimal value_2,
              big_decimal *result) {
  b_null_decimal(result);

  big_decimal c_result = {0}, one = {0};
  one.b_bits[0] = 1;

  for (int i = 0; i <= 7; i++) value_2.b_bits[i] = ~value_2.b_bits[i];
 
  b_add(value_1, value_2, &c_result);
  b_add(c_result, one, &c_result);

  *result = c_result;

  return 0;
}