//
// Created by kubak on 08.06.2022.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

typedef struct {
    double * rows;
} Matrix;

double** create_matrix(unsigned int rows, unsigned int cols, double val);
#endif //MATRIX_MATRIX_H
