#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int silnia(int);
int prime_req(int);
int prime_wew(int, int);
void witaj(int);
int is_square(int);
int is_triangle(int a, int b, int c);
void do_binar(int n);

int main(void) {
    int liczba = 5;
    printf("Silnia %d to %d\n", liczba, silnia(liczba));

    int liczba2 = 18;
    printf("Liczba pierwsza: %d\n", (int) prime_req(liczba2));
    witaj(8);
    printf("\n");
    int liczba3 = 15;
    printf("is %d a square? %d\n", liczba3, is_square(liczba3));
    int a = 2;
    int b = 2;
    int c = 8;
    printf("is %d %d %d a triangle? %d\n",a,b,c, is_triangle(a,b,c));
    printf("Binary of %d is ", 23);
    do_binar(23);
    printf("\n");

    return EXIT_SUCCESS;
}


int silnia(int n) {
    if(n == 1) {
        return 1;
    }
    return n * silnia(n-1);
}

int prime_req(int n) {
    return (n == 0 || n == 1) ? 0 : prime_wew(n,2);
}

int prime_wew(int n, int i) {
    if(i == n) {
        return 1;
    }
    if (n % i == 0) {
        return 0;
    }
    return prime_wew(n, i+1);
}

void witaj(int n) {
    if (n > 0) {
        printf("witaj ");
        witaj(n-1);
    }
}

int is_square(int n) {
    for(int i = 0; i < n; ++i) {
        if (i*i == n) {
            return 1;
        }
    }
    return 0;
}

int is_triangle(int a, int b, int c) {
    if(a + b > c && a + c > b && b + c > a) {
        return 1;
    }
    return 0;
}

void do_binar(int n) {
    // Zapamietaj cyfre na danej pozycji.
    const int r = n % 2;

    if (n >= 2) {
        do_binar(n / 2);
    }

    // Wypisuj cyfry "od końca", czyli od cyfry najbardziej znaczącej
    // (oznaczającej największą potęgę liczby 2).
    printf("%d", r);
}
