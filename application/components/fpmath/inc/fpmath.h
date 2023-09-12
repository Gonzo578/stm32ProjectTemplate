// MIT License

// Copyright (c) 2023 Ralf Hochhausen

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

/**
 * ***************************************************************************************************************
 *  Fixed point math library
 *****************************************************************************************************************
*/

#ifndef __FPM_H
#define __FPM_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************************************************
 * INCLUDES ******************************************************************************************************
 *****************************************************************************************************************/
#include <stdint.h>

/*****************************************************************************************************************
 * GLOBAL TYPES **************************************************************************************************
 *****************************************************************************************************************/

/**
    \brief Type definition of the fixed point data format
*/
typedef int32_t  TFp;

/**
  \brief Type definition of the used angle format
*/
typedef int16_t  TAngle;

/**
  \brief Type definition of a complex number in cartesian format
*/
typedef struct _TCartNum {
    TFp tRe;    /**< Real part of the complex number */
    TFp tIm;    /**< Imag part of the complex number */
}TCartNum;

/**
  \brief Type definition of a complex number in polar format
*/
typedef struct _TPolNum {
    TFp     tMag;       /**< Magnitude of the complex vector */
    TAngle  siAngle;    /**< Angle of the complex vector */
}TPolNum;

/**
   \brief Type definition of a complex number
*/
typedef struct _TCplxNum {
    TCartNum    tCartNum;     /**< Complex number in cartesian format */
    TPolNum     tPolNum;      /**< Complex number in polar format */
}TCplxNum;

/**
    \brief Type definition of a common three phase system value
*/
typedef struct _TThreePhase {
    TFp a;    /**< Component of the A phase */
    TFp b;    /**< Component of the B phase */
    TFp c;    /**< Component of the C phase */
}TThreePhase;

/**
 * \brief Type definition of a point
 *
 * A point is defined by a x coordinate and a y coordinate in a cartesian coordinate system
 * */
typedef struct _TPoint {
	TFp	tXValue;	/**< x-Coordinate */
	TFp	tYValue;	/**< y-Coordinate */
}TPoint;

/**
 * 	\brief	Structure type definition of a generic 3D-LUT
 * */
typedef struct _TLookUpTable3D {
	TFp*		ptXValues;		/**< Pointer to x-values of the grid */
	TFp*		ptYValues;		/**< Pointer to x-values of the grid */
	TFp*		ptZValues;		/**< Pointer to a z-value grid */
	uint32_t	ulXSize;		/**< Look-up-table size in x-direction */
	uint32_t	ulYSize;		/**< Look-up-table size in y-direction */
}TLookUpTable3D;

/*****************************************************************************************************************
 * GLOBAL DEFINITIONS ********************************************************************************************
 *****************************************************************************************************************/

/**
  \brief Definition of the global fixed point format
 
  This value determines the number of bits used for the fractional part in
  all standard fixed point numbers.

  \remark CONFIGURE HERE THE DESIRED FP FORMAT
*/
#define FPM_GLOBAL_FP_FORMAT    12

#define FPM_SHIFT_360                  65536   /* 360� q16  */
#define FPM_TWO_PI            ((TAngle)65535)  /* 360� q15  */
#define FPM_PI                ((TAngle)32767)  /* 180� q15  */
#define FPM_NEG_PI            ((TAngle)32768)  /*-180� q15  */
#define FPM_PI_HALF           ((TAngle)16384)  /*  90� q15  */
#define FPM_NEG_PI_HALF       ((TAngle)-16384) /* -90� q15  */
#define FPM_PI_QUARTER        ((TAngle) 8192)  /*  45� q15  */
#define FPM_NEG_PI_QUARTER    ((TAngle)-8192)  /* -45� q15  */
#define FPM_PI_THIRD          ((TAngle)10923)  /*  60� q15  */

#define FPM_SQRT3_INV_Q15    Q15(0.577350279)  /* 1/sqrt(3)        q15 format */
#define FPM_SQRT3_INV_Q      FP(0.577350279)   /* 1/sqrt(3)     global format */
#define FPM_TWO_DIV_SQRT3_Q  FP(1.154700538)   /* 2/sqrt(3)     global format */

