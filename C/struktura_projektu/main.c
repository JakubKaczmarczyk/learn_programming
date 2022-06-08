#include <stdio.h>
#include <stdlib.h>
#include "prad.h"

void increment_y(void);

int main() {
    double prad = 6.0;
    printf("Opor wynosi: %.3f\n", calc_R(napiecie,prad));
//    extern int x;
//    printf("%d\n",x);

    char slowo[] = "new";
    printf("%s", slowo);
    for(int i=0; i<5; ++i) {
        increment_y();
    }


    return EXIT_SUCCESS;
}

void increment_y(void) {
    static int y = 0;
    int y2 = 0;
    printf("y: %d y2:%d\n", y++, y2++);
}
