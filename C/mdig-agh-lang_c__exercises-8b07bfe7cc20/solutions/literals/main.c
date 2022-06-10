#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int main(void) {
    double d = 1;
    float f = 1;

    char c = 'A';
    bool b = false;

    f += 1.0f;

    unsigned int ui = INT_MAX + 1U;

    printf("l = %ld\n", 3L);

    printf("c = %c\n", c);
    printf("b = %d\n", b);

    // Poniższe instrukcje zostały dodane po to, aby kompilator nie zgłaszał
    // błędów związanych z nieużywanymi zmiennymi.
    ui += 1;
    d += 0.0;

    return EXIT_SUCCESS;
}
