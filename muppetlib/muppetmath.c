#include "muppetmath.h"

#include <stdlib.h>

uint64_t getRandi(uint64_t min, uint64_t max) {
	return ((uint64_t)rand() | ((uint64_t)rand() << 32) + min) % (max+1);
}
