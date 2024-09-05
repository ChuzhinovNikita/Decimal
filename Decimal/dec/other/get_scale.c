#include "../decimal.h"

int get_scale(const decimal *value) { return (char)(value->bits[3] >> 16); }