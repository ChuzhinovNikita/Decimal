#include "decimal.h"

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEC powf(2.0f, 96.0f) - 1.0

Suite *test_arithmetic(void);
Suite *test_comparison(void);
Suite *test_converters(void);
Suite *test_other(void);

float dec_rand_r(float a, float b);
void dec_zero_decimal(decimal *dst);


//------------------------------------------------------------------------add

START_TEST(add_0) {
  decimal val1 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{2, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, add(val1, val2, &res));
}
END_TEST

START_TEST(add_1) {
  decimal val1 = {{15, 0, 0, 0}};
  decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(0, add(val1, val2, &res));
}
END_TEST

START_TEST(add_2) {
  decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  decimal val2 = {{1, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(1, add(val1, val2, &res));
}
END_TEST

START_TEST(add_3) {
  decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(2, add(val1, val2, &res));
}
END_TEST

START_TEST(add_4) {
  decimal val1 = {{8, 0, 0, 0}};
  decimal val2 = {{2, 0, 0, 0}};
  decimal res;
  ck_assert_int_eq(0, add(val1, val2, &res));
}
END_TEST

START_TEST(add_5) {
  decimal val1 = {{2, 0, 0, 0}};
  decimal val2 = {{8, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, add(val1, val2, &res));
}
END_TEST

START_TEST(add_6) {
  decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{2, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, add(val1, val2, &res));
}
END_TEST

START_TEST(add_7) {
  decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{8, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, add(val1, val2, &res));
}
END_TEST

START_TEST(add_8) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, add(val1, val2, &res));
}
END_TEST

START_TEST(add_9) {
  decimal val1 = {{4, 0, 0, 0}};
  decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {0};
  ck_assert_int_eq(0, add(val1, val2, &res));
}
END_TEST

START_TEST(add_10) {
  decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, add(val1, val2, &res));
}
END_TEST

START_TEST(add_11) {
  decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  decimal val2 = {{4, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, add(val1, val2, &res));
}
END_TEST

START_TEST(add_12) {
  decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(2, add(val1, val2, &res));
}
END_TEST

START_TEST(add_13) {
  decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(0, add(val1, val2, &res));
}
END_TEST

START_TEST(add_14) {
  decimal val1 = {{4, 0, 0, 0}};
  decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(0, add(val1, val2, &res));
}
END_TEST

START_TEST(add_15) {
  decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, add(val1, val2, &res));
}
END_TEST

START_TEST(add_16) {
  decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(2, add(val1, val2, &res));
}
END_TEST

START_TEST(add_17) {
  decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_scale(&val1, 5);
  set_scale(&val2, 3);
  decimal res = {{0}};
  ck_assert_int_eq(0, add(val1, val2, &res));
}
END_TEST

START_TEST(add_18) {
  decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  set_scale(&val1, 5);
  set_scale(&val2, 3);
  decimal res = {{0}};
  ck_assert_int_eq(0, add(val1, val2, &res));
}
END_TEST

START_TEST(add_19) {
  float a = dec_rand_r(-10e8, 10e8);
  float b = dec_rand_r(-10e8, 10e8);
  float c = 0;

  decimal _a = {{0, 0, 0, 0}};
  decimal _b = {{0, 0, 0, 0}};
  decimal res = {{0, 0, 0, 0}};

  from_float_to_decimal(a, &_a);
  from_float_to_decimal(b, &_b);
  add(_a, _b, &res);
  from_decimal_to_float(res, &c);

  ck_assert_float_eq_tol(a + b, c, 10e2);
}
END_TEST

START_TEST(add_test_1) {
  int num1 = 42;
  int num2 = 30;
  int sum_int = 72;
  decimal a = {{0}};
  decimal b = {{0}};
  from_int_to_decimal(num1, &a);
  from_int_to_decimal(num2, &b);
  decimal res_dec = {0};
  int res_int = 0;
  add(a, b, &res_dec);
  from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
  ck_assert_int_eq(add(a, b, &res_dec), 0);
}
END_TEST

