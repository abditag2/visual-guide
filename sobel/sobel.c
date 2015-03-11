/*
 * File: sobel.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 06-Mar-2015 20:42:33
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sobel.h"
#include "sobel_emxutil.h"
#include "sqrt.h"
#include "conv2.h"

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * Arguments    : const emxArray_real_T *originalImage
 *                double threshold
 *                emxArray_uint8_T *edgeImage
 * Return Type  : void
 */
void sobel(const emxArray_real_T *originalImage, double threshold,
           emxArray_uint8_T *edgeImage)
{
  emxArray_real_T *H;
  emxArray_real_T *V;
  int b_H;
  int c_H;
  emxInit_real_T(&H, 2);
  emxInit_real_T(&V, 2);

  /*  edgeImage = sobel(originalImage, threshold) */
  /*  Sobel edge detection. Given a normalized image (with double values) */
  /*  return an image where the edges are detected w.r.t. threshold value. */
  conv2(originalImage, H);
  b_conv2(originalImage, V);
  b_H = H->size[0] * H->size[1];
  emxEnsureCapacity((emxArray__common *)H, b_H, (int)sizeof(double));
  b_H = H->size[0];
  c_H = H->size[1];
  c_H *= b_H;
  for (b_H = 0; b_H < c_H; b_H++) {
    H->data[b_H] = H->data[b_H] * H->data[b_H] + V->data[b_H] * V->data[b_H];
  }

  emxFree_real_T(&V);
  b_sqrt(H);
  b_H = edgeImage->size[0] * edgeImage->size[1];
  edgeImage->size[0] = H->size[0];
  edgeImage->size[1] = H->size[1];
  emxEnsureCapacity((emxArray__common *)edgeImage, b_H, (int)sizeof(unsigned
    char));
  c_H = H->size[0] * H->size[1];
  for (b_H = 0; b_H < c_H; b_H++) {
    edgeImage->data[b_H] = (unsigned char)rt_roundd_snf((double)(H->data[b_H] >
      threshold) * 255.0);
  }

  emxFree_real_T(&H);
}

/*
 * File trailer for sobel.c
 *
 * [EOF]
 */
