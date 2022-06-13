#include <stdio.h>
#include <string.h>

unsigned long dlugosc(const char* str);
int palindrom_rec(const char* p, const char* k);

int palindrom(const char* str) {
    return palindrom_rec(str, str + strlen(str) - 1);
}

int palindrom_rec(const char* p, const char* k) {
    if (p >= k) {
        // Doszlismy do srodka wyrazu.
        return 1;
    } else if (*p != *k) {
        // Rozne znaki.
        return 0;
    } else {
        // Znaki takie same - przegladamy dalej.
        return palindrom_rec(p + 1, k - 1);
    }
}

int main(void) {
    char str[] = "No siema byku  ";
    printf("%lu", dlugosc(str));
    return 0;
}

unsigned long dlugosc(const char* str) {
    size_t i = 0;
    while (str[i] != '\0') {
        i += 1;
    }
    const char str_pal[] = "kajak";
    const char str_npal[] = "pies";

    printf("Czy wyraz \"%s\" jest palindromem:  %d\n", str_pal, palindrom(str_pal));
    printf("Czy wyraz \"%s\" jest palindromem:  %d\n", str_npal, palindrom(str_npal));
    return (unsigned long ) i;
}

