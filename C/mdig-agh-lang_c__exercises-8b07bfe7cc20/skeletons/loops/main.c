#define __USE_MINGW_ANSI_STDIO 1

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * Oblicz sumę liczb całkowitych z zakresu 1-8 z wyjątkiem liczb podzielnych przez n.
 *
 * Wskazówka: Suma liczb całkowitych z zakresu 1-8 wynosi 36.
 *
 * @param n [liczba naturalna dodatnia]
 * @return suma liczb z zakresu 1-8 z wyjątkiem liczb podzielnych przez n
 */
// TODO: Uzupełnij implementację poniższej funkcji zgodnie z jej powyższą
//   specyfikacją.
int fancy_range_sum1(int n) {
     return n;  // TODO: Popraw to.
}

/**
 * Oblicz sumę ciągu 1*1 + 1*2 + 1*3 + ... + 1*n + 2*1 + 2*2 + ... + n*n.
 *
 * UWAGA! Przerwij obliczanie kolejnych elementów ciągu (i*j) dla i = 1
 *   w momencie, gdy j >= e_estop (kontynuuj obliczanie od i = 2).
 *
 * @param n maksymalny czynnik
 * @param stop wartość iloczynu, przy której następuje przerwanie dalszych
 *   obliczeń i zwrócenie wyniku
 * @return obliczona suma
 */
// TODO: Uzupełnij implementację poniższej funkcji zgodnie z jej powyższą
//   specyfikacją.
int fancy_range_sum2(int n, int stop) {
     return n + stop;  // TODO: Popraw to.
}

/**
 * Oblicz sumę ciągu 1*1 + 1*2 + 1*3 + ... + 1*n + 2*1 + 2*2 + ... + n*n.
 *
 * UWAGA! Przerwij obliczanie (i dodawanie) kolejnych elementów ciągu
 *    w momencie, gdy element ciągu (i*j) będzie miał wartość `stop`.
 *
 * @param n maksymalny czynnik
 * @param stop wartość iloczynu, przy której następuje przerwanie dalszych
 *   obliczeń i zwrócenie wyniku
 * @return obliczona suma
 */
// TODO: Uzupełnij implementację poniższej funkcji zgodnie z jej powyższą
//   specyfikacją.
int fancy_range_sum3(int n, int stop) {
     return n + stop;  // TODO: Popraw to.
}

int main(void) {
    // `counter` ma wartość logiczną PRAWDA także wówczas, gdy jest ujemny!
    for (int counter = 3, i = 1; counter; counter -= 2, ++i) {
        printf("i = %d, counter = %d\n", i, counter);
        if (i > 3) {
            break;
        }
    }

    assert(fancy_range_sum1(2) == 16);
    assert(fancy_range_sum1(3) == 27);

    // 1*1 + 2*1 + 2*2 + 2*3 + 3*1 + 3*2 + 3*3
    assert(fancy_range_sum2(3, 2) == 31);

    // 1*1 + 1*2 + 2*1 + 2*2 + 2*3 + 3*1 + 3*2 + 3*3
    assert(fancy_range_sum2(3, 3) == 33);

    // 1*1 + 1*2 + 1*3 + 2*1 + 2*2 (+ 2*3 - STOP)
    assert(fancy_range_sum3(3, 6) == 12);

    // 1*1 + 1*2 + 1*3 + 2*1 + 2*2 + 2*3 + 3*1 + 3*2 (+ 3*3 - STOP)
    assert(fancy_range_sum3(3, 9) == 27);

    return EXIT_SUCCESS;
}