#define FPM_SIN_MAX_Q15              Q15(1.0)  /* Q15 maximum value  (reference) */

/*****************************************************************************************************************
 * GLOBAL MACROS *************************************************************************************************
 *****************************************************************************************************************/

/**
  \brief Definition of the fixed point conversion macro
 
  The passed number is converted to the standard fixed point format as it is
  defined above (refer to FPM_GLOBAL_FP_FORMAT)
 
*/
#define Q28(x)    ((TFp)(x*268435456.0))   /**< Q28 fixed point number definition macro */
#define Q27(x)    ((TFp)(x*134217728.0))   /**< Q27 fixed point number definition macro */
#define Q26(x)    ((TFp)(x*67108864.0))    /**< Q26 fixed point number definition macro */
#define Q25(x)    ((TFp)(x*33554432.0))    /**< Q25 fixed point number definition macro */
#define Q24(x)    ((TFp)(x*16777216.0))    /**< Q24 fixed point number definition macro */
#define Q23(x)    ((TFp)(x*8388608.0))     /**< Q23 fixed point number definition macro */
#define Q22(x)    ((TFp)(x*4194304.0))     /**< Q22 fixed point number definition macro */
#define Q21(x)    ((TFp)(x*2097152.0))     /**< Q21 fixed point number definition macro */
#define Q20(x)    ((TFp)(x*1048576.0))     /**< Q20 fixed point number definition macro */
#define Q19(x)    ((TFp)(x*524288.0))      /**< Q19 fixed point number definition macro */
#define Q18(x)    ((TFp)(x*262144.0))      /**< Q18 fixed point number definition macro */
#define Q17(x)    ((TFp)(x*131072.0))      /**< Q17 fixed point number definition macro */
#define Q16(x)    ((TFp)(x*65536.0))       /**< Q16 fixed point number definition macro */
#define Q15(x)    ((TFp)(x*32768.0))       /**< Q15 fixed point number definition macro */
#define Q14(x)    ((TFp)(x*16384.0))       /**< Q14 fixed point number definition macro */
#define Q13(x)    ((TFp)(x*8192.0))        /**< Q13 fixed point number definition macro */
#define Q12(x)    ((TFp)(x*4096.0))        /**< Q12 fixed point number definition macro */
#define Q11(x)    ((TFp)(x*2048.0))        /**< Q11 fixed point number definition macro */
#define Q10(x)    ((TFp)(x*1024.0))        /**< Q10 fixed point number definition macro */
#define Q9(x)     ((TFp)(x*512.0))         /**< Q9 fixed point number definition macro */
#define Q8(x)     ((TFp)(x*256.0))         /**< Q8 fixed point number definition macro */
#define Q7(x)     ((TFp)(x*128.0))         /**< Q7 fixed point number definition macro */
#define Q6(x)     ((TFp)(x*64.0))          /**< Q6 fixed point number definition macro */
#define Q5(x)     ((TFp)(x*32.0))          /**< Q5 fixed point number definition macro */
#define Q4(x)     ((TFp)(x*16.0))          /**< Q4 fixed point number definition macro */
#define Q3(x)     ((TFp)(x*8.0))           /**< Q3 fixed point number definition macro */
#define Q2(x)     ((TFp)(x*4.0))           /**< Q2 fixed point number definition macro */
#define Q1(x)     ((TFp)(x*2.0))           /**< Q1 fixed point number definition macro */
#define Q0(x)     ((TFp)(x*1.0))           /**< Q0 fixed point number definition macro */

