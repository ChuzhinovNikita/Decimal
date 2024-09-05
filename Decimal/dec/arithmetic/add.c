#include "../decimal.h"


int add(decimal value_1, decimal value_2, decimal *result) {

  decimal c_res = {0};
  big_decimal big_value_1 = {0}, big_value_2 = {0}, big_result = {0};
  int ret = OK, scale_1 = get_scale(&value_1), scale_2 = get_scale(&value_2);

  if (result == NULL || ((scale_1 > 28 || scale_1 < 0) || (scale_2 > 28 || scale_2 < 0))) {
    ret = 4;
  }else if (correct_last_bits(value_1) != 1 || correct_last_bits(value_2) != 1) {
    ret = 4;
  }else {
    null_decimal(result);
    
    int sign_1 = get_sign(&value_1), sign_2 = get_sign(&value_2), sign = 0,
        scale = 0;
    b_normalize(value_1, value_2, &big_value_1, &big_value_2, &scale);
    int ret_flag = different_signs_add(big_value_1, big_value_2, &big_result,
                                       sign_1, sign_2, &sign);

    if (scale_1 == scale_2) scale = scale_1;

    ret = convertBigToDecimal(big_result, &c_res, &scale);

    if (ret == 1 && sign == 1) ret = NEGATIVE_INF;
    if (c_res.bits[2] == 0 && c_res.bits[1] == 0 && c_res.bits[0] == 0 &&
        ret == OK)
      ret = NEGATIVE_INF;
    if((!is_zero(value_1) && !is_zero(value_2)) && sign == 0 && ret == NEGATIVE_INF) ret = INF;
    if (is_zero(value_1) && is_zero(value_2)) ret = OK;
    if (ret_flag == 1) ret = OK;

    set_scale(&c_res, scale);
    set_sign(&c_res, sign);
    removing_zeros(&c_res);

    *result = c_res;
  }

  return ret;
}

int different_signs_add(big_decimal big_value_1,
                        big_decimal big_value_2,
                        big_decimal *big_result, int sign_1, int sign_2,
                        int *sign) {
  b_null_decimal(big_result);

  big_decimal c_big_result = {0};
  int ret_flag = 0;

  if (sign_1 != sign_2) {
    if (b_is_greater(big_value_1, big_value_2)) {
      b_sub(big_value_1, big_value_2, &c_big_result);

      if (sign_1 == 1) *sign = 1;
      if (sign_1 == 0) *sign = 0;
    }

    if (b_is_greater(big_value_2, big_value_1)) {
      b_sub(big_value_2, big_value_1, &c_big_result);

      if (sign_2 == 1) *sign = 1;
      if (sign_2 == 0) *sign = 0;
    }

    if (b_is_zero(c_big_result)) ret_flag = 1;
  } else {
    b_add(big_value_1, big_value_2, &c_big_result);
    *sign = sign_1;
  }

  *big_result = c_big_result;
  

  return ret_flag;
}

int b_add(big_decimal value_1, big_decimal value_2,
              big_decimal *result) {
  b_null_decimal(result);

  big_decimal c_res = {0};
  int overflow_bits = 0;

  for (int i = 0; i < 255; i++) {
    int mask_a = 1 << (i % 32), mask_b = 1 << (i % 32), num_bits = 0;

    if (i > 31 && i < 64) num_bits = 1;
    if (i > 63 && i < 96) num_bits = 2;
    if (i > 95 && i < 128) num_bits = 3;
    if (i > 127 && i < 160) num_bits = 4;
    if (i > 159 && i < 192) num_bits = 5;
    if (i > 191 && i < 224) num_bits = 6;
    if (i > 223 && i < 256) num_bits = 7;

    if (overflow_bits == 1 && b_get_bit(value_1, i) != 1) {
      value_1.b_bits[num_bits] = value_1.b_bits[num_bits] | mask_a;
      overflow_bits = 0;
    } else if (overflow_bits == 1 && b_get_bit(value_2, i) != 1) {
      value_2.b_bits[num_bits] = value_2.b_bits[num_bits] | mask_a;
      overflow_bits = 0;
    }

    if (b_get_bit(value_1, i) == 1 && b_get_bit(value_2, i) == 1 &&
        overflow_bits == 1) {
      c_res.b_bits[num_bits] = c_res.b_bits[num_bits] | mask_b;
      continue;
    }

    if (b_get_bit(value_1, i) ^ b_get_bit(value_2, i))
      c_res.b_bits[num_bits] = c_res.b_bits[num_bits] | mask_b;
    if (b_get_bit(value_1, i) == 1 && b_get_bit(value_2, i) == 1)
      overflow_bits = 1;
  }

  *result = c_res;

  return 0;
}

