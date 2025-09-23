/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
 */
/*
 * Modified by Wagner Morais on Aug 2022.
 */
 
#include <stddef.h>
#include <stdlib.h>
#include "expstruct.h"

ExpStruct *iexp(int x){
    // check pre-condition 
    if (x<0 || x>20){
        fprintf(stderr, "Error: Entered number should be between 0 to 20 \n");
        return NULL;
    }

    double factorialSum = 0;  
    double termValue = 1.0;  
    int interation = 0; 

    while (iteration < 100) {
        termValue *= x/n ; // termValue  = (x/n) * (x^(n-1) / ((n-1)!))
        factorialSum += termValue;

        // if new term is small enough that will not effect the result(sum) beyond two decimal place stop the iteration 
        if(termValue < 0.001){
            break;
        }

        iteration++;
    }

	ExpStruct *e = malloc(sizeof(ExpStruct));
    e->expInt = (int) floor(factorialSum);
    e->expFraction = (int)((factorialSum - expInt)*100);
    
	return e;	
}
