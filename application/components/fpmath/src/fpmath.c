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
 * Fixed point math implementation
*/
/*****************************************************************************************************************
 * INCLUDES 
 *****************************************************************************************************************/

#include "fpmath.h"     /* Include own header */

/*****************************************************************************************************************
 * LOCAL DEFINITIONS *********************************************************************************************
 *****************************************************************************************************************/
#define FPM_CORDIC_ITERATIONS      (14)      /**< Number of CORDIC iterations 	*/
#define	COUNT_16				   (16)		 /**< Counter 16 					*/

/**
  \brief Definition of the CORDIC scale factor
 
  The scaling factor is equal to 0.607253
*/
#define FPM_CORDIC_SCALE_FACTOR_Q16        (Q16(0.607253))

/*****************************************************************************************************************
 * LOCAL CONSTANTS ***********************************************************************************************
 *****************************************************************************************************************/

/**
  \brief Definition of the CORDIC angle table
 
  These angles define the angle iteration step sizes of the CORDIC algorithm.
*/
static const TAngle FPM_tCordicAngleTabQ15 [] = {
     8192,
     4836,
     2555,
     1297,
     651,
     326,
     163,
     81,
     41,
     20,
     10,
     5,
     3,
     1,
     1,
     0
};

/**
 * 	\brief	Sine function look-up-table
 *
 * 			The table consists of 256 entries in q15-fixed point format.
 * */
