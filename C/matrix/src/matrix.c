//
// Created by kubak on 08.06.2022.
//
#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"

double** create_matrix(size_t rows, size_t cols, double val) {
    double ** matrix = malloc(rows * sizeof(double*));
    for(size_t i=0; i<rows; ++i) {
        matrix[i] = malloc(cols * sizeof(double ));
        for(size_t j=0; j<cols; ++j) {
            matrix[i][j] = val;
        }
    }

    return matrix;
}