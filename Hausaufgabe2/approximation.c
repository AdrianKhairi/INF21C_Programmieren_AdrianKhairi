#include <stdio.h>
#include "newton_raphson_method_library.h"

int main(){

    //x0 will later be the x this code works with
    double x0;
    //selectedDerivation will later be the type selecter of Derivation
    double selectedDerivation; 

    printf("Which x shall the Newton-Raphson Method start with: "); 
    //saving input in x0
    scanf("%lf", &x0);

    //input- and error handling
    do{ 
        printf("Which type of derivation should be selected: analytic derivation (1) or numeric derivation (2): ");
        scanf("%lf", &selectedDerivation);
        //jumps out of while loop if input is valid
        if(selectedDerivation == 1 || selectedDerivation == 2){
            break;
        }
        //print error message
        else {
            printf("ERROR: Please select between analytic derivation (1) and numeric derivation(2) \n");
        }
    }
    //continues to loop through "do" while input is invalid
    while(selectedDerivation != 1 && selectedDerivation != 2);

    //continue with Newton-Raphson-Method
    newton_raphson_method(x0, selectedDerivation);

    return 0;
}