const TFp FPM_tSineTabQ15[] = {
      Q15(0.0000000000),
      Q15(0.0245412285),
      Q15(0.0490676743),
      Q15(0.0735645636),
      Q15(0.0980171403),
      Q15(0.1224106752),
      Q15(0.1467304745),
      Q15(0.1709618888),
      Q15(0.1950903220),
      Q15(0.2191012402),
      Q15(0.2429801799),
      Q15(0.2667127575),
      Q15(0.2902846773),
      Q15(0.3136817404),
      Q15(0.3368898534),
      Q15(0.3598950365),
      Q15(0.3826834324),
      Q15(0.4052413140),
      Q15(0.4275550934),
      Q15(0.4496113297),
      Q15(0.4713967368),
      Q15(0.4928981922),
      Q15(0.5141027442),
      Q15(0.5349976199),
      Q15(0.5555702330),
      Q15(0.5758081914),
      Q15(0.5956993045),
      Q15(0.6152315906),
      Q15(0.6343932842),
      Q15(0.6531728430),
      Q15(0.6715589548),
      Q15(0.6895405447),
      Q15(0.7071067812),
      Q15(0.7242470830),
      Q15(0.7409511254),
      Q15(0.7572088465),
      Q15(0.7730104534),
      Q15(0.7883464276),
      Q15(0.8032075315),
      Q15(0.8175848132),
      Q15(0.8314696123),
      Q15(0.8448535652),
      Q15(0.8577286100),
      Q15(0.8700869911),
      Q15(0.8819212643),
      Q15(0.8932243012),
      Q15(0.9039892931),
      Q15(0.9142097557),
      Q15(0.9238795325),
      Q15(0.9329927988),
      Q15(0.9415440652),
      Q15(0.9495281806),
      Q15(0.9569403357),
      Q15(0.9637760658),
      Q15(0.9700312532),
      Q15(0.9757021300),
      Q15(0.9807852804),
      Q15(0.9852776424),
      Q15(0.9891765100),
      Q15(0.9924795346),
      Q15(0.9951847267),
      Q15(0.9972904567),
      Q15(0.9987954562),
      Q15(0.9996988187),
      Q15(1.0000000000),
      Q15(0.9996988187),
      Q15(0.9987954562),
      Q15(0.9972904567),
      Q15(0.9951847267),
      Q15(0.9924795346),
      Q15(0.9891765100),
      Q15(0.9852776424),
      Q15(0.9807852804),
      Q15(0.9757021300),
      Q15(0.9700312532),
      Q15(0.9637760658),
      Q15(0.9569403357),
      Q15(0.9495281806),
      Q15(0.9415440652),
      Q15(0.9329927988),
      Q15(0.9238795325),
      Q15(0.9142097557),
      Q15(0.9039892931),
      Q15(0.8932243012),
      Q15(0.8819212643),
      Q15(0.8700869911),
      Q15(0.8577286100),
      Q15(0.8448535652),
      Q15(0.8314696123),
      Q15(0.8175848132),
      Q15(0.8032075315),
      Q15(0.7883464276),
      Q15(0.7730104534),
      Q15(0.7572088465),
      Q15(0.7409511254),
      Q15(0.7242470830),
      Q15(0.7071067812),
      Q15(0.6895405447),
      Q15(0.6715589548),
      Q15(0.6531728430),
      Q15(0.6343932842),
      Q15(0.6152315906),
      Q15(0.5956993045),
      Q15(0.5758081914),
      Q15(0.5555702330),
      Q15(0.5349976199),
      Q15(0.5141027442),
      Q15(0.4928981922),
      Q15(0.4713967368),
      Q15(0.4496113297),
      Q15(0.4275550934),
      Q15(0.4052413140),
      Q15(0.3826834324),
      Q15(0.3598950365),
      Q15(0.3368898534),
      Q15(0.3136817404),
      Q15(0.2902846773),
      Q15(0.2667127575),
      Q15(0.2429801799),
      Q15(0.2191012402),
      Q15(0.1950903220),
      Q15(0.1709618888),
      Q15(0.1467304745),
      Q15(0.1224106752),
      Q15(0.0980171403),
      Q15(0.0735645636),
      Q15(0.0490676743),
      Q15(0.0245412285),
      Q15(0.0000000000),
      Q15(-0.0245412285),
      Q15(-0.0490676743),
      Q15(-0.0735645636),
      Q15(-0.0980171403),
      Q15(-0.1224106752),
      Q15(-0.1467304745),
      Q15(-0.1709618888),
      Q15(-0.1950903220),
      Q15(-0.2191012402),
      Q15(-0.2429801799),
      Q15(-0.2667127575),
      Q15(-0.2902846773),
      Q15(-0.3136817404),
      Q15(-0.3368898534),
      Q15(-0.3598950365),
      Q15(-0.3826834324),
      Q15(-0.4052413140),
      Q15(-0.4275550934),
      Q15(-0.4496113297),
      Q15(-0.4713967368),
      Q15(-0.4928981922),
      Q15(-0.5141027442),
      Q15(-0.5349976199),
      Q15(-0.5555702330),
      Q15(-0.5758081914),
      Q15(-0.5956993045),
      Q15(-0.6152315906),
      Q15(-0.6343932842),
      Q15(-0.6531728430),
      Q15(-0.6715589548),
      Q15(-0.6895405447),
      Q15(-0.7071067812),
      Q15(-0.7242470830),
      Q15(-0.7409511254),
      Q15(-0.7572088465),
      Q15(-0.7730104534),
      Q15(-0.7883464276),
      Q15(-0.8032075315),
      Q15(-0.8175848132),
      Q15(-0.8314696123),
      Q15(-0.8448535652),
      Q15(-0.8577286100),
      Q15(-0.8700869911),
      Q15(-0.8819212643),
      Q15(-0.8932243012),
      Q15(-0.9039892931),
      Q15(-0.9142097557),
      Q15(-0.9238795325),
      Q15(-0.9329927988),
      Q15(-0.9415440652),
      Q15(-0.9495281806),
      Q15(-0.9569403357),
      Q15(-0.9637760658),
      Q15(-0.9700312532),
      Q15(-0.9757021300),
      Q15(-0.9807852804),
      Q15(-0.9852776424),
      Q15(-0.9891765100),
      Q15(-0.9924795346),
      Q15(-0.9951847267),
      Q15(-0.9972904567),
      Q15(-0.9987954562),
      Q15(-0.9996988187),
      Q15(-1.0000000000),
      Q15(-0.9996988187),
      Q15(-0.9987954562),
      Q15(-0.9972904567),
      Q15(-0.9951847267),
      Q15(-0.9924795346),
      Q15(-0.9891765100),
      Q15(-0.9852776424),
      Q15(-0.9807852804),
      Q15(-0.9757021300),
      Q15(-0.9700312532),
      Q15(-0.9637760658),
      Q15(-0.9569403357),
      Q15(-0.9495281806),
      Q15(-0.9415440652),
      Q15(-0.9329927988),
      Q15(-0.9238795325),
      Q15(-0.9142097557),
      Q15(-0.9039892931),
      Q15(-0.8932243012),
      Q15(-0.8819212643),
      Q15(-0.8700869911),
      Q15(-0.8577286100),
      Q15(-0.8448535652),
      Q15(-0.8314696123),
      Q15(-0.8175848132),
      Q15(-0.8032075315),
      Q15(-0.7883464276),
      Q15(-0.7730104534),
      Q15(-0.7572088465),
      Q15(-0.7409511254),
      Q15(-0.7242470830),
      Q15(-0.7071067812),
      Q15(-0.6895405447),
      Q15(-0.6715589548),
      Q15(-0.6531728430),
      Q15(-0.6343932842),
      Q15(-0.6152315906),
      Q15(-0.5956993045),
      Q15(-0.5758081914),
      Q15(-0.5555702330),
      Q15(-0.5349976199),
      Q15(-0.5141027442),
      Q15(-0.4928981922),
      Q15(-0.4713967368),
      Q15(-0.4496113297),
      Q15(-0.4275550934),
      Q15(-0.4052413140),
      Q15(-0.3826834324),
      Q15(-0.3598950365),
      Q15(-0.3368898534),
      Q15(-0.3136817404),
      Q15(-0.2902846773),
      Q15(-0.2667127575),
      Q15(-0.2429801799),
      Q15(-0.2191012402),
      Q15(-0.1950903220),
      Q15(-0.1709618888),
      Q15(-0.1467304745),
      Q15(-0.1224106752),
      Q15(-0.0980171403),
      Q15(-0.0735645636),
      Q15(-0.0490676743),
      Q15(-0.0245412285)
};

