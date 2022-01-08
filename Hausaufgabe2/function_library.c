#include <math.h>

//returns the value of the given x of the function that shall be searched for nearest zero
double evaluateBaseFunction(double x){
    return (pow((x-3),2));
}

//returns value of analytic derivation of given x
double analyticDerivationOfBaseFunction(double x){
    return (2*(x-3));
}

//returns value of numeric derivation of given x
double numericDerivationOfBaseFunction(double x){
    return ((evaluateBaseFunction(x+pow(10,-8))-evaluateBaseFunction(x))/pow(10,-8));
}