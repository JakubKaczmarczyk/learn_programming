#include <stdlib.h>
#include <stdio.h>

#define C11_TAG 201112L
#define C99_TAG 199901L

/*
 * TODO: Zdefiniuj stałe symboliczne o wartościach zgodnych stałej symbolicznej
 *   dla standardu C11 oraz C99.
 */

/**
 * Zwraca (własny) umowny identyfikator w zależności od wersji języka C:
 *
 * Jeśli stała symboliczna `__STDC_VERSION__` została zdefiniowana:
 *   Jeśli standard co najmniej C11: 2
 *   W przeciwnym razie, jeśli standard co najmniej C99: 1
 *   W przeciwnym razie: -1 (zapewne błąd)
 * W przeciwnym razie (starsze niż C99): 0
 *
 * @return (własny) umowny identyfikator wersji języka
 */
// TODO: Uzupełnij logikę poniższej funkcji zgodnie z powyższą specyfikacją.
int get_dummy_cstd_identifier() {
    #if  defined(__STDC_VERSION__)
        #if __STDC_VERSION__ >= C11_TAG
        return 2;
        #elif __STDC_VERSION__ >= C99_TAG
        return 1;
        #else
        return -1;
        #endif
    #else
    return 0;
    #endif
}

int main(void) {
    printf("Dummy C-version identifier: %d\n", get_dummy_cstd_identifier());

    return EXIT_SUCCESS;
}
