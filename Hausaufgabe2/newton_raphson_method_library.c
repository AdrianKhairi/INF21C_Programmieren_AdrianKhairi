#include <stdio.h>
#include <math.h>
#include "function_library.h"

//is needed to temporarily store xn+1
double followingX;
//is needed for selecting derivation type
double selectedDerivation;
//represents maximum iteration steps
int iterations = 1000;

void newton_raphson_method(double x0, double derivativeType){
    //loop is responsible for iterations; maximum iteration steps is determined by "iterations"
    for(int currentIterationsStep = 0; currentIterationsStep < iterations; currentIterationsStep++){

        //switch case: select between analytic derivation and numeric derivation
        switch ((int)derivativeType){
            case 1: selectedDerivation = analyticDerivationOfBaseFunction(x0); break;
            case 2: selectedDerivation = numericDerivationOfBaseFunction(x0); break;
        }

        //termination conditions: absolute value of f(x0)<10^-10 OR difference between iteration steps is smaller than 10^-10
        if((evaluateBaseFunction(x0)<pow(10,-10) && evaluateBaseFunction(x0)>-pow(10,-10)) ||
        ((x0-(evaluateBaseFunction(x0)/selectedDerivation)-x0)<pow(10,-10) && (x0-(evaluateBaseFunction(x0)/selectedDerivation)-x0)>-pow(10,-10))){
            //output of approximated zero and needed iterations
            printf("Number of iterations:\t%d\n", currentIterationsStep);
            printf("Approximated zero:\t%.10lf\n", x0);
            break;
        }
        //error message when given "iterations" are not enough to trigger one termination condition
        if(currentIterationsStep == iterations-1){
            printf("ERROR: %d iteration(s) were not enough to approximate zero\n", iterations);
        }
        //"followingX" saves xn+1
        followingX = (x0-(evaluateBaseFunction(x0)/selectedDerivation));
        //saving xn+1 as xn for following iteration
        x0 = followingX;

    }
}