START_TEST(add_test_2) {
  int num1 = 1000;
  int num2 = 2000;
  int sum_int = 3000;
  decimal a = {{0}};
  decimal b = {{0}};
  from_int_to_decimal(num1, &a);
  from_int_to_decimal(num2, &b);
  decimal res_dec = {0};
  int res_int = 0;
  add(a, b, &res_dec);
  from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(add_test_3) {
  int num1 = 0;
  int num2 = 0;
  int sum_int = 0;
  decimal a = {{0}};
  decimal b = {{0}};
  from_int_to_decimal(num1, &a);
  from_int_to_decimal(num2, &b);
  decimal res_dec = {0};
  int res_int = 0;
  add(a, b, &res_dec);
  from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(add_test_4) {
  int num1 = -15;
  int num2 = 5;
  int sum_int = -10;
  decimal a = {{0}};
  decimal b = {{0}};
  from_int_to_decimal(num1, &a);
  from_int_to_decimal(num2, &b);
  decimal res_dec = {0};
  int res_int = 0;
  add(a, b, &res_dec);
  from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(add_test_5) {
  int num1 = 11115;
  int num2 = 5;
  int sum_int = 11120;
  decimal a = {{0}};
  decimal b = {{0}};
  from_int_to_decimal(num1, &a);
  from_int_to_decimal(num2, &b);
  decimal res_dec = {0};
  int res_int = 0;
  add(a, b, &res_dec);
  from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(add_test_6) {
  int num1 = -1;
  int num2 = -10;
  int sum_int = -11;
  decimal a = {{0}};
  decimal b = {{0}};
  from_int_to_decimal(num1, &a);
  from_int_to_decimal(num2, &b);
  decimal res_dec = {0};
  int res_int = 0;
  add(a, b, &res_dec);
  from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(add_test_7) {
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  int a = -1234;
  int b = 234;
  int res_origin = -1000;
  from_int_to_decimal(a, &src1);
  from_int_to_decimal(b, &src2);
  decimal res_dec = {0};
  int res_int = 0;
  add(src1, src2, &res_dec);
  from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(add_test_8) {
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  int a = -9403;
  int b = 234;
  int res_origin = -9169;
  from_int_to_decimal(a, &src1);
  from_int_to_decimal(b, &src2);
  decimal res_dec = {0};
  int res_int = 0;
  add(src1, src2, &res_dec);
  from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(add_test_9) {
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  int a = 9403;
  int b = 202;
  int res_origin = 9605;
  from_int_to_decimal(a, &src1);
  from_int_to_decimal(b, &src2);
  decimal res_dec = {0};
  int res_int = 0;
  add(src1, src2, &res_dec);
  from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(add_test_10) {
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  int a = 450;
  int b = -50;
  int res_origin = 400;
  from_int_to_decimal(a, &src1);
  from_int_to_decimal(b, &src2);
  decimal res_dec = {0};
  int res_int = 0;
  add(src1, src2, &res_dec);
  from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(add_test_11) {
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  float num1 = 7.25;
  float num2 = 9.5;
  float res_origin = 16.75;
  from_float_to_decimal(num1, &src1);
  from_float_to_decimal(num2, &src2);
  decimal res_dec = {0};
  float res_float = 0.0;
  add(src1, src2, &res_dec);
  from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_12) {
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  int num1 = -1234;
  float num2 = 1.234;
  float res_origin = -1232.766;
  from_int_to_decimal(num1, &src1);
  from_float_to_decimal(num2, &src2);
  decimal res_dec = {0};
  float res_float = 0.0;
  add(src1, src2, &res_dec);
  from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_13) {
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  int num1 = -1234;
  float num2 = -1.234;
  float res_origin = -1235.234;
  from_int_to_decimal(num1, &src1);
  from_float_to_decimal(num2, &src2);
  decimal res_dec = {0};
  float res_float = 0.0;
  add(src1, src2, &res_dec);
  from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_14) {
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  float num1 = -94;
  float num2 = 0.002340;
  float res_origin = 0;
  res_origin = num1 + num2;
  from_float_to_decimal(num1, &src1);
  from_float_to_decimal(num2, &src2);
  decimal res_dec = {0};
  float res_float = 0.0;
  add(src1, src2, &res_dec);
  from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq_tol(res_float, res_origin, 1e-4);
}
END_TEST

START_TEST(add_test_15) {
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  float num1 = -940.3;
  float num2 = 0.000234;
  float res_origin = -940.299766;
  from_float_to_decimal(num1, &src1);
  from_float_to_decimal(num2, &src2);
  decimal res_dec = {0};
  float res_float = 0.0;
  add(src1, src2, &res_dec);
  from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq_tol(res_float, res_origin, 1e-3);
}
END_TEST

START_TEST(add_test_16) {
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  float num1 = -0.9403;
  float num2 = 0.000234;
  float res_origin = -0.940066;
  from_float_to_decimal(num1, &src1);
  from_float_to_decimal(num2, &src2);
  decimal res_dec = {0};
  float res_float = 0.0;
  add(src1, src2, &res_dec);
  from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_18) {
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  float num1 = -0.9403;
  float num2 = -112.0234;
  float res_origin = -112.9637;
  from_float_to_decimal(num1, &src1);
  from_float_to_decimal(num2, &src2);
  decimal res_dec = {0};
  float res_float = 0.0;
  add(src1, src2, &res_dec);
  from_decimal_to_float(res_dec, &res_float);

  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_19) {
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  float num1 = -0.94e03;
  float num2 = -112.0234;
  float res_origin = -1052.0234;
  from_float_to_decimal(num1, &src1);
  from_float_to_decimal(num2, &src2);
  decimal res_dec = {0};
  float res_float = 0.0;
  add(src1, src2, &res_dec);
  from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_20) {
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  float num1 = -0.94e03;
  float num2 = -112.0e2;
  float res_origin = -12140;
  from_float_to_decimal(num1, &src1);
  from_float_to_decimal(num2, &src2);
  decimal res_dec = {0};
  float res_float = 0.0;
  add(src1, src2, &res_dec);
  from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_test_21) {
  decimal dec1 = {{0}};
  decimal dec2 = {{0}};
  int tmp1 = 100;
  int tmp2 = 99999;
  int res_s21 = 0;
  int res = 100099;
  decimal res1 = {{0}};
  from_int_to_decimal(tmp1, &dec1);
  from_int_to_decimal(tmp2, &dec2);
  add(dec1, dec2, &res1);
  from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(add_test_22) {
  decimal dec1 = {{0}};
  decimal dec2 = {{0}};
  int tmp1 = -100;
  int tmp2 = -99999;
  int res_s21 = 0;
  int res = -100099;
  decimal res1 = {{0}};
  from_int_to_decimal(tmp1, &dec1);
  from_int_to_decimal(tmp2, &dec2);
  add(dec1, dec2, &res1);
  from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(add_test_23) {
  decimal dec1 = {{0}};
  decimal dec2 = {{0}};
  int tmp1 = 2147483647;
  int tmp2 = -2147483647;
  int res_s21 = 0;
  int res = 0;
  decimal res1 = {{0}};
  from_int_to_decimal(tmp1, &dec1);
  from_int_to_decimal(tmp2, &dec2);
  add(dec1, dec2, &res1);
  from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST


START_TEST(add_test_25) {
  decimal dec1 = {{0}};
  decimal dec2 = {{0}};
  int tmp1 = -2147483647;
  int tmp2 = 2147483647;
  int res_s21 = 0;
  int res = 0;
  decimal res1 = {{0}};
  from_int_to_decimal(tmp1, &dec1);
  from_int_to_decimal(tmp2, &dec2);
  add(dec1, dec2, &res1);
  from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(add_test_26) {
  unsigned tmp1 = 4294967295;
  decimal dec1 = {{tmp1, tmp1, tmp1, 0}};
  decimal dec2 = {{1, 0, 0, 0}};
  decimal res1 = {{0}};

  int ret_s21 = add(dec1, dec2, &res1);

  ck_assert_int_eq(1, ret_s21);
}
END_TEST

START_TEST(add_test_27) {
  unsigned tmp1 = 4294967295;
  float tmp2 = pow(2, 31);
  decimal dec1 = {{tmp1, tmp1, tmp1, tmp2}};
  decimal dec2 = {{1, 0, 0, tmp2}};
  decimal res1 = {{0}};
  int ret_s21 = add(dec1, dec2, &res1);
  ck_assert_int_eq(2, ret_s21);
}
END_TEST

START_TEST(add_test_28) {
  float float_a = -8.218750;
  float float_b = 6.843750;

  float float_res = 0;
  float_res = float_a + float_b;

  decimal expected = {0};
  from_float_to_decimal(float_res, &expected);

  decimal dec_a = {0};
  from_float_to_decimal(float_a, &dec_a);
  decimal dec_b = {0};
  from_float_to_decimal(float_b, &dec_b);

  decimal result = {0};
  int code = add(dec_a, dec_b, &result);

  float got_float = 0;
  from_decimal_to_float(result, &got_float);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, float_res, 1e-06);
}
END_TEST

START_TEST(add_test_29) {
  decimal src1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  decimal src2 = {0};
  float a = 0.01448;
  from_float_to_decimal(a, &src2);
  decimal res_dec = {0};
  add(src1, src2, &res_dec);
  ck_assert_int_eq(add(src1, src2, &res_dec), 0);
}
END_TEST

START_TEST(add_test_30) {
  decimal src1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(INT_MAX)}};
  decimal src2 = {0};
  float a = -0.01448;
  from_float_to_decimal(a, &src2);
  decimal res_dec = {0};
  add(src1, src2, &res_dec);
  ck_assert_int_eq(add(src1, src2, &res_dec), 0);
}
END_TEST

START_TEST(test_decimal_add_0) {
  decimal c = {{5, 0, 0, 0}};
  decimal d = {{5, 0, 0, 0}};
  decimal etalon = {{10, 0, 0, 0}};
  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;
  // 0 - OK 1 - число слишком велико или равно бесконечности
  // 2 - число слишком мало или равно отрицательной бесконечности
  // 3 - деление на 0
  int res_add = add(c, d, p_res);
  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(res_add, 0);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_1) {
  decimal c = {{100, 0, 0, 0}};
  decimal d = {{100, 0, 0, 0}};
  decimal etalon = {{100, 0, 0, 0}};
  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;
  // 0 - OK 1 - число слишком велико или равно бесконечности
  // 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  int equal = is_equal(res, etalon);
  ck_assert_int_eq(res_add, 0);
  ck_assert_int_eq(equal, 0);
}
END_TEST

START_TEST(test_decimal_add_2) {
  decimal c = {{2147483647, 0, 0, 0}};
  decimal d = {{2147483647, 0, 0, 0}};
  decimal etalon = {{4294967294, 0, 0, 0}};
  decimal result = {{0, 0, 0, 0}};
  decimal* p_result = &result;
  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_result);
  ck_assert_int_eq(res_add, 0);
  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  int equal = is_equal(result, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_3) {
  decimal c = {{1000, 0, 0, 0}};
  decimal d = {{1000, 0, 0, 0}};
  decimal etalon = {{2000, 0, 0, 0}};
  decimal result = {{0, 0, 0, 0}};
  decimal* p_result = &result;
  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_result);
  ck_assert_int_eq(res_add, 0);
  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  int equal = is_equal(result, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_4) {
  decimal c = {{1000, 0, 0, ~(INT_MAX)}};
  decimal d = {{1000, 0, 0, 0}};
  decimal etalon = {{0, 0, 0, 0}};
  decimal result = {{0, 0, 0, 0}};
  decimal* p_result = &result;
  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_result);
  ck_assert_int_eq(res_add, 0);
  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  int equal = is_equal(result, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_5) {
  decimal c = {{1, 0, 0, ~(INT_MAX)}};
  decimal d = {{1, 0, 0, ~(INT_MAX)}};
  decimal etalon = {{2, 0, 0, ~(INT_MAX)}};
  decimal result = {{0, 0, 0, 0}};
  decimal* p_result = &result;
  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_result);
  ck_assert_int_eq(res_add, 0);
  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  int equal = is_equal(*p_result, etalon);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_6) {
  decimal c = {{0, 0, 0, 0}};
  decimal d = {{0, 0, 0, 0}};
  decimal etalon = {{0, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_7) {
  decimal c = {{1, 0, 0, 0}};
  decimal d = {{1, 0, 0, 0}};
  decimal etalon = {{2, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_8) {
  decimal c = {{1000, 0, 0, 0}};
  decimal d = {{1000, 0, 0, 0}};
  decimal etalon = {{2000, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_8_1) {
  decimal c = {{INT_MAX, 0, 0, 0}};
  decimal d = {{INT_MAX, 0, 0, 0}};
  decimal etalon = {{4294967294, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_9) {
  decimal c = {{INT_MAX, 0, 0, 0}};
  decimal d = {{INT_MAX, 0, 0, 0}};
  decimal etalon = {{UINT32_MAX - 1, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_10) {
  decimal c = {{UINT32_MAX, 0, 0, 0}};
  decimal d = {{1, 0, 0, 0}};
  decimal etalon = {{0, 1, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  ck_assert_int_eq(res.bits[3], etalon.bits[3]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[0], etalon.bits[0]);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_11) {
  decimal c = {{0, UINT_MAX - 1, 0, 0}};
  decimal d = {{0, 1, 0, 0}};
  decimal etalon = {{0, UINT_MAX, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_12) {
  decimal c = {{0, 0, UINT_MAX - 1, 0}};
  decimal d = {{0, 0, 1, 0}};
  decimal etalon = {{0, 0, UINT_MAX, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_13) {
  decimal c = {{0, 0, 0, ~(INT_MAX)}};
  decimal d = {{0, 0, 0, ~(INT_MAX)}};
  decimal etalon = {{0, 0, 0, ~(INT_MAX)}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_14) {
  decimal c = {{1, 0, 0, ~(INT_MAX)}};
  decimal d = {{1, 0, 0, 0}};
  decimal etalon = {{0, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_15) {  // -1 + (-1) = -2
  decimal c = {{1, 0, 0, ~(INT_MAX)}};
  decimal d = {{1, 0, 0, ~(INT_MAX)}};
  decimal etalon = {{2, 0, 0, ~(INT_MAX)}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  ck_assert_int_eq(res.bits[3], etalon.bits[3]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[0], etalon.bits[0]);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_16) {
  decimal c = {{11, 0, 0, 65536}};
  decimal d = {{0, 0, 0, 0}};
  decimal etalon = {{11, 0, 0, 65536}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_17) {
  decimal c = {{11, 0, 0, 65536}};
  decimal d = {{1, 0, 0, 0}};
  decimal etalon = {{21, 0, 0, 65536}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_18) {
  decimal c = {{111, 0, 0, 65536}};
  decimal d = {{1, 0, 0, 0}};
  decimal etalon = {{121, 0, 0, 65536}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_19) {
  decimal c = {{111, 0, 0, 196608}};
  decimal d = {{1, 0, 0, 0}};
  decimal etalon = {{1111, 0, 0, 196608}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_20) {
  decimal c = {0};
  c.bits[0] = 0b11111111111111111111111111111110;
  c.bits[1] = 0b00000000000000000000000000000000;
  c.bits[2] = 0b00000000000000000000000000000000;
  c.bits[3] = 0b00000000000000000000000000000000;
  decimal d = {{1, 0, 0, 0}};
  decimal etalon = {0};
  etalon.bits[0] = 0b11111111111111111111111111111111;
  etalon.bits[1] = 0b00000000000000000000000000000000;
  etalon.bits[2] = 0b00000000000000000000000000000000;
  etalon.bits[3] = 0b00000000000000000000000000000000;
  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_21) {
  decimal c = {{UINT32_MAX - 1, UINT32_MAX, 0, 0}};
  decimal d = {{1, 0, 0, 0}};
  decimal etalon = {{UINT32_MAX, UINT32_MAX, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_25) {
  decimal c = {{0b00000000000000000001100101111001, 0, 0, 0}};
  decimal d = {{0b00000000000000010010000110001001, 0, 0, 0}};
  decimal etalon = {{0b00000000000000010011101100000010, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_26) {
  decimal c = {{0b10001001111001111111111111111111,
                    0b10001010110001110010001100000100, 0, 0}};
  decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
  decimal etalon = {{0b10001001111010000000000000000000,
                         0b10001010110001110010001100000100, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_27) {
  decimal c = {{UINT_MAX, UINT_MAX, 0, 0}};
  decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
  decimal etalon = {{0, 0, 1, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_28) {
  decimal c = {
      {0b10000010111000100101101011101101, 0b11111001111010000010010110101101,
       0b10110000001111101111000010010100, 0b10000000000011100000000000000000}};
  decimal d = {{0b00000011010000001001011100101110, 0, 0, 0}};
  decimal etalon = {
      {0b01110001001010101101101011101101, 0b00101110001111001110000111111000,
       0b10110000001111101110111101101101, 0b10000000000011100000000000000000}};
  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_30) {
  decimal src1, src2, origin;
  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  origin.bits[0] = 0b01001110111001000011100101110110;
  origin.bits[1] = 0b01001011001101011010000111011001;
  origin.bits[2] = 0b00011001101110010111010010111111;
  origin.bits[3] = 0b00000000000011110000000000000000;

  decimal result = {{0, 0, 0, 0}};
  decimal* p_res = &result;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(src1, src2, p_res);
  ck_assert_int_eq(res_add, 0);

  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);

  int equal = is_equal(
      result, origin);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_0) {
  decimal c = {{0, 0, 0, 0}};
  decimal d = {{0, 0, 0, 0}};
  decimal etalon = {{0, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_1) {
  decimal c = {{1, 0, 0, 0}};
  decimal d = {{1, 0, 0, 0}};
  decimal etalon = {{2, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_2) {
  decimal c = {{1000, 0, 0, 0}};
  decimal d = {{1000, 0, 0, 0}};
  decimal etalon = {{2000, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_3) {
  decimal c = {{INT_MAX, 0, 0, 0}};
  decimal d = {{INT_MAX, 0, 0, 0}};
  decimal etalon = {{4294967294, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_4) {
  decimal c = {{INT_MAX, 0, 0, 0}};
  decimal d = {{INT_MAX, 0, 0, 0}};
  decimal etalon = {{UINT32_MAX - 1, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_5) {
  decimal c = {{UINT_MAX, 0, 0, 0}};
  decimal d = {{1, 0, 0, 0}};
  decimal etalon = {{0, 1, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  ck_assert_int_eq(res.bits[3], etalon.bits[3]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[0], etalon.bits[0]);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_6) {
  decimal c = {{0, UINT_MAX - 1, 0, 0}};
  decimal d = {{0, 1, 0, 0}};
  decimal etalon = {{0, UINT_MAX, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_7) {
  decimal c = {{0, 0, UINT_MAX - 1, 0}};
  decimal d = {{0, 0, 1, 0}};
  decimal etalon = {{0, 0, UINT_MAX, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_8) {
  decimal c = {{0, 0, 0, ~(INT_MAX)}};
  decimal d = {{0, 0, 0, ~(INT_MAX)}};
  decimal etalon = {{0, 0, 0, ~(INT_MAX)}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_9) {
  decimal c = {{1, 0, 0, 0b10000000000000000000000000000000}};
  decimal d = {{1, 0, 0, 0}};
  decimal etalon = {{0, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_10) {  // -1 + (-1) = -2
  decimal c = {{1, 0, 0, ~(INT_MAX)}};
  decimal d = {{1, 0, 0, ~(INT_MAX)}};
  decimal etalon = {{2, 0, 0, ~(INT_MAX)}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_11) {
  decimal c = {{11, 0, 0, 65536}};
  decimal d = {{0, 0, 0, 0}};
  decimal etalon = {{11, 0, 0, 65536}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_12) {
  decimal c = {{11, 0, 0, 65536}};
  decimal d = {{1, 0, 0, 0}};
  decimal etalon = {{21, 0, 0, 65536}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_13) {
  decimal c = {{111, 0, 0, 65536}};
  decimal d = {{1, 0, 0, 0}};
  decimal etalon = {{121, 0, 0, 65536}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_14) {
  decimal c = {{111, 0, 0, 196608}};
  decimal d = {{1, 0, 0, 0}};
  decimal etalon = {{1111, 0, 0, 196608}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);
  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_20) {
  decimal c = {{0b00000000000000000001100101111001, 0, 0, 0}};
  decimal d = {{0b00000000000000010010000110001001, 0, 0, 0}};
  decimal etalon = {{0b00000000000000010011101100000010, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_21) {
  decimal c = {{0b10001001111001111111111111111111,
                    0b10001010110001110010001100000100, 0, 0}};
  decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
  decimal etalon = {{0b10001001111010000000000000000000,
                         0b10001010110001110010001100000100, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_22) {
  decimal c = {{UINT_MAX, UINT_MAX, 0, 0}};
  decimal d = {{0b00000000000000000000000000000001, 0, 0, 0}};
  decimal etalon = {{0, 0, 1, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_add_simple_23) {
  decimal c = {
      {0b10000010111000100101101011101101, 0b11111001111010000010010110101101,
       0b10110000001111101111000010010100, 0b10000000000011100000000000000000}};
  decimal d = {{0b00000011010000001001011100101110, 0, 0, 0}};
  decimal etalon = {
      {0b01110001001010101101101011101101, 0b00101110001111001110000111111000,
       0b10110000001111101110111101101101, 0b10000000000011100000000000000000}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  int res_add = add(c, d, p_res);
  ck_assert_int_eq(res_add, 0);

  ck_assert_int_eq(res.bits[0], etalon.bits[0]);
  ck_assert_int_eq(res.bits[1], etalon.bits[1]);
  ck_assert_int_eq(res.bits[2], etalon.bits[2]);
  ck_assert_int_eq(res.bits[3], etalon.bits[3]);

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int equal =
      is_equal(res, etalon);  // Возвращаемое значение: 0 - FALSE 1 - TRUE
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(add_max_31) {
  decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  decimal s21_res = {0};
  ck_assert_int_eq(add(src1, src2, &s21_res), 0);
}
END_TEST


START_TEST(add_max_33) {
  decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal s21_res = {0};
  ck_assert_int_eq(add(src1, src2, &s21_res), 1);
}
END_TEST



//------------------------------------------------------------------------sub

START_TEST(sub_0) {
  decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{2, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_1) {
  decimal val1 = {{2, 0, 0, 0}};
  decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal res;
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_2) {
  decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_3) {
  decimal val1 = {{2, 0, 0, 0}};
  decimal val2 = {{2, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_4) {
  decimal val1 = {{8, 0, 0, 0}};
  decimal val2 = {{2, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_5) {
  decimal val1 = {{2, 0, 0, 0}};
  decimal val2 = {{8, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_6) {
  decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{2, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_7) {
  decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{8, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_8) {
  decimal val1 = {{2, 0, 0, 0}};
  decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_9) {
  decimal val1 = {{8, 0, 0, 0}};
  decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_10) {
  decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_11) {
  decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  decimal val2 = {{4, 0, 0, 0}};
  decimal res = {{0}};

  ck_assert_int_eq(2, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_12) {
  decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  decimal val2 = {{4, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_13) {
  decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_14) {
  decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(2, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_15) {
  decimal val1 = {{4, 0, 0, 0}};
  decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_16) {
  decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_17) {
  decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(1, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_18) {
  decimal val1 = {{4, 0, 0, 0}};
  decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(1, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_19) {
  decimal val1 = {{4, 0, 0, 0}};
  decimal val2 = {{4, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_20) {
  decimal dec1 = {{0}};
  decimal dec2 = {{0}};
  int tmp1 = 100;
  int tmp2 = 99999;
  int res_s21 = 0;
  int res = -99899;
  decimal res1 = {{0}};
  from_int_to_decimal(tmp1, &dec1);
  from_int_to_decimal(tmp2, &dec2);
  sub(dec1, dec2, &res1);
  from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(sub_21) {
  decimal dec1 = {{0}};
  decimal dec2 = {{0}};
  int tmp1 = -100;
  int tmp2 = -99999;
  int res_s21 = 0;
  decimal res1 = {{0}};
  int res = 99899;
  from_int_to_decimal(tmp1, &dec1);
  from_int_to_decimal(tmp2, &dec2);
  sub(dec1, dec2, &res1);
  from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(sub_22) {
  decimal value_1 = {{13, 0, 0, 0}};
  set_scale(&value_1, 1);
  set_bit(&value_1, 127, 1);
  decimal value_2 = {{286, 0, 0, 0}};
  set_scale(&value_2, 2);
  set_bit(&value_2, 127, 1);
  decimal result = {0};
  decimal check = {{156, 0, 0, 0}};
  set_scale(&check, 2);
  int return_value = sub(value_1, value_2, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(sub_23) {
  decimal value_1 = {{13, 0, 0, 0}};
  set_scale(&value_1, 1);
  set_bit(&value_1, 127, 1);
  decimal value_2 = {{286, 0, 0, 0}};
  set_scale(&value_2, 2);
  decimal result = {0};
  decimal check = {{416, 0, 0, 0}};
  set_scale(&check, 2);
  set_bit(&check, 127, 1);
  int return_value = sub(value_1, value_2, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(sub_24) {
  decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_bit(&value_1, 127, 1);
  decimal value_2 = {{2, 0, 0, 0}};
  decimal result = {0};
  decimal check = {{0, 0, 0, 0}};
  int return_value = sub(value_1, value_2, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(sub_25) {
  decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_bit(&value_1, 127, 1);
  decimal value_2 = {{2, 0, 0, 0}};
  set_bit(&value_2, 127, 1);
  decimal result = {0};
  decimal check = {{0, 0, 0, 0}};
  int return_value = add(value_1, value_2, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(sub_26) {
  decimal value_1 = {{64071, 0, 0, 0}};
  set_scale(&value_1, 4);
  decimal value_2 = {{5919, 0, 0, 0}};
  set_scale(&value_2, 1);
  decimal result = {0};
  decimal check = {{5854929, 0, 0, 0}};
  set_scale(&check, 4);
  set_bit(&check, 127, 1);
  int return_value = sub(value_1, value_2, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(sub_27) {
  decimal src1 = {0}, src2 = {0};
  float a = -9403;
  float b = 202.098;
  float res_our_dec = 0.0;
  from_float_to_decimal(a, &src1);
  from_float_to_decimal(b, &src2);
  float res_origin = a - b;
  decimal res_od = {0};
  sub(src1, src2, &res_od);
  from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(sub_28) {
  decimal src1 = {0}, src2 = {0};
  src1.bits[3] = 0b00000000000000010000000000000000;
  src1.bits[2] = 0;
  src1.bits[1] = 0;
  src1.bits[0] = 0b00000000000000000110011011110000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  src2.bits[2] = 0;
  src2.bits[1] = 0;
  src2.bits[0] = 0b00000000000001000101000111010110;
  decimal result_origin = {0};
  result_origin.bits[3] = 0b00000000000000110000000000000000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b00000000001000111110001111101010;
  decimal result_our = {0};
  sub(src1, src2, &result_our);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST

START_TEST(subTest1) {
  // 863
  decimal src1, src2, origin;
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest2) {
  // 889
  decimal src1, src2, origin;
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest3) {
  // 915
  decimal src1, src2, origin;
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest4) {
  // 941
  decimal src1, src2, origin;
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest5) {
  // 967
  decimal src1, src2, origin;
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest6) {
  // 993
  decimal src1, src2, origin;
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest7) {
  // 1019
  decimal src1, src2, origin;
  // src1 = 6521;
  // src2 = 74121;

  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000010000100000010000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest8) {
  // 1045
  decimal src1, src2, origin;
  // src1 = 4;
  // src2 = 97623323;

  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b00000101110100011001110100010111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest9) {
  // 1071
  decimal src1, src2, origin;
  // src1 = 65658654;
  // src2 = 5;

  src1.bits[0] = 100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 95;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 5;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest10) {
  // 1097
  decimal src1, src2, origin;
  // src1 = -364748;
  // src2 = 1;

  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000001011001000011001101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest11) {
  // 1123
  decimal src1, src2, origin;
  // src1 = 1;
  // src2 = 98745654321;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b11111101101100110001110000110000;
  origin.bits[1] = 0b00000000000000000000000000010110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest12) {
  // 1149
  decimal src1, src2, origin;
  // src1 = -9878798789;
  // src2 = -3;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b01001100110100101000000111000010;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest13) {
  // 1175
  decimal src1, src2, origin;
  // src1 = 9999999999999999999;
  // src2 = 1;

  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b10001001111001111111111111111110;
  origin.bits[1] = 0b10001010110001110010001100000100;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest14) {
  // 1201
  decimal src1, src2, origin;
  // src1 = 18446744073709551615;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b11111111111111111111111111111110;
  origin.bits[1] = 0b11111111111111111111111111111111;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST



START_TEST(subTest18) {
  // 1305
  decimal src1, src2, origin;
  // src1 = 7961327845421.879754123131254;
  // src2 = 0;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b01001110111001000011100101110110;
  origin.bits[1] = 0b01001011001101011010000111011001;
  origin.bits[2] = 0b00011001101110010111010010111111;
  origin.bits[3] = 0b00000000000011110000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest23) {
  // 1435
  decimal src1 = {0};
  decimal src2 = {0};
  decimal origin = {0};
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;

  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST



START_TEST(subTest26) {
  // 1513
  decimal src1, src2, origin;
  // src1 = 792281625142643375935439503;
  // src2 = -1;

  src1.bits[0] = 0b00101000111101011100001010001111;
  src1.bits[1] = 0b11110101110000101000111101011100;
  src1.bits[2] = 0b00000010100011110101110000101000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b00101000111101011100001010010000;
  origin.bits[1] = 0b11110101110000101000111101011100;
  origin.bits[2] = 0b00000010100011110101110000101000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest27) {
  // 1539
  decimal src1, src2, origin;
  // src1 = 7922816251427554395;
  // src2 = 65645646;

  src1.bits[0] = 0b01011111000010000000010001011011;
  src1.bits[1] = 0b01101101111100110111111101100111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000011111010011010110001001110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b01011011000111100101100000001101;
  origin.bits[1] = 0b01101101111100110111111101100111;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest28) {
  // 1565
  decimal src1, src2, origin;
  // src1 = 665464545;
  // src2 = 8798232189789785;

  src1.bits[0] = 0b00100111101010100010111011100001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00010000010100101110011001011001;
  src2.bits[1] = 0b00000000000111110100000111110010;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b11101000101010001011011101111000;
  origin.bits[1] = 0b00000000000111110100000111110001;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest29) {
  // 1591
  decimal src1, src2, origin;
  // src1 = 2.7986531268974139743;
  // src2 = 9.979623121254565121244554;

  src1.bits[0] = 0b11111110100100001101100101011111;
  src1.bits[1] = 0b10000100011001000010000111101000;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;

  src2.bits[0] = 0b11010100101011100011110110001010;
  src2.bits[1] = 0b01110100000101000010011110100011;
  src2.bits[2] = 0b00000000000010000100000101000100;
  src2.bits[3] = 0b00000000000110000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b00001110111111111010100000101010;
  origin.bits[1] = 0b00101001110101100000001000110100;
  origin.bits[2] = 0b00000000000001011111000010100001;
  origin.bits[3] = 0b10000000000110000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest30) {
  // 1617
  decimal src1, src2, origin;
  // src1 = -9798956154578676.797564534156;
  // src2 = -2156878451.854764;

  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] = 0b00011111101010011000000110101101;
  src1.bits[3] = 0b10000000000011000000000000000000;

  src2.bits[0] = 0b01100101111100100100110110101100;
  src2.bits[1] = 0b00000000000001111010100110101011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000001100000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b11010010100100100111101010001100;
  origin.bits[1] = 0b10011110100111100111000100000100;
  origin.bits[2] = 0b00011111101010011000000100111000;
  origin.bits[3] = 0b10000000000011000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(subTest31) {
  // 1643
  decimal src1, src2, origin;
  // src1 = 0.5456465465486476846545465485;
  // src2 = 0.68985125146545154;

  src1.bits[0] = 0b00001011000011110111000010001101;
  src1.bits[1] = 0b10010110101100000101100101010001;
  src1.bits[2] = 0b00010001101000010111101110000001;
  src1.bits[3] = 0b00000000000111000000000000000000;

  src2.bits[0] = 0b00010111001001010100110000000010;
  src2.bits[1] = 0b00000000111101010001010110011011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000100010000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b01011010101111100101111101110011;
  origin.bits[1] = 0b00101101001111010011000001101000;
  origin.bits[2] = 0b00000100101010001101010101010111;
  origin.bits[3] = 0b10000000000111000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST
START_TEST(subTest33) {
  // 1695
  decimal src1, src2, origin;
  // src1 = -7922816251426433759354395033;
  // src2 = 1;

  src1.bits[0] = 0b10011001100110011001100110011001;
  src1.bits[1] = 0b10011001100110011001100110011001;
  src1.bits[2] = 0b00011001100110011001100110011001;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  sub(src1, src2, &result);

  origin.bits[0] = 0b10011001100110011001100110011010;
  origin.bits[1] = 0b10011001100110011001100110011001;
  origin.bits[2] = 0b00011001100110011001100110011001;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_decimal_sub_simple_0) {  // 10 -5 =5
  decimal c = {{10, 0, 0, 0}};
  decimal d = {{5, 0, 0, 0}};
  decimal etalon = {{5, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int add = sub(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = is_equal(res, etalon);  // Возвращаемое значение: 0 - 0 1 - 1
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_sub_simple_1) {  // 100 -5 !=5
  decimal c = {{100, 0, 0, 0}};
  decimal d = {{5, 0, 0, 0}};
  decimal etalon = {{5, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int add = sub(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = is_equal(res, etalon);  // Возвращаемое значение: 0 - 0 1 - 1
  ck_assert_int_eq(equal, 0);  // *
}
END_TEST

START_TEST(test_decimal_sub_simple_2) {  // INT_MAX -5 = 2147483642
  decimal c = {{INT_MAX, 0, 0, 0}};
  decimal d = {{5, 0, 0, 0}};
  decimal etalon = {{2147483642, 0, 0, 0}};
  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int add = sub(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = is_equal(res, etalon);  // Возвращаемое значение: 0 - 0 1 - 1
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_sub_simple_3) {  // роботает только с ппервым
                                             // массивом - ложный результат
  decimal c = {{INT_MAX, INT_MAX, 0, 0}};
  decimal d = {{5, 0, 0, 0}};
  decimal etalon = {{INT_MAX - 5, INT_MAX, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int add = sub(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = is_equal(res, etalon);  // Возвращаемое значение: 0 - 0 1 - 1
  ck_assert_int_eq(equal, 1);
}

START_TEST(test_decimal_sub_simple_7) {  // 1-(-1)=2
  decimal c = {{1, 0, 0, 0}};
  decimal d = {{1, 0, 0, ~(INT_MAX)}};
  decimal etalon = {{2, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int add = sub(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = is_equal(res, etalon);  // Возвращаемое значение: 0 - 0 1 - 1
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_sub_simple_8) {  // -1-(-1)=0
  decimal c = {{1, 0, 0, ~(INT_MAX)}};
  decimal d = {{1, 0, 0, ~(INT_MAX)}};
  decimal etalon = {{0, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int add = sub(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = is_equal(res, etalon);  // Возвращаемое значение: 0 - 0 1 - 1
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_sub_simple_10) {  // 1-(-1)=2
  decimal c = {{100, 0, 0, 0}};
  decimal d = {{100, 0, 0, ~(INT_MAX)}};
  decimal etalon = {{200, 0, 0, 0}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int add = sub(c, d, p_res);
  ck_assert_int_eq(add, 0);

  int equal = is_equal(res, etalon);  // Возвращаемое значение: 0 - 0 1 - 1
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(test_decimal_sub_simple_11) {  // -1-(-1)=0
  decimal c = {{100, 0, 0, ~(INT_MAX)}};
  decimal d = {{100, 0, 0, ~(INT_MAX)}};

  decimal res = {{0, 0, 0, 0}};
  decimal* p_res = &res;

  // 0 - OK 1 - число слишком велико или равно бесконечности 2 - число слишком
  // мало или равно отрицательной бесконечности 3 - деление на 0
  int add = sub(c, d, p_res);
  ck_assert_int_eq(add, 0);
}
END_TEST

START_TEST(sub_test_12) {
  int num1 = -123;
  float num2 = 12.5;
  float dif_float = num1 - num2;
  decimal a = {0};
  decimal b = {0};
  from_int_to_decimal(num1, &a);
  from_float_to_decimal(num2, &b);
  decimal res_dec = {0};
  float res_float = 0.0;
  sub(a, b, &res_dec);
  from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, dif_float);
}
END_TEST

START_TEST(sub_test_14) {
  int num1 = 9403;
  float num2 = 202.098;
  float dif_float = 9200.902;
  decimal a = {0};
  decimal b = {0};
  from_int_to_decimal(num1, &a);
  from_float_to_decimal(num2, &b);
  decimal res_dec = {0};
  float res_float = 0.0;
  sub(a, b, &res_dec);
  from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, dif_float);
}
END_TEST

START_TEST(sub_test_16) {
  float num1 = 9403.0;
  float num2 = 2020806;
  float dif_float = num1 - num2;
  decimal a = {0};
  decimal b = {0};
  from_float_to_decimal(num1, &a);
  from_float_to_decimal(num2, &b);
  decimal res_dec = {0};
  float res_float = 0.0;
  sub(a, b, &res_dec);
  from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq_tol(res_float, dif_float, 1e-06);
}
END_TEST

START_TEST(sub_test_18) {
  float num1 = -9403.0e2;
  int num2 = -202;
  float dif_float = num1 - num2;
  decimal a = {0};
  decimal b = {0};
  from_float_to_decimal(num1, &a);
  from_int_to_decimal(num2, &b);
  decimal res_dec = {0};
  float res_float = 0.0;
  sub(a, b, &res_dec);
  from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, dif_float);
}
END_TEST

START_TEST(sub_test_20) {
  float num1 = -1.0 / 0.0;
  int num2 = 202;
  double dif_float = 0 - num2;
  decimal a = {0};
  decimal b = {0};
  from_float_to_decimal(num1, &a);
  from_int_to_decimal(num2, &b);
  decimal res_dec = {0};
  float res_float = 0.0;
  sub(a, b, &res_dec);
  from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, dif_float);
}
END_TEST

START_TEST(sub_test_21) {
  float num1 = 1.0 / 0.0;
  int num2 = 20;
  double dif_float = 0 - num2;
  decimal a = {0};
  decimal b = {0};
  from_float_to_decimal(num1, &a);
  from_int_to_decimal(num2, &b);
  decimal res_dec = {0};
  float res_float = 0.0;
  sub(a, b, &res_dec);
  from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, dif_float);
}
END_TEST

START_TEST(sub_int_22) {
  decimal dec1;
  decimal dec2;
  int tmp1 = 100;
  int tmp2 = 99999;
  int res_s21 = 0;
  int res = -99899;
  decimal res1 = {{0}};
  from_int_to_decimal(tmp1, &dec1);
  from_int_to_decimal(tmp2, &dec2);
  sub(dec1, dec2, &res1);
  from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(sub_int_23) {
  decimal dec1;
  decimal dec2;
  int tmp1 = -100;
  int tmp2 = -99999;
  int res_s21 = 0;
  int res = 99899;
  decimal res1 = {{0}};
  from_int_to_decimal(tmp1, &dec1);
  from_int_to_decimal(tmp2, &dec2);
  sub(dec1, dec2, &res1);
  from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(sub_int_24) {
  decimal dec1;
  decimal dec2;
  int tmp1 = -2147483647;
  int tmp2 = -2147483647;
  int res_s21 = 0;
  int res = 0;
  from_int_to_decimal(tmp1, &dec1);
  from_int_to_decimal(tmp2, &dec2);
  decimal res1 = {{0}};
  sub(dec1, dec2, &res1);
  from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(sub_int_25) {
  decimal dec1;
  decimal dec2;
  int tmp1 = -214748347;
  int tmp2 = 217483647;
  int res_s21 = 0;
  int res = -214748347 - 217483647;
  from_int_to_decimal(tmp1, &dec1);
  from_int_to_decimal(tmp2, &dec2);
  decimal res1 = {{0}};
  sub(dec1, dec2, &res1);
  from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(sub_int_26) {
  decimal dec1;
  decimal dec2;
  int tmp1 = 214748347;
  int tmp2 = -217483647;
  int res_s21 = 0;
  int res = 214748347 - -217483647;
  from_int_to_decimal(tmp1, &dec1);
  from_int_to_decimal(tmp2, &dec2);
  decimal res1 = {{0}};
  sub(dec1, dec2, &res1);
  from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(sub_inf_27) {
  float tmp = pow(2, 31);
  decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}};
  decimal dec2 = {{1, 0, 0, tmp}};
  decimal res1 = {{0}};
  int ret_s21 = sub(dec1, dec2, &res1);
  ck_assert_int_eq(1, ret_s21);
}
END_TEST

START_TEST(sub_neg_inf_28) {
  float tmp = pow(2, 31);
  decimal dec1 = {{4294967295, 4294967295, 4294967295, tmp}};
  decimal dec2 = {{1, 0, 0, 0}};
  decimal res1 = {{0}};
  int ret_s21 = sub(dec1, dec2, &res1);
  ck_assert_int_eq(2, ret_s21);
}
END_TEST


START_TEST(sub_max_32) {
  decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal original_res = {0};
  original_res.bits[0] = 0b11111111111111111111111111111110;
  original_res.bits[1] = 0b11111111111111111111111111111111;
  original_res.bits[2] = 0b11111111111111111111111111111111;
  original_res.bits[3] = 0b00000000000000000000000000000000;
  decimal s21_res = {0};
  sub(src1, src2, &s21_res);
  ck_assert_int_eq(sub(src1, src2, &s21_res), 0);
  ck_assert_int_eq(original_res.bits[0], s21_res.bits[0]);
  ck_assert_int_eq(original_res.bits[1], s21_res.bits[1]);
  ck_assert_int_eq(original_res.bits[2], s21_res.bits[2]);
  ck_assert_int_eq(original_res.bits[3], s21_res.bits[3]);
}
END_TEST

START_TEST(sub_max_35) {
  decimal src1 = {0};
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  decimal s21_res = {0};
  ck_assert_int_eq(sub(src1, src2, &s21_res), 2);
}
END_TEST

//------------------------------------------------------------------------mul

START_TEST(mul_0) {
  decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{2, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_1) {
  decimal val1 = {{2, 0, 0, 0}};
  decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal res;
  ck_assert_int_eq(0, mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_2) {
  decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(0, mul(val1, val2, &res));
}
END_TEST


START_TEST(mul_4) {
  decimal val1 = {{8, 0, 0, 0}};
  decimal val2 = {{2, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_5) {
  decimal val1 = {{2, 0, 0, 0}};
  decimal val2 = {{8, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_6) {
  decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{2, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_7) {
  decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{8, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_8) {
  decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};

  ck_assert_int_eq(1, mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_9) {
  decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  decimal val2 = {{2, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(2, mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_10) {
  decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  decimal val2 = {{2, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(1, mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_11) {
  decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  decimal val2 = {{0, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_12) {
  decimal value_1 = {{5, 0, 0, 0}};
  decimal value_2 = {{7, 0, 0, 0}};
  decimal result = {{0, 0, 0, 0}};
  decimal check = {{35, 0, 0, 0}};
  int return_value = mul(value_1, value_2, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST
START_TEST(mul_13) {
  decimal value_1 = {{0xFFFFFFFF, 0, 0, 0}};
  decimal value_2 = {{0xFFFFFFFF, 0, 0, 0}};
  decimal result = {{0, 0, 0, 0}};
  decimal check = {{1, 0xFFFFFFFE, 0, 0}};
  int return_value = mul(value_1, value_2, &result);

  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mul_14) {
  decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  decimal value_2 = {{2, 0, 0, 0}};
  decimal result = {{0, 0, 0, 0}};
  decimal check = {{0, 0, 0, 0}};
  int return_value = mul(value_1, value_2, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(mul_15) {
  decimal value_1 = {{123456u, 123u, 0, 0}};
  decimal value_2 = {{654321u, 654u, 0, 0}};
  set_bit(&value_2, 127, 1);
  set_scale(&value_1, 2);
  set_scale(&value_2, 3);
  decimal result = {{0, 0, 0, 0}};
  decimal check = {{0x148B6E80, 0x60187BAA, 0xC4644, 0x80030000}};
  int return_value = mul(value_1, value_2, &result);
  ck_assert_int_eq(is_equal(result, check), 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mul_16) {
  decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  decimal value_2 = {{2, 0, 0, 0}};
  set_bit(&value_2, 127, 1);
  decimal result = {{0, 0, 0, 0}};
  decimal check = {{0, 0, 0, 0}};
  int return_value = mul(value_1, value_2, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(mul_17) {
  decimal value_1 = {{17, 0, 0, 0}};
  set_bit(&value_1, 127, 1);
  decimal value_2 = {{0, 0, 0, 0}};
  decimal result = {0};
  decimal check = {{0, 0, 0, 0}};
  int return_value = mul(value_1, value_2, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(mul_18) {
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  float a = 9403.0e2;
  float b = 9403.0e2;
  float res_our_dec = 0.0;
  from_float_to_decimal(a, &src1);
  from_float_to_decimal(b, &src2);
  float res_origin = 884164090000;
  decimal res_od = {0};
  mul(src1, src2, &res_od);
  from_decimal_to_float(res_od, &res_our_dec);

  ck_assert_float_eq_tol(res_our_dec, res_origin, 1e6);
}
END_TEST

START_TEST(mul_19) {
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  int a = -32768;
  int b = 32768;
  int res_our_dec = 0;
  from_int_to_decimal(a, &src1);
  from_int_to_decimal(b, &src2);
  int res_origin = -1073741824;
  decimal res_od = {0};
  mul(src1, src2, &res_od);
  from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(mul_test_1) {
  int num1 = -10;
  int num2 = -10;
  int prod_int = 100;
  decimal a = {0};
  decimal b = {0};
  from_int_to_decimal(num1, &a);
  from_int_to_decimal(num2, &b);
  decimal res_dec = {0};
  int res_int = 0;
  mul(a, b, &res_dec);
  from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_2) {
  int num1 = 10;
  int num2 = 20;
  int prod_int = 200;
  decimal a = {0};
  decimal b = {0};
  from_int_to_decimal(num1, &a);
  from_int_to_decimal(num2, &b);
  decimal res_dec = {0};
  int res_int = 0;
  mul(a, b, &res_dec);
  from_decimal_to_int(res_dec, &res_int);

  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_3) {
  int num1 = -10;
  int num2 = 20;
  int prod_int = -200;
  decimal a = {0};
  decimal b = {0};
  from_int_to_decimal(num1, &a);
  from_int_to_decimal(num2, &b);
  decimal res_dec = {0};
  int res_int = 0;
  mul(a, b, &res_dec);
  from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(mul_test_4) {
  int num1 = 9403;
  int num2 = 202;
  int res_origin = 1899406;
  decimal a = {0};
  decimal b = {0};
  from_int_to_decimal(num1, &a);
  from_int_to_decimal(num2, &b);
  decimal res_dec = {0};
  int res_int = 0;
  mul(a, b, &res_dec);
  from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_5) {
  int num1 = -32768;
  int num2 = 2;
  int res_origin = -65536;
  decimal a = {0};
  decimal b = {0};
  from_int_to_decimal(num1, &a);
  from_int_to_decimal(num2, &b);
  decimal res_dec = {0};
  int res_int = 0;
  mul(a, b, &res_dec);
  from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_6) {
  int num1 = -32768;
  int num2 = 32768;
  int res_origin = -1073741824;
  decimal a = {0};
  decimal b = {0};
  from_int_to_decimal(num1, &a);
  from_int_to_decimal(num2, &b);
  decimal res_dec = {0};
  int res_int = 0;
  mul(a, b, &res_dec);
  from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_test_8) {
  float num1 = 9403.0e2;
  float num2 = 9403.0e2;
  float res_origin = 884164090000;
  decimal a = {0};
  decimal b = {0};
  from_float_to_decimal(num1, &a);
  from_float_to_decimal(num2, &b);
  decimal res_dec = {0};
  float res_float = 0;
  mul(a, b, &res_dec);
  from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq_tol(res_float, res_origin, 1e6);
}
END_TEST

//------------------------------------------------------------------------dec_div

START_TEST(div_0) {
  decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{2, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(0, dec_div(val1, val2, &res));
}
END_TEST

START_TEST(div_1) {
  decimal val1 = {{2, 0, 0, 0}};
  decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal res;
  ck_assert_int_eq(0, dec_div(val1, val2, &res));
}
END_TEST

START_TEST(div_2) {
  decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(0, dec_div(val1, val2, &res));
}
END_TEST

START_TEST(div_3) {
  decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal val2 = {{0, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(3, dec_div(val1, val2, &res));
}
END_TEST

START_TEST(div_4) {
  decimal val1 = {{2, 0, 0, 0}};
  decimal val2 = {{0, 0, 0, 0}};
  decimal res = {{0}};
  ck_assert_int_eq(3, dec_div(val1, val2, &res));
}
END_TEST

START_TEST(div_5) {
  decimal value_1 = {{35, 0, 0, 0}};
  decimal value_2 = {{5, 0, 0, 0}};
  decimal result = {{0, 0, 0, 0}};
  decimal check = {{70, 0, 0, 0}};
  set_scale(&value_1, 1);
  set_scale(&value_2, 2);
  int return_value = dec_div(value_1, value_2, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(div_6) {
  decimal value_1 = {{0x88888888, 0x88888888, 0x88888888, 0}};
  decimal value_2 = {{0x2, 0, 0, 0}};
  set_bit(&value_2, 127, 1);
  decimal result = {{0, 0, 0, 0}};
  decimal check = {{0x44444444, 0x44444444, 0x44444444, 0}};
  set_bit(&check, 127, 1);
  int return_value = dec_div(value_1, value_2, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(div_7) {
  decimal value_1 = {{10, 0, 0, 0}};
  set_bit(&value_1, 127, 1);
  decimal value_2 = {{8, 0, 0, 0}};
  set_bit(&value_2, 127, 1);
  decimal result = {{0, 0, 0, 0}};
  decimal check = {{125, 0, 0, 0}};
  set_scale(&check, 2);
  int return_value = dec_div(value_1, value_2, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(div_8) {
  decimal value_1 = {{15, 0, 0, 0}};
  set_bit(&value_1, 127, 1);
  decimal value_2 = {{0, 0, 0, 0}};
  decimal result = {{0, 0, 0, 0}};
  decimal check = {{0, 0, 0, 0}};
  int return_value = dec_div(value_1, value_2, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

START_TEST(div_9) {
  decimal value_1 = {{10, 0, 0, 0}};
  decimal value_2 = {{1, 0, 0, 0}};
  set_scale(&value_2, 2);
  decimal result = {{0, 0, 0, 0}};
  decimal check = {{1000u, 0, 0, 0}};
  int return_value = dec_div(value_1, value_2, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

//------------------------------------------------------------------------END

Suite* test_arithmetic(void) {
  Suite* suite = suite_create("arithmetic_suite");
  TCase* tcase = tcase_create("arithmetic_tcase");

  //------------------------------------------------------------------------add

  tcase_add_test(tcase, add_0);
  tcase_add_test(tcase, add_1);
  tcase_add_test(tcase, add_2);
  tcase_add_test(tcase, add_3);
  tcase_add_test(tcase, add_4);
  tcase_add_test(tcase, add_5);
  tcase_add_test(tcase, add_6);
  tcase_add_test(tcase, add_7);
  tcase_add_test(tcase, add_8);
  tcase_add_test(tcase, add_9);
  tcase_add_test(tcase, add_10);
  tcase_add_test(tcase, add_11);
  tcase_add_test(tcase, add_12);
  tcase_add_test(tcase, add_13);
  tcase_add_test(tcase, add_14);
  tcase_add_test(tcase, add_15);
  tcase_add_test(tcase, add_16);
  tcase_add_test(tcase, add_17);
  tcase_add_test(tcase, add_18);
  tcase_add_loop_test(tcase, add_19, 0, 100);
  tcase_add_test(tcase, add_test_1);
  tcase_add_test(tcase, add_test_2);
  tcase_add_test(tcase, add_test_3);
  tcase_add_test(tcase, add_test_4);
  tcase_add_test(tcase, add_test_5);
  tcase_add_test(tcase, add_test_6);
  tcase_add_test(tcase, add_test_7);
  tcase_add_test(tcase, add_test_8);
  tcase_add_test(tcase, add_test_9);
  tcase_add_test(tcase, add_test_10);
  tcase_add_test(tcase, add_test_11);
  tcase_add_test(tcase, add_test_12);
  tcase_add_test(tcase, add_test_13);
  tcase_add_test(tcase, add_test_14);
  tcase_add_test(tcase, add_test_15);
  tcase_add_test(tcase, add_test_16);
  tcase_add_test(tcase, add_test_18);
  tcase_add_test(tcase, add_test_19);
  tcase_add_test(tcase, add_test_20);
  tcase_add_test(tcase, test_decimal_add_0);
  tcase_add_test(tcase, test_decimal_add_1);
  tcase_add_test(tcase, test_decimal_add_2);
  tcase_add_test(tcase, test_decimal_add_3);
  tcase_add_test(tcase, test_decimal_add_4);
  tcase_add_test(tcase, test_decimal_add_5);
  tcase_add_test(tcase, test_decimal_add_6);
  tcase_add_test(tcase, test_decimal_add_7);
  tcase_add_test(tcase, test_decimal_add_8);
  tcase_add_test(tcase, test_decimal_add_8_1);
  tcase_add_test(tcase, test_decimal_add_9);
  tcase_add_test(tcase, test_decimal_add_10);
  tcase_add_test(tcase, test_decimal_add_11);
  tcase_add_test(tcase, test_decimal_add_12);
  tcase_add_test(tcase, test_decimal_add_13);
  tcase_add_test(tcase, test_decimal_add_14);
  tcase_add_test(tcase, test_decimal_add_15);
  tcase_add_test(tcase, test_decimal_add_16);
  tcase_add_test(tcase, test_decimal_add_17);
  tcase_add_test(tcase, test_decimal_add_18);
  tcase_add_test(tcase, test_decimal_add_19);
  tcase_add_test(tcase, test_decimal_add_20);
  tcase_add_test(tcase, test_decimal_add_21);
  tcase_add_test(tcase, test_decimal_add_25);
  tcase_add_test(tcase, test_decimal_add_26);
  tcase_add_test(tcase, test_decimal_add_27);
  tcase_add_test(tcase, test_decimal_add_28);
  tcase_add_test(tcase, test_decimal_add_30);
  tcase_add_test(tcase, test_decimal_add_simple_0);
  tcase_add_test(tcase, test_decimal_add_simple_1);
  tcase_add_test(tcase, test_decimal_add_simple_2);
  tcase_add_test(tcase, test_decimal_add_simple_3);
  tcase_add_test(tcase, test_decimal_add_simple_4);
  tcase_add_test(tcase, test_decimal_add_simple_5);
  tcase_add_test(tcase, test_decimal_add_simple_6);
  tcase_add_test(tcase, test_decimal_add_simple_7);
  tcase_add_test(tcase, test_decimal_add_simple_8);
  tcase_add_test(tcase, test_decimal_add_simple_9);
  tcase_add_test(tcase, test_decimal_add_simple_10);
  tcase_add_test(tcase, test_decimal_add_simple_11);
  tcase_add_test(tcase, test_decimal_add_simple_12);
  tcase_add_test(tcase, test_decimal_add_simple_13);
  tcase_add_test(tcase, test_decimal_add_simple_14);
  tcase_add_test(tcase, test_decimal_add_simple_20);
  tcase_add_test(tcase, test_decimal_add_simple_21);
  tcase_add_test(tcase, test_decimal_add_simple_22);
  tcase_add_test(tcase, test_decimal_add_simple_23);
  tcase_add_test(tcase, add_test_21);
  tcase_add_test(tcase, add_test_22);
  tcase_add_test(tcase, add_test_23);
  tcase_add_test(tcase, add_test_25);
  tcase_add_test(tcase, add_test_26);
  tcase_add_test(tcase, add_test_27);
  tcase_add_test(tcase, add_test_28);
  tcase_add_test(tcase, add_test_29);
  tcase_add_test(tcase, add_test_30);
  tcase_add_test(tcase, add_max_31);
  tcase_add_test(tcase, add_max_33);

  //------------------------------------------------------------------------sub

  tcase_add_test(tcase, sub_0);
  tcase_add_test(tcase, sub_1);
  tcase_add_test(tcase, sub_2);
  tcase_add_test(tcase, sub_3);
  tcase_add_test(tcase, sub_4);
  tcase_add_test(tcase, sub_5);
  tcase_add_test(tcase, sub_6);
  tcase_add_test(tcase, sub_7);
  tcase_add_test(tcase, sub_8);
  tcase_add_test(tcase, sub_9);
  tcase_add_test(tcase, sub_10);
  tcase_add_test(tcase, sub_11);
  tcase_add_test(tcase, sub_12);
  tcase_add_test(tcase, sub_13);
  tcase_add_test(tcase, sub_14);
  tcase_add_test(tcase, sub_15);
  tcase_add_test(tcase, sub_16);
  tcase_add_test(tcase, sub_17);
  tcase_add_test(tcase, sub_18);
  tcase_add_test(tcase, sub_19);
  tcase_add_test(tcase, sub_20);
  tcase_add_test(tcase, sub_21);
  tcase_add_test(tcase, sub_22);
  tcase_add_test(tcase, sub_23);
  tcase_add_test(tcase, sub_24);
  tcase_add_test(tcase, sub_25);
  tcase_add_test(tcase, sub_26);
  tcase_add_test(tcase, sub_27);
  tcase_add_test(tcase, sub_28);
  tcase_add_test(tcase, subTest1);
  tcase_add_test(tcase, subTest2);
  tcase_add_test(tcase, subTest3);
  tcase_add_test(tcase, subTest4);
  tcase_add_test(tcase, subTest5);
  tcase_add_test(tcase, subTest6);
  tcase_add_test(tcase, subTest7);
  tcase_add_test(tcase, subTest8);
  tcase_add_test(tcase, subTest9);
  tcase_add_test(tcase, subTest10);
  tcase_add_test(tcase, subTest11);
  tcase_add_test(tcase, subTest12);
  tcase_add_test(tcase, subTest13);
  tcase_add_test(tcase, subTest14);
  tcase_add_test(tcase, subTest18);
  tcase_add_test(tcase, subTest23);
  tcase_add_test(tcase, subTest26);
  tcase_add_test(tcase, subTest27);
  tcase_add_test(tcase, subTest28);
  tcase_add_test(tcase, subTest29);
  tcase_add_test(tcase, subTest30);
  tcase_add_test(tcase, subTest31);
  tcase_add_test(tcase, subTest33);
  tcase_add_test(tcase, test_decimal_sub_simple_0);
  tcase_add_test(tcase, test_decimal_sub_simple_1);
  tcase_add_test(tcase, test_decimal_sub_simple_2);
  tcase_add_test(tcase, test_decimal_sub_simple_3);
  tcase_add_test(tcase, test_decimal_sub_simple_7);
  tcase_add_test(tcase, test_decimal_sub_simple_8);
  tcase_add_test(tcase, test_decimal_sub_simple_10);
  tcase_add_test(tcase, test_decimal_sub_simple_11);
  tcase_add_test(tcase, sub_test_12);
  tcase_add_test(tcase, sub_test_14);
  tcase_add_test(tcase, sub_test_16);
  tcase_add_test(tcase, sub_test_18);
  tcase_add_test(tcase, sub_test_20);
  tcase_add_test(tcase, sub_test_21);
  tcase_add_test(tcase, sub_int_22);
  tcase_add_test(tcase, sub_int_23);
  tcase_add_test(tcase, sub_int_24);
  tcase_add_test(tcase, sub_int_25);
  tcase_add_test(tcase, sub_int_26);
  tcase_add_test(tcase, sub_inf_27);
  tcase_add_test(tcase, sub_neg_inf_28);
  tcase_add_test(tcase, sub_max_32);
  tcase_add_test(tcase, sub_max_35);

  //------------------------------------------------------------------------mul

  tcase_add_test(tcase, mul_0);
  tcase_add_test(tcase, mul_1);
  tcase_add_test(tcase, mul_2);
  tcase_add_test(tcase, mul_4);
  tcase_add_test(tcase, mul_5);
  tcase_add_test(tcase, mul_6);
  tcase_add_test(tcase, mul_7);
  tcase_add_test(tcase, mul_8);
  tcase_add_test(tcase, mul_9);
  tcase_add_test(tcase, mul_10);
  tcase_add_test(tcase, mul_11);
  tcase_add_test(tcase, mul_12);
  tcase_add_test(tcase, mul_13);
  tcase_add_test(tcase, mul_14);
  tcase_add_test(tcase, mul_15);
  tcase_add_test(tcase, mul_16);
  tcase_add_test(tcase, mul_17);
  tcase_add_test(tcase, mul_18);
  tcase_add_test(tcase, mul_19);
  tcase_add_test(tcase, mul_test_1);
  tcase_add_test(tcase, mul_test_2);
  tcase_add_test(tcase, mul_test_3);
  tcase_add_test(tcase, mul_test_4);
  tcase_add_test(tcase, mul_test_5);
  tcase_add_test(tcase, mul_test_6);
  tcase_add_test(tcase, mul_test_8);

  //------------------------------------------------------------------------dec_div

  tcase_add_test(tcase, div_0);
  tcase_add_test(tcase, div_1);
  tcase_add_test(tcase, div_2);
  tcase_add_test(tcase, div_3);
  tcase_add_test(tcase, div_4);
  tcase_add_test(tcase, div_5);
  tcase_add_test(tcase, div_6);
  tcase_add_test(tcase, div_7);
  tcase_add_test(tcase, div_8);
  tcase_add_test(tcase, div_9);

  //------------------------------------------------------------------------END

  suite_add_tcase(suite, tcase);

  return suite;
}




//------------------------------------------------------------------------is_less

START_TEST(is_less_00) {
  decimal value_1 = {{0}};
  decimal value_2 = {{0}};
  ck_assert_int_eq(0, is_less(value_1, value_2));
}
END_TEST

START_TEST(is_less_01) {
  decimal value_1 = {{0}};
  decimal value_2 = {{0}};
  value_1.bits[0] = 255;
  value_2.bits[0] = 256;
  ck_assert_int_eq(1, is_less(value_1, value_2));
}
END_TEST

START_TEST(is_less_02) {
  decimal value_1 = {{0}};
  decimal value_2 = {{0}};
  value_1.bits[0] = 256;
  value_2.bits[0] = 256;
  ck_assert_int_eq(0, is_less(value_1, value_2));
}
END_TEST

START_TEST(is_less_03) {
  decimal value_1 = {{0}};
  decimal value_2 = {{0}};
  value_1.bits[0] = 257;
  value_2.bits[0] = 256;
  ck_assert_int_eq(0, is_less(value_1, value_2));
}
END_TEST

START_TEST(is_less_04) {
  decimal value_1 = {{0}};
  decimal value_2 = {{0}};
  set_bit(&value_1, 127, 1);
  ck_assert_int_eq(0, is_less(value_1, value_2));
}
END_TEST

START_TEST(is_less_05) {
  decimal value_1 = {{0}};
  decimal value_2 = {{0}};
  value_1.bits[0] = 257;
  value_2.bits[0] = 256;
  value_1.bits[2] = 256;
  value_2.bits[2] = 257;
  set_scale(&value_1, 11);
  set_scale(&value_2, 10);
  ck_assert_int_eq(1, is_less(value_1, value_2));
}
END_TEST

START_TEST(is_less_06) {
  decimal value_1 = {{0}};
  decimal value_2 = {{0}};
  value_1.bits[0] = 257;
  value_2.bits[0] = 257;
  value_1.bits[2] = 256;
  value_2.bits[2] = 257;
  set_scale(&value_1, 10);
  set_scale(&value_2, 11);
  ck_assert_int_eq(0, is_less(value_1, value_2));
}
END_TEST

START_TEST(is_less_07) {
  decimal value_1 = {{0}};
  decimal value_2 = {{0}};
  value_2.bits[2] = 257;
  set_scale(&value_1, 13);
  set_scale(&value_2, 13);
  ck_assert_int_eq(1, is_less(value_1, value_2));
}
END_TEST

START_TEST(is_less_08) {
  decimal value_1 = {{0}};
  decimal value_2 = {{0}};
  set_bit(&value_1, 127, 1);
  set_bit(&value_2, 127, 1);
  set_bit(&value_1, 83, 1);
  set_scale(&value_1, 12);
  set_scale(&value_2, 11);
  ck_assert_int_eq(1, is_less(value_1, value_2));
}
END_TEST

START_TEST(is_less_09) {
  decimal value_1 = {{0}};
  decimal value_2 = {{0}};
  set_bit(&value_1, 127, 1);
  set_bit(&value_2, 127, 1);
  set_bit(&value_1, 83, 1);
  set_bit(&value_2, 83, 1);
  set_scale(&value_1, 10);
  set_scale(&value_2, 11);
  ck_assert_int_eq(1, is_less(value_1, value_2));
}
END_TEST

START_TEST(is_less_10) {
  decimal value_1 = {{0}};
  decimal value_2 = {{0}};
  set_bit(&value_1, 127, 1);
  set_bit(&value_2, 127, 1);
  set_bit(&value_1, 83, 1);
  set_scale(&value_1, 10);
  set_scale(&value_2, 10);
  ck_assert_int_eq(1, is_less(value_1, value_2));
}
END_TEST

START_TEST(is_less_11) {
  decimal value_1 = {{0}};
  decimal value_2 = {{0}};
  set_bit(&value_1, 127, 1);
  set_bit(&value_2, 127, 0);
  set_bit(&value_1, 83, 1);
  ck_assert_int_eq(1, is_less(value_1, value_2));
}
END_TEST

START_TEST(is_less_12) {
  decimal value_1 = {{0}};
  decimal value_2 = {{0}};
  set_bit(&value_1, 127, 1);
  set_bit(&value_2, 127, 0);
  ck_assert_int_eq(0, is_less(value_1, value_2));
}
END_TEST

START_TEST(is_less_13) {
  float a = dec_rand_r(-10e20, 10e20);
  float b = dec_rand_r(-10e20, 10e20);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(b, &_b);

  ck_assert_int_eq(is_less(_a, _b), a < b);
}
END_TEST

START_TEST(is_less_14) {
  float a = dec_rand_r(-1e-6, 1e-6);
  float b = dec_rand_r(-1e-6, 1e-6);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(b, &_b);
  ck_assert_int_eq(is_less(_a, _b), a < b);
}
END_TEST

START_TEST(is_less_15) {
  float a = -25.158531;
  float b = -39.425785;

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(b, &_b);
  ck_assert_int_eq(is_less(_a, _b), a < b);
}
END_TEST

START_TEST(is_less_16) {
  float a = dec_rand_r(-10e20, 10e20);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(a, &_b);
  ck_assert_int_eq(is_less(_a, _b), 0);
}
END_TEST

START_TEST(is_less_17) {
  decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int error = is_less(value_1, value_2);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(is_less_18) {
  decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  set_bit(&value_1, 127, 1);
  int error = is_less(value_1, value_2);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(is_less_19) {
  decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  set_bit(&value_2, 127, 1);
  int error = is_less(value_1, value_2);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(is_less_20) {
  decimal value_1 = {{0, 0, 0, 0}};
  decimal value_2 = {{0, 0, 0, 0}};
  set_bit(&value_2, 127, 1);
  int error = is_less(value_1, value_2);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(is_less_21) {
  decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  set_bit(&value_1, 127, 1);
  set_bit(&value_2, 127, 1);
  int error = is_less(value_1, value_2);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(is_less_22) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_less_23) {
  float num1 = 1.39;
  float num2 = 1.39;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_less_24) {
  float num1 = 1.39;
  float num2 = -1.39;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_less_25) {
  int num1 = 0;
  int num2 = 0;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_less(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_less_26) {
  int num1 = 3;
  int num2 = 9;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_less(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_less_27) {
  int num1 = -3;
  int num2 = -3;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_less(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_less_28) {
  float num1 = -34534534.232446543232446543;
  float num2 = -3.232323233232323233;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less(dec1, dec2);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_less_29) {
  decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}};  // -1.2
  ck_assert_int_eq(is_less(dec5, dec6), 0);
  ck_assert_int_eq(is_less(dec6, dec5), 1);

  decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(is_less(dec7, dec8), 1);
  ck_assert_int_eq(is_less(dec8, dec7), 0);

  decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(is_less(dec1, dec2), 0);
  ck_assert_int_eq(is_less(dec2, dec1), 1);

  decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  decimal dec4 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //  -1.2;
  ck_assert_int_eq(is_less(dec3, dec4), 1);
  ck_assert_int_eq(is_less(dec4, dec3), 0);

  decimal dec9 = {{12345, 0, 0, 0}};
  decimal dec10 = {{12345, 0, 0, 0}};
  ck_assert_int_eq(is_less(dec9, dec10), 0);
  ck_assert_int_eq(is_less(dec10, dec9), 0);

  decimal dec11 = {{0, 0, 0, 0}};
  decimal dec12 = {{0, 0, 0, 0}};
  ck_assert_int_eq(is_less(dec11, dec12), 0);
  ck_assert_int_eq(is_less(dec12, dec11), 0);
}
END_TEST

//------------------------------------------------------------------------is_less_or_equal

START_TEST(is_less_or_equal_0) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  ck_assert_int_eq(1, is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_1) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_2) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_3) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_4) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_bit(&val1, 127, 1);
  ck_assert_int_eq(1, is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_5) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 11);
  set_scale(&val2, 10);
  ck_assert_int_eq(1, is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_6) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 10);
  set_scale(&val2, 11);
  ck_assert_int_eq(0, is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_7) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val2.bits[2] = 257;
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 1);
  ck_assert_int_eq(0, is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(is_less_or_equal_8) {
  float a = dec_rand_r(-10e20, 10e20);
  float b = dec_rand_r(-10e20, 10e20);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(b, &_b);
  ck_assert_int_eq(is_less_or_equal(_a, _b), a <= b);
}
END_TEST

START_TEST(is_less_or_equal_9) {
  float a = dec_rand_r(-10e1, 10e1);
  float b = dec_rand_r(-10e1, 10e1);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(b, &_b);
  ck_assert_int_eq(is_less_or_equal(_a, _b), a <= b);
}
END_TEST

START_TEST(is_less_or_equal_10) {
  float a = -25.158531;
  float b = -39.425785;

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(b, &_b);
  ck_assert_int_eq(is_less_or_equal(_a, _b), a <= b);
}
END_TEST

START_TEST(is_less_or_equal_11) {
  float a = dec_rand_r(-10e20, 10e20);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(a, &_b);
  ck_assert_int_eq(is_less(_a, _b), 0);
}
END_TEST

START_TEST(is_less_or_equal_12) {
  decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(is_less_or_equal_13) {
  decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  set_bit(&value_1, 127, 1);
  int return_value = is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_less_or_equal_14) {
  decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  set_bit(&value_2, 127, 1);
  int return_value = is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(is_less_or_equal_15) {
  decimal value_1 = {{0, 0, 0, 0}};
  decimal value_2 = {{0, 0, 0, 0}};
  set_bit(&value_2, 127, 1);
  int return_value = is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_less_or_equal_16) {
  decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  set_bit(&value_1, 127, 1);
  set_bit(&value_2, 127, 1);
  int return_value = is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(is_less_or_equal_17) {
  decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  set_scale(&value_2, 2);

  int return_value = is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);  // 1
}
END_TEST

START_TEST(is_less_or_equal_18) {
  decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(less_or_equal_1) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_or_equal_2) {
  float num1 = 1.39;
  float num2 = 1.39;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_or_equal_3) {
  float num1 = 1.39;
  float num2 = -1.39;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(less_or_equal_4) {
  int num1 = 0;
  int num2 = 0;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_or_equal_5) {
  int num1 = 3;
  int num2 = 9;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_or_equal_6) {
  int num1 = -3;
  int num2 = -3;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_or_equal_7) {
  float num1 = -3453434.232446543232446543;
  float num2 = -3.232323233232323233;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_or_equal_8) {
  float num1 = -34534553434.232446543232446543;
  float num2 = 34534553434.232446543232446543;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_or_equal_9) {
  float num1 = 1.78;
  float num2 = 1.39;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(less_or_equal_10) {
  float num1 = -3453453452.0;
  float num2 = -34.0;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_or_equal_11) {
  float num1 = 104235454634.34534534;
  float num2 = 1042354546.34534534;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(less_or_equal_12) {
  float num1 = 1042354546.34534534;
  float num2 = 104235454634.345345;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_or_equal_13) {
  float num1 = 1042.5667777;
  float num2 = 1042.345345;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(less_or_equal_14) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_or_equal_15) {
  float num1 = 1.39;
  float num2 = 1.39;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_or_equal_16) {
  float num1 = 1.39;
  float num2 = -1.39;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(less_or_equal_17) {
  int num1 = 0;
  int num2 = 0;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_or_equal_18) {
  int num1 = 3;
  int num2 = 9;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_or_equal_19) {
  int num1 = -3;
  int num2 = -3;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_or_equal_20) {
  int num1 = 10;
  int num2 = 3;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(less_or_equal_21) {
  float num1 = 104232346.34534534;
  float num2 = 3.3453453234;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(less_or_equal_22) {
  float num1 = -3.34534534;
  float num2 = 3.34534534;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_less_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_less_or_equal_23) {
  decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}};  // -1.2;
  ck_assert_int_eq(is_less_or_equal(dec5, dec6), 0);
  ck_assert_int_eq(is_less_or_equal(dec6, dec5), 1);

  decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(is_less_or_equal(dec7, dec8), 1);
  ck_assert_int_eq(is_less_or_equal(dec8, dec7), 0);

  decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(is_less_or_equal(dec1, dec2), 0);
  ck_assert_int_eq(is_less_or_equal(dec2, dec1), 1);

  decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  decimal dec4 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //  -1.2;
  ck_assert_int_eq(is_less_or_equal(dec3, dec4), 1);
  ck_assert_int_eq(is_less_or_equal(dec4, dec3), 0);

  decimal dec9 = {{12345, 0, 0, 0}};
  decimal dec10 = {{12345, 0, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(dec9, dec10), 1);
  ck_assert_int_eq(is_less_or_equal(dec10, dec9), 1);

  decimal dec11 = {{0, 0, 0, 0}};
  decimal dec12 = {{0, 0, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(dec11, dec12), 1);
  ck_assert_int_eq(is_less_or_equal(dec12, dec11), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_1) {
  decimal a = {{1, 0, 0, 0}};
  decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_2) {
  decimal a = {{1, 0, 0, 0}};
  decimal b = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_2i) {
  decimal a = {{UINT_MAX, 0, 0, 0}};
  decimal b = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_3) {
  decimal a = {{UINT_MAX - 1, 0, 0, 0}};
  decimal b = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_4) {
  decimal a = {{UINT_MAX, 0, 0, 0}};
  decimal b = {{UINT_MAX, 1, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_41) {
  decimal a = {{UINT_MAX, 1, 0, 0}};
  decimal b = {{UINT_MAX, 1, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_5) {
  decimal a = {{UINT_MAX, UINT_MAX - 1, 0, 0}};
  decimal b = {{UINT_MAX, UINT_MAX, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_6) {
  decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  decimal b = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_7) {
  decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX - 1, 0}};
  decimal b = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_8) {
  decimal a = {{0, UINT_MAX, UINT_MAX, 0}};
  decimal b = {{0, UINT_MAX, UINT_MAX, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_9) {
  decimal a = {{0, 0, UINT_MAX, 0}};
  decimal b = {{0, 0, UINT_MAX, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_or_equal_10) {
  decimal a = {{0, 0, 0, 0}};
  decimal b = {{0, 0, UINT_MAX, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equalTest01) {
  // 2596
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest1) {
  // 3172
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest2) {
  // 3190
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest3) {
  // 3208
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 3;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest4) {
  // 3226
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest5) {
  // 3244
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest6) {
  // 3262
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest7) {
  // 3280
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 6521;
  // src2 = 74121;

  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest8) {
  // 3298
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 4;
  // src2 = 97623323;

  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest9) {
  // 3316
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 65658654;
  // src2 = 5;

  src1.bits[0] = 0b00000011111010011101111100011110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest10) {
  // 3334
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = -364748;
  // src2 = 1;

  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest11) {
  // 3352
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 1;
  // src2 = 98745654321;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest12) {
  // 3370
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = -9878798789;
  // src2 = -3;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest13) {
  // 3388
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 9999999999999999999;
  // src2 = 1;

  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest14) {
  // 3406
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 18446744073709551615;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest15) {
  // 3424
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;

  src1.bits[0] = 0b11111111111111111111111111110110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000001001;
  src1.bits[3] = 0b00000000000000010000000000000000;
  src2.bits[0] = 0b00111001100010111010010101100010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest16) {
  // 3442
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = -545454512454545.35265454545645;
  // src2 = 54564654;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;
  src2.bits[0] = 0b00000011010000001001011100101110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest18) {
  // 3478
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 7961327845421.879754123131254;
  // src2 = 0;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest19) {
  // 3496
  decimal src1 = {{0}};
  decimal src2 = {{0}};

  // 44888571,679810019404305144576
  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;

  // 551006440570,2897413741940543
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest20) {
  // 3514
  decimal src1 = {{0}};
  decimal src2 = {{0}};

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest21) {
  // 3532
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 12345677.987654345678987654346;
  // src2 = -87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b10000000000100000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest22) {
  // 3550
  decimal src1 = {0}, src2 = {0};

  // 44888571,679810019404305144576
  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;

  // 551006440570,2897413741940543
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest23) {
  // 3568
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest24) {
  // 3586
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest25) {
  // 3604
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest26) {
  // 3622
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 79228162514264337593543950335;
  // src2 = -1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest27) {
  // 3640
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 7922816251427554395;
  // src2 = 65645646;

  src1.bits[0] = 0b01011111000010000000010001011011;
  src1.bits[1] = 0b01101101111100110111111101100111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000011111010011010110001001110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest28) {
  // 3658
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 665464545;
  // src2 = 8798232189789785;

  src1.bits[0] = 0b00100111101010100010111011100001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00010000010100101110011001011001;
  src2.bits[1] = 0b00000000000111110100000111110010;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest29) {
  // 3676
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 2.7986531268974139743;
  // src2 = 9.979623121254565121244554;

  src1.bits[0] = 0b11111110100100001101100101011111;
  src1.bits[1] = 0b10000100011001000010000111101000;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;
  src2.bits[0] = 0b11010100101011100011110110001010;
  src2.bits[1] = 0b01110100000101000010011110100011;
  src2.bits[2] = 0b00000000000010000100000101000100;
  src2.bits[3] = 0b00000000000110000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest30) {
  // 3694
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = -9798956154578676.797564534156;
  // src2 = -2156878451.854764;

  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] = 0b00011111101010011000000110101101;
  src1.bits[3] = 0b10000000000011000000000000000000;
  src2.bits[0] = 0b01100101111100100100110110101100;
  src2.bits[1] = 0b00000000000001111010100110101011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000001100000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest31) {
  // 3712
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 0.5456465465486476846545465485;
  // src2 = 0.68985125146545154;

  src1.bits[0] = 0b00001011000011110111000010001101;
  src1.bits[1] = 0b10010110101100000101100101010001;
  src1.bits[2] = 0b00010001101000010111101110000001;
  src1.bits[3] = 0b00000000000111000000000000000000;
  src2.bits[0] = 0b00010111001001010100110000000010;
  src2.bits[1] = 0b00000000111101010001010110011011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000100010000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest32) {
  // 3730
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = -0.77545545454546589781;
  // src2 = 87894515154546456456;

  src1.bits[0] = 0b10101100001010000001100001010101;
  src1.bits[1] = 0b00110100001010010001111010111100;
  src1.bits[2] = 0b00000000000000000000000000000100;
  src1.bits[3] = 0b10000000000101000000000000000000;
  src2.bits[0] = 0b00010011111011011111011110001000;
  src2.bits[1] = 0b11000011110010000000101111011001;
  src2.bits[2] = 0b00000000000000000000000000000100;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest33) {
  // 3748
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = -79228162514264337593543950335;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest34) {
  // 3766
  decimal src1 = {0}, src2 = {0};
  // src1 = 32323465788987654;
  // src2 = 67543278.89765424354657687;

  src1.bits[0] = 0b01011000010000110001100100000110;
  src1.bits[1] = 0b00000000011100101101011000000101;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b10111110000100011000010110010111;
  src2.bits[1] = 0b11011001001111010001001011000110;
  src2.bits[2] = 0b00000000000001011001011001001000;
  // src2.bits[3] = 0b00000000000100010000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest35) {
  // 3784
  decimal src1 = {{0}};
  decimal src2 = {{0}};

  src1.bits[0] = 0b10110001001110110100010111110100;
  src1.bits[1] = 0b00111000100000111010110010000001;
  src1.bits[2] = 0b00011001010110010101110000011000;
  // src1.bits[3] = 0b10000000000100110000000000000000;
  src1.bits[3] = 0b10000000000010110000000000000000;

  src2.bits[0] = 0b11100110001001011001001101101001;
  src2.bits[1] = 0b00111000110110101110001010110100;
  src2.bits[2] = 0b10111011010111111101000100011110;
  src2.bits[3] = 0b10000000000010110000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equalTest36) {
  // 3802
  decimal src1 = {{0}};
  decimal src2 = {{0}};

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b01001111101101000110000001100101;
  src2.bits[1] = 0b01000010001101101011011001100001;
  src2.bits[2] = 0b01111010101111011000110010011010;
  src2.bits[3] = 0b10000000000011000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

//------------------------------------------------------------------------is_greater

START_TEST(is_greater_00) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  ck_assert_int_eq(0, is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_01) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_02) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_03) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_04) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_bit(&val1, 127, 1);
  ck_assert_int_eq(0, is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_05) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 11);
  set_scale(&val2, 10);
  ck_assert_int_eq(0, is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_06) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 10);
  set_scale(&val2, 11);
  ck_assert_int_eq(1, is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_07) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val2.bits[2] = 257;
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 1);
  ck_assert_int_eq(1, is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_08) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val2.bits[2] = 257;
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 0);
  ck_assert_int_eq(0, is_greater(val1, val2));
}
END_TEST

START_TEST(is_greater_09) {
  float a = dec_rand_r(-10e20, 10e20);
  float b = dec_rand_r(-10e20, 10e20);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(b, &_b);
  ck_assert_int_eq(is_greater(_a, _b), a > b);
}
END_TEST

START_TEST(is_greater_10) {
  float a = dec_rand_r(-10e1, 10e1);
  float b = dec_rand_r(-10e1, 10e1);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(b, &_b);
  ck_assert_int_eq(is_greater(_a, _b), a > b);
}
END_TEST

START_TEST(is_greater_11) {
  decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int error = is_greater(value_1, value_2);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(is_greater_12) {
  decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  set_bit(&value_1, 127, 1);
  int error = is_greater(value_1, value_2);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(is_greater_13) {
  decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  set_bit(&value_2, 127, 1);
  int error = is_greater(value_1, value_2);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(is_greater_14) {
  decimal value_1 = {{0, 0, 0, 0}};
  decimal value_2 = {{0, 0, 0, 0}};
  set_bit(&value_2, 127, 1);
  int error = is_greater(value_1, value_2);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(is_greater_15) {
  decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  set_bit(&value_1, 127, 1);
  set_bit(&value_2, 127, 1);
  int error = is_greater(value_1, value_2);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(is_greater_16) {
  decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};

  int error = is_greater(value_1, value_2);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(is_greater_17) {
  decimal value_1 = {{234, 0, 0, 0}};
  decimal value_2 = {{2, 0, 0, 0}};
  set_scale(&value_1, 2);
  int error = is_greater(value_1, value_2);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(is_greater_18) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_19) {
  float num1 = 1.39;
  float num2 = 1.39;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_20) {
  float num1 = 1.39;
  float num2 = -1.39;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_21) {
  int num1 = 0;
  int num2 = 0;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);

  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_22) {
  int num1 = 3;
  int num2 = 9;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_23) {
  int num1 = -3;
  int num2 = -3;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_24) {
  int num1 = -3;
  int num2 = 3;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_25) {
  float num1 = -3.232446546;
  float num2 = -3.2;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_26) {
  float num1 = -345.232446546;
  float num2 = -3.2;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_27) {
  float num1 = -3.232323233232323233;
  float num2 = -34545124.232446543232446543;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_28) {
  decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  decimal dec6 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //  -1.2;
  ck_assert_int_eq(is_greater(dec5, dec6), 1);
  ck_assert_int_eq(is_greater(dec6, dec5), 0);

  decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(is_greater(dec7, dec8), 0);
  ck_assert_int_eq(is_greater(dec8, dec7), 1);

  decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2
  ck_assert_int_eq(is_greater(dec1, dec2), 1);
  ck_assert_int_eq(is_greater(dec2, dec1), 0);

  decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  decimal dec4 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //   -1.2
  ck_assert_int_eq(is_greater(dec3, dec4), 0);
  ck_assert_int_eq(is_greater(dec4, dec3), 1);
}
END_TEST

START_TEST(is_greater_29) {
  decimal a = {{2, 0, 0, 0}};
  decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
  // Возвращаемое значение : 0 - 0   1 - TRUE
}
END_TEST

START_TEST(is_greater_30) {
  decimal a = {{UINT_MAX, 0, 0, 0}};
  decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_31) {
  decimal a = {{UINT_MAX, 0, 0, 0}};
  decimal b = {{UINT_MAX - 1, 0, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_32) {
  decimal a = {{UINT_MAX, 0, 0, 0}};
  decimal b = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 0);
}
END_TEST

START_TEST(is_greater_33) {
  decimal a = {{UINT_MAX, 0, 0, 0}};
  decimal b = {{UINT_MAX, 1, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 0);
}
END_TEST

START_TEST(is_greater_34) {
  decimal a = {{UINT_MAX, 1, 0, 0}};
  decimal b = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_35) {
  decimal a = {{UINT_MAX, UINT_MAX, 0, 0}};
  decimal b = {{UINT_MAX, UINT_MAX - 1, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_36) {
  decimal a = {{UINT_MAX, UINT_MAX, 0, 0}};
  decimal b = {{UINT_MAX, UINT_MAX, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 0);
}
END_TEST

START_TEST(is_greater_37) {
  decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  decimal b = {{UINT_MAX, UINT_MAX, UINT_MAX - 1, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_38) {
  decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX - 1, 0}};
  decimal b = {{UINT_MAX, UINT_MAX, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_39) {
  decimal a = {{0, UINT_MAX, UINT_MAX, 0}};
  decimal b = {{0, UINT_MAX, UINT_MAX - 1, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_40) {
  decimal a = {{0, 0, UINT_MAX, 0}};
  decimal b = {{0, 0, UINT_MAX - 1, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_41) {
  decimal a = {{0, 0, 0, 0}};
  decimal b = {{0, 0, UINT_MAX, 0}};
  ck_assert_int_eq(is_greater(a, b), 0);
}
END_TEST

START_TEST(is_greater_42) {
  // 3820
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_43) {
  // 3838
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_44) {
  // 3856
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 3;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_45) {
  // 3874
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_46) {
  // 3892
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_47) {
  // 3910
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_48) {
  // 3928
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 6521;
  // src2 = 74121;

  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_49) {
  // 3946
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 4;
  // src2 = 97623323;

  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_50) {
  // 3964
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 65658654;
  // src2 = 5;

  src1.bits[0] = 0b00000011111010011101111100011110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_51) {
  // 3982
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = -364748;
  // src2 = 1;

  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_52) {
  // 4000
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 1;
  // src2 = 98745654321;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_53) {
  // 4018
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = -9878798789;
  // src2 = -3;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_54) {
  // 4036
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 9999999999999999999;
  // src2 = 1;

  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_55) {
  // 4054
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 18446744073709551615;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_56) {
  // 4072
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;

  src1.bits[0] = 0b11111111111111111111111111110110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000001001;
  src1.bits[3] = 0b00000000000000010000000000000000;
  src2.bits[0] = 0b00111001100010111010010101100010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_57) {
  // 4090
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = -545454512454545.35265454545645;
  // src2 = 54564654;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;
  src2.bits[0] = 0b00000011010000001001011100101110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_58) {
  // 4126
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 7961327845421.879754123131254;
  // src2 = 0;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_59) {
  // 4144
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 12345677.987654345678987654346; 21
  // src2 = 87654323456.9876545678987653; 16
  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;

  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_60) {
  // 4162
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = -12345677.987654345678987654346;
  // src2 = 87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_61) {
  // 4180
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 12345677.987654345678987654346;
  // src2 = -87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b10000000000100000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_62) {
  // 4198
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = -12345677.987654345678987654346;
  // src2 = -87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b10000000000100000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_63) {
  // 4216
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_64) {
  // 4234
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_65) {
  // 4252
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_66) {
  // 4270
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 79228162514264337593543950335;
  // src2 = -1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_67) {
  // 4288
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 7922816251427554395;
  // src2 = 65645646;

  src1.bits[0] = 0b01011111000010000000010001011011;
  src1.bits[1] = 0b01101101111100110111111101100111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000011111010011010110001001110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_68) {
  // 4306
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 665464545;
  // src2 = 8798232189789785;

  src1.bits[0] = 0b00100111101010100010111011100001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00010000010100101110011001011001;
  src2.bits[1] = 0b00000000000111110100000111110010;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_69) {
  // 4324
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 2.7986531268974139743;
  // src2 = 9.979623121254565121244554;

  src1.bits[0] = 0b11111110100100001101100101011111;
  src1.bits[1] = 0b10000100011001000010000111101000;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;
  src2.bits[0] = 0b11010100101011100011110110001010;
  src2.bits[1] = 0b01110100000101000010011110100011;
  src2.bits[2] = 0b00000000000010000100000101000100;
  src2.bits[3] = 0b00000000000110000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_70) {
  // 4342
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = -9798956154578676.797564534156;
  // src2 = -2156878451.854764;

  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] = 0b00011111101010011000000110101101;
  src1.bits[3] = 0b10000000000011000000000000000000;
  src2.bits[0] = 0b01100101111100100100110110101100;
  src2.bits[1] = 0b00000000000001111010100110101011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000001100000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_71) {
  // 4360
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 0.5456465465486476846545465485;
  // src2 = 0.68985125146545154;

  src1.bits[0] = 0b00001011000011110111000010001101;
  src1.bits[1] = 0b10010110101100000101100101010001;
  src1.bits[2] = 0b00010001101000010111101110000001;
  src1.bits[3] = 0b00000000000111000000000000000000;
  src2.bits[0] = 0b00010111001001010100110000000010;
  src2.bits[1] = 0b00000000111101010001010110011011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000100010000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_72) {
  // 4378
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = -0.77545545454546589781;
  // src2 = 87894515154546456456;

  src1.bits[0] = 0b10101100001010000001100001010101;
  src1.bits[1] = 0b00110100001010010001111010111100;
  src1.bits[2] = 0b00000000000000000000000000000100;
  src1.bits[3] = 0b10000000000101000000000000000000;
  src2.bits[0] = 0b00010011111011011111011110001000;
  src2.bits[1] = 0b11000011110010000000101111011001;
  src2.bits[2] = 0b00000000000000000000000000000100;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_73) {
  // 4396
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = -79228162514264337593543950335;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_74) {
  // 4414
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 32323465788987654;
  // src2 = 67543278.89765424354657687;

  src1.bits[0] = 0b01011000010000110001100100000110;
  src1.bits[1] = 0b00000000011100101101011000000101;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b10111110000100011000010110010111;
  src2.bits[1] = 0b11011001001111010001001011000110;
  src2.bits[2] = 0b00000000000001011001011001001000;
  src2.bits[3] = 0b00000000000100010000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_greater_75) {
  // 4450
  decimal src1 = {{0}};
  decimal src2 = {{0}};
  // src1 = 0;
  // src2 = -37986322154988653.784354545765;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b01001111101101000110000001100101;
  src2.bits[1] = 0b01000010001101101011011001100001;
  src2.bits[2] = 0b01111010101111011000110010011010;
  src2.bits[3] = 0b10000000000011000000000000000000;
  int error = is_greater(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

//------------------------------------------------------------------------is_greater_or_equal

START_TEST(is_greater_or_equal_00) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  ck_assert_int_eq(1, is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_01) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val1.bits[0] = 255;
  val2.bits[0] = 256;
  ck_assert_int_eq(0, is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_02) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val1.bits[0] = 256;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_03) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val1.bits[0] = 257;
  val2.bits[0] = 256;
  ck_assert_int_eq(1, is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_04) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_bit(&val1, 127, 1);
  ck_assert_int_eq(1, is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_05) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 11);
  set_scale(&val2, 10);
  ck_assert_int_eq(0, is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_06) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val1.bits[0] = 257;
  val2.bits[0] = 257;
  val1.bits[2] = 256;
  val2.bits[2] = 257;
  set_scale(&val1, 10);
  set_scale(&val2, 11);
  ck_assert_int_eq(1, is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_07) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  val2.bits[2] = 257;
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 1);
  ck_assert_int_eq(1, is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(is_greater_or_equal_08) {
  float a = dec_rand_r(-10e20, 10e20);
  float b = dec_rand_r(-10e20, 10e20);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(b, &_b);
  ck_assert_int_eq(is_greater_or_equal(_a, _b), a >= b);
}
END_TEST

START_TEST(is_greater_or_equal_09) {
  float a = dec_rand_r(-10e1, 10e1);
  float b = dec_rand_r(-10e1, 10e1);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(b, &_b);
  ck_assert_int_eq(is_greater_or_equal(_a, _b), a >= b);
}
END_TEST

START_TEST(is_greater_or_equal_10) {
  float a = dec_rand_r(-10e20, 10e20);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(a, &_b);
  ck_assert_int_eq(is_greater_or_equal(_a, _b), 1);
}
END_TEST

START_TEST(is_greater_or_equal_11) {
  decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int error = is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(is_greater_or_equal_12) {
  decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  set_bit(&value_1, 127, 1);
  int error = is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(is_greater_or_equal_13) {
  decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  set_bit(&value_2, 127, 1);
  int error = is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(is_greater_or_equal_14) {
  decimal value_1 = {{0, 0, 0, 0}};
  decimal value_2 = {{0, 0, 0, 0}};
  set_bit(&value_2, 127, 1);
  int error = is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(is_greater_or_equal_15) {
  decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  set_bit(&value_1, 127, 1);
  set_bit(&value_2, 127, 1);
  int error = is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(is_greater_or_equal_17) {
  decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int error = is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(is_greater_or_equal_18) {
  decimal value_1 = {{12345, 0, 0, 0}};
  set_scale(&value_1, 4);
  decimal value_2 = {{12u, 0, 0, 0}};
  set_scale(&value_1, 1);
  int error = is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(is_greater_or_equal_19) {
  float num1 = 1.375323;
  float num2 = 1.39;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_or_equal_20) {
  int num1 = 2;
  int num2 = 1;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_or_equal_21) {
  float num1 = 1.39;
  float num2 = -1.39;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_or_equal_22) {
  int num1 = 0;
  int num2 = 0;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_or_equal_23) {
  int num1 = 3;
  int num2 = 9;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_or_equal_24) {
  int num1 = -3;
  int num2 = -3;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_or_equal_25) {
  int num1 = 10;
  int num2 = 3;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_or_equal_26) {
  float num1 = 10423546.34534534;
  float num2 = 3.34534534;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_or_equal_27) {
  float num1 = -3.34534534;
  float num2 = 3.34534534;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_or_equal_28) {
  float num1 = 1042634.34534534;
  float num2 = 10424546.34534534;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_or_equal_29) {
  float num1 = 10426.34534534;
  float num2 = 104234.345345;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_or_equal_30) {
  float num1 = 1042.5667777;
  float num2 = 1042.345345;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_or_equal_31) {
  decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}};  //
  ck_assert_int_eq(is_greater_or_equal(dec5, dec6), 1);
  ck_assert_int_eq(is_greater_or_equal(dec6, dec5), 0);

  decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};
  ck_assert_int_eq(is_greater_or_equal(dec7, dec8), 0);
  ck_assert_int_eq(is_greater_or_equal(dec8, dec7), 1);

  decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};
  ck_assert_int_eq(is_greater_or_equal(dec1, dec2), 1);
  ck_assert_int_eq(is_greater_or_equal(dec2, dec1), 0);

  decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  decimal dec4 = {{12, 0, 0, 0b10000000000000010000000000000000}};  //

  ck_assert_int_eq(is_greater_or_equal(dec3, dec4), 0);
  ck_assert_int_eq(is_greater_or_equal(dec4, dec3), 1);

  decimal dec9 = {{12345, 0, 0, 0}};
  decimal dec10 = {{12345, 0, 0, 0}};
  ck_assert_int_eq(is_greater_or_equal(dec9, dec10), 1);
  ck_assert_int_eq(is_greater_or_equal(dec10, dec9), 1);

  decimal dec11 = {{0, 0, 0, 0}};
  decimal dec12 = {{0, 0, 0, 0}};
  ck_assert_int_eq(is_greater_or_equal(dec11, dec12), 1);
  ck_assert_int_eq(is_greater_or_equal(dec12, dec11), 1);
}
END_TEST

//------------------------------------------------------------------------is_equal

START_TEST(is_equal_00) {
  decimal val1 = {{0, 0, 0, 0}};
  decimal val2 = {{0, 0, 0, 0}};
  set_bit(&val2, 127, 1);
  ck_assert_int_eq(1, is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_01) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_bit(&val2, 3, 1);
  ck_assert_int_eq(0, is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_02) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_bit(&val2, 127, 1);
  set_bit(&val1, 33, 1);
  set_bit(&val2, 33, 1);
  ck_assert_int_eq(0, is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_03) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_bit(&val1, 3, 1);
  set_bit(&val2, 3, 1);
  ck_assert_int_eq(1, is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_04) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_bit(&val1, 3, 1);
  set_bit(&val2, 4, 1);
  ck_assert_int_eq(0, is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_05) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_scale(&val1, 3);
  set_scale(&val2, 3);
  ck_assert_int_eq(1, is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_06) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_bit(&val1, 3, 1);
  set_bit(&val2, 4, 1);
  set_scale(&val1, 3);
  set_scale(&val2, 3);
  ck_assert_int_eq(0, is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_07) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_scale(&val1, 3);
  set_scale(&val2, 2);
  ck_assert_int_eq(1, is_equal(val1, val2));
}
END_TEST

START_TEST(is_equal_08) {
  float a = dec_rand_r(-10e20, 10e20);
  float b = dec_rand_r(-10e20, 10e20);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(b, &_b);
  ck_assert_int_eq(is_equal(_a, _b), a == b);
}
END_TEST

START_TEST(is_equal_09) {
  float a = dec_rand_r(-10e1, 10e1);
  float b = dec_rand_r(-10e1, 10e1);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(b, &_b);
  ck_assert_int_eq(is_equal(_a, _b), a == b);
}
END_TEST

START_TEST(is_equal_10) {
  float a = dec_rand_r(-10e20, 10e20);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(a, &_b);
  ck_assert_int_eq(is_equal(_a, _b), 1);
}
END_TEST

START_TEST(is_equal_11) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_equal_12) {
  float num1 = 1.39;
  float num2 = 1.39;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_equal_13) {
  float num1 = 1.39;
  float num2 = -1.39;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_equal_14) {
  int num1 = 0;
  int num2 = 0;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_equal_15) {
  int num1 = 3;
  int num2 = 9;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_equal_16) {
  int num1 = -3;
  int num2 = -3;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_equal_17) {
  float num1 = 7.0000003;
  float num2 = 1.1;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_equal_18) {
  float num1 = 7.9e+28;
  float num2 = 1.342;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_equal_19) {
  float num1 = 7.9e+25;
  float num2 = 1.342;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_equal_20) {
  float num1 = NAN;
  float num2 = 2.3;
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_equal_22) {
  decimal dec1 = {{0, 0, 0, 0}};
  decimal dec2 = {{0, 0, 0, 0}};
  from_int_to_decimal(0, &dec1);
  from_int_to_decimal(0, &dec2);
  dec1.bits[3] = 0;
  ck_assert_int_eq(is_equal(dec1, dec2), 1);
}
END_TEST

START_TEST(is_equal_23) {
  // 5116
  decimal src1, src2;
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_24) {
  // 5134
  decimal src1, src2;
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_25) {
  // 5152
  decimal src1, src2;
  // src1 = 3;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_26) {
  // 5170
  decimal src1, src2;
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_27) {
  // 5188
  decimal src1, src2;
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_28) {
  // 5206
  decimal src1, src2;
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_29) {
  // 5224
  decimal src1, src2;
  // src1 = 6521;
  // src2 = 74121;

  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_30) {
  // 5242
  decimal src1, src2;
  // src1 = 4;
  // src2 = 97623323;

  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_31) {
  // 5260
  decimal src1, src2;
  // src1 = 65658654;
  // src2 = 5;

  src1.bits[0] = 0b00000011111010011101111100011110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_32) {
  // 5278
  decimal src1, src2;
  // src1 = -364748;
  // src2 = 1;

  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_33) {
  // 5296
  decimal src1, src2;
  // src1 = 1;
  // src2 = 98745654321;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_34) {
  // 5314
  decimal src1, src2;
  // src1 = -9878798789;
  // src2 = -3;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_35) {
  // 5332
  decimal src1, src2;
  // src1 = 9999999999999999999;
  // src2 = 1;

  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_36) {
  // 5350
  decimal src1, src2;
  // src1 = 18446744073709551615;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_37) {
  // 5368
  decimal src1, src2;
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;

  src1.bits[0] = 0b11111111111111111111111111110110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000001001;
  src1.bits[3] = 0b00000000000000010000000000000000;

  src2.bits[0] = 0b00111001100010111010010101100010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_38) {
  // 5386
  decimal src1, src2;
  // src1 = -545454512454545.35265454545645;
  // src2 = 54564654;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;

  src2.bits[0] = 0b00000011010000001001011100101110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_39) {
  // 5404
  decimal src1, src2;
  // src1 = -545454512454545.35265454545645;
  // src2 = -5.352654545456454545645464;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;

  src2.bits[0] = 0b01001000000110110001111110011000;
  src2.bits[1] = 0b11111011111111011000100101101101;
  src2.bits[2] = 0b00000000000001000110110101110111;
  src2.bits[3] = 0b10000000000110000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_40) {
  // 5422
  decimal src1, src2;
  // src1 = 7961327845421.879754123131254;
  // src2 = 0;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_41) {
  // 5440
  decimal src1, src2;
  // src1 = 12345677.987654345678987654346;
  // src2 = 87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;

  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_42) {
  // 5458
  decimal src1, src2;
  // src1 = -12345677.987654345678987654346;
  // src2 = 87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;

  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_43) {
  // 5476
  decimal src1, src2;
  // src1 = 12345677.987654345678987654346;
  // src2 = -87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b00000000000101010000000000000000;

  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b10000000000100000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_44) {
  // 5494
  decimal src1, src2;
  // src1 = -12345677.987654345678987654346;
  // src2 = -87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;

  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b10000000000100000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_45) {
  // 5512
  decimal src1, src2;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_46) {
  // 5530
  decimal src1, src2;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_47) {
  // 5548
  decimal src1, src2;
  // src1 = 0;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 1;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_48) {
  // 5566
  decimal src1, src2;
  // src1 = 79228162514264337593543950335;
  // src2 = -1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_49) {
  // 5584
  decimal src1, src2;
  // src1 = 7922816251427554395;
  // src2 = 65645646;

  src1.bits[0] = 0b01011111000010000000010001011011;
  src1.bits[1] = 0b01101101111100110111111101100111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000011111010011010110001001110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_50) {
  // 5602
  decimal src1, src2;
  // src1 = 665464545;
  // src2 = 8798232189789785;

  src1.bits[0] = 0b00100111101010100010111011100001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00010000010100101110011001011001;
  src2.bits[1] = 0b00000000000111110100000111110010;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_51) {
  // 5620
  decimal src1, src2;
  // src1 = 2.7986531268974139743;
  // src2 = 9.979623121254565121244554;

  src1.bits[0] = 0b11111110100100001101100101011111;
  src1.bits[1] = 0b10000100011001000010000111101000;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;

  src2.bits[0] = 0b11010100101011100011110110001010;
  src2.bits[1] = 0b01110100000101000010011110100011;
  src2.bits[2] = 0b00000000000010000100000101000100;
  src2.bits[3] = 0b00000000000110000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_52) {
  // 5638
  decimal src1, src2;
  // src1 = -9798956154578676.797564534156;
  // src2 = -2156878451.854764;

  src1.bits[0] = 0b01010100010000000011110110001100;
  src1.bits[1] = 0b10001011010100100000010101011001;
  src1.bits[2] = 0b00011111101010011000000110101101;
  src1.bits[3] = 0b10000000000011000000000000000000;

  src2.bits[0] = 0b01100101111100100100110110101100;
  src2.bits[1] = 0b00000000000001111010100110101011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000001100000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_53) {
  // 5656
  decimal src1, src2;
  // src1 = 0.5456465465486476846545465485;
  // src2 = 0.68985125146545154;

  src1.bits[0] = 0b00001011000011110111000010001101;
  src1.bits[1] = 0b10010110101100000101100101010001;
  src1.bits[2] = 0b00010001101000010111101110000001;
  src1.bits[3] = 0b00000000000111000000000000000000;

  src2.bits[0] = 0b00010111001001010100110000000010;
  src2.bits[1] = 0b00000000111101010001010110011011;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000100010000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_54) {
  // 5674
  decimal src1, src2;
  // src1 = -0.77545545454546589781;
  // src2 = 87894515154546456456;

  src1.bits[0] = 0b10101100001010000001100001010101;
  src1.bits[1] = 0b00110100001010010001111010111100;
  src1.bits[2] = 0b00000000000000000000000000000100;
  src1.bits[3] = 0b10000000000101000000000000000000;

  src2.bits[0] = 0b00010011111011011111011110001000;
  src2.bits[1] = 0b11000011110010000000101111011001;
  src2.bits[2] = 0b00000000000000000000000000000100;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_55) {
  // 5692
  decimal src1, src2;
  // src1 = -79228162514264337593543950335;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_56) {
  // 5710
  decimal src1, src2;
  // src1 = 32323465788987654;
  // src2 = 67543278.89765424354657687;

  src1.bits[0] = 0b01011000010000110001100100000110;
  src1.bits[1] = 0b00000000011100101101011000000101;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b10111110000100011000010110010111;
  src2.bits[1] = 0b11011001001111010001001011000110;
  src2.bits[2] = 0b00000000000001011001011001001000;
  src2.bits[3] = 0b00000000000100010000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_57) {
  // 5728
  decimal src1, src2;
  // src1 = -784515454.7989898652154545652;
  // src2 = -579895323215489956.67897455465;

  src1.bits[0] = 0b10110001001110110100010111110100;
  src1.bits[1] = 0b00111000100000111010110010000001;
  src1.bits[2] = 0b00011001010110010101110000011000;
  src1.bits[3] = 0b10000000000100110000000000000000;

  src2.bits[0] = 0b11100110001001011001001101101001;
  src2.bits[1] = 0b00111000110110101110001010110100;
  src2.bits[2] = 0b10111011010111111101000100011110;
  src2.bits[3] = 0b10000000000010110000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(is_equal_58) {
  // 5746
  decimal src1, src2;
  // src1 = 0;
  // src2 = -37986322154988653.784354545765;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b01001111101101000110000001100101;
  src2.bits[1] = 0b01000010001101101011011001100001;
  src2.bits[2] = 0b01111010101111011000110010011010;
  src2.bits[3] = 0b10000000000011000000000000000000;
  int error = is_equal(src1, src2);
  int origin_error = 0;
  ck_assert_int_eq(error, origin_error);
}
END_TEST

START_TEST(s21_equal_21) {
  decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  decimal dec2 = {{12, 0, 0, 0b10000000000000010000000000000000}};  //
  // -1.2;
  ck_assert_int_eq(is_equal(dec1, dec2), 0);

  decimal dec3 = {
      {120000, 0, 0, 0b00000000000001000000000000000000}};  //  12.0000
  decimal dec4 = {{12, 0, 0, 0b00000000000000000000000000000000}};  //
  // 12;
  ck_assert_int_eq(is_equal(dec3, dec4), 1);

  decimal dec5 = {{0, 0, 0, 0b00000000000000000000000000000000}};  //  0
  decimal dec6 = {{0, 0, 0, 0b00000000000000010000000000000000}};  //
  // 0.0;
  ck_assert_int_eq(is_equal(dec5, dec6), 1);

  decimal dec7 = {{0, 0, 0, 0b00000000000000000000000000000000}};  //   0
  decimal dec8 = {{0, 0, 0, 0b10000000000000000000000000000000}};  // -0;
  ck_assert_int_eq(is_equal(dec7, dec8), 1);
}
END_TEST

//------------------------------------------------------------------------is_not_equal

START_TEST(dec_is_not_equal_00) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_bit(&val1, 127, 1);
  set_bit(&val2, 127, 0);
  ck_assert_int_eq(0, is_not_equal(val1, val2));
}
END_TEST

START_TEST(dec_is_not_equal_01) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_bit(&val2, 3, 1);
  ck_assert_int_eq(1, is_not_equal(val1, val2));
}
END_TEST

START_TEST(dec_is_not_equal_02) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_bit(&val2, 127, 1);
  set_bit(&val1, 33, 1);
  set_bit(&val2, 33, 1);
  ck_assert_int_eq(1, is_not_equal(val1, val2));
}
END_TEST

START_TEST(dec_is_not_equal_03) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_bit(&val1, 3, 1);
  set_bit(&val2, 3, 1);
  ck_assert_int_eq(0, is_not_equal(val1, val2));
}
END_TEST

START_TEST(dec_is_not_equal_04) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_bit(&val1, 3, 1);
  set_bit(&val2, 4, 1);
  ck_assert_int_eq(1, is_not_equal(val1, val2));
}
END_TEST

START_TEST(dec_is_not_equal_05) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_scale(&val1, 3);
  set_scale(&val2, 3);
  ck_assert_int_eq(0, is_not_equal(val1, val2));
}
END_TEST

START_TEST(dec_is_not_equal_06) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_bit(&val1, 3, 1);
  set_bit(&val2, 4, 1);
  set_scale(&val1, 3);
  set_scale(&val2, 3);
  ck_assert_int_eq(1, is_not_equal(val1, val2));
}
END_TEST

START_TEST(dec_is_not_equal_07) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  set_scale(&val1, 3);
  set_scale(&val2, 2);
  ck_assert_int_eq(0, is_not_equal(val1, val2));
}
END_TEST

START_TEST(dec_is_not_equal_08) {
  decimal val1 = {{0}};
  decimal val2 = {{0}};
  ck_assert_int_eq(0, is_not_equal(val1, val2));
}
END_TEST

START_TEST(dec_is_not_equal_09) {
  float a = dec_rand_r(-10e20, 10e20);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(a, &_b);
  ck_assert_int_eq(is_not_equal(_a, _b), 0);
}
END_TEST

START_TEST(dec_is_not_equal_10) {
  float a = dec_rand_r(-10e20, 10e20);
  float b = dec_rand_r(-10e20, 10e20);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(b, &_b);
  ck_assert_int_eq(is_not_equal(_a, _b), a != b);
}
END_TEST

START_TEST(dec_is_not_equal_11) {
  float a = dec_rand_r(-10e1, 10e1);
  float b = dec_rand_r(-10e1, 10e1);

  decimal _a = {{0}};
  decimal _b = {{0}};
  from_float_to_decimal(a, &_a);
  from_float_to_decimal(b, &_b);
  ck_assert_int_eq(is_not_equal(_a, _b), a != b);
}
END_TEST

START_TEST(dec_is_not_equal_12) {
  decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  int error = is_not_equal(value_1, value_2);
  // printb(value_1, 127);
  // printb(value_2, 127);
  ck_assert_int_eq(error, 0);
}
END_TEST


START_TEST(dec_is_not_equal_14) {
  decimal value_1 = {{0, 0, 0, 80000000}};
  decimal value_2 = {{0, 0, 0, 0}};
  int error = is_not_equal(value_1, value_2);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(dec_is_not_equal_15) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  decimal dec1 = {{0}};
  decimal dec2 = {{0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(dec_is_not_equal_16) {
  float num1 = 1.39;
  float num2 = 1.39;
  decimal dec1 = {{0}};
  decimal dec2 = {{0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(dec_is_not_equal_17) {
  float num1 = 1.39;
  float num2 = -1.39;
  decimal dec1 = {{0}};
  decimal dec2 = {{0}};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(dec_is_not_equal_18) {
  int num1 = 0;
  int num2 = 0;
  decimal dec1 = {{0}};
  decimal dec2 = {{0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(dec_is_not_equal_19) {
  int num1 = 3;
  int num2 = 9;
  decimal dec1 = {{0}};
  decimal dec2 = {{0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(dec_is_not_equal_20) {
  int num1 = -3;
  int num2 = -3;
  decimal dec1 = {{0}};
  decimal dec2 = {{0}};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(dec_is_not_equal_21) {
  decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  decimal dec2 = {{12, 0, 0, 0b10000000000000010000000000000000}};  // -1.2;
  ck_assert_int_eq(is_not_equal(dec1, dec2), 1);
}
END_TEST
START_TEST(dec_is_not_equal_22) {
  decimal dec3 = {
      {120000, 0, 0, 0b00000000000001000000000000000000}};  //  12.0000
  decimal dec4 = {{12, 0, 0, 0b00000000000000000000000000000000}};  //
  ck_assert_int_eq(is_not_equal(dec3, dec4), 0);
}
END_TEST
START_TEST(dec_is_not_equal_23) {
  decimal dec5 = {{0, 0, 0, 0b00000000000000000000000000000000}};   //  0
  decimal dec6 = {{00, 0, 0, 0b00000000000000010000000000000000}};  //
  ck_assert_int_eq(is_not_equal(dec5, dec6), 0);
}
END_TEST

//------------------------------------------------------------------------END

Suite *test_comparison(void) {
  Suite *suite = suite_create("comparison_suite");
  TCase *tcase = tcase_create("comparison_tcase");

  //------------------------------------------------------------------------

  tcase_add_test(tcase, is_less_00);
  tcase_add_test(tcase, is_less_01);
  tcase_add_test(tcase, is_less_02);
  tcase_add_test(tcase, is_less_03);
  tcase_add_test(tcase, is_less_04);
  tcase_add_test(tcase, is_less_05);
  tcase_add_test(tcase, is_less_06);
  tcase_add_test(tcase, is_less_07);
  tcase_add_test(tcase, is_less_08);
  tcase_add_test(tcase, is_less_09);
  tcase_add_test(tcase, is_less_10);
  tcase_add_test(tcase, is_less_11);
  tcase_add_test(tcase, is_less_12);
  tcase_add_test(tcase, is_less_13);
  tcase_add_loop_test(tcase, is_less_14, 0, 100);
  tcase_add_loop_test(tcase, is_less_15, 0, 100);
  tcase_add_loop_test(tcase, is_less_16, 0, 100);
  tcase_add_test(tcase, is_less_17);
  tcase_add_test(tcase, is_less_18);
  tcase_add_test(tcase, is_less_19);
  tcase_add_test(tcase, is_less_20);
  tcase_add_test(tcase, is_less_21);
  tcase_add_test(tcase, is_less_22);
  tcase_add_test(tcase, is_less_23);
  tcase_add_test(tcase, is_less_24);
  tcase_add_test(tcase, is_less_25);
  tcase_add_test(tcase, is_less_26);
  tcase_add_test(tcase, is_less_27);
  tcase_add_test(tcase, is_less_28);
  tcase_add_test(tcase, is_less_29);

  //------------------------------------------------------------------------

  tcase_add_test(tcase, is_less_or_equal_0);
  tcase_add_test(tcase, is_less_or_equal_1);
  tcase_add_test(tcase, is_less_or_equal_2);
  tcase_add_test(tcase, is_less_or_equal_3);
  tcase_add_test(tcase, is_less_or_equal_4);
  tcase_add_test(tcase, is_less_or_equal_5);
  tcase_add_test(tcase, is_less_or_equal_6);
  tcase_add_test(tcase, is_less_or_equal_7);
  tcase_add_loop_test(tcase, is_less_or_equal_8, 0, 1000);
  tcase_add_loop_test(tcase, is_less_or_equal_9, 0, 1000);
  tcase_add_test(tcase, is_less_or_equal_10);
  tcase_add_loop_test(tcase, is_less_or_equal_11, 0, 1000);
  tcase_add_test(tcase, is_less_or_equal_12);
  tcase_add_test(tcase, is_less_or_equal_13);
  tcase_add_test(tcase, is_less_or_equal_14);
  tcase_add_test(tcase, is_less_or_equal_15);
  tcase_add_test(tcase, is_less_or_equal_16);
  tcase_add_test(tcase, is_less_or_equal_17);
  tcase_add_test(tcase, is_less_or_equal_18);
  tcase_add_test(tcase, less_or_equal_1);
  tcase_add_test(tcase, less_or_equal_2);
  tcase_add_test(tcase, less_or_equal_3);
  tcase_add_test(tcase, less_or_equal_4);
  tcase_add_test(tcase, less_or_equal_5);
  tcase_add_test(tcase, less_or_equal_6);
  tcase_add_test(tcase, less_or_equal_7);
  tcase_add_test(tcase, less_or_equal_8);
  tcase_add_test(tcase, less_or_equal_9);
  tcase_add_test(tcase, less_or_equal_10);
  tcase_add_test(tcase, less_or_equal_11);
  tcase_add_test(tcase, less_or_equal_12);
  tcase_add_test(tcase, less_or_equal_13);
  tcase_add_test(tcase, less_or_equal_14);
  tcase_add_test(tcase, less_or_equal_15);
  tcase_add_test(tcase, less_or_equal_16);
  tcase_add_test(tcase, less_or_equal_17);
  tcase_add_test(tcase, less_or_equal_18);
  tcase_add_test(tcase, less_or_equal_19);
  tcase_add_test(tcase, less_or_equal_20);
  tcase_add_test(tcase, less_or_equal_21);
  tcase_add_test(tcase, less_or_equal_22);
  tcase_add_test(tcase, s21_less_or_equal_23);
  tcase_add_test(tcase, test_is_less_or_equal_1);
  tcase_add_test(tcase, test_is_less_or_equal_2);
  tcase_add_test(tcase, test_is_less_or_equal_2i);
  tcase_add_test(tcase, test_is_less_or_equal_3);
  tcase_add_test(tcase, test_is_less_or_equal_4);
  tcase_add_test(tcase, test_is_less_or_equal_41);
  tcase_add_test(tcase, test_is_less_or_equal_5);
  tcase_add_test(tcase, test_is_less_or_equal_6);
  tcase_add_test(tcase, test_is_less_or_equal_7);
  tcase_add_test(tcase, test_is_less_or_equal_8);
  tcase_add_test(tcase, test_is_less_or_equal_8);
  tcase_add_test(tcase, test_is_less_or_equal_9);
  tcase_add_test(tcase, test_is_less_or_equal_10);
  tcase_add_test(tcase, is_less_or_equalTest01);
  tcase_add_test(tcase, is_less_or_equalTest1);
  tcase_add_test(tcase, is_less_or_equalTest2);
  tcase_add_test(tcase, is_less_or_equalTest3);
  tcase_add_test(tcase, is_less_or_equalTest4);
  tcase_add_test(tcase, is_less_or_equalTest5);
  tcase_add_test(tcase, is_less_or_equalTest6);
  tcase_add_test(tcase, is_less_or_equalTest7);
  tcase_add_test(tcase, is_less_or_equalTest8);
  tcase_add_test(tcase, is_less_or_equalTest9);
  tcase_add_test(tcase, is_less_or_equalTest10);
  tcase_add_test(tcase, is_less_or_equalTest11);
  tcase_add_test(tcase, is_less_or_equalTest12);
  tcase_add_test(tcase, is_less_or_equalTest13);
  tcase_add_test(tcase, is_less_or_equalTest14);
  tcase_add_test(tcase, is_less_or_equalTest15);
  tcase_add_test(tcase, is_less_or_equalTest16);
  tcase_add_test(tcase, is_less_or_equalTest18);
  tcase_add_test(tcase, is_less_or_equalTest19);
  tcase_add_test(tcase, is_less_or_equalTest20);
  tcase_add_test(tcase, is_less_or_equalTest21);
  tcase_add_test(tcase, is_less_or_equalTest22);
  tcase_add_test(tcase, is_less_or_equalTest23);
  tcase_add_test(tcase, is_less_or_equalTest24);
  tcase_add_test(tcase, is_less_or_equalTest25);
  tcase_add_test(tcase, is_less_or_equalTest26);
  tcase_add_test(tcase, is_less_or_equalTest27);
  tcase_add_test(tcase, is_less_or_equalTest28);
  tcase_add_test(tcase, is_less_or_equalTest29);
  tcase_add_test(tcase, is_less_or_equalTest30);
  tcase_add_test(tcase, is_less_or_equalTest31);
  tcase_add_test(tcase, is_less_or_equalTest32);
  tcase_add_test(tcase, is_less_or_equalTest33);
  tcase_add_test(tcase, is_less_or_equalTest34);
  tcase_add_test(tcase, is_less_or_equalTest35);
  tcase_add_test(tcase, is_less_or_equalTest36);

  //------------------------------------------------------------------------

  tcase_add_test(tcase, is_greater_00);
  tcase_add_test(tcase, is_greater_01);
  tcase_add_test(tcase, is_greater_02);
  tcase_add_test(tcase, is_greater_03);
  tcase_add_test(tcase, is_greater_04);
  tcase_add_test(tcase, is_greater_05);
  tcase_add_test(tcase, is_greater_06);
  tcase_add_test(tcase, is_greater_07);
  tcase_add_test(tcase, is_greater_08);
  tcase_add_loop_test(tcase, is_greater_09, 0, 1000);
  tcase_add_loop_test(tcase, is_greater_10, 0, 1000);
  tcase_add_test(tcase, is_greater_11);
  tcase_add_test(tcase, is_greater_12);
  tcase_add_test(tcase, is_greater_13);
  tcase_add_test(tcase, is_greater_14);
  tcase_add_test(tcase, is_greater_15);
  tcase_add_test(tcase, is_greater_16);
  tcase_add_test(tcase, is_greater_17);
  tcase_add_test(tcase, is_greater_18);
  tcase_add_test(tcase, is_greater_19);
  tcase_add_test(tcase, is_greater_20);
  tcase_add_test(tcase, is_greater_21);
  tcase_add_test(tcase, is_greater_22);
  tcase_add_test(tcase, is_greater_23);
  tcase_add_test(tcase, is_greater_24);
  tcase_add_test(tcase, is_greater_25);
  tcase_add_test(tcase, is_greater_26);
  tcase_add_test(tcase, is_greater_27);
  tcase_add_test(tcase, is_greater_28);
  tcase_add_test(tcase, is_greater_29);
  tcase_add_test(tcase, is_greater_30);
  tcase_add_test(tcase, is_greater_31);
  tcase_add_test(tcase, is_greater_32);
  tcase_add_test(tcase, is_greater_33);
  tcase_add_test(tcase, is_greater_34);
  tcase_add_test(tcase, is_greater_35);
  tcase_add_test(tcase, is_greater_36);
  tcase_add_test(tcase, is_greater_37);
  tcase_add_test(tcase, is_greater_38);
  tcase_add_test(tcase, is_greater_39);
  tcase_add_test(tcase, is_greater_40);
  tcase_add_test(tcase, is_greater_41);
  tcase_add_test(tcase, is_greater_42);
  tcase_add_test(tcase, is_greater_43);
  tcase_add_test(tcase, is_greater_44);
  tcase_add_test(tcase, is_greater_45);
  tcase_add_test(tcase, is_greater_46);
  tcase_add_test(tcase, is_greater_47);
  tcase_add_test(tcase, is_greater_48);
  tcase_add_test(tcase, is_greater_49);
  tcase_add_test(tcase, is_greater_50);
  tcase_add_test(tcase, is_greater_51);
  tcase_add_test(tcase, is_greater_52);
  tcase_add_test(tcase, is_greater_53);
  tcase_add_test(tcase, is_greater_54);
  tcase_add_test(tcase, is_greater_55);
  tcase_add_test(tcase, is_greater_56);
  tcase_add_test(tcase, is_greater_57);
  tcase_add_test(tcase, is_greater_58);
  tcase_add_test(tcase, is_greater_59);
  tcase_add_test(tcase, is_greater_60);
  tcase_add_test(tcase, is_greater_61);
  tcase_add_test(tcase, is_greater_62);
  tcase_add_test(tcase, is_greater_63);
  tcase_add_test(tcase, is_greater_64);
  tcase_add_test(tcase, is_greater_65);
  tcase_add_test(tcase, is_greater_66);
  tcase_add_test(tcase, is_greater_67);
  tcase_add_test(tcase, is_greater_68);
  tcase_add_test(tcase, is_greater_69);
  tcase_add_test(tcase, is_greater_70);
  tcase_add_test(tcase, is_greater_71);
  tcase_add_test(tcase, is_greater_72);
  tcase_add_test(tcase, is_greater_73);
  tcase_add_test(tcase, is_greater_74);
  tcase_add_test(tcase, is_greater_75);

  //------------------------------------------------------------------------

  tcase_add_test(tcase, is_greater_or_equal_00);
  tcase_add_test(tcase, is_greater_or_equal_01);
  tcase_add_test(tcase, is_greater_or_equal_02);
  tcase_add_test(tcase, is_greater_or_equal_03);
  tcase_add_test(tcase, is_greater_or_equal_04);
  tcase_add_test(tcase, is_greater_or_equal_05);
  tcase_add_test(tcase, is_greater_or_equal_06);
  tcase_add_test(tcase, is_greater_or_equal_07);
  tcase_add_loop_test(tcase, is_greater_or_equal_08, 0, 1000);
  tcase_add_loop_test(tcase, is_greater_or_equal_09, 0, 1000);
  tcase_add_loop_test(tcase, is_greater_or_equal_10, 0, 1000);
  tcase_add_test(tcase, is_greater_or_equal_11);
  tcase_add_test(tcase, is_greater_or_equal_12);
  tcase_add_test(tcase, is_greater_or_equal_13);
  tcase_add_test(tcase, is_greater_or_equal_14);
  tcase_add_test(tcase, is_greater_or_equal_15);
  tcase_add_test(tcase, is_greater_or_equal_17);
  tcase_add_test(tcase, is_greater_or_equal_18);
  tcase_add_test(tcase, is_greater_or_equal_19);
  tcase_add_test(tcase, is_greater_or_equal_20);
  tcase_add_test(tcase, is_greater_or_equal_21);
  tcase_add_test(tcase, is_greater_or_equal_22);
  tcase_add_test(tcase, is_greater_or_equal_23);
  tcase_add_test(tcase, is_greater_or_equal_24);
  tcase_add_test(tcase, is_greater_or_equal_25);
  tcase_add_test(tcase, is_greater_or_equal_26);
  tcase_add_test(tcase, is_greater_or_equal_27);
  tcase_add_test(tcase, is_greater_or_equal_28);
  tcase_add_test(tcase, is_greater_or_equal_29);
  tcase_add_test(tcase, is_greater_or_equal_30);
  tcase_add_test(tcase, is_greater_or_equal_31);

  //------------------------------------------------------------------------

  tcase_add_test(tcase, is_equal_00);
  tcase_add_test(tcase, is_equal_01);
  tcase_add_test(tcase, is_equal_02);
  tcase_add_test(tcase, is_equal_03);
  tcase_add_test(tcase, is_equal_04);
  tcase_add_test(tcase, is_equal_05);
  tcase_add_test(tcase, is_equal_06);
  tcase_add_test(tcase, is_equal_07);
  tcase_add_loop_test(tcase, is_equal_08, 0, 1000);
  tcase_add_loop_test(tcase, is_equal_09, 0, 1000);
  tcase_add_loop_test(tcase, is_equal_10, 0, 1000);
  tcase_add_test(tcase, is_equal_11);
  tcase_add_test(tcase, is_equal_12);
  tcase_add_test(tcase, is_equal_13);
  tcase_add_test(tcase, is_equal_14);
  tcase_add_test(tcase, is_equal_15);
  tcase_add_test(tcase, is_equal_16);
  tcase_add_test(tcase, is_equal_17);
  tcase_add_test(tcase, is_equal_18);
  tcase_add_test(tcase, is_equal_19);
  tcase_add_test(tcase, is_equal_20);
  tcase_add_test(tcase, is_equal_22);
  tcase_add_test(tcase, is_equal_23);
  tcase_add_test(tcase, is_equal_24);
  tcase_add_test(tcase, is_equal_25);
  tcase_add_test(tcase, is_equal_26);
  tcase_add_test(tcase, is_equal_27);
  tcase_add_test(tcase, is_equal_28);
  tcase_add_test(tcase, is_equal_29);
  tcase_add_test(tcase, is_equal_30);
  tcase_add_test(tcase, is_equal_31);
  tcase_add_test(tcase, is_equal_32);
  tcase_add_test(tcase, is_equal_33);
  tcase_add_test(tcase, is_equal_34);
  tcase_add_test(tcase, is_equal_35);
  tcase_add_test(tcase, is_equal_36);
  tcase_add_test(tcase, is_equal_37);
  tcase_add_test(tcase, is_equal_38);
  tcase_add_test(tcase, is_equal_39);
  tcase_add_test(tcase, is_equal_40);
  tcase_add_test(tcase, is_equal_41);
  tcase_add_test(tcase, is_equal_42);
  tcase_add_test(tcase, is_equal_43);
  tcase_add_test(tcase, is_equal_44);
  tcase_add_test(tcase, is_equal_45);
  tcase_add_test(tcase, is_equal_46);
  tcase_add_test(tcase, is_equal_47);
  tcase_add_test(tcase, is_equal_48);
  tcase_add_test(tcase, is_equal_49);
  tcase_add_test(tcase, is_equal_50);
  tcase_add_test(tcase, is_equal_51);
  tcase_add_test(tcase, is_equal_52);
  tcase_add_test(tcase, is_equal_53);
  tcase_add_test(tcase, is_equal_54);
  tcase_add_test(tcase, is_equal_55);
  tcase_add_test(tcase, is_equal_56);
  tcase_add_test(tcase, is_equal_57);
  tcase_add_test(tcase, is_equal_58);
  tcase_add_test(tcase, s21_equal_21);

  tcase_add_test(tcase, dec_is_not_equal_00);
  tcase_add_test(tcase, dec_is_not_equal_01);
  tcase_add_test(tcase, dec_is_not_equal_02);
  tcase_add_test(tcase, dec_is_not_equal_03);
  tcase_add_test(tcase, dec_is_not_equal_04);
  tcase_add_test(tcase, dec_is_not_equal_05);
  tcase_add_test(tcase, dec_is_not_equal_06);
  tcase_add_test(tcase, dec_is_not_equal_07);
  tcase_add_test(tcase, dec_is_not_equal_08);
  tcase_add_loop_test(tcase, dec_is_not_equal_09, 0, 1000);
  tcase_add_loop_test(tcase, dec_is_not_equal_10, 0, 1000);
  tcase_add_loop_test(tcase, dec_is_not_equal_11, 0, 1000);
  tcase_add_test(tcase, dec_is_not_equal_12);
  tcase_add_test(tcase, dec_is_not_equal_14);
  tcase_add_test(tcase, dec_is_not_equal_15);
  tcase_add_test(tcase, dec_is_not_equal_16);
  tcase_add_test(tcase, dec_is_not_equal_17);
  tcase_add_test(tcase, dec_is_not_equal_18);
  tcase_add_test(tcase, dec_is_not_equal_19);
  tcase_add_test(tcase, dec_is_not_equal_20);
  tcase_add_test(tcase, dec_is_not_equal_21);
  tcase_add_test(tcase, dec_is_not_equal_22);
  tcase_add_test(tcase, dec_is_not_equal_23);

  //------------------------------------------------------------------------

  suite_add_tcase(suite, tcase);

  return suite;
}




//------------------------------------------------------------------------from_int_to_decimal

START_TEST(from_int_to_decimal_0) {
  decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -2147483648;
  from_int_to_decimal(tmp, &val);
  from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_1) {
  decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -123456789;
  from_int_to_decimal(tmp, &val);
  from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_2) {
  decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 2147483647;
  from_int_to_decimal(tmp, &val);
  from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_1_1) {
  decimal val = {{0, 0, 0, 0}};

  from_int_to_decimal(0, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  dec_zero_decimal(&val);
  from_int_to_decimal(-128, &val);
  ck_assert_int_eq(val.bits[0], 128);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 2147483648);

  dec_zero_decimal(&val);
  from_int_to_decimal(127, &val);
  ck_assert_int_eq(val.bits[0], 127);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  dec_zero_decimal(&val);
  from_int_to_decimal(-2147483648, &val);
  ck_assert_int_eq(val.bits[0], 2147483648);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 2147483648);

  dec_zero_decimal(&val);
  from_int_to_decimal(2147483647, &val);
  ck_assert_int_eq(val.bits[0], 2147483647);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST


START_TEST(test_from_int_to_decimal_1_2) {
  int a = 100;
  decimal b = {{0, 0, 0, 0}};
  decimal *ptr_b = &b;

  int add = from_int_to_decimal(a, ptr_b);  // a записываем в b
  decimal etalon = {{1000, 0, 0, 0}};
  ck_assert_int_eq(add, 0);
  // выходное значение from_int_to_decimal -
  // 0 TRUE и 1 FALSE
  // is_equal Возвращаемое значение: 0 - FALSE 1 - TRUE
  int error = is_equal(b, etalon);
  ck_assert_int_eq(error, 0);
}
END_TEST


START_TEST(from_int_to_decimalTest1) {
  // 6412
  int src1 = 1;
  decimal origin = {0}, result = {0};
  decimal *res = &result;
  from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimalTest2) {
  // 6428
  int src1 = -1;
  decimal origin = {0}, result = {0};
  decimal *res = &result;
  from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimalTest3) {
  // 6444
  int src1 = 0;
  decimal origin = {0}, result = {0};
  decimal *res = &result;
  from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimalTest4) {
  // 6460
  int src1 = 0;
  decimal origin = {0}, result = {0};
  decimal *res = &result;
  from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimalTest5) {
  // 6476
  int src1 = -987879878;
  decimal origin = {0}, result = {0};
  decimal *res = &result;
  from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00111010111000011101100111000110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimalTest6) {
  // 6492
  int src1 = -2147483646;
  decimal origin = {0}, result = {0};
  decimal *res = &result;
  from_int_to_decimal(src1, res);

  origin.bits[0] = 0b01111111111111111111111111111110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimalTest7) {
  // 6508
  int src1 = 2147483646;
  decimal origin = {0}, result = {0};
  decimal *res = &result;
  from_int_to_decimal(src1, res);

  origin.bits[0] = 0b01111111111111111111111111111110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimalTest8) {
  // 6524
  int src1 = 796132784;
  decimal origin = {0}, result = {0};
  decimal *res = &result;
  from_int_to_decimal(src1, res);

  origin.bits[0] = 0b00101111011101000000010110110000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimalTest9) {
  // 6540
  int src1 = -12345677;
  decimal origin = {0}, result = {0};
  decimal *res = &result;
  from_int_to_decimal(src1, res);
  origin.bits[0] = 0b00000000101111000110000101001101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

//------------------------------------------------------------------------from_float_to_decimal

START_TEST(float_to_decimal_1) {
  float a = 1234567.0;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {0};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_2) {
  float a = 123456.8;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {0};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_3) {
  float a = 12345.60;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {0};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_4) {
  float a = 1.000000;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {0};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_5) {
  float a = 1.00001;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {0};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);

  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_6) {
  float a = 1.456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {0};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_10) {
  float a = 0.123456;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {0};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_13) {
  float a = 1.7891289;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {0};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(float_to_decimal_16) {
  float a = 123.456;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {0};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_19) {
  float a = 123456.1;
  float b = 0;
  int error = 0;
  int func_error = 0;
  decimal dec = {0};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_29) {
  float a = 0.9;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {{0}};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_30) {
  float a = 1.200000e-27;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {{0}};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_31) {
  float a = 1.2e-26;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {{0}};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_32) {
  float a = 1.2e-25;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {{0}};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_33) {
  float a = 1.2e-24;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {{0}};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_34) {
  float a = 1.2e-23;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {{0}};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_35) {
  float a = 1.2e-22;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {{0}};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_36) {
  float a = 1.2e-21;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {{0}};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_52) {
  float a = 0.0;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {{0}};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_53) {
  float a = MAX_DEC;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  decimal dec = {{0}};
  func_error = from_float_to_decimal(a, &dec);
  from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
}
END_TEST

START_TEST(float_to_decimal_54) {
  decimal val = {0};
  float fl1 = 3.000000;
  float fl2 = 127.1234;
  float fl1_res = 0;
  float fl2_res = 0;
  from_float_to_decimal(fl1, &val);
  from_decimal_to_float(val, &fl1_res);
  dec_zero_decimal(&val);
  ck_assert_double_eq(fl1, fl1_res);
  from_float_to_decimal(fl2, &val);
  from_decimal_to_float(val, &fl2_res);

  ck_assert_double_eq(fl2, fl2_res);
}
END_TEST

START_TEST(float_to_decimal_55) {
  decimal val1 = {0};
  decimal val2 = {0};
  float fl1 = -128.023;
  float fl2 = 12345.4;
  float fl1_res = 0;
  float fl2_res = 0;

  from_float_to_decimal(fl1, &val1);
  from_decimal_to_float(val1, &fl1_res);

  ck_assert_double_eq_tol(fl1, fl1_res, 1e-6);

  from_float_to_decimal(fl2, &val2);
  from_decimal_to_float(val2, &fl2_res);

  ck_assert_double_eq_tol(fl2, fl2_res, 1e-6);
}
END_TEST

START_TEST(float_to_decimal_56) {
  decimal val = {0};
  float num = -2147483;
  from_float_to_decimal(num, &val);

  ck_assert_int_eq(val.bits[0], 2147483);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 2147483648);
}
END_TEST

START_TEST(float_to_decimal_58) {
  decimal val = {0};
  from_float_to_decimal(1.02E+09, &val);

  ck_assert_int_eq(val.bits[0], 1020000000);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_59) {
  decimal val = {0};
  float fl1 = -333.2222;
  float fl2 = -2.147483E+20;
  float fl1_res = 0;
  float fl2_res = 0;

  from_float_to_decimal(fl1, &val);
  from_decimal_to_float(val, &fl1_res);
  ck_assert_double_eq_tol(fl1, fl1_res, 1e-28);
  dec_zero_decimal(&val);

  from_float_to_decimal(fl2, &val);
  from_decimal_to_float(val, &fl2_res);

  ck_assert_double_eq_tol(fl2, fl2_res, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_60) {
  decimal val = {0};
  float a = 1.0 / 0.0;
  from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_61) {
  decimal val = {0};
  float a = -1.0 / 0.0;
  from_float_to_decimal(a, &val);
  from_decimal_to_float(val, &a);

  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_62) {
  decimal val = {0};
  float a = 1e-30;
  from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_63) {
  decimal dec = {0};
  float tmp = 0;
  float tmp1 = 0.03;
  from_float_to_decimal(tmp1, &dec);
  from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, tmp1, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_64) {
  decimal dec = {0};
  from_float_to_decimal(-128.023, &dec);
  float tmp = 0;
  from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -128.023, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_65) {
  decimal dec = {0};
  from_float_to_decimal(-2.147483E+09, &dec);
  float tmp = 0;
  from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -2.147483E+09, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_66) {
  decimal dec = {0};
  from_float_to_decimal(22.14836E+03, &dec);
  float tmp = 0;
  from_decimal_to_float(dec, &tmp);

  ck_assert_float_eq_tol(tmp, 22148.36, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_67) {
  decimal dec = {0};
  from_float_to_decimal(1.02E+08, &dec);
  float tmp = 0;
  from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 1.02E+08, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_68) {
  decimal dec = {0};
  from_float_to_decimal(-333.2222, &dec);
  float tmp = 0;
  from_decimal_to_float(dec, &tmp);

  ck_assert_float_eq_tol(tmp, -333.2222, 1e-06);
}
END_TEST

START_TEST(float_to_decimal_69) {
  decimal dec = {0};
  float a = 1.0 / 0.0;
  int ret = from_float_to_decimal(a, &dec);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(float_to_decimal_70) {
  decimal dec = {0};
  float a = -1.0 / 0.0;
  from_float_to_decimal(a, &dec);
  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(float_to_decimal_71) {
  float f = 0.03;
  decimal result = {0};
  decimal check = {{3, 0, 0, 0}};
  set_scale(&check, 2);
  int return_value = from_float_to_decimal(f, &result);

  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST


START_TEST(float_to_decimal_73) {
  float f = 1.0 / 0.0;
  decimal result = {0};
  decimal check = {{0, 0, 0, 0}};
  int return_value = from_float_to_decimal(f, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

//------------------------------------------------------------------------from_decimal_to_int

#define EXPONENT_PLUS_1 65536

#define EXPONENT_PLUS_28 1835008
START_TEST(from_decimal_to_int_0) {
  decimal val = {{123456789, 0, 0, 0}};
  set_scale(&val, 5);
  int res = 1234;
  int tmp = 0;
  int *dst = &tmp;
  from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_int_1) {
  decimal val = {{123456789, 0, 0, 0}};
  set_bit(&val, 127, 1);
  set_scale(&val, 5);
  int res = -1234;
  int tmp = 0;
  int *dst = &tmp;
  from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_int_2) {
  decimal var = {{0, 0, 0, 0}};
  int value = 0;
  from_int_to_decimal(5, &var);
  from_decimal_to_int(var, &value);
  ck_assert_int_eq(5, value);
}
END_TEST

START_TEST(from_decimal_to_int_3) {
  int n = dec_rand_r(-8388608, 8388608);
  decimal var = {{0, 0, 0, 0}};
  int value = 0;
  from_int_to_decimal(n, &var);
  from_decimal_to_int(var, &value);
  ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(from_decimal_to_int_4) {
  int n = 666;
  decimal var = {{0, 1, 0, 0}};
  int value = 0;
  from_int_to_decimal(n, &var);
  from_decimal_to_int(var, &value);
  ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(from_decimal_to_int_1_1) {
  decimal src = {{0}};
  int result = 0, number = 0;
  src.bits[0] = INT_MAX;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = from_decimal_to_int(src, &number);
  ck_assert_float_eq(number, 2147483647);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_decimal_to_int_2_1) {
  decimal src = {{0}};
  int result = 0, number = 0;
  src.bits[0] = 133141;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 133141);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_decimal_to_int_3_1) {
  decimal src = {{0}};
  int result = 0, number = 0;
  src.bits[0] = 2147483647;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  set_bit(&src, 127, 1);
  result = from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -2147483647);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_decimal_to_int_4_1) {
  decimal src = {{0}};
  int result = 0, number = 0;
  long int c = 2147483648;
  src.bits[0] = 123451234;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;
  result = from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -123451234);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_decimal_to_int_5) {
  decimal src = {{0}};
  int result = 0, number = 0;
  long int c = 2147483648;
  src.bits[0] = 18;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;  // 2147483648
  result = from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -18);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_decimal_to_int_6) {
  decimal src = {{0}};
  int result = 0, number = 0;
  src.bits[0] = UINT_MAX;
  src.bits[1] = UINT_MAX;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -1);
  ck_assert_int_eq(result, 1);
}
END_TEST

int check, result, code;

START_TEST(test_from_decimal_to_int_0) {
  decimal a = {{100, 0, 0, 0}};
  check = 100;
  code = from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_from_decimal_to_int_1) {
  decimal a = {{INT_MAX, 0, 0, 0}};
  check = INT_MAX;
  code = from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_from_decimal_to_int_2) {
  decimal a = {{INT_MAX, INT_MAX, 0, 0}};
  set_bit(&a, 127, 1);
  code = from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, -2147483647);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_3) {
  decimal a = {{INT_MAX, INT_MAX, INT_MAX, 0}};
  code = from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, 2147483647);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_4) {
  decimal a = {{INT_MAX, INT_MAX, INT_MAX, INT_MAX}};
  code = from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, 2147483647);
  ck_assert_int_eq(code, 1);
}
END_TEST


START_TEST(test_from_decimal_to_int_7) {
  int result = 0;
  decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  check = -1;
  code = from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 1);
}
END_TEST


START_TEST(test_from_decimal_to_int_9) {
  decimal a = {{INT_MAX, 0, 0, INT_MIN}};
  check = -INT_MAX;
  code = from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_from_decimal_to_int_10) {
  decimal a = {{INT_MAX, 0, 0, INT_MIN}};

  check = -INT_MAX;
  code = from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_from_decimal_to_int_11) {
  decimal a = {{INT_MAX, 0, 0, EXPONENT_PLUS_1}};
  check = 214748364;  // (int)(INT_MAX / 10^1)
  code = from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST


START_TEST(test_from_decimal_to_int_14) {
  decimal a = {{INT_MAX, 0, 0, EXPONENT_PLUS_28}};
  check = 0;  // (int)(INT_MAX / 10^28)
  code = from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST


START_TEST(test_from_decimal_to_int_16) {
  decimal a;
  a.bits[0] = 0b00000000000000000000000000000001;
  a.bits[1] = 0b00000000000000000000000000000000;
  a.bits[2] = 0b00000000000000000000000000000000;
  a.bits[3] = 0b00000000000000000000000000000000;
  check = 1;
  code = from_decimal_to_int(a, &result);
  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, 0);
}
END_TEST


START_TEST(from_decimal_to_intTest1) {
  // 6556
  decimal src1;
  // src1 = 2;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int result = 0;
  int *res = &result;
  from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(from_decimal_to_intTest2) {
  // 6570
  decimal src1;
  // src1 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int result = 0;
  int *res = &result;
  from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_decimal_to_intTest3) {
  // 6584
  decimal src1;
  // src1 = 3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  int result = 0;
  int *res = &result;
  from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 3);
}
END_TEST

START_TEST(from_decimal_to_intTest4) {
  // 6598
  decimal src1;
  // src1 = 4.5;

  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  int result = 0;
  int *res = &result;
  from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 4);
}
END_TEST

START_TEST(from_decimal_to_intTest5) {
  // 6612
  decimal src1;
  // src1 = -4.5;

  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  int result = 0;
  int *res = &result;
  from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -4);
}
END_TEST

START_TEST(from_decimal_to_intTest11) {
  // 6696
  decimal src1;
  // src1 = 1;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int result = 0;
  int *res = &result;
  from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(from_decimal_to_intTest12) {
  // 6710
  decimal src1;
  // src1 = 1.25;

  src1.bits[0] = 0b00000000000000000000000001111101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000100000000000000000;
  int result = 0;
  int *res = &result;
  from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(from_decimal_to_intTest13) {
  // 6724
  decimal src1;
  // src1 = -1.25;

  src1.bits[0] = 0b00000000000000000000000001111101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000100000000000000000;
  int result = 0;
  int *res = &result;
  from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(from_decimal_to_intTest14) {
  // 6738
  decimal src1;
  // src1 = -12.25;

  src1.bits[0] = 0b00000000000000000000010011001001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000100000000000000000;
  int result = 0;
  int *res = &result;
  from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -12);
}
END_TEST

START_TEST(from_decimal_to_intTest15) {
  // 6752
  decimal src1;
  // src1 = -3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  int result = 0;
  int *res = &result;
  from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -3);
}
END_TEST

//------------------------------------------------------------------------from_decimal_to_float

START_TEST(from_decimal_to_float_0) {
  decimal val = {{123456789, 0, 0, 0}};
  set_scale(&val, 5);
  float res = 1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_float_1) {
  decimal val = {{123456789, 0, 0, 0}};
  set_bit(&val, 127, 1);
  set_scale(&val, 5);
  float res = -1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_float_2) {
  decimal var = {{0, 0, 0, 0}};
  float value = 0;
  from_float_to_decimal(5.0, &var);
  from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(5.0, value, 10e-5);
}
END_TEST

START_TEST(from_decimal_to_float_3) {
  float n = dec_rand_r(-8388608, 8388608);
  decimal var = {{0, 0, 0, 0}};
  float value = 0;
  from_float_to_decimal(n, &var);
  from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(from_decimal_to_float_4) {
  float n = dec_rand_r(-1e-6 / 3, 1e-6 / 3);
  decimal var = {{0, 0, 0, 0}};
  float value = 0;
  from_float_to_decimal(n, &var);
  from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(from_decimal_to_float_1_1) {
  decimal var = {0};
  float value = 0;
  from_float_to_decimal(5.0, &var);
  from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(5.0, value, 10e-5);
}
END_TEST

START_TEST(from_decimal_to_float_2_1) {
  float n = dec_rand_r(-8388608, 8388608);
  decimal var = {0};
  float value = 0;
  from_float_to_decimal(n, &var);
  from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(from_decimal_to_float_3_1) {
  float n = dec_rand_r(-1e-6 / 3, 1e-6 / 3);
  decimal var = {0};
  float value = 0;
  from_float_to_decimal(n, &var);
  from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(n, value, 10);
}
END_TEST

START_TEST(from_decimal_to_float_4_1) {
  decimal value = {{1812, 0, 0, 0}};
  set_bit(&value, 127, 1);
  float result = 0;
  float check = -1812;
  int return_value = from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(from_decimal_to_float_5) {
  decimal value = {{18122, 0, 0, 0}};
  set_scale(&value, 3);
  set_bit(&value, 127, 1);
  float result = 0;
  float check = -18.122;
  int return_value = from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(from_decimal_to_float_6) {
  decimal value = {{0xFFFFFF, 0, 0, 0}};
  float result = 0;
  float check = 16777215;
  int return_value = from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(from_decimal_to_float_7) {
  decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  float result = 0;
  float check = 0xFFFFFFFFFFFFFFFF;
  int return_value = from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

//------------------------------------------------------------------------END

Suite *test_converters(void) {
  Suite *suite = suite_create("converters_suite");
  TCase *tcase = tcase_create("converters_tcase");

  //------------------------------------------------------------------------from_int_to_decimal

  tcase_add_test(tcase, from_int_to_decimal_0);
  tcase_add_test(tcase, from_int_to_decimal_1);
  tcase_add_test(tcase, from_int_to_decimal_2);
  tcase_add_test(tcase, from_int_to_decimal_1_1);
  tcase_add_test(tcase, test_from_int_to_decimal_1_2);
  tcase_add_test(tcase, from_int_to_decimalTest1);
  tcase_add_test(tcase, from_int_to_decimalTest2);
  tcase_add_test(tcase, from_int_to_decimalTest3);
  tcase_add_test(tcase, from_int_to_decimalTest4);
  tcase_add_test(tcase, from_int_to_decimalTest5);
  tcase_add_test(tcase, from_int_to_decimalTest6);
  tcase_add_test(tcase, from_int_to_decimalTest7);
  tcase_add_test(tcase, from_int_to_decimalTest8);
  tcase_add_test(tcase, from_int_to_decimalTest9);
  tcase_add_test(tcase, from_int_to_decimal_0);

  //------------------------------------------------------------------------from_decimal_to_int

  tcase_add_test(tcase, from_decimal_to_int_0);
  tcase_add_test(tcase, from_decimal_to_int_1);
  tcase_add_test(tcase, from_decimal_to_int_2);
  tcase_add_loop_test(tcase, from_decimal_to_int_3, 0, 1000);
  tcase_add_test(tcase, from_decimal_to_int_4);
  tcase_add_test(tcase, from_decimal_to_int_1_1);
  tcase_add_test(tcase, from_decimal_to_int_2_1);
  tcase_add_test(tcase, from_decimal_to_int_3_1);
  tcase_add_test(tcase, from_decimal_to_int_4_1);
  tcase_add_test(tcase, from_decimal_to_int_5);
  tcase_add_test(tcase, from_decimal_to_int_6);
  tcase_add_test(tcase, test_from_decimal_to_int_0);
  tcase_add_test(tcase, test_from_decimal_to_int_1);
  tcase_add_test(tcase, test_from_decimal_to_int_2);
  tcase_add_test(tcase, test_from_decimal_to_int_3);
  tcase_add_test(tcase, test_from_decimal_to_int_4);
  tcase_add_test(tcase, test_from_decimal_to_int_7);
  tcase_add_test(tcase, test_from_decimal_to_int_9);
  tcase_add_test(tcase, test_from_decimal_to_int_10);
  tcase_add_test(tcase, test_from_decimal_to_int_11);
  tcase_add_test(tcase, test_from_decimal_to_int_14);
  tcase_add_test(tcase, test_from_decimal_to_int_16);
  tcase_add_test(tcase, from_decimal_to_intTest1);
  tcase_add_test(tcase, from_decimal_to_intTest2);
  tcase_add_test(tcase, from_decimal_to_intTest3);
  tcase_add_test(tcase, from_decimal_to_intTest4);
  tcase_add_test(tcase, from_decimal_to_intTest5);
  tcase_add_test(tcase, from_decimal_to_intTest11);
  tcase_add_test(tcase, from_decimal_to_intTest12);
  tcase_add_test(tcase, from_decimal_to_intTest13);
  tcase_add_test(tcase, from_decimal_to_intTest14);
  tcase_add_test(tcase, from_decimal_to_intTest15);

  //------------------------------------------------------------------------from_float_to_decimal

  tcase_add_test(tcase, float_to_decimal_1);
  tcase_add_test(tcase, float_to_decimal_2);
  tcase_add_test(tcase, float_to_decimal_3);
  tcase_add_test(tcase, float_to_decimal_4);
  tcase_add_test(tcase, float_to_decimal_5);
  tcase_add_test(tcase, float_to_decimal_6);
  tcase_add_test(tcase, float_to_decimal_10);
  tcase_add_test(tcase, float_to_decimal_13);
  tcase_add_test(tcase, float_to_decimal_16);
  tcase_add_test(tcase, float_to_decimal_19);
  tcase_add_test(tcase, float_to_decimal_29);
  tcase_add_test(tcase, float_to_decimal_30);
  tcase_add_test(tcase, float_to_decimal_31);
  tcase_add_test(tcase, float_to_decimal_32);
  tcase_add_test(tcase, float_to_decimal_33);
  tcase_add_test(tcase, float_to_decimal_34);
  tcase_add_test(tcase, float_to_decimal_35);
  tcase_add_test(tcase, float_to_decimal_36);
  tcase_add_test(tcase, float_to_decimal_52);
  tcase_add_test(tcase, float_to_decimal_53);
  tcase_add_test(tcase, float_to_decimal_54);
  tcase_add_test(tcase, float_to_decimal_55);
  tcase_add_test(tcase, float_to_decimal_56);
  tcase_add_test(tcase, float_to_decimal_58);
  tcase_add_test(tcase, float_to_decimal_59);
  tcase_add_test(tcase, float_to_decimal_60);
  tcase_add_test(tcase, float_to_decimal_61);
  tcase_add_test(tcase, float_to_decimal_62);
  tcase_add_test(tcase, float_to_decimal_63);
  tcase_add_test(tcase, float_to_decimal_64);
  tcase_add_test(tcase, float_to_decimal_65);
  tcase_add_test(tcase, float_to_decimal_66);
  tcase_add_test(tcase, float_to_decimal_67);
  tcase_add_test(tcase, float_to_decimal_68);
  tcase_add_test(tcase, float_to_decimal_69);
  tcase_add_test(tcase, float_to_decimal_70);
  tcase_add_test(tcase, float_to_decimal_71);
  tcase_add_test(tcase, float_to_decimal_73);

  //------------------------------------------------------------------------from_decimal_to_float

  tcase_add_test(tcase, from_decimal_to_float_0);
  tcase_add_test(tcase, from_decimal_to_float_1);
  tcase_add_test(tcase, from_decimal_to_float_2);
  tcase_add_loop_test(tcase, from_decimal_to_float_3, 0, 100);
  tcase_add_loop_test(tcase, from_decimal_to_float_4, 0, 100);
  tcase_add_test(tcase, from_decimal_to_float_1_1);
  tcase_add_loop_test(tcase, from_decimal_to_float_2_1, 0, 100);
  tcase_add_loop_test(tcase, from_decimal_to_float_3_1, 0, 100);
  tcase_add_test(tcase, from_decimal_to_float_4_1);
  tcase_add_test(tcase, from_decimal_to_float_5);
  tcase_add_test(tcase, from_decimal_to_float_6);
  tcase_add_test(tcase, from_decimal_to_float_7);

  //------------------------------------------------------------------------END

  suite_add_tcase(suite, tcase);

  return suite;
}


//------------------------------------------------------------------------dec_floor

void floor_test_function(float n, float accuracy) {
  decimal var1 = {0}, var2 = {0};
  float value1 = 0, value2 = 0;
  from_float_to_decimal(n, &var1);
  dec_floor(var1, &var2);
  from_decimal_to_float(var2, &value2);
  value1 = floorf(n);
  ck_assert_float_eq_tol(value1, value2, accuracy);
}

START_TEST(floor_0) {
  decimal val = {{2, 0, 0, 0}};
  decimal res;
  ck_assert_int_eq(0, dec_floor(val, &res));
}
END_TEST

START_TEST(floor_1) {
  decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  dec_floor(val, &res);
  float fres = 0;
  from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-2, fres);
}
END_TEST

START_TEST(floor_2) {
  decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  set_scale(&val, 5);
  dec_floor(val, &res);
  float fres = 0;
  from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-1, fres);
}
END_TEST

START_TEST(floor_3) {
  decimal val = {{2, 0, 0, 0}};
  decimal res = {{0}};
  set_scale(&val, 5);
  dec_floor(val, &res);
  float fres = 0;
  from_decimal_to_float(res, &fres);
  ck_assert_float_eq(0, fres);
}
END_TEST

START_TEST(floor_4) {
  float n = dec_rand_r(-8388608, 8388608);
  floor_test_function(n, 10);
}

START_TEST(floor_5) {
  decimal value_1 = {{7444923, 0, 0, 0}};
  set_scale(&value_1, 5);
  decimal check = {{74, 0, 0, 0}};
  decimal result = {0};
  int return_value = dec_floor(value_1, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(floor_6) {
  decimal value_1 = {{7444923, 0, 0, 0}};
  set_scale(&value_1, 5);
  set_bit(&value_1, 127, 1);
  decimal check = {{75, 0, 0, 0}};
  set_bit(&check, 127, 1);
  decimal result = {0};
  int return_value = dec_floor(value_1, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(floor_7) {
  decimal src1;
  src1.bits[0] = 0b00001111111111111111111111111111;
  src1.bits[1] = 0b00111110001001010000001001100001;
  src1.bits[2] = 0b00100000010011111100111001011110;
  src1.bits[3] = 0b10000000000010100000000000000000;
  decimal res_od = {0};
  dec_floor(src1, &res_od);
  decimal result = {0};
  result.bits[0] = 0b10100111011001000000000000000000;
  result.bits[1] = 0b00001101111000001011011010110011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

//------------------------------------------------------------------------dec_round

void round_test_function(float n, float accuracy) {
  decimal var1 = {{0}}, var2 = {{0}};
  float value1 = 0.0, value2 = 0.0;
  from_float_to_decimal(n, &var1);
  dec_round(var1, &var2);
  from_decimal_to_float(var2, &value2);
  value1 = roundf(n);
  ck_assert_float_eq_tol(value1, value2, accuracy);
  return;
}

START_TEST(round_0) {
  decimal val = {{7, 7, 7, 0}};
  decimal res;
  dec_round(val, &res);
  float fres = 0;
  from_decimal_to_float(res, &fres);
  float need = 129127208515966861312.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(round_1) {
  decimal val = {{3, 3, 3, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(0, dec_round(val, &res));
}
END_TEST

START_TEST(round_2) {
  decimal val = {{3, 3, 3, 0}};
  decimal res = {{0}};
  set_scale(&val, 5);
  ck_assert_int_eq(0, dec_round(val, &res));
}
END_TEST

START_TEST(round_3) {
  decimal val = {{7, 7, 7, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  set_scale(&val, 5);
  ck_assert_int_eq(0, dec_round(val, &res));
}
END_TEST

START_TEST(round_4) {
  decimal val = {{25, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  set_scale(&val, 1);
  ck_assert_int_eq(0, dec_round(val, &res));
}
END_TEST

START_TEST(round_5) {
  decimal val = {{26, 0, 0, 0}};
  decimal res = {{0}};
  set_scale(&val, 1);
  ck_assert_int_eq(0, dec_round(val, &res));
}
END_TEST

START_TEST(round_6) {
  decimal val = {{115, 0, 0, 0}};
  decimal res = {{0}};
  set_scale(&val, 1);
  ck_assert_int_eq(0, dec_round(val, &res));
}
END_TEST

START_TEST(round_7) {
  decimal val = {{118, 0, 0, 0}};
  decimal res = {{0}};
  set_scale(&val, 1);
  ck_assert_int_eq(0, dec_round(val, &res));
}
END_TEST

START_TEST(round_8) {
  decimal val = {{125, 0, 0, 0}};
  decimal res = {{0}};
  set_scale(&val, 1);
  ck_assert_int_eq(0, dec_round(val, &res));
}
END_TEST

START_TEST(round_9) {
  decimal val = {{128, 0, 0, 0}};
  decimal res = {{0}};
  set_scale(&val, 1);
  dec_round(val, &res);
  float fres = 0;
  from_decimal_to_float(res, &fres);
  float need = 13;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(round_10) {
  float n = dec_rand_r(-8388608, 8388608);
  round_test_function(n, 10);
}

START_TEST(round_11) {
  decimal value_1 = {{7464923, 0, 0, 0}};
  set_scale(&value_1, 5);
  decimal check = {{75, 0, 0, 0}};
  decimal result = {0};
  int return_value = dec_round(value_1, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(round_12) {
  decimal value_1 = {{7444923, 0, 0, 0}};
  set_scale(&value_1, 5);
  decimal check = {{74, 0, 0, 0}};
  decimal result = {0};
  int return_value = dec_round(value_1, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(round_13) {
  decimal value_1 = {{7464923, 0, 0, 0}};
  set_bit(&value_1, 127, 1);
  set_scale(&value_1, 5);
  decimal check = {{75, 0, 0, 0}};
  set_bit(&check, 127, 1);
  decimal result = {0};
  int return_value = dec_round(value_1, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(round_14) {
  decimal value_1 = {{7444923, 0, 0, 0}};
  set_bit(&value_1, 127, 1);
  set_scale(&value_1, 5);
  decimal check = {{74, 0, 0, 0}};
  set_bit(&check, 127, 1);
  decimal result = {0};
  int return_value = dec_round(value_1, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(round_15) {
  decimal src1 = {0};
  src1.bits[0] = 0b01010101001110101110101110110001;
  src1.bits[1] = 0b00001101101101001101101001011111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000100100000000000000000;
  decimal result = {0};
  result.bits[0] = 0b00000000000000000000000000000001;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  decimal res_od = {0};
  dec_round(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(round_16) {
  decimal src1 = {0};
  src1.bits[0] = 0b10010111011100111001111111111111;
  src1.bits[1] = 0b00111100000010000011000110001101;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b10000000000001110000000000000000;
  decimal res_od = {0};
  dec_round(src1, &res_od);
  decimal result = {0};
  result.bits[3] = 0b10000000000000000000000000000000;
  result.bits[2] = 0;
  result.bits[1] = 0b00000000000000000000001000010010;
  result.bits[0] = 0b00110110101101101000110001000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(dec_round_1) {
  decimal dec1 = {0};
  dec1.bits[0] = 0b10010011111100000001110001010010;
  dec1.bits[1] = 0b00000000000000000000000100100000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000010100000000000000000;
  decimal result = {0};
  result.bits[0] = 0b00000000000000000000000001111100;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  decimal res1 = {0};
  dec_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(dec_round_2) {
  decimal dec1 = {0};
  dec1.bits[0] = 0b00000000000000000000000010100100;  // -16.4
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000000010000000000000000;
  decimal result = {0};
  result.bits[0] = 0b00000000000000000000000000010000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  decimal res1 = {0};
  dec_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(dec_round_3) {
  decimal dec1 = {0};
  dec1.bits[0] = 0b11111111111111111111111111111111;  //
  dec1.bits[1] = 0b00000000001111111111111111111111;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000110000000000000000;
  decimal result = {0};

  result.bits[0] = 0b01001101110100101111000110101001;  // 18014398509481
  result.bits[1] = 0b00000000000000000001000001100010;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  decimal res1 = {0};
  dec_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(dec_round_4) {
  decimal dec1 = {0};
  dec1.bits[0] = 0b00000000000011110111001001110100;  // -10123.40
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000000110000000000000000;
  decimal result = {0};
  result.bits[0] = 0b00000000000000000000001111110100;  // -1012
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  decimal res1 = {0};
  dec_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(dec_round_5) {
  decimal dec1 = {0};
  dec1.bits[0] = 0b10000000000000000000001111110100;  // 112590205.4327284
  dec1.bits[1] = 0b00000000000001000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000001110000000000000000;
  decimal result = {0};
  result.bits[0] = 0b00000110101101011111110101111101;  // 112590205
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  decimal res1 = {0};
  dec_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(dec_round_6) {
  decimal dec1 = {0};
  dec1.bits[0] = 0b10000000000000000000001111110100;  // 2147484660
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {0};
  result.bits[0] = 0b10000000000000000000001111110100;  // 2147484660
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  decimal res1 = {0};
  dec_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(dec_round_7) {
  decimal dec1 = {0};

  dec1.bits[0] = 0b01100011000011111111111111111111;
  dec1.bits[1] = 0b01101011110001110101111000101101;
  dec1.bits[2] = 0b00000000000000000000000000000101;
  dec1.bits[3] = 0b10000000000010100000000000000000;
  decimal result = {0};
  result.bits[0] = 0b01010100000010111110010000000000;
  result.bits[1] = 0b00000000000000000000000000000010;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  decimal res1 = {0};
  dec_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(dec_round_8) {
  decimal dec1 = {0};

  dec1.bits[0] = 0b01010101001110101110101110110001;
  dec1.bits[1] = 0b00001101101101001101101001011111;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000100100000000000000000;
  decimal result = {0};
  result.bits[0] = 0b00000000000000000000000000000001;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  decimal res1 = {0};
  dec_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(dec_round_9) {
  decimal dec1 = {0};

  dec1.bits[0] = 0b10010011111100000001110001010010;
  dec1.bits[1] = 0b00000000000000000000000100100000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000010100000000000000000;
  decimal result = {0};
  result.bits[0] = 0b00000000000000000000000001111100;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  decimal res1 = {0};
  dec_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
}
END_TEST

START_TEST(dec_round_12) {
  decimal dec1 = {0};

  dec1.bits[0] = 0b10010111011100111001111111111111;
  dec1.bits[1] = 0b00111100000010000011000110001101;
  dec1.bits[2] = 0b00000000000000000000000000000001;
  dec1.bits[3] = 0b00000000000001110000000000000000;
  decimal res1 = {0};
  dec_round(dec1, &res1);
  decimal result = {0};
  result.bits[0] = 0b00110110101101101000110001000000;
  result.bits[1] = 0b00000000000000000000001000010010;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(dec_round_13) {
  decimal dec1 = {0};

  dec1.bits[0] = 0b10010111011100111001111111111111;
  dec1.bits[1] = 0b00111100000010000011000110001101;
  dec1.bits[2] = 0b00000000000000000000000000000001;
  dec1.bits[3] = 0b10000000000001110000000000000000;
  decimal res1 = {0};
  dec_round(dec1, &res1);
  decimal result = {0};
  result.bits[0] = 0b00110110101101101000110001000000;
  result.bits[1] = 0b00000000000000000000001000010010;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;

  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(dec_roundTest1) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = 2;

  src1.bits[0] = 2;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  dec_round(src1, &result);
  origin.bits[0] = 2;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(dec_roundTest2) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = 3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  decimal result = {{0, 0, 0, 0}};
  dec_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(dec_roundTest3) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = -3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  decimal result = {{0, 0, 0, 0}};
  dec_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(dec_roundTest4) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  dec_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(dec_roundTest5) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = -9878798789;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  dec_round(src1, &result);
  origin.bits[0] = 0b01001100110100101000000111000101;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(dec_roundTest6) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = -545454512454545.35265;

  src1.bits[0] = 0b11011110101101001010101001100001;
  src1.bits[1] = 0b11110100111110000101111011101001;
  src1.bits[2] = 0b00000000000000000000000000000010;
  src1.bits[3] = 0b10000000000001010000000000000000;
  decimal result = {{0, 0, 0, 0}};
  dec_round(src1, &result);
  origin.bits[0] = 0b10000110011101001011101110010001;
  origin.bits[1] = 0b00000000000000011111000000010110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(dec_roundTest7) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = -5.492654545456454545645464;

  src1.bits[0] = 0b00000111100110110001111110011000;
  src1.bits[1] = 0b01100110010010001001000110100011;
  src1.bits[2] = 0b00000000000001001000101100011101;
  src1.bits[3] = 0b10000000000110000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  dec_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(dec_roundTest8) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = 7961327845421.879754123131254;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  decimal result = {{0, 0, 0, 0}};
  dec_round(src1, &result);
  origin.bits[0] = 0b10100100000111100100000000101110;
  origin.bits[1] = 0b00000000000000000000011100111101;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(dec_roundTest9) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = -12345677.187654345678987654346;

  src1.bits[0] = 0b01111000100010101111010011001010;
  src1.bits[1] = 0b01100010000010101110010010000111;
  src1.bits[2] = 0b00100111111001000001101011010101;
  src1.bits[3] = 0b10000000000101010000000000000000;
  decimal result = {{0, 0, 0, 0}};
  dec_round(src1, &result);
  origin.bits[0] = 0b00000000101111000110000101001101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(dec_roundTest10) {
  decimal src1 = {0};
  decimal origin = {0};

  src1.bits[0] = 0b10101101110010001101100101011111;
  src1.bits[1] = 0b01001000101000101011010010000001;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;
  decimal result = {{0, 0, 0, 0}};
  dec_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(dec_roundTest11) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = 1;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  dec_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(dec_roundTest12) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = 1.1;

  src1.bits[0] = 0b00000000000000000000000000001011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  decimal result = {{0, 0, 0, 0}};
  dec_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(dec_roundTest13) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = -1.1;

  src1.bits[0] = 0b00000000000000000000000000001011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  decimal result = {{0, 0, 0, 0}};
  dec_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(dec_roundTest14) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = 24.56;

  src1.bits[0] = 0b00000000000000000000100110001000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000100000000000000000;
  decimal result = {{0, 0, 0, 0}};
  dec_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000011000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(dec_roundTest15) {
  decimal src1 = {0};    // src1 = -2.124;
  decimal origin = {0};  // 2

  src1.bits[0] = 0b00000000000000000000100001001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000110000000000000000;
  decimal result = {{0, 0, 0, 0}};
  dec_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;

  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

//------------------------------------------------------------------------truncate

void truncate_test_function(float n, float accuracy) {
  float value0 = 0.0;
  decimal var1 = {{0}}, var2 = {{0}};

  int value1 = 0, value2 = 0;
  from_float_to_decimal(n, &var1);
  truncate(var1, &var2);
  from_decimal_to_float(var2, &value0);
  value2 = (int)value0;
  value1 = truncf(n);
  ck_assert_float_eq_tol(value1, value2, accuracy);
  return;
}

START_TEST(truncate_0) {
  decimal val = {{7, 7, 7, 0}};
  decimal res;
  ck_assert_int_eq(0, truncate(val, &res));
  float fres = 0;
  from_decimal_to_float(res, &fres);
  float need = 129127208515966861312.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_1) {
  decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(0, truncate(val, &res));
  float fres = 0;
  from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_2) {
  decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  ck_assert_int_eq(0, truncate(val, &res));
  float fres = 0;
  from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_3) {
  decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  set_scale(&val, 5);
  ck_assert_int_eq(0, truncate(val, &res));
  float fres = 0;
  from_decimal_to_float(res, &fres);
  float need = -0.0;
  ck_assert_float_eq(need, fres);
}

START_TEST(truncate_4) {
  decimal val = {{128, 0, 0, 0}};
  decimal res = {{0}};
  set_scale(&val, 1);
  ck_assert_int_eq(0, truncate(val, &res));
  float fres = 0;
  from_decimal_to_float(res, &fres);
  float need = 12;
  ck_assert_float_eq(need, fres);
}

START_TEST(truncate_5) {
  float n = dec_rand_r(-8388608, 8388608);
  truncate_test_function(n, 10);
}
END_TEST

START_TEST(truncate_6) {
  decimal value_1 = {{35, 0, 0, 0}};
  decimal check = {{3, 0, 0, 0}};
  set_scale(&value_1, 1);
  truncate(value_1, &value_1);
  ck_assert_int_eq(is_equal(value_1, check), 1);
}
END_TEST

START_TEST(truncate_7) {
  decimal value_1 = {{123456, 0, 0, 0}};
  set_scale(&value_1, 3);
  set_bit(&value_1, 127, 1);
  decimal check = {{123, 0, 0, 0}};
  set_bit(&check, 127, 1);
  truncate(value_1, &value_1);
  ck_assert_int_eq(is_equal(value_1, check), 1);
}
END_TEST

START_TEST(truncate_8) {
  decimal src1 = {0};
  src1.bits[3] = 0x000A0000;
  src1.bits[2] = 0x0;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[0] = 0xFFFFFFFF;
  decimal result = {0};
  result.bits[3] = 0x0;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x6DF37F67;
  decimal res_od = {0};
  truncate(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(truncate_9) {
  decimal src1 = {0};
  src1.bits[0] = 0b00000000000000000000000001101101;
  src1.bits[1] = 0b00000000000011000110010101011011;
  src1.bits[2] = 0b00000000000000000011000000111001;
  src1.bits[3] = 0b00000000000011100000000000000000;
  decimal result = {0};
  result.bits[0] = 0b10000111101111000001011000011110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  decimal res_od = {0};
  truncate(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_trun_1) {
  decimal dec1 = {0};
  dec1.bits[0] = 0b00000000000000000000000011010011;  // 21.1
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000010000000000000000;
  decimal result = {0};
  result.bits[0] = 0b00000000000000000000000000010101;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  decimal res1 = {0};
  truncate(dec1, &res1);
  ck_assert_int_eq(res1.bits[0], result.bits[0]);
  ck_assert_int_eq(res1.bits[1], result.bits[1]);
  ck_assert_int_eq(res1.bits[2], result.bits[2]);
  ck_assert_int_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_trun_2) {
  decimal dec1 = {0};
  dec1.bits[0] = 0b00000000000000000000000010100101;
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000010000000000000000;
  decimal result = {0};
  result.bits[0] = 0b00000000000000000000000000010000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  decimal res1 = {0};
  truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_trun_4) {
  decimal dec1 = {0};
  dec1.bits[0] = 0b10000000000000000000000010100101;  // 214.7483813
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000001110000000000000000;
  float num = 0.0;
  from_decimal_to_float(dec1, &num);
  decimal result = {0};
  result.bits[0] = 0b00000000000000000000000011010110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  decimal res1 = {0};
  truncate(dec1, &res1);
  ck_assert_int_eq(res1.bits[0], result.bits[0]);
  ck_assert_int_eq(res1.bits[1], result.bits[1]);
  ck_assert_int_eq(res1.bits[2], result.bits[2]);
  ck_assert_int_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(truncate_1_1) {
  decimal dec1 = {0};

  dec1.bits[3] = 0x000A0000;
  dec1.bits[2] = 0x0;
  dec1.bits[1] = 0xFFFFFFFF;
  dec1.bits[0] = 0xFFFFFFFF;
  decimal result = {0};
  result.bits[3] = 0x0;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x6DF37F67;
  decimal res1 = {0};
  truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(truncate_2_1) {
  decimal dec1 = {0};

  dec1.bits[3] = 0b10000000000011000000000000000000;
  dec1.bits[2] = 0x0;
  dec1.bits[1] = 0xFFFFFFFF;
  dec1.bits[0] = 0xFFFFFFFF;
  decimal result = {0};
  result.bits[3] = 0b10000000000000000000000000000000;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x1197998;
  decimal res1 = {0};
  truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(truncate_3_1) {
  decimal dec1 = {0};

  dec1.bits[3] = 0x80000000;
  dec1.bits[2] = 0x0;
  dec1.bits[1] = 0xFFFFFFFF;
  dec1.bits[0] = 0xFFFFFFFF;
  decimal result = {0};
  result.bits[3] = 0x80000000;
  result.bits[2] = 0x0;
  result.bits[1] = 0xFFFFFFFF;
  result.bits[0] = 0xFFFFFFFF;
  decimal res1 = {0};
  truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(truncate_4_1) {
  decimal dec1 = {0};

  dec1.bits[0] = 0b00000000000000000000000001101101;
  dec1.bits[1] = 0b00000000000011000110010101011011;
  dec1.bits[2] = 0b00000000000000000011000000111001;
  dec1.bits[3] = 0b00000000000011100000000000000000;
  decimal result = {0};
  result.bits[0] = 0b10000111101111000001011000011110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  decimal res1 = {0};
  truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(truncate_6_1) {
  decimal dec1 = {0};

  dec1.bits[3] = 0x80090000;
  dec1.bits[2] = 0;
  dec1.bits[1] = 0xFFFFEA34;
  dec1.bits[0] = 0xFF837E4F;
  decimal result = {0};
  truncate(dec1, &result);
  decimal res1 = {0};

  res1.bits[3] = 0x80000000;
  res1.bits[2] = 0;
  res1.bits[1] = 0x4;
  res1.bits[0] = 0x4B829C70;
  ck_assert_int_eq(res1.bits[3], result.bits[3]);
  ck_assert_int_eq(res1.bits[2], result.bits[2]);
  ck_assert_int_eq(res1.bits[1], result.bits[1]);
  ck_assert_int_eq(res1.bits[0], result.bits[0]);
}
END_TEST

START_TEST(truncate_7_1) {
  decimal dec1 = {0};

  dec1.bits[0] = 0b11010000101000110011000001101101;
  dec1.bits[1] = 0b00011111100110100110101101011000;
  dec1.bits[2] = 0;
  dec1.bits[3] = 0b00000000000010010000000000000000;
  decimal result = {0};
  truncate(dec1, &result);
  decimal result_origin;
  result_origin.bits[3] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b10000111101111000001011000011110;
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(truncate_8_1) {
  decimal dec1 = {0};

  dec1.bits[0] = 0b01111000101001111011110011000110;
  dec1.bits[1] = 0b10011111111111001111101010000100;
  dec1.bits[2] = 0b00011111111010011010111101101101;
  dec1.bits[3] = 0b00000000000111000000000000000000;
  decimal result = {0};
  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  decimal res1 = {0};
  truncate(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(truncateTest1) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = 2;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(truncateTest2) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = 3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  decimal result = {{0, 0, 0, 0}};
  truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(truncateTest3) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(truncateTest4) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = 0;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(truncateTest5) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = -9878798789;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  truncate(src1, &result);

  origin.bits[0] = 0b01001100110100101000000111000101;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(truncateTest6) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = -545454512454545.35265454545645;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;
  decimal result = {{0, 0, 0, 0}};
  truncate(src1, &result);

  origin.bits[0] = 0b10000110011101001011101110010001;
  origin.bits[1] = 0b00000000000000011111000000010110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(truncateTest7) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = -5.492654545456454545645464;

  src1.bits[0] = 0b00000111100110110001111110011000;
  src1.bits[1] = 0b01100110010010001001000110100011;
  src1.bits[2] = 0b00000000000001001000101100011101;
  src1.bits[3] = 0b10000000000110000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(truncateTest8) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = 7961327845421.879754123131254;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  decimal result = {{0, 0, 0, 0}};
  truncate(src1, &result);

  origin.bits[0] = 0b10100100000111100100000000101101;
  origin.bits[1] = 0b00000000000000000000011100111101;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(truncateTest9) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = -12345677.187654345678987654346;

  src1.bits[0] = 0b01111000100010101111010011001010;
  src1.bits[1] = 0b01100010000010101110010010000111;
  src1.bits[2] = 0b00100111111001000001101011010101;
  src1.bits[3] = 0b10000000000101010000000000000000;
  decimal result = {{0, 0, 0, 0}};
  truncate(src1, &result);

  origin.bits[0] = 0b00000000101111000110000101001101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(truncateTest10) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = 2.5086531268974139743;

  src1.bits[0] = 0b01100101111011101101100101011111;
  src1.bits[1] = 0b01011100001001010100001101000110;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;
  decimal result = {{0, 0, 0, 0}};
  truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(truncateTest11) {
  decimal src1 = {0};
  decimal origin = {0};  // src1 = 1;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  decimal result = {{0, 0, 0, 0}};
  truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

//------------------------------------------------------------------------negate

void negate_test_function(float n, float accuracy) {
  decimal var1 = {{0}}, var2 = {{0}}, var3 = {{0}};
  float value1 = 0.0, value2 = 0.0;
  from_float_to_decimal(n, &var1);
  negate(var1, &var2);
  from_decimal_to_float(var2, &value2);
  value1 = -1 * n;
  from_float_to_decimal(value1, &var3);
  ck_assert_float_eq_tol(value1, value2, accuracy);
  return;
}

START_TEST(negate_0) {
  decimal val = {{2, 0, 0, 0}};
  decimal res = {{0}};
  int sign_before = get_bit(val, 127);
  negate(val, &res);
  int sign_after = get_bit(res, 127);

  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_1) {
  decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  decimal res;
  int sign_before = get_bit(val, 127);
  negate(val, &res);
  int sign_after = get_bit(res, 127);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_2) {
  decimal val = {{0, 0, 0, ~(UINT_MAX / 2)}};
  decimal res = {{0}};
  int sign_before = get_bit(val, 127);
  negate(val, &res);
  int sign_after = get_bit(res, 127);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_3) {
  decimal val = {{0}};
  decimal res = {{0}};
  int sign_before = get_bit(val, 127);
  negate(val, &res);
  int sign_after = get_bit(res, 127);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_4) {
  float n = dec_rand_r(-8388608, 8388608);
  negate_test_function(n, 10);
}
END_TEST

START_TEST(negate_5) {
  decimal value_1 = {{5, 0xFFFFFFFF, 0, 0}};
  set_bit(&value_1, 127, 1);
  decimal check = {{5, 0xFFFFFFFF, 0, 0}};
  decimal result = {0};
  int return_value = negate(value_1, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(negate_6) {
  decimal value_1 = {{1, 1, 1, 0}};
  decimal check = {{1, 1, 1, 0x80000000}};
  decimal result = {0};
  int return_value = negate(value_1, &result);
  ck_assert_int_eq(is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(negate_7) {
  float a = 10.1234e5;
  float res_a = 0;
  decimal src = {0};
  decimal res = {0};
  from_float_to_decimal(a, &src);
  negate(src, &res);
  from_decimal_to_float(res, &res_a);
  ck_assert_float_eq(-1.012340e+06, res_a);
}
END_TEST

//------------------------------------------------------------------------END

Suite *test_other(void) {
  Suite *suite = suite_create("other_suite");
  TCase *tcase = tcase_create("other_tcase");

  tcase_add_test(tcase, floor_0);
  tcase_add_test(tcase, floor_1);
  tcase_add_test(tcase, floor_2);
  tcase_add_test(tcase, floor_3);
  tcase_add_loop_test(tcase, floor_4, 0, 1000);
  tcase_add_test(tcase, floor_5);
  tcase_add_test(tcase, floor_6);
  tcase_add_test(tcase, floor_7);

  tcase_add_test(tcase, round_0);
  tcase_add_test(tcase, round_1);
  tcase_add_test(tcase, round_2);
  tcase_add_test(tcase, round_3);
  tcase_add_test(tcase, round_4);
  tcase_add_test(tcase, round_5);
  tcase_add_test(tcase, round_6);
  tcase_add_test(tcase, round_7);
  tcase_add_test(tcase, round_8);
  tcase_add_test(tcase, round_9);
  tcase_add_loop_test(tcase, round_10, 0, 10);
  tcase_add_test(tcase, round_11);
  tcase_add_test(tcase, round_12);
  tcase_add_test(tcase, round_13);
  tcase_add_test(tcase, round_14);
  tcase_add_test(tcase, round_15);
  tcase_add_test(tcase, round_16);
  tcase_add_test(tcase, dec_round_1);
  tcase_add_test(tcase, dec_round_2);
  tcase_add_test(tcase, dec_round_3);
  tcase_add_test(tcase, dec_round_4);
  tcase_add_test(tcase, dec_round_5);
  tcase_add_test(tcase, dec_round_6);
  tcase_add_test(tcase, dec_round_7);
  tcase_add_test(tcase, dec_round_8);
  tcase_add_test(tcase, dec_round_9);
  tcase_add_test(tcase, dec_round_12);
  tcase_add_test(tcase, dec_round_13);
  tcase_add_test(tcase, dec_roundTest1);
  tcase_add_test(tcase, dec_roundTest2);
  tcase_add_test(tcase, dec_roundTest3);
  tcase_add_test(tcase, dec_roundTest4);
  tcase_add_test(tcase, dec_roundTest5);
  tcase_add_test(tcase, dec_roundTest6);
  tcase_add_test(tcase, dec_roundTest7);
  tcase_add_test(tcase, dec_roundTest8);
  tcase_add_test(tcase, dec_roundTest9);
  tcase_add_test(tcase, dec_roundTest10);
  tcase_add_test(tcase, dec_roundTest11);
  tcase_add_test(tcase, dec_roundTest12);
  tcase_add_test(tcase, dec_roundTest13);
  tcase_add_test(tcase, dec_roundTest14);
  tcase_add_test(tcase, dec_roundTest15);

  tcase_add_test(tcase, truncate_0);
  tcase_add_test(tcase, truncate_1);
  tcase_add_test(tcase, truncate_2);
  tcase_add_test(tcase, truncate_3);
  tcase_add_test(tcase, truncate_4);
  tcase_add_loop_test(tcase, truncate_5, 0, 1000);
  tcase_add_test(tcase, truncate_6);
  tcase_add_test(tcase, truncate_7);
  tcase_add_test(tcase, truncate_8);
  tcase_add_test(tcase, truncate_9);
  tcase_add_test(tcase, s21_trun_1);
  tcase_add_test(tcase, s21_trun_2);
  tcase_add_test(tcase, s21_trun_4);
  tcase_add_test(tcase, truncate_1_1);
  tcase_add_test(tcase, truncate_2_1);
  tcase_add_test(tcase, truncate_3_1);
  tcase_add_test(tcase, truncate_4_1);
  tcase_add_test(tcase, truncate_6_1);
  tcase_add_test(tcase, truncate_7_1);
  tcase_add_test(tcase, truncate_8_1);
  tcase_add_test(tcase, truncateTest1);
  tcase_add_test(tcase, truncateTest2);
  tcase_add_test(tcase, truncateTest3);
  tcase_add_test(tcase, truncateTest4);
  tcase_add_test(tcase, truncateTest5);
  tcase_add_test(tcase, truncateTest6);
  tcase_add_test(tcase, truncateTest7);
  tcase_add_test(tcase, truncateTest8);
  tcase_add_test(tcase, truncateTest9);
  tcase_add_test(tcase, truncateTest10);
  tcase_add_test(tcase, truncateTest11);
  tcase_add_test(tcase, negate_0);
  tcase_add_test(tcase, negate_1);
  tcase_add_test(tcase, negate_2);
  tcase_add_test(tcase, negate_3);
  tcase_add_loop_test(tcase, negate_4, 0, 1000);
  tcase_add_test(tcase, negate_5);
  tcase_add_test(tcase, negate_6);
  tcase_add_test(tcase, negate_7);

  suite_add_tcase(suite, tcase);

  return suite;
}

int test_run(Suite *test) {
  int failed = 0;
  SRunner *sr = srunner_create(test);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return failed;
}

int main() {
  int failed = 0;

  Suite *suites_list[] = {test_arithmetic(), test_comparison(),
                          test_converters(), test_other(), NULL};
  for (Suite **current = suites_list; *current != NULL; current++) {
    printf("_________________________________________\n");
    failed += test_run(*current);
  }
  
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

float dec_rand_r(float a, float b) {
  float m = (float)rand() / RAND_MAX;
  float num = a + m * (b - a);
  return num;
}

void dec_zero_decimal(decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
}


