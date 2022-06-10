#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


int main() {
    size_t rows = 5U;
    size_t cols = 7U;
    double val = 13.0;
    double ** matrix = create_matrix(rows,cols, val);
    for(size_t i=0; i<rows; ++i) {
        for(size_t j=0; j<cols; ++j) {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
