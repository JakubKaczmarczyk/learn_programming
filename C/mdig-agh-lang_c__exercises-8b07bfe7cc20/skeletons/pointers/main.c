#include <stdlib.h>

#include "ptrlib.h"

// TODO: Warto stosować kwalifikator `const`, gdyż przy próbie niedozwolonych
//   modyfikacji kompilator zgłosi stosowny błąd (zob. poniższe przykłady
//   funkcji `fooX()`).
//  Spróbuj skompilować program najpierw bez flag kompilacji, a następnie z flagami.
//  Po zaobserwowaniu różnicy zakomentuj lub usuń funkcje `fooX()` - zostały
//    one dodane wyłącznie w celach demonstracyjnych.
void foo1(const int* p) {
    *p = 1;
}

const int* foo2(const int* const p) {
    p = 1;
    return p;
}

int* foo3(const int* const p) {
    return p;
}

int main(void) {
    int n = 3;
    // TODO: Do wyświetlania adresu służy specyfikator konwersji `%p`.
    //   Zwróć uwagę, że wymaga on wartości typu `void*`.
    printf("adres = %p", (void*) &n);

    return EXIT_SUCCESS;
}
