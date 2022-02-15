#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HA04_EulerLib.h"

#define NUMOFSTATES 2

void RHS_MSD(double*rhs, double*y){ // mass spring damper

    //those are the values for the demanded behaviour in exercise 2, which can be changed
    double m = 1.0; // mass of object
    double c = 2.0; // feder constant
    double d = 3.0; // damper constant

    double x = y[0]; // position
    double v = y[1]; // speed

    /*calc derivatives and store in rhs*/

    rhs[0] = v;
    rhs[1] = -((d*v/m)+(c*x/m));
}

void eulerSettings_MSD(simHandle* handle){
    int size;

    /*num of states*/
    handle->numOfStates = (int)NUMOFSTATES;
    
    /*right hand site*/
    handle->f = &RHS_MSD;
    
    /*reserve storage for init state vec*/
    handle->stateVecInit = malloc(sizeof(double) * (handle->numOfStates));

    /*get user defined Simtime*/
    do
    {
        printf("Simtime (in s): \n");
        scanf("%lf", &(handle->simTime));
        if(handle->simTime>0){
            break;
        }
        printf("ERROR: invalid input for simtime, simtime must not be negative or zero\n");
    } while (handle->simTime<=0);
    

    /*get user defined StepSize*/
    do
    {
        printf("StepSize (in s): \n");
        scanf("%lf", &(handle->stepSize));
        if (handle->stepSize>0)
        {
            break;
        }
        printf("ERROR: invalid input for stepsize, stepsize must not be negative or zero\n");
    } while (handle->stepSize<=0);
    

    /*get init state position*/
    printf("position(t = 0): \n");
    scanf("%lf", &(handle->stateVecInit[0]));

    /*get init state speed*/
    printf("speed(t = 0): \n");
    scanf("%lf", &(handle->stateVecInit[1]));

    /*reserve storage for states and derivatives*/
    //ceil rounds up to next integer, so that the last simulationstep also works
    size = ceil(handle->simTime/handle->stepSize);
    handle->stateVec = malloc(sizeof(double) * (handle->numOfStates) * size);
    handle->derivStateVec = malloc(sizeof(double) * (handle->numOfStates) * size);

    /*init states and derivatives with zero*/
    for(int i = 2; i < size*2; i++){
        handle->stateVec[i] = 0;
        handle->derivStateVec[i] = 0;
    }
}

void eulerForward(simHandle* handle){ // this is called only once
    int numOfStates = handle->numOfStates;
    int integratorSteps = (int)ceil(handle->simTime/handle->stepSize);
    double stepSize = handle->stepSize;
    double* derivativeTemporary;
    double* statesTemporary;

    derivativeTemporary = malloc(sizeof(double) * (handle->numOfStates));
    statesTemporary = malloc(sizeof(double) * (handle->numOfStates));

    /*write init states*/
    for(int i = 0; i < numOfStates; i++){
        handle->stateVec[i] = handle->stateVecInit[i];
    }
    for(int i = 0; i < integratorSteps; i++){
        /*get derivatives*/

        //2*i+0 equals all even numbers --> position
        //2*i+1 equals all odd numbers  --> speed
        for(int j = 0; j < numOfStates; j++){
            statesTemporary[j] = handle->stateVec[2*i+j];
        }
        handle->f(derivativeTemporary, statesTemporary);
        for(int k = 0; k < numOfStates; k++){
            handle->derivStateVec[2*i+k] = derivativeTemporary[k];
        }

        for(int j = 0; j < numOfStates; j++){
        /*euler step*/
        //+2 because start values should not be overwritten
        handle->stateVec[i*2+2+j] = handle->stateVec[i*2+j] + (stepSize * handle->derivStateVec[i*2+j]);
       }
    }
}

void showResults_MSD(simHandle* handle){
    int integratorSteps = (int)ceil(handle->simTime/handle->stepSize);
    FILE *fPtr;

    /*print data to text file*/
    fPtr = fopen("simData.txt", "w");

    //errorhandling: check if filepointer opened successfully
    if(fPtr == NULL){
        printf("ERROR: something went wrong when creating or opening the file\n");
        return;
    }
    for(int i = 0; i<integratorSteps; i++){
        fprintf(fPtr, "%lf ", i*handle->stepSize);
        fprintf(fPtr, "%lf ", handle->stateVec[i*2]);
        fprintf(fPtr, "%lf\n", handle->stateVec[i*2+1]);
    }
    fclose(fPtr);

    /*call gnuplot*/
    //provided by Mr. Wiessler in a previous lecture
    char *gnuPlotInput[] = {"set title 'Results of simulation'",

                            "set xlabel 'time in s'",

                            "plot 'simData.txt' using 1:2 title 'position',\
                            'simData.txt' using 1:3 title 'speed'"};

    FILE *gnuPlotPointer = popen("gnuplot -persistent", "w");

    //errorhandling: check if gnuPlotPipe successfully opened
    if(gnuPlotPointer == NULL) {
        printf("ERROR: there is a problem with gnuplot");
        return;
    }
    for(int i = 0; i < 3; i++){
        fprintf(gnuPlotPointer, "%s\n", gnuPlotInput[i]);
    }
    fprintf(gnuPlotPointer, "exit");
    fclose(gnuPlotPointer);
}
