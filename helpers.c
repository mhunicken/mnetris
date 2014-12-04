#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "helpers.h"

uint64_t get_miliseconds(){
    struct timespec tp;
    assert(clock_gettime(CLOCK_MONOTONIC, &tp) == 0);
    return ((uint64_t)tp.tv_sec) * 1000 + tp.tv_nsec / 1000000;
}
