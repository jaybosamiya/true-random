#include <stdio.h>
#include "true_random.h"

int main() {
    int i;
    for ( i = 0 ; i < 10; i++ )
        printf("%ld\n", true_random());
}
