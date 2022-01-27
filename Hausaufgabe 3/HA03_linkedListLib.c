#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HA03_linkedListLib.h"

void addListElem(listElement *start)
{

    listElement *new;
    new = (listElement *)malloc(sizeof(listElement));
    if (new == NULL)
    {
        printf("can't reserve storage.\n");
        return;
    }

    listElement *currElem = start;
    while (currElem->nextElem != NULL)
        currElem = currElem->nextElem; // get last elem in list
    currElem->nextElem = new;          // add new to the end of list
    new->nextElem = NULL;

    /* fill data in new element */
    printf("Please enter last name: \n");
    scanf("%s", new->lastName);
    printf("Please enter first name: \n");
    scanf("%s", new->firstName);
    printf("Please enter age: \n");
    scanf("%d", &(new->age));
    printf("end of function\n");
}

void printList(listElement *start)
{

    if (start->nextElem == NULL)
        printf("List is empty.\n");
    else
    {
        int i = 0;
        listElement *currElem = start;
        printf("\ncurrent list:\n\n");
        do
        {
            currElem = currElem->nextElem;
            printf("%d", i);
            i++;
            printf("\t last name: %s\n", currElem->lastName);
            printf("\t first name: %s\n", currElem->firstName);
            printf("\t age: %d\n", currElem->age);
        } while (currElem->nextElem != NULL);
    }
    printf("\n");
}

void delListElem(listElement *start)
{
    int counter = 0;
    int indexOfDeletingElement;
    listElement *temporaryNr1, *temporaryNr2 = start;
    
    //Errorhandling: Checking whether list is empty
    if(start->nextElem == NULL){
        printf("ERROR: There is no element in the list\n\n");
        return;
    }

    printList(start);
    printf("Enter index of element you want to delete [indices start at 0]: \n");
    scanf("%d", &indexOfDeletingElement);
    system("cls");   
    printList(start);

    //Errorhandling for invalid indices of listelements
    if(indexOfDeletingElement>getLenOfList(start)-1 || indexOfDeletingElement<0){
        do
        {
            printf("ERROR: There is no element with the given index\nEnter index of element you want to delete [indices start at 0]: \n");
            scanf("%d", &indexOfDeletingElement);
            system("cls");
            printList(start);
        } while (indexOfDeletingElement>getLenOfList(start)-1 || indexOfDeletingElement<0);
    }

    //iterating to element that is infront of indexOfDeletingElement
    while (counter < indexOfDeletingElement)
    {
        temporaryNr1 = temporaryNr2->nextElem;
        temporaryNr2 = temporaryNr1;
        counter++;
    }
    
    free(temporaryNr2->nextElem);
    temporaryNr1 = temporaryNr2->nextElem->nextElem;
    temporaryNr2->nextElem = temporaryNr1;
    system("cls");
    printf("\nthe element with the index %d has been deleted\n\n", indexOfDeletingElement);
}

void delList(listElement *start)
{
    listElement *temporaryNr1 = start->nextElem, *temporaryNr2;

    //Errorhandling: Checking whether list is empty
    if(start->nextElem == NULL){
        printf("ERROR: There is no element in the list\n\n");
        return;
    }

    //iterating through list while deleting every element
    if(temporaryNr1->nextElem != NULL){
        do
        {
            temporaryNr2 = temporaryNr1->nextElem;
            temporaryNr1->nextElem = temporaryNr2->nextElem;
            free(temporaryNr2);
        } while (temporaryNr1->nextElem != NULL);        
    }
    free(temporaryNr1);
    start->nextElem = NULL;
    printf("Every element of the list has been deleted\n\n");
}

int getLenOfList(listElement *start)
{ // we use this for save list fcn

    int counter = 0;
    listElement *currElem = start;
    while (currElem->nextElem != NULL)
    { // get last elem in list
        currElem = currElem->nextElem;
        counter++;
    }
    return counter;
}