#if (FPM_GLOBAL_FP_FORMAT == 0)
#define FP(x)     Q0(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 1)
#define FP(x)     Q1(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 2)
#define FP(x)     Q2(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 3)
#define FP(x)     Q3(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 4)
#define FP(x)     Q4(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 5)
#define FP(x)     Q5(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 6)
#define FP(x)     Q6(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 7)
#define FP(x)     Q7(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 8)
#define FP(x)     Q8(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 9)
#define FP(x)     Q9(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 10)
#define FP(x)     Q10(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 11)
#define FP(x)     Q11(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 12)
#define FP(x)     Q12(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 13)
#define FP(x)     Q13(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 14)
#define FP(x)     Q14(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 15)
#define FP(x)     Q15(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 16)
#define FP(x)     Q16(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 17)
#define FP(x)     Q17(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 18)
#define FP(x)     Q18(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 19)
#define FP(x)     Q19(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 20)
#define FP(x)     Q20(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 21)
#define FP(x)     Q21(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 22)
#define FP(x)     Q22(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 23)
#define FP(x)     Q23(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 24)
#define FP(x)     Q24(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 25)
#define FP(x)     Q25(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 26)
#define FP(x)     Q26(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 27)
#define FP(x)     Q27(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 28)
#define FP(x)     Q28(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 29)
#define FP(x)     Q29(x)  
#endif
#if (FPM_GLOBAL_FP_FORMAT == 30)
#define FP(x)     Q30(x)  
#endif

/******************************************************************************
 * FORMAT CONVERSION MACROS ***************************************************
 ******************************************************************************/
#define   GFPF   FPM_GLOBAL_FP_FORMAT

#define   FPM_GQtoQ30(x)  ((TFp) x * (TFp)(1UL << (30 - GFPF)))
#define   FPM_Q30toGQ(x)  ((TFp) x / (TFp)(1UL << (30 - GFPF)))

#define   FPM_GQtoQ29(x)  ((GFPF >= 29) ? ((TFp) x / (TFp)(1UL << (GFPF - 29))) : ((TFp) x * (TFp)(1UL << (29 - GFPF))))
#define   FPM_Q29toGQ(x)  ((GFPF >= 29) ? ((TFp) x * (TFp)(1UL << (GFPF - 29))) : ((TFp) x / (TFp)(1UL << (29 - GFPF))))

#define   FPM_GQtoQ28(x)  ((GFPF >= 28) ? ((TFp) x / (TFp)(1UL << (GFPF - 28))) : ((TFp) x * (TFp)(1UL << (28 - GFPF))))
#define   FPM_Q28toGQ(x)  ((GFPF >= 28) ? ((TFp) x * (TFp)(1UL << (GFPF - 28))) : ((TFp) x / (TFp)(1UL << (28 - GFPF))))

#define   FPM_GQtoQ27(x)  ((GFPF >= 27) ? ((TFp) x / (TFp)(1UL << (GFPF - 27))) : ((TFp) x * (TFp)(1UL << (27 - GFPF))))
#define   FPM_Q27toGQ(x)  ((GFPF >= 27) ? ((TFp) x * (TFp)(1UL << (GFPF - 27))) : ((TFp) x / (TFp)(1UL << (27 - GFPF))))

#define   FPM_GQtoQ26(x)  ((GFPF >= 26) ? ((TFp) x / (TFp)(1UL << (GFPF - 26))) : ((TFp) x * (TFp)(1UL << (26 - GFPF))))
#define   FPM_Q26toGQ(x)  ((GFPF >= 26) ? ((TFp) x * (TFp)(1UL << (GFPF - 26))) : ((TFp) x / (TFp)(1UL << (26 - GFPF))))

#define   FPM_GQtoQ25(x)  ((GFPF >= 25) ? ((TFp) x / (TFp)(1UL << (GFPF - 25))) : ((TFp) x * (TFp)(1UL << (25 - GFPF))))
#define   FPM_Q25toGQ(x)  ((GFPF >= 25) ? ((TFp) x * (TFp)(1UL << (GFPF - 25))) : ((TFp) x / (TFp)(1UL << (25 - GFPF))))

#define   FPM_GQtoQ24(x)  ((GFPF >= 24) ? ((TFp) x / (TFp)(1UL << (GFPF - 24))) : ((TFp) x * (TFp)(1UL << (24 - GFPF))))
#define   FPM_Q24toGQ(x)  ((GFPF >= 24) ? ((TFp) x * (TFp)(1UL << (GFPF - 24))) : ((TFp) x / (TFp)(1UL << (24 - GFPF))))

