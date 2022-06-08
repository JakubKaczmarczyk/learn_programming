#include <stdlib.h>
#include<stdio.h>
#include "source1.h"

#define N 5


int sum_array(int* arr_begin, int* arr_end);
void print_tab(int tab[3][4]);
void print1Dtab(int tab[], int n);
void change_tab(int tab[], int n);
void fill_2D_tab(double** tab, unsigned int w, unsigned int k,double war);
void print_2D_tab(double** tab, unsigned int w, unsigned int k);
void free_2D_tab(double** tab, unsigned int w);

int main(void) {
    int tab_a[3][4] = {{1,2,3},{1,2,3}};
    int tab_b[3][4] = {{1,2,3,1},{2,3}};
    print_tab(tab_a);
    print_tab(tab_b);
    printf("%d\n",(int) tab_a);
    printf("%d\n", (int) &tab_a);
    int tab_c[8] = {1,2,3,4,5,6,7,8};
    printf("sum tab_c : %d\n", sum_array(tab_c, tab_c+N));
    print1Dtab(tab_c, (int) sizeof(tab_c)/sizeof(tab_c[0]));
    change_tab(tab_c,(int) sizeof(tab_c)/sizeof(tab_c[0]));
    print1Dtab(tab_c, (int) sizeof(tab_c)/sizeof(tab_c[0]));


//    extern const int stable;
    printf("%d\n", stable);


    // dynamiczne

    unsigned int rozmiar = 10u;
    double* tab_d = (double*) malloc(rozmiar * sizeof(*tab_d));
    for(int i=0;i<(int) rozmiar;++i) {
        printf("%f ", tab_d[i]);
    }

    free(tab_d);

    const unsigned int wiersze = 4;
    const unsigned int kolumny = 3;

    double** tab2D = malloc(wiersze *sizeof(double*));
    for(unsigned int i=0;i<wiersze;++i) {
        tab2D[i] = malloc(kolumny * sizeof(double ));
    }
    fill_2D_tab(tab2D,wiersze,kolumny,2.0);
    print_2D_tab(tab2D,wiersze,kolumny);
    free_2D_tab(tab2D,wiersze);
    return EXIT_SUCCESS;
}

int sum_array(int* arr_begin, int* const arr_end) {
    int sum = 0;
    for (int* arr_current = arr_begin; arr_current < arr_end; ++arr_current) {
        sum += *arr_current;
    }
    return sum;
}

void print_tab(int tab[3][4]) {
    for(size_t i=0;i<3;++i) {
        for(size_t j=0;j<4;++j) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

void print1Dtab(int tab[], int n) {
    for(int i=0;i<n;++i) {
        printf("%d ",tab[i]);
    }
    printf("\n");
}

void change_tab(int tab[], int n) {
    for(int i=0;i<n;++i) {
        tab[i] = 1;
    }
}

void fill_2D_tab(double** tab, unsigned int w, unsigned int k,double war) {
    for(unsigned int i=0;i<w;++i) {
        for(unsigned int j=0;j<k;++j) {
            tab[i][j] = war;
        }
    }
}

void print_2D_tab(double** tab, unsigned int w, unsigned int k) {
    printf("\n");
    for(unsigned int i=0;i<w;++i) {
        for(unsigned int j=0;j<k;++j) {
            printf("%.2f ", tab[i][j]);
        }
        printf("\n");
    }
}

void free_2D_tab(double** tab, unsigned int w) {
    for(unsigned int i=0;i<w;++i) {
        free(tab[i]);
    }
    free(tab);
}
