#include <unistd.h>
#include "true_random.h"

int main() {
    while(1) {
        unsigned char n = 0;
        int i;
        for ( i = 0 ; i < 8; i++ ) {
            n *= 2; n += get_fair_bit();
        }
        write(STDOUT_FILENO, &n, 1);
    }
}