#define   FPM_GQtoQ23(x)  ((GFPF >= 23) ? ((TFp) x / (TFp)(1UL << (GFPF - 23))) : ((TFp) x * (TFp)(1UL << (23 - GFPF))))
#define   FPM_Q23toGQ(x)  ((GFPF >= 23) ? ((TFp) x * (TFp)(1UL << (GFPF - 23))) : ((TFp) x / (TFp)(1UL << (23 - GFPF))))

#define   FPM_GQtoQ22(x)  ((GFPF >= 22) ? ((TFp) x / (TFp)(1UL << (GFPF - 22))) : ((TFp) x * (TFp)(1UL << (22 - GFPF))))
#define   FPM_Q22toGQ(x)  ((GFPF >= 22) ? ((TFp) x * (TFp)(1UL << (GFPF - 22))) : ((TFp) x / (TFp)(1UL << (22 - GFPF))))

#define   FPM_GQtoQ21(x)  ((GFPF >= 21) ? ((TFp) x / (TFp)(1UL << (GFPF - 21))) : ((TFp) x * (TFp)(1UL << (21 - GFPF))))
#define   FPM_Q21toGQ(x)  ((GFPF >= 21) ? ((TFp) x * (TFp)(1UL << (GFPF - 21))) : ((TFp) x / (TFp)(1UL << (21 - GFPF))))

#define   FPM_GQtoQ20(x)  ((GFPF >= 20) ? ((TFp) x / (TFp)(1UL << (GFPF - 20))) : ((TFp) x * (TFp)(1UL << (20 - GFPF))))
#define   FPM_Q20toGQ(x)  ((GFPF >= 20) ? ((TFp) x * (TFp)(1UL << (GFPF - 20))) : ((TFp) x / (TFp)(1UL << (20 - GFPF))))

#define   FPM_GQtoQ19(x)  ((GFPF >= 19) ? ((TFp) x / (TFp)(1UL << (GFPF - 19))) : ((TFp) x * (TFp)(1UL << (19 - GFPF))))
#define   FPM_Q19toGQ(x)  ((GFPF >= 19) ? ((TFp) x * (TFp)(1UL << (GFPF - 19))) : ((TFp) x / (TFp)(1UL << (19 - GFPF))))

#define   FPM_GQtoQ18(x)  ((GFPF >= 18) ? ((TFp) x / (TFp)(1UL << (GFPF - 18))) : ((TFp) x * (TFp)(1UL << (18 - GFPF))))
#define   FPM_Q18toGQ(x)  ((GFPF >= 18) ? ((TFp) x * (TFp)(1UL << (GFPF - 18))) : ((TFp) x / (TFp)(1UL << (18 - GFPF))))

#define   FPM_GQtoQ17(x)  ((GFPF >= 17) ? ((TFp) x / (TFp)(1UL << (GFPF - 17))) : ((TFp) x * (TFp)(1UL << (17 - GFPF))))
#define   FPM_Q17toGQ(x)  ((GFPF >= 17) ? ((TFp) x * (TFp)(1UL << (GFPF - 17))) : ((TFp) x / (TFp)(1UL << (17 - GFPF))))

#define   FPM_GQtoQ16(x)  ((GFPF >= 16) ? ((TFp) x / (TFp)(1UL << (GFPF - 16))) : ((TFp) x * (TFp)(1UL << (16 - GFPF))))
#define   FPM_Q16toGQ(x)  ((GFPF >= 16) ? ((TFp) x * (TFp)(1UL << (GFPF - 16))) : ((TFp) x / (TFp)(1UL << (16 - GFPF))))

#define   FPM_GQtoQ15(x)  ((GFPF >= 15) ? ((TFp) x / (TFp)(1UL << (GFPF - 15))) : ((TFp) x * (TFp)(1UL << (15 - GFPF))))
#define   FPM_Q15toGQ(x)  ((GFPF >= 15) ? ((TFp) x * (TFp)(1UL << (GFPF - 15))) : ((TFp) x / (TFp)(1UL << (15 - GFPF))))

