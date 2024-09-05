#include "../decimal.h"

void clear_bits(decimal *val) { memset(val->bits, 0, sizeof(val->bits)); }