void saveList(listElement *start)
{
    listElement *temporary = start->nextElem;
    int maxInputLength = 300;
    char userInput[maxInputLength];
    //maxInputLength+4 = userInput + ".txt"
    char *userInputWithSuffix = calloc(maxInputLength+4, sizeof(char));
    char suffix[4];
    int counter = 0;

    strcpy(suffix, ".txt");

    //Errorhandling: Checking whether list is empty
    if(start->nextElem == NULL){
        printf("ERROR: There is no element in the list\n\n");
        return;
    }

    printf("enter a name for the textfile wihtout a fileending: \n");
    scanf("%s", userInput);
    strcat(userInputWithSuffix, userInput);
    strcat(userInputWithSuffix, suffix);

    FILE *fPtr = fopen(userInputWithSuffix, "w");
    //Errorhandling: check whether file can be opened
    if(fPtr == NULL){
        printf("ERROR: Unable to open file or the filename is too long\n");
        return;
    }

    fprintf(fPtr, "%d\n", getLenOfList(start));

    //iterating through list while writing each element to file
    while (counter < getLenOfList(start))
    {
        fprintf(fPtr, "%s\t", temporary->lastName);
        fprintf(fPtr, "%s\t", temporary->firstName);
        fprintf(fPtr, "%d\n", temporary->age);
        temporary = temporary->nextElem;
        counter++;
    }

    fclose(fPtr);
    system("cls");
    printf("\nthe list %s has been saved\n\n", userInputWithSuffix);
}

void loadList(listElement *start)
{
    char userInput[300];
    FILE *fPtr;
    int listLength;
    int counter = 0;

    char listLastName[50], listFirstName[50];
    int listAge;

    //Errorhandling: checking if there is a .txt file in directory
    if(system("dir *.txt") == 1){
        system("cls");
        printf("ERROR: Cannot find a file ending with .txt in directory\n\n");
        return;
    }

    printf("Enter a filename to load: \n");
    scanf("%s", &userInput);
    //Errorhandling: checks if file is in directory
    if((fPtr = fopen(userInput, "r"))==NULL){
        do
        {
            system("cls");
            system("dir *.txt");
            printf("ERROR: Unable to find or open given textfile\n");
            printf("Enter a filename to load: \n");
            scanf("%s", &userInput);
        } while ((fPtr = fopen(userInput, "r"))==NULL);
    }

    fscanf(fPtr, "%d", &listLength);

    while (counter < listLength)
    {
        listElement *new;
        new = malloc(sizeof(listElement));
        listElement *currElem = start;
        while (currElem->nextElem != NULL){
            currElem=currElem->nextElem;
        }
        currElem->nextElem = new;
        new->nextElem = NULL;

        fscanf(fPtr, "%s", listLastName);
        fscanf(fPtr, "%s", listFirstName);
        fscanf(fPtr, "%d\n", &listAge);
        strcpy(new->lastName, listLastName);
        strcpy(new->firstName, listFirstName);
        new->age = listAge;
        counter++;
    }
    
    fclose(fPtr);
    system("cls");
    printf("List has been loaded\n");
    printList(start);
}


void exitFcn(listElement *start)
{
    int exitUserInput;

    //Errorhandling: checks whether list is empty
    if(start->nextElem == NULL) {
        system("cls");
        printf("\nNo elements in list, saving is obsolete\n\n");
        return;
    } 

    printf("Do you want to save before exit? \n");
    printf("0... No\n1... Yes\n");
    scanf("%d", &exitUserInput);

    //Errorhandling: checking if userinput is 0 or 1
    if(exitUserInput != 0 && exitUserInput != 1){
        do
        {
            system("cls");
            printf("ERROR: Invalid input\nDo you want to save before exit? \n");
            printf("0... No\n1... Yes\n");
            scanf("%d", &exitUserInput);
        } while (exitUserInput != 0 && exitUserInput != 1);
    }

    if(exitUserInput == 0){
        return;
    } else if (exitUserInput == 1){
        saveList(start);
        return;
    } else{
        return;
    }
}

void sortList(listElement *start)
{

    printf("\n>>sortList fcn is tbd.\n\n");
}

void stringToLower(char *string)
{

    printf("\n>>stringToLower fcn is tbd.\n\n");
}