#define   FPM_GQtoQ14(x)  ((GFPF >= 14) ? ((TFp) x / (TFp)(1UL << (GFPF - 14))) : ((TFp) x * (TFp)(1UL << (14 - GFPF))))
#define   FPM_Q14toGQ(x)  ((GFPF >= 14) ? ((TFp) x * (TFp)(1UL << (GFPF - 14))) : ((TFp) x / (TFp)(1UL << (14 - GFPF))))

#define   FPM_GQtoQ13(x)  ((GFPF >= 13) ? ((TFp) x / (TFp)(1UL << (GFPF - 13))) : ((TFp) x * (TFp)(1UL << (13 - GFPF))))
#define   FPM_Q13toGQ(x)  ((GFPF >= 13) ? ((TFp) x * (TFp)(1UL << (GFPF - 13))) : ((TFp) x / (TFp)(1UL << (13 - GFPF))))

#define   FPM_GQtoQ12(x)  ((GFPF >= 12) ? ((TFp) x / (TFp)(1UL << (GFPF - 12))) : ((TFp) x * (TFp)(1UL << (12 - GFPF))))
#define   FPM_Q12toGQ(x)  ((GFPF >= 12) ? ((TFp) x * (TFp)(1UL << (GFPF - 12))) : ((TFp) x / (TFp)(1UL << (12 - GFPF))))

#define   FPM_GQtoQ11(x)  ((GFPF >= 11) ? ((TFp) x / (TFp)(1UL << (GFPF - 11))) : ((TFp) x * (TFp)(1UL << (11 - GFPF))))
#define   FPM_Q11toGQ(x)  ((GFPF >= 11) ? ((TFp) x * (TFp)(1UL << (GFPF - 11))) : ((TFp) x / (TFp)(1UL << (11 - GFPF))))

#define   FPM_GQtoQ10(x)  ((GFPF >= 10) ? ((TFp) x / (TFp)(1UL << (GFPF - 10))) : ((TFp) x * (TFp)(1UL << (10 - GFPF))))
#define   FPM_Q10toGQ(x)  ((GFPF >= 10) ? ((TFp) x * (TFp)(1UL << (GFPF - 10))) : ((TFp) x / (TFp)(1UL << (10 - GFPF))))

#define   FPM_GQtoQ9(x)   ((GFPF >=  9) ? ((TFp) x / (TFp)(1UL << (GFPF -  9))) : ((TFp) x * (TFp)(1UL << ( 9 - GFPF))))
#define   FPM_Q9toGQ(x)   ((GFPF >=  9) ? ((TFp) x * (TFp)(1UL << (GFPF -  9))) : ((TFp) x / (TFp)(1UL << ( 9 - GFPF))))

#define   FPM_GQtoQ8(x)   ((GFPF >=  8) ? ((TFp) x / (TFp)(1UL << (GFPF -  8))) : ((TFp) x * (TFp)(1UL << ( 8 - GFPF))))
#define   FPM_Q8toGQ(x)   ((GFPF >=  8) ? ((TFp) x * (TFp)(1UL << (GFPF -  8))) : ((TFp) x / (TFp)(1UL << ( 8 - GFPF))))

#define   FPM_GQtoQ7(x)   ((GFPF >=  7) ? ((TFp) x / (TFp)(1UL << (GFPF -  7))) : ((TFp) x * (TFp)(1UL << ( 7 - GFPF))))
#define   FPM_Q7toGQ(x)   ((GFPF >=  7) ? ((TFp) x * (TFp)(1UL << (GFPF -  7))) : ((TFp) x / (TFp)(1UL << ( 7 - GFPF))))

#define   FPM_GQtoQ6(x)   ((GFPF >=  6) ? ((TFp) x / (TFp)(1UL << (GFPF -  6))) : ((TFp) x * (TFp)(1UL << ( 6 - GFPF))))
#define   FPM_Q6toGQ(x)   ((GFPF >=  6) ? ((TFp) x * (TFp)(1UL << (GFPF -  6))) : ((TFp) x / (TFp)(1UL << ( 6 - GFPF))))

