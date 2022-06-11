#include <stdlib.h>
#include <stdio.h>

#include "ptrlib.h"

// TODO: Warto stosować kwalifikator `const`, gdyż przy próbie niedozwolonych
//   modyfikacji kompilator zgłosi stosowny błąd (zob. poniższe przykłady
//   funkcji `fooX()`).
//  Spróbuj skompilować program najpierw bez flag kompilacji, a następnie z flagami.
//  Po zaobserwowaniu różnicy zakomentuj lub usuń funkcje `fooX()` - zostały
//    one dodane wyłącznie w celach demonstracyjnych.
//void foo1(const int* p) {
//    *p = 1;
//}
//
//const int* foo2(const int* const p) {
//    p = 1;
//    return p;
//}
//
//int* foo3(const int* const p) {
//    return p;
//}

int main(void) {
    int a = 4;
    int b = 5;

    swap(&a, &b);

    if (a == 5 && b == 4) {
        printf("OK\n");
    } else {
        printf("Cos poszlo nie tak...\n");
    }

    int v1;
    double x = 0.0;
    int v2;

    long addr_v1 = (long) &v1;
    long addr_v2 = (long) &v2;
    long n_mem = addr_v2 - addr_v1;

    printf("x = %lf\n\n", x);
    printf("&v1         = %16ld\n", addr_v1);
    printf("&v2         = %16ld\n", addr_v2);
    printf("n_mem_cells = %16ld\n", n_mem);

    return EXIT_SUCCESS;
}
