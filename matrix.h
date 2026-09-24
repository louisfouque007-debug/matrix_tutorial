#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdio.h>

typedef double scalar;

typedef struct matrix {
  unsigned n1, n2;
  bool ok;
  scalar *data;
} matrix;

matrix matrix_create(unsigned n1, unsigned n2, scalar v);
void matrix_destroy(matrix m);
matrix matrix_identity(unsigned n);
scalar *matrix_get(matrix m, unsigned i, unsigned j);
matrix matrix_add(matrix m, matrix n);
void matrix_print(FILE *f, matrix m);

matrix matrix_mult(matrix m1, matrix m2);
matrix matrix_pow(matrix m, int n);
matrix matrix_scalar(matrix m, double lambda);
double matrix_dot(matrix m1, matrix m2);
double matrix_trace(matrix m);
matrix matrix_transpose(matrix m);

#endif /* MATRIX_H */