#define   FPM_GQtoQ5(x)   ((GFPF >=  5) ? ((TFp) x / (TFp)(1UL << (GFPF -  5))) : ((TFp) x * (TFp)(1UL << ( 5 - GFPF))))
#define   FPM_Q5toGQ(x)   ((GFPF >=  5) ? ((TFp) x * (TFp)(1UL << (GFPF -  5))) : ((TFp) x / (TFp)(1UL << ( 5 - GFPF))))

#define   FPM_GQtoQ4(x)   ((GFPF >=  4) ? ((TFp) x / (TFp)(1UL << (GFPF -  4))) : ((TFp) x * (TFp)(1UL << ( 4 - GFPF))))
#define   FPM_Q4toGQ(x)   ((GFPF >=  4) ? ((TFp) x * (TFp)(1UL << (GFPF -  4))) : ((TFp) x / (TFp)(1UL << ( 4 - GFPF))))

#define   FPM_GQtoQ3(x)   ((GFPF >=  3) ? ((TFp) x / (TFp)(1UL << (GFPF -  3))) : ((TFp) x * (TFp)(1UL << ( 3 - GFPF))))
#define   FPM_Q3toGQ(x)   ((GFPF >=  3) ? ((TFp) x * (TFp)(1UL << (GFPF -  3))) : ((TFp) x / (TFp)(1UL << ( 3 - GFPF))))

#define   FPM_GQtoQ2(x)   ((GFPF >=  2) ? ((TFp) x / (TFp)(1UL << (GFPF -  2))) : ((TFp) x * (TFp)(1UL << ( 2 - GFPF))))
#define   FPM_Q2toGQ(x)   ((GFPF >=  2) ? ((TFp) x * (TFp)(1UL << (GFPF -  2))) : ((TFp) x / (TFp)(1UL << ( 2 - GFPF))))

#define   FPM_GQtoQ1(x)   ((TFp) x / (TFp)(1UL << (GFPF - 1)))
#define   FPM_Q1toGQ(x)   ((TFp) x * (TFp)(1UL << (GFPF - 1)))

/* Generic conversion macro */
#define   FPM_QxtoQy(val,x,y)  ((x >= y) ? ((TFp) val / (TFp)(1UL << (x - y))):((TFp) val * (TFp)(1UL << (y - x))))

/******************************************************************************
 * FIXED POINT MULTIPLICATION MACROS ******************************************
 ******************************************************************************/
#define FPM_FpMul(x,y)     ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL << FPM_GLOBAL_FP_FORMAT)))

#define FPM_FpMulQ1(x,y)   ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 1)))
#define FPM_FpMulQ2(x,y)   ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 2)))
#define FPM_FpMulQ3(x,y)   ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 3)))
#define FPM_FpMulQ4(x,y)   ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 4)))
#define FPM_FpMulQ5(x,y)   ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 5)))
#define FPM_FpMulQ6(x,y)   ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 6)))
#define FPM_FpMulQ7(x,y)   ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 7)))
#define FPM_FpMulQ8(x,y)   ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 8)))
#define FPM_FpMulQ9(x,y)   ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 9)))
#define FPM_FpMulQ10(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 10)))
#define FPM_FpMulQ11(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 11)))
#define FPM_FpMulQ12(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 12)))
#define FPM_FpMulQ13(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 13)))
#define FPM_FpMulQ14(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 14)))
#define FPM_FpMulQ15(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 15)))
#define FPM_FpMulQ16(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 16)))
#define FPM_FpMulQ17(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 17)))
#define FPM_FpMulQ18(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 18)))
#define FPM_FpMulQ19(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 19)))
#define FPM_FpMulQ20(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 20)))
#define FPM_FpMulQ21(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 21)))
#define FPM_FpMulQ22(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 22)))
#define FPM_FpMulQ23(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 23)))
#define FPM_FpMulQ24(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 24)))
#define FPM_FpMulQ25(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 25)))
#define FPM_FpMulQ26(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 26)))
#define FPM_FpMulQ27(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 27)))
#define FPM_FpMulQ28(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 28)))
#define FPM_FpMulQ29(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 29)))
#define FPM_FpMulQ30(x,y)  ((TFp)(((TFp)x*(TFp)y) / (TFp)(1UL  << 30)))

