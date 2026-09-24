#include "utest.h"
#include "matrix.h"

UTEST(matrix_create, simple) {
  matrix m = matrix_create(3, 5, 0.);
  ASSERT_TRUE(m.ok && m.n1==3 && m.n2==5);
}

UTEST(matrix_create, too_large) {
  matrix m = matrix_create((unsigned)-1, (unsigned)-1, 0.);
  ASSERT_FALSE(m.ok);
}

UTEST(matrix_create, zero) {
  matrix m = matrix_create(0, 0, 0.);
  ASSERT_TRUE(m.ok && m.n1==0 && m.n2==0);
}

UTEST(matrix_identity, simple) {
  matrix m = matrix_identity(42);
  ASSERT_TRUE(m.ok && m.n1==42 && m.n2==42);
}

UTEST(matrix_identity, too_large) {
  matrix m = matrix_identity((unsigned) -1);
  ASSERT_TRUE(!m.ok);
}

UTEST(matrix_identity, zero) {
  matrix m = matrix_identity(0);
  ASSERT_TRUE(m.ok && m.n1==0 && m.n2==0);
}

UTEST(matrix_destroy, simple) {
  matrix m = matrix_create(2, 5, 0.);
  matrix_destroy(m);
  ASSERT_TRUE(1);
}

UTEST(matrix_destroy, wrong) {
  matrix m;
  m.ok=false;
  m.data=(scalar*)0xdeadbeef;
  matrix_destroy(m);
  ASSERT_TRUE(1);
}

UTEST(matrix_get, simple) {
  matrix m = matrix_identity(12);
  ASSERT_TRUE(*matrix_get(m,3,3)==1.);
}

UTEST(matrix_get, wrong) {
  matrix m;
  m.ok=false;
  ASSERT_TRUE(matrix_get(m, 0, 0)==NULL);
}

UTEST(matrix_scalar, zero1) {
  matrix m = matrix_identity(12);
  m = matrix_scalar(m, 0.);
  
  ASSERT_TRUE(*matrix_get(m, 5, 5)==0.);
}

UTEST(matrix_scalar, zero2) {
  matrix m = matrix_create(6, 5, 0.);
  m = matrix_scalar(m, 42.1);
  
  ASSERT_TRUE(*matrix_get(m, 5, 3)==0.);
}

UTEST(matrix_scalar, regular) {
  matrix m = matrix_create(6, 5, 2.);
  m = matrix_scalar(m, 42.0);
  
  ASSERT_TRUE(*matrix_get(m, 5, 3)==84.);
}

UTEST(matrix_dot, regular1)  {
  matrix m = matrix_create(2, 3, 1.);
  matrix m2 = matrix_create(2, 3, 4.);
  double mm = matrix_dot(m, m2);
  
  ASSERT_TRUE(mm=24.);
}

UTEST(matrix_dot, regular2)  {
  matrix m = matrix_create(2, 3, 1.);
  matrix m2 = matrix_create(2, 3, 4.);
  *matrix_get(m2, 1, 0) = 67.;
  double mm = matrix_dot(m, m2);
  
  ASSERT_EQ(mm,87.);
}

UTEST(matrix_dot, zero)  {
  matrix m = matrix_create(2, 3, 4.523);
  matrix m2 = matrix_create(2, 3, 0.);
  double mm = matrix_dot(m, m2);
  
  ASSERT_EQ(mm,0);
}

UTEST(matrix_mult, testmult) {
  matrix m1 = matrix_create(6, 7, 6.7);
  matrix m2 = matrix_create(7, 8, 7.89);
  matrix m3 = matrix_mult(m1, m2);
  matrix m4 = matrix_mult(m2, m1);
  ASSERT_TRUE(m3.ok == true);
  ASSERT_TRUE(m4.ok == false);
  ASSERT_NEAR(*matrix_get(m3, 0, 0), 370.041, 1e-5);
  matrix_destroy(m1);
  matrix_destroy(m2);
  matrix_destroy(m3);
  matrix_destroy(m4);
}

UTEST(matrix_pow, testpow) {
  matrix m = matrix_create(7, 7, 9.);
  matrix n = matrix_pow(m, 67);
  matrix o = matrix_pow(m, 0);
  ASSERT_NEAR(*matrix_get(n, 0, 0), 5.13710891275050618264802650675e119, 1e110);
  ASSERT_NEAR(*matrix_get(o, 1, 1), 1., 1e-10);
  ASSERT_NEAR(*matrix_get(o, 6, 7), 0., 1e-10);
}

UTEST(matrix_transpose, simple) {
	matrix m = matrix_identity(100);
	*matrix_get(m, 11, 0) = 1;
	matrix m2 = matrix_transpose(m);
	ASSERT_TRUE(*matrix_get(m2, 0, 11) == 1);
}

UTEST(matrix_trace, simple) {	
	matrix m = matrix_identity(12);
	ASSERT_TRUE(matrix_trace(m) == 12);
}

UTEST_MAIN()  
