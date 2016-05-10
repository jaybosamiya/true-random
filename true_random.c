#include <time.h>
#include "true_random.h"

const long MILLISEC_TO_NANOSEC = 1000000;
const long MAX_NANOSEC = 1000000000;
const long TRUE_RAND_MAX = 2147483647;

static int get_bit() {
    struct timespec tp1, tp2;
    clock_gettime(CLOCK_MONOTONIC, &tp1);
    clock_gettime(CLOCK_MONOTONIC, &tp2);
    int bit = 0;
    long nanosec_cross_value = (tp1.tv_nsec + MILLISEC_TO_NANOSEC) % MAX_NANOSEC;
    while ( tp2.tv_nsec < nanosec_cross_value ) {
        bit = !bit;
        clock_gettime(CLOCK_MONOTONIC, &tp2);
    }
    return bit;
}

static int get_fair_bit() {
    while (1) {
        int bit = get_bit();
        if ( bit != get_bit() ) {
            return bit;
        }
    }
}

long true_random() {
    int i;
    long n = 0;
    for ( i = 0 ; i < 31 ; i++ ) {
        n *= 2; n += get_fair_bit();
    }
    return n;
}