/******************************************************************************
 * FIXED POINT DIVISION MACROS ************************************************
 ******************************************************************************/
#define FPM_FpDiv(x,y)     ((TFp)(((TFp)x * (TFp)(1UL  << FPM_GLOBAL_FP_FORMAT))/(TFp)y))

#define FPM_FpDivQ1(x,y)   ((TFp)(((TFp)x * (TFp)(1UL  << 1 ))/(TFp)y))
#define FPM_FpDivQ2(x,y)   ((TFp)(((TFp)x * (TFp)(1UL  << 2 ))/(TFp)y))
#define FPM_FpDivQ3(x,y)   ((TFp)(((TFp)x * (TFp)(1UL  << 3 ))/(TFp)y))
#define FPM_FpDivQ4(x,y)   ((TFp)(((TFp)x * (TFp)(1UL  << 4 ))/(TFp)y))
#define FPM_FpDivQ5(x,y)   ((TFp)(((TFp)x * (TFp)(1UL  << 5 ))/(TFp)y))
#define FPM_FpDivQ6(x,y)   ((TFp)(((TFp)x * (TFp)(1UL  << 6 ))/(TFp)y))
#define FPM_FpDivQ7(x,y)   ((TFp)(((TFp)x * (TFp)(1UL  << 7 ))/(TFp)y))
#define FPM_FpDivQ8(x,y)   ((TFp)(((TFp)x * (TFp)(1UL  << 8 ))/(TFp)y))
#define FPM_FpDivQ9(x,y)   ((TFp)(((TFp)x * (TFp)(1UL  << 9 ))/(TFp)y))
#define FPM_FpDivQ10(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 10))/(TFp)y))
#define FPM_FpDivQ11(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 11))/(TFp)y))
#define FPM_FpDivQ12(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 12))/(TFp)y))
#define FPM_FpDivQ13(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 13))/(TFp)y))
#define FPM_FpDivQ14(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 14))/(TFp)y))
#define FPM_FpDivQ15(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 15))/(TFp)y))
#define FPM_FpDivQ16(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 16))/(TFp)y))
#define FPM_FpDivQ17(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 17))/(TFp)y))
#define FPM_FpDivQ18(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 18))/(TFp)y))
#define FPM_FpDivQ19(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 19))/(TFp)y))
#define FPM_FpDivQ20(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 20))/(TFp)y))
#define FPM_FpDivQ21(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 21))/(TFp)y))
#define FPM_FpDivQ22(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 22))/(TFp)y))
#define FPM_FpDivQ23(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 23))/(TFp)y))
#define FPM_FpDivQ24(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 24))/(TFp)y))
#define FPM_FpDivQ25(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 25))/(TFp)y))
#define FPM_FpDivQ26(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 26))/(TFp)y))
#define FPM_FpDivQ27(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 27))/(TFp)y))
#define FPM_FpDivQ28(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 28))/(TFp)y))
#define FPM_FpDivQ29(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 29))/(TFp)y))
#define FPM_FpDivQ30(x,y)  ((TFp)(((TFp)x * (TFp)(1UL  << 30))/(TFp)y))

/******************************************************************************
 * FIXED POINT ABS MACRO ******************************************************
 ******************************************************************************/
#define FPM_FpAbs(x)		((((TFp)x) >= 0) ? ((TFp)x) : ((TFp)(-x)))

/*****************************************************************************************************************
 * GLOBAL FUNCTIONS **********************************************************************************************
 *****************************************************************************************************************/

/**
 * \brief Clarke transformation
 * */
void FPM_vClarkeTrans(TThreePhase* ptInput, TCartNum* ptOutput);

/**
 * \brief Conversion from cartesian to polar coordinates
 * */
