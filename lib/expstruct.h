/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
 */
/*
 * Modified by Wagner Morais on Aug 2022.
 */
 
#ifndef _EXPSTRUCT_H
#define _EXPSTRUCT_H

struct expStruct {
	int expInt;
	int expFraction;
};

typedef struct expStruct ExpStruct;

/**@brief 
 *      Approximate the value of e^x using Taylor series expansion
 * @param 
 *      1. x such that 0<=x<=20
 * 
 * @pre-condition 
 *      1. x should be integer such tht 0<=x<=20
 * 
 * @post-condition 
 *      1. Should return a pointer of struct expStruct (not Null)
 *      2. expInt stores the integer part of the result 
 *      3. expFraction stores the integer part of the result 
 *      4. Fraction part should be two digits after the decimal point
 *    
 * @properties 
 *      1. Taylor series expansion of e^x:
 *          e^x = 1 + x + (x^2)/(2!) + (x^3)/(3!) + (x^4)/(4!) + .....
 *          generalizing, 
 *          e^x = Σ (x^n / n!) such that 0<=n<=100, to prevent excessive computation
 *      2. Accuracy upto two decimal places (≈0.01)
 *      3. expInt = (int)floor(result of e^x)
 *      4. expFraction = (int)((result - expInt)*100)
 * 
 * @test-cases:
 *    1. If x = 0, iexp(0) → {expInt=1, expFraction=0}.
 *    2. If x = 1, iexp(1) → {expInt=2, expFraction=72}.
 *    3. If x = 5, iexp(5) → {expInt=148, expFraction=41}.
 *    4. If x = 10, iexp(10) → {expInt=22026, expFraction=47}.
 *    5. If x = 20, iexp(20) → {expInt=485165195, expFraction=9}.
 * 
*/

ExpStruct *iexp (int);

#endif