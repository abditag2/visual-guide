/*
 * File: conv2.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 06-Mar-2015 22:56:06
 */

/* Include files */
#include "rt_nonfinite.h"
#include "prewit.h"
#include "conv2.h"
#include "prewit_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *arg1
 *                emxArray_real_T *c
 * Return Type  : void
 */
void b_conv2(const emxArray_real_T *arg1, emxArray_real_T *c)
{
  short unnamed_idx_0;
  short unnamed_idx_1;
  int i2;
  int jc;
  int ja1;
  int ja2;
  int ic;
  int ia1;
  int ia2;
  double s;
  int ja;
  int b_ja;
  int jb;
  int i3;
  int ia;
  int b_ia;
  static const signed char b[9] = { 1, 1, 1, 0, 0, 0, -1, -1, -1 };

  unnamed_idx_0 = (short)arg1->size[0];
  unnamed_idx_1 = (short)arg1->size[1];
  i2 = c->size[0] * c->size[1];
  c->size[0] = unnamed_idx_0;
  c->size[1] = unnamed_idx_1;
  emxEnsureCapacity((emxArray__common *)c, i2, (int)sizeof(double));
  if ((arg1->size[0] == 0) || (arg1->size[1] == 0)) {
    i2 = c->size[0] * c->size[1];
    c->size[0] = unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *)c, i2, (int)sizeof(double));
    i2 = c->size[0] * c->size[1];
    c->size[1] = unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)c, i2, (int)sizeof(double));
    jc = unnamed_idx_0 * unnamed_idx_1;
    for (i2 = 0; i2 < jc; i2++) {
      c->data[i2] = 0.0;
    }
  } else {
    for (jc = 2; jc - 2 < arg1->size[1]; jc++) {
      if (3 < 1 + jc) {
        ja1 = jc - 2;
      } else {
        ja1 = 1;
      }

      ja2 = arg1->size[1];
      if (ja2 <= jc) {
      } else {
        ja2 = jc;
      }

      for (ic = 2; ic - 2 < arg1->size[0]; ic++) {
        if (3 < 1 + ic) {
          ia1 = ic - 2;
        } else {
          ia1 = 1;
        }

        ia2 = arg1->size[0];
        if (ia2 <= ic) {
        } else {
          ia2 = ic;
        }

        s = 0.0;
        i2 = ja2 - ja1;
        for (ja = 0; ja <= i2; ja++) {
          b_ja = ja1 + ja;
          jb = jc - b_ja;
          i3 = ia2 - ia1;
          for (ia = 0; ia <= i3; ia++) {
            b_ia = ia1 + ia;
            s += arg1->data[(b_ia + arg1->size[0] * (b_ja - 1)) - 1] * (double)
              b[(ic - b_ia) + 3 * jb];
          }
        }

        c->data[(ic + c->size[0] * (jc - 2)) - 2] = s;
      }
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *arg1
 *                emxArray_real_T *c
 * Return Type  : void
 */
void conv2(const emxArray_real_T *arg1, emxArray_real_T *c)
{
  short unnamed_idx_0;
  short unnamed_idx_1;
  int i0;
  int jc;
  int ja1;
  int ja2;
  int ic;
  int ia1;
  int ia2;
  double s;
  int ja;
  int b_ja;
  int jb;
  int i1;
  int ia;
  int b_ia;
  static const signed char b[9] = { 1, 0, -1, 1, 0, -1, 1, 0, -1 };

  unnamed_idx_0 = (short)arg1->size[0];
  unnamed_idx_1 = (short)arg1->size[1];
  i0 = c->size[0] * c->size[1];
  c->size[0] = unnamed_idx_0;
  c->size[1] = unnamed_idx_1;
  emxEnsureCapacity((emxArray__common *)c, i0, (int)sizeof(double));
  if ((arg1->size[0] == 0) || (arg1->size[1] == 0)) {
    i0 = c->size[0] * c->size[1];
    c->size[0] = unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *)c, i0, (int)sizeof(double));
    i0 = c->size[0] * c->size[1];
    c->size[1] = unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)c, i0, (int)sizeof(double));
    jc = unnamed_idx_0 * unnamed_idx_1;
    for (i0 = 0; i0 < jc; i0++) {
      c->data[i0] = 0.0;
    }
  } else {
    for (jc = 2; jc - 2 < arg1->size[1]; jc++) {
      if (3 < 1 + jc) {
        ja1 = jc - 2;
      } else {
        ja1 = 1;
      }

      ja2 = arg1->size[1];
      if (ja2 <= jc) {
      } else {
        ja2 = jc;
      }

      for (ic = 2; ic - 2 < arg1->size[0]; ic++) {
        if (3 < 1 + ic) {
          ia1 = ic - 2;
        } else {
          ia1 = 1;
        }

        ia2 = arg1->size[0];
        if (ia2 <= ic) {
        } else {
          ia2 = ic;
        }

        s = 0.0;
        i0 = ja2 - ja1;
        for (ja = 0; ja <= i0; ja++) {
          b_ja = ja1 + ja;
          jb = jc - b_ja;
          i1 = ia2 - ia1;
          for (ia = 0; ia <= i1; ia++) {
            b_ia = ia1 + ia;
            s += arg1->data[(b_ia + arg1->size[0] * (b_ja - 1)) - 1] * (double)
              b[(ic - b_ia) + 3 * jb];
          }
        }

        c->data[(ic + c->size[0] * (jc - 2)) - 2] = s;
      }
    }
  }
}

/*
 * File trailer for conv2.c
 *
 * [EOF]
 */
