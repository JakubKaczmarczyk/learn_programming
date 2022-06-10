#define __USE_MINGW_ANSI_STDIO 1

#include <stdlib.h>
#include <stdio.h>

int main(void) {
    double d = 1;
    float f = 1;

    f += (float) d;

    printf("sizeof(int) = %zu\n", sizeof(int));

    return EXIT_SUCCESS;
}