/*****************************************************************************************************************
 * GLOBAL FUNCTIONS **********************************************************************************************
 *****************************************************************************************************************/

/******************************************************************************
 * void FPM_vCart2Pol(TCartNum* tCN, TPolNum* tPN)
 ******************************************************************************/
void FPM_vCart2Pol(TCartNum* tCN, TPolNum* tPN)
{
   int32_t  slIdx;
   TCartNum tCartNum;
   TCartNum tCartNum_;
   TAngle   tAngOffset;
   if (tCN->tRe < 0)
   {
      /* Quadrant II or III */
      if (tCN->tIm < 0)
      {
         /* Quadrant III */
         tCartNum.tRe = -tCN->tIm;
         tCartNum.tIm = tCN->tRe;
         tAngOffset   = -(TAngle)FPM_PI_HALF;
      }
      else
      {
         /* Quadrant II */
         tCartNum.tRe = tCN->tIm;
         tCartNum.tIm = -tCN->tRe;
         tAngOffset   = (TAngle)FPM_PI_HALF;
      }
   }
   else
   {
      /* Quadrant I or IV*/
      tCartNum   = *tCN;
      tAngOffset = (TAngle)0;
   }
   tPN->siAngle = 0;
   for (slIdx = 0; slIdx < FPM_CORDIC_ITERATIONS; slIdx++)
   {
      if (tCartNum.tIm < 0)
      {
         /* Imaginary part is negative => rotate counter clock wise */
         tCartNum_.tRe = tCartNum.tRe - (tCartNum.tIm >> slIdx);
         tCartNum_.tIm = tCartNum.tIm + (tCartNum.tRe >> slIdx);

         /* Accumulate angle */
         tPN->siAngle -= FPM_tCordicAngleTabQ15[slIdx];
      }
      else
      {
         /* Imaginary part is positive => rotate clock wise */
         tCartNum_.tRe = tCartNum.tRe + (tCartNum.tIm >> slIdx);
         tCartNum_.tIm = tCartNum.tIm - (tCartNum.tRe >> slIdx);

         /* Accumulate angle */
         tPN->siAngle += FPM_tCordicAngleTabQ15[slIdx];
      }
      /* Prepare next iteration */
      tCartNum = tCartNum_;
   }
   tPN->tMag     = (FPM_CORDIC_SCALE_FACTOR_Q16 * tCartNum.tRe) >> 16;
   tPN->siAngle += tAngOffset;
}

