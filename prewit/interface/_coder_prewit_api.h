/* 
 * File: _coder_prewit_api.h 
 *  
 * MATLAB Coder version            : 2.6 
 * C/C++ source code generated on  : 06-Mar-2015 22:56:06 
 */

#ifndef ___CODER_PREWIT_API_H__
#define ___CODER_PREWIT_API_H__
/* Include files */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T
{
    double *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_real_T*/
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /*typedef_emxArray_real_T*/
#ifndef struct_emxArray_uint8_T
#define struct_emxArray_uint8_T
struct emxArray_uint8_T
{
    unsigned char *data;
    int *size;
    int allocatedSize;
    int numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_uint8_T*/
#ifndef typedef_emxArray_uint8_T
#define typedef_emxArray_uint8_T
typedef struct emxArray_uint8_T emxArray_uint8_T;
#endif /*typedef_emxArray_uint8_T*/

/* Function Declarations */
extern void prewit_initialize(emlrtContext *aContext);
extern void prewit_terminate(void);
extern void prewit_atexit(void);
extern void prewit_api(const mxArray *prhs[2], const mxArray *plhs[1]);
extern void prewit(emxArray_real_T *originalImage, double threshold, emxArray_uint8_T *edgeImage);
extern void prewit_xil_terminate(void);

#endif
/* 
 * File trailer for _coder_prewit_api.h 
 *  
 * [EOF] 
 */
