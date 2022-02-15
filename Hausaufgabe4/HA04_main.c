#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "HA04_EulerLib.h"
/*******************************************************
* NAME: HA04_main.c (main) 
*
* AUTHOR: jannik wiessler
*
* DATE: 2021-01-10
*
* DESCRIPTION:  implementation of simple explicit euler method to solve first order ode system
*               mass spring damper system
*
* DEPENDENCIES: HA04_eulerLib.h
                gnuplot in PATH
*
* INFO: For DHBW use only.
*   >> Practice of explicit euler method
*
**/
int main(){

    /* define simHandle */ 
    simHandle myHandle;
    simHandle* handle = &myHandle;

    /* euler method settings */
    eulerSettings_MSD(handle);

    /* euler method call */
    eulerForward(handle);

    /* plot sim results */
    showResults_MSD(handle);

    return 0;
}