/******************************************************************************
 * void FPM_vClarkeTrans(TThreePhase* ptInput, TCartNum* ptOutput)
 ******************************************************************************/
void FPM_vClarkeTrans(TThreePhase* ptInput, TCartNum* ptOutput)
{
   TFp tTemp;

   /* Real part */
   ptOutput->tRe = ptInput->a;

   /* Imaginary part -> Imag = 1/sqrt(3)*(A + 2 * B) */
   tTemp  = ptInput->b * 2;
   tTemp += ptInput->a;
   tTemp  = FPM_FpMulQ15(tTemp,FPM_SQRT3_INV_Q15);

   ptOutput->tIm = tTemp;
}

/******************************************************************************
 * uint32_t FPM_ulSqrt(uint32_t ulRadicand)
 ******************************************************************************/
uint32_t FPM_ulSqrt(uint32_t ulRadicand)
{
   uint32_t ulRem  = 0;
   uint32_t ulRoot = 0;
   int32_t  slIdx;
   for (slIdx = 0; slIdx < COUNT_16; slIdx++)
   {
      ulRoot     <<= 1;
      ulRem        = ((ulRem << 2) + (ulRadicand >> 30));
      ulRadicand <<= 2;
      ulRoot++;
      if (ulRoot <= ulRem)
      {
         ulRem -= ulRoot;
         ulRoot++;
      }
      else
      {
         ulRoot--;
      }
   }
   return (ulRoot >> 1);
}

/******************************************************************************
 * TFp FPM_tInterpolate2D(TFp tXValue, TPoint* ptLUT, uint32_t ulLUTSize)
 ******************************************************************************/
TFp FPM_tInterpolate2D(TFp tXValue, TPoint* ptLUT, uint32_t ulLUTSize) {
	TFp			tResult;
	uint32_t	ulIdx;

	/* Search the matching index in the LUT */
	for (ulIdx = 1; ulIdx < (ulLUTSize-1); ulIdx++) {
		if(tXValue <= ptLUT[ulIdx].tXValue) {
			/*
			 * Matching index has been found
			 * => stop searching and continue interpolation
			 * => the xValue lies between the indexes (ulIdx-1) and ulIdx
			 * */
			break;
		}
	}

	/*
	 * Interpolate between two points in the LUT
	 * Yinterpol = dx * DeltaY/DeltaX + Y0
	 *  */
	tResult = tXValue;

	tResult -= ptLUT[ulIdx-1].tXValue;

	tResult *= (ptLUT[ulIdx].tYValue - ptLUT[ulIdx-1].tYValue);

	if(tResult >= (TFp)0) {
		tResult += (ptLUT[ulIdx].tXValue - ptLUT[ulIdx-1].tXValue)/2;	/* Round */
	} else {
		tResult -= (ptLUT[ulIdx].tXValue - ptLUT[ulIdx-1].tXValue)/2;	/* Round */
	}

	tResult /= (ptLUT[ulIdx].tXValue - ptLUT[ulIdx-1].tXValue);

	tResult += ptLUT[ulIdx-1].tYValue;

	return tResult;
}

