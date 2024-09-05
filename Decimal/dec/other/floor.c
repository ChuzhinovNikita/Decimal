#include "../decimal.h"

int dec_floor(decimal value, decimal *result) {
  int ret = 0;
  if (result == NULL) {
    ret = 1;
  }else{
    int sign = get_sign(&value);
    decimal truncated;
    truncate(value, &truncated);

    if (sign && !is_equal(value, truncated)) {
      decimal one = {{1, 0, 0, 0}};
      decimal temp = {0};
      sub(truncated, one, &temp);
      *result = temp;
    } else {
      *result = truncated;
    }

    set_sign(result, sign);
  }

  return ret;
}