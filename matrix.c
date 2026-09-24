#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "matrix.h"

#define PRINT_PRECISION "6"
#define PRINT_DECIMAL_PRECISION "2"

matrix matrix_create(unsigned n1, unsigned n2, scalar v)
{
  matrix m={n1,n2,true,NULL};
  if(n1==0 || n2==0)
    return m;
  else if(SIZE_MAX / n1 <= n2)
    m.ok = false;
  else if (!(m.data=calloc(((size_t) n1)*n2, sizeof(scalar))))
    m.ok = false;
  else {
    for(unsigned i=0; i<n1; ++i)
      for(unsigned j=0; j<n2; ++j)
        *matrix_get(m,i,j) = v;
  }
 
  return m;
}

matrix matrix_identity(unsigned n)
{
  matrix m = matrix_create(n, n, 0.);
  if(!m.ok)
    return m;

  for(unsigned i=0; i<n; ++i)
    *matrix_get(m, i, i) = 1.;
  return m;
}

void matrix_destroy(matrix m)
{
  if(m.ok) {
    m.ok = false;
    free(m.data);
  }
}

scalar *matrix_get(matrix m, unsigned i, unsigned j)
{
  if(!m.ok || i>m.n1 || i>m.n2)
    return NULL;

  return &m.data[i*m.n2+j];
}

matrix matrix_add(matrix m, matrix n)
{
  matrix res={0,0,false,NULL};

  if(m.n1!=n.n1 || m.n2!=n.n2 || !m.ok || !n.ok)
    return res;

  res=matrix_create(m.n1, m.n2, 0.);
  for(unsigned i=0; i<m.n1; ++i)
    for(unsigned j=0; j<m.n2; ++j)
      *matrix_get(res, i, j) = *matrix_get(m, i, j) + *matrix_get(n, i, j);

  return res;
}

void matrix_print(FILE *f, matrix m)
{
  if(!m.ok)
    fprintf(f, "Invalid matrix\n");
  else {
    for(unsigned i=0; i<m.n1; ++i) {
      for(unsigned j=0; j<m.n2; ++j)
        fprintf(
            f, 
            "%"PRINT_PRECISION"."PRINT_DECIMAL_PRECISION"f ",
            *matrix_get(m, i, j));
      fprintf(f, "\n");
    }
  }
}

matrix matrix_scalar(matrix m, double lambda) {
	matrix m2 = matrix_create(m.n1, m.n2, 0);
	for (unsigned i = 0; i < m.n1; i++){
		for (unsigned j = 0; j < m.n2; j++){
			*matrix_get(m2, i, j) = lambda * *matrix_get(m, i, j);
		}
	}
	return m2;
}



matrix matrix_mult(matrix m1, matrix m2) {
  matrix res={m1.n1,m2.n2,false,NULL};

  if(m1.n2!=m2.n1 || !m1.ok || !m2.ok)
    return res;
	int kk = m1.n2;

  res=matrix_create(m1.n1, m2.n2, 0.);
  for(unsigned i=0; i<m1.n1; ++i)
    for(unsigned j=0; j<m2.n2; ++j)
			for (unsigned k; k<kk; k++)
				*matrix_get(res, i, j) = *matrix_get(res, i, j) + *matrix_get(m1, i, k) + *matrix_get(m2, k, j);

  return res;

}

matrix matrix_transpose(matrix m) {
  matrix res={m.n1,m.n2,false,NULL};

  if(!m.ok)
    return res;

  res=matrix_create(m.n1, m.n2, 0.);
  for(unsigned i=0; i<m.n1; ++i)
    for(unsigned j=0; j<m.n2; ++j)
			*matrix_get(res, i, j) = *matrix_get(m, j, i);

  return res;
}

matrix matrix_pow(matrix m, int n)
{
	if (m.n1 != m.n2) {
		matrix m1 = {.n1 = 0; .n2 = 0; .ok=false; .data=NULL};
		return m1;
	}
	if (n <= 0) return matrix_identity(m.n1);
	matrix m1 = matrix_pow(m, n/2);
	matrix m2 = matrix_mult(m1, m1);
	matrix_destroy(m1);
	if (n % 2) 
	{
			matrix m3 = matrix_mult(m2, m);
			matrix_destroy(m2);
			return m3;
	}
	return m2;
}

double matrix_dot(matrix m1, matrix m2) {
	double total = 0;
	if (m1.n1 != m2.n1 || m1.n2 != m2.n2){
		return 0;
	}
	for (unsigned i = 0; i < m1.n1; i++){
		for (unsigned j = 0; j < m1.n2; j++){
			total += *matrix_get(m1, i, j) * *matrix_get(m2, i, j);
		}
	}
	return total;
}


double matrix_trace(matrix m)
{
		if (m.n1 != m.n2) return 0;
		double s = 0.0;
		for(int i=0; i<m.n1; i++)
		{
				s += *matrix_get(m, i, i);
		}
		return s;
}

