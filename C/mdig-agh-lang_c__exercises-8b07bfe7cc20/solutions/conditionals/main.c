#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * Zwróć wartość bezwzględną argumentu.
 * @param x liczba całkowita
 * @return wartość bezwzględna z `x`
 */
int my_abs(int x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

/**
 * Zwróć wartość bezwzględną argumentu.
 * @param x liczba całkowita
 * @return wartość bezwzględna z `x`
 */
int my_abs2(int x) {
    if (x < 0) {
        x = -x;
        printf("MY_ABS2: argument was negative\n");
    }
    return x;
}

int main(void) {
    bool b = true;

    char cnd = (char) (b ? 't' : 'f');
    printf("%c\n\n", cnd);

    int x = 1;
    printf("my_abs(%d) = %d\n", x, my_abs(x));
    printf("my_abs2(%d) = %d\n\n", x, my_abs2(x));

    x = -1;
    printf("my_abs(%d) = %d\n", x, my_abs(x));
    printf("my_abs2(%d) = %d\n", x, my_abs2(x));

    return EXIT_SUCCESS;
}
