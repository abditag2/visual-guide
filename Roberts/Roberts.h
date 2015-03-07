/*
 * File: Roberts.h
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 06-Mar-2015 22:47:14
 */

#ifndef __ROBERTS_H__
#define __ROBERTS_H__

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "Roberts_types.h"

/* Function Declarations */
extern void Roberts(const emxArray_real_T *originalImage, double threshold,
                    emxArray_uint8_T *edgeImage);

#endif

/*
 * File trailer for Roberts.h
 *
 * [EOF]
 */
