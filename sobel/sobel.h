/*
 * File: sobel.h
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 06-Mar-2015 20:42:33
 */

#ifndef __SOBEL_H__
#define __SOBEL_H__

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "sobel_types.h"

/* Function Declarations */
extern void sobel(const emxArray_real_T *originalImage, double threshold,
                  emxArray_uint8_T *edgeImage);

#endif

/*
 * File trailer for sobel.h
 *
 * [EOF]
 */
