/*
 * File: sqrt.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 06-Mar-2015 20:42:33
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sobel.h"
#include "sqrt.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *x
 * Return Type  : void
 */
void b_sqrt(emxArray_real_T *x)
{
  int i4;
  int k;
  i4 = x->size[0] * x->size[1];
  for (k = 0; k < i4; k++) {
    x->data[k] = sqrt(x->data[k]);
  }
}

/*
 * File trailer for sqrt.c
 *
 * [EOF]
 */
