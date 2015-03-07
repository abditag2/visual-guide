/*
 * File: Roberts_emxutil.h
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 06-Mar-2015 22:47:14
 */

#ifndef __ROBERTS_EMXUTIL_H__
#define __ROBERTS_EMXUTIL_H__

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "Roberts_types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxFree_uint8_T(emxArray_uint8_T **pEmxArray);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInit_uint8_T(emxArray_uint8_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for Roberts_emxutil.h
 *
 * [EOF]
 */
