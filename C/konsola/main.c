#include <stdlib.h>
#include <stdio.h>


int main(void) {
    while(1) {
        int id;
        double x, y;
        printf("Podaj ID i wspolrzedne punktu: ");
        scanf("%d %lf %lf", &id, &x, &y);
        printf("Odczytano: P#%d = [%f, %f]\n", id, x, y);
    }
    return EXIT_SUCCESS;
}