void FPM_vCart2Pol(TCartNum* tCN, TPolNum* tPN);

/**
    \brief Integer square root implementation

    Function calculates the integer square root of the passed parameter.

    \param ulRadicand Radicand for which the sqrt is computed

    \return uint32_t Square root of the passed parameter

    \remark The result would also fit in an uint16 type but the native type
            of the target processor is 32bit wide => this prevents a value
            extension with 0

    \remark RUNTIME: ~4-5us

    \remark Source: Math Toolkit for Real-Time Programming (Jack W. Crenshaw)
*/
uint32_t FPM_ulSqrt(uint32_t ulRadicand);

/**
 *	\brief	2D interpolation
 *
 * 			Function implements an interpolation in a two dimensional coordinate system.
 *
 * 	\param	tXValue		X-coordinate
 * 	\param 	ptLUT		Pointer to the look-up-table
 * 	\param 	ulLUTSize	Size of the look-up-table
 *
 *	\return TFp	Interpolated y-value
 *
 *	\note	The function also works if input values that are out of the defined value range.
 *			In this case the function extrapolates the y-value with the border parameters
 *			of the LUT.
 * */
TFp FPM_tInterpolate2D(TFp tXValue, TPoint* ptLUT, uint32_t ulLUTSize);

/**
 * 	\brief 	3D interpolation
 *
 * 			Function implements an interpolation in a three dimensional coordinate system.\n
 * 			How to use this function:\n
 * 			The user has to define:\n
 * 			\li Two vectors with x and y coordinates. These define the grid
 * 			\li A two dimensional array with z-values, i.e. there must be one entry for each
 * 				coordinate combination of x and y. E.g. if the x vector has a size of 4 elements
 * 				and the y-vector a size of 7 elements the array is of type array[7][4].
 * 			\li The data grid is combined in a structure of type "TLookUpTable3D" which is
 * 				passed to the function.
 *
 * 	\param	ptInputVal	Pointer to the input value (x,y)-coordinates
 * 	\param	ptLUT		Pointer to the look-up-table object
 *
 * 	\return TFp	Interpolated z-value
 *
 * 	\note	The function also works if input values that are out of the defined value range.
 * 			In this case the function extrapolates the z-value.
 * 	\note	ENSURE, that the lookup table has at least two entries and that the size is
 * 			transfered correctly in any case !
 * */
TFp FPM_tInterpolate3D(TPoint* ptInputVal, TLookUpTable3D* ptLUT);

/*****************************************************************************************************************
 * GLOBAL TRIGONOMETRIC FUNCTIONS ********************************************************************************
 *****************************************************************************************************************/

/**
    \brief Decalration of the sine look up table (LUT)
*/
extern const TFp FPM_tSineTabQ15[];

/**
    \brief Size of the sine LUT (no. of elements)
*/
#define FPM_SINE_TAB_SIZE           (sizeof(FPM_tSineTabQ15)/sizeof(TFp))

/**
    \brief No. of bits used for the angle argument within the sine tab
*/
#define FPM_SINE_TAB_ANGLE_BITS     (8)

/**
    \brief Mapping of the implemented sine table
*/
#define FPM_tSineTab                FPM_tSineTabQ15

/**
    \brief Sin function (Q15-Format)

    The macro reads the mapped sine table according to the passed angle argument.
    The angle is a 16Bit value which is mapped on a 8Bit table index.
*/
#define FPM_tSin(Phi)        (FPM_tSineTab[(uint16_t)Phi >> (16-FPM_SINE_TAB_ANGLE_BITS)])

/**
    \brief Cos function (Q15-Format)

    The macro reads the mapped sine table according to the passed angle argument.
    The angle is a 16Bit value which is mapped on a 8Bit table index.
*/
#define FPM_tCos(Phi)       (FPM_tSineTab[(((uint32_t)Phi + (uint32_t)FPM_PI_HALF) & 0x0000FFFF) >> (16-FPM_SINE_TAB_ANGLE_BITS)])

#ifdef __cplusplus
}
#endif

#endif		/* __FPM_H */