/******************************************************************************
 *	TFp FPM_tInterpolate3D(TPoint* ptInputVal, TLookUpTable3D* ptLUT)
 ******************************************************************************/
TFp FPM_tInterpolate3D(TPoint* ptInputVal, TLookUpTable3D* ptLUT) {
	TFp		tResult;
	TFp* ptX1;
	TFp* ptX2;
	TFp* ptY1;
	TFp* ptY2;
	TFp* ptZX1Y1;
	TFp* ptZX2Y1;
	TFp* ptZX1Y2;
	TFp* ptZX2Y2;
	TFp tZ1;
	TFp tZ2;

	/*
	 * 	Search the x-range in the grid where the x-input-value lies in
	 * */
	ptX1 = ptLUT->ptXValues;
	ptX2 = ptLUT->ptXValues+1;
	ptZX2Y2 = ptLUT->ptZValues+1+ptLUT->ulXSize;
	do {
		if((ptX2 >= (ptLUT->ptXValues + ptLUT->ulXSize - 1)) || (ptInputVal->tXValue <= *ptX2)) {
			ptX1 = ptX2-1;
			break;
		}
		ptX2++;
		ptZX2Y2++;
	}while(1);

	/*
	 * 	Search the x-range in the grid where the x-input-value lies in
	 * */
	ptY1 = ptLUT->ptYValues;
	ptY2 = ptLUT->ptYValues+1;
	do {
		if((ptY2 >= (ptLUT->ptYValues + ptLUT->ulYSize - 1)) || (ptInputVal->tYValue <= *ptY2)) {
			ptY1 = ptY2-1;
			break;
		}
		ptY2++;
		ptZX2Y2 += ptLUT->ulXSize;
	}while(1);

	ptZX1Y2 = ptZX2Y2 - 1;
	ptZX2Y1 = ptZX2Y2 - ptLUT->ulXSize;
	ptZX1Y1 = ptZX2Y1 - 1;

	/*
	 * 	Note:
	 * 	We now have pointers that define the upper and lower borders in the grid
	 * 	where the input value is located. Between these borders we can now interpolate.
	 * 	If the found values are outside of the defined grid, the pointers are set in
	 * 	a way that the function automatically extrapolates.
	 *
	 * 	The interpolation works in two steps:
	 * 	1st we interpolate z in x-direction on the two y-curves.
	 * 	2nd we interpolate z in y-direction
	 *
	 * 	=> 1st Interpolate z in x-direction
	 * 	1. z1 on curve y1
	 * 	2. z2 on curve y2
	 * */
	tZ1	= ptInputVal->tXValue - *ptX1;

	tZ1 *= (*ptZX2Y1 - *ptZX1Y1);

	/* Round */
	if(tZ1 >= (TFp)0) {
		tZ1 += (*ptX2 - *ptX1)/2;
	} else {
		tZ1 -= (*ptX2 - *ptX1)/2;
	}

	tZ1 /= (*ptX2 - *ptX1);

	tZ1 += *ptZX1Y1;

	tZ2	= ptInputVal->tXValue - *ptX1;

	tZ2 *= (*ptZX2Y2 - *ptZX1Y2);

	/* Round */
	if(tZ2 >= (TFp)0) {
		tZ2 += (*ptX2 - *ptX1)/2;
	} else {
		tZ2 -= (*ptX2 - *ptX1)/2;
	}

	tZ2 /= (*ptX2 - *ptX1);

	tZ2 += *ptZX1Y2;

	/*
	 * 	Interpolate z in y-direction
	 * */
	tResult = ptInputVal->tYValue - *ptY1;

	tResult *= (tZ2 - tZ1);

	/* Round */
	if(tResult >= (TFp)0) {
		tResult += (*ptY2 - *ptY1)/2;
	} else {
		tResult -= (*ptY2 - *ptY1)/2;
	}

	tResult /= (*ptY2 - *ptY1);

	tResult += tZ1;

	return tResult;
}
