#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

void swap_table(double* tab, size_t size_of_tab);
int* create_table(size_t n);

int main(void) {
    double tab[] = {1.0, 2.0, 3.0, 4.0, 6.0};
    double sum1d = 0;
    for(size_t i = 0; i < sizeof(tab)/ sizeof(tab[0]); ++i) {
        sum1d += tab[i];
    }
    printf("suma %f\n", sum1d);
    double max_1d = DBL_MIN;
    for(size_t i = 0; i < sizeof(tab)/ sizeof(tab[0]); ++i) {
        if (tab[i] > max_1d) {
            max_1d = tab[i];
        }
    }
    printf("max %f\n", max_1d);
    swap_table(tab,sizeof(tab)/sizeof(tab[0]));
    for(size_t i = 0; i < sizeof(tab)/ sizeof(tab[0]); ++i) {
        printf("%f ", tab[i]);
    }

    int* tab2 = create_table(7);
    printf("\n");
    for(size_t i = 0; i < 14; ++i) {
        printf("%d ", tab2[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}

void swap_table(double* tab, size_t size_of_tab) {
    double swapper = 0;
//    size_t size_of_tab = sizeof(tab)/sizeof(tab[0]);
    for(size_t i = 0; i < (size_t) size_of_tab/2; ++i) {
        swapper = tab[i];
        tab[i] = tab[size_of_tab-1-i];
        tab[size_of_tab-1-i] = swapper;
    }
}

int* create_table(size_t n){
    int* tab = (int*) malloc(n*sizeof(int*));
    for(size_t i = 0; i < n; ++i) {
        tab[i] = 1;
    }
    tab = realloc(tab, 2*n*sizeof(tab));
    for(size_t i = n; i < 2*n; ++i) {
        tab[i] = 0;
    }
    return tab;
}

