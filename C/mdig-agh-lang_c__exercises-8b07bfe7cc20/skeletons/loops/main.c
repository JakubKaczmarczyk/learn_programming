#define __USE_MINGW_ANSI_STDIO 1

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

/**
 * Oblicz sumę liczb całkowitych z zakresu 1-8 z wyjątkiem liczb podzielnych przez n.
 *
 * Wskazówka: Suma liczb całkowitych z zakresu 1-8 wynosi 36.
 *
 * @param n [liczba naturalna dodatnia]
 * @return suma liczb z zakresu 1-8 z wyjątkiem liczb podzielnych przez n
 */

int fancy_range_sum1(int n) {
    int sum = 0;
    for(int i=1; i<=8;++i) {
        if(i % n == 0) {
            continue;
        }
        sum += i;
    }
     return sum;
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

int fancy_range_sum2(int n, int stop) {
    int sum = 0;
    for(int i=1; i<=n; ++i) {
        for (int j=1; j <= n; ++j) {
            if(i == 1 && i*j >= stop) {
                break;
            } else {
                sum += i*j;
            }
        }
    }
     return sum;
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

int fancy_range_sum3(int n, int stop) {
    int sum = 0;
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j) {
            if(i*j == stop) {
                goto finish;
            }
            sum += i*j;
        }
    }

    finish:
    return sum;
}

double my_abs(double x) {
    if (x < 0) {
        return -x;
    }
    return x;
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


    // Stairs
    int n = 6;

    for(int i=1; i<=n; ++i) {
        for(int j=1; j<=i; ++j) {
            printf("$");
        }
        printf("\n");
    }
    printf("\n");

    // BOX

    n = 18;
    for(int i=1; i<=n; ++i) {
        for(int j=1; j<=n; ++j) {
            if(i==1 || i == n || j==1 || j == n || i == j) {
                printf("*");
                continue;
            }
            printf(" ");
        }
        printf("\n");
    }

    // DIGSUM
    int liczba = 196;
    int setki = (int) liczba/100;
    int dzies = (int) (liczba-setki*100)/10;
    int jedn = (int) (liczba-setki*100-dzies*10);
    printf("suma = %d\n", setki+dzies+jedn);

    // PRIME

    liczba = 18;
    bool is_number_prime = true;

    for(int i=2;i<liczba;++i){
        if(liczba % i == 0) {
            is_number_prime = false;
            break;
        }
    }
    if (is_number_prime) {
        printf("TAK\n");
    } else {
        printf("NIE\n");
    }

    double s = 2;
    double xn = s;
    const double DIF_REQ = 1e-4;
    double x_next = (xn + s/xn)/2;
    while (my_abs((xn-x_next)) > DIF_REQ) {
        xn = x_next;
        x_next = (xn + s/xn)/2;
    }
    printf("Pierw: %.4f\n", x_next);


    // SQUARE

    n = 5;
    for(int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if(i == 1) {
                printf("%d ", j);
            } else {

            }
        }
    }
    return EXIT_SUCCESS;
}
