#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"
// I should mention that I used the test of the previous semester in C course in order to arrive at a solution

typedef struct AdptArray_
{
	int ArrSize; // represent a size of array
	PElement* pElemArr; 
	DEL_FUNC delFunc; // delete the elements of the array
	COPY_FUNC copyFunc; // copy the elements of the array
    PRINT_FUNC printFunc; // print the elements of the array  
}AdptArray;

// the purpose of this func is to initialize an empty array

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL) // if the allocation fails return NULL else the allocated structure is initialized with default values
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
    pArr->printFunc = printFunc_;
	return pArr; // a pointer to the initialized AdptArray structure is returned
}

// the main goal of this func is to free the memory that was allocated for the array and its elements

void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
		if ((pArr->pElemArr)[i]!=NULL)
		{
		pArr->delFunc((pArr->pElemArr)[i]); // delfunc responsible for free the memory of each elemant 
	    }
	}
	free(pArr->pElemArr); // the func frees the memory for the array of pointers by calling the free func
	free(pArr); 
}

// this func updates the element at a given index of an adaptive array-pArr with a new element-pNewElem

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement* newpElemArr; // a pointer to the new element that will replace the old element at the given index
	if (pArr == NULL)
		return FAIL;

	if (idx >= pArr->ArrSize)
	{
		
// Extend Array
		if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL) 
			return FAIL;
			//extends the array by allocating a new block of memory using calloc 
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement)); //copying the old elements to the new array using memcpy
		free(pArr->pElemArr); //old array is then free
		pArr->pElemArr = newpElemArr; // new array is set as the pElemArr pointer of the AdptArray
	}

	// Delete Previous Elem
	if ((pArr->pElemArr)[idx]!=NULL)
    {
       	pArr->delFunc((pArr->pElemArr)[idx]);

    }
    // deletes the old element at the given index using the delFunc
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem); // creates a copy of the new element using the copyFunc func pointer of the AdptArray

	// Update Array Size
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;  // the new size of the array
	return SUCCESS;
}

// this func takes an index as an input and returns a copy to this element 
 
PElement GetAdptArrayAt(PAdptArray pArr, int i){
    if (pArr == NULL || i < 0 || i >= pArr->ArrSize || pArr->pElemArr[i] == NULL) // if one of these conditions are met the func return NULL
    {
        return NULL;
    }
    return pArr->copyFunc((pArr->pElemArr)[i]); // else the func calls the copyFunc func passes through the elements and return the result
}

// the goal of thie func is to retrieve the size of an array

int GetAdptArraySize(PAdptArray pArr) {
	return (pArr != NULL) ? pArr->ArrSize : -1; // if the input parameter is valid it will return the ArrSize member else it will return minus 1

}

// the goal of this func is to print the elements in the array

void PrintDB(PAdptArray pArr) {
    int i;
    if (pArr == NULL || pArr->pElemArr == NULL) // if either of them is NULL, it means there is nothing to print
        return;
    for (i = 0; i < pArr->ArrSize; ++i)
	{
	    PElement elem = pArr->pElemArr[i];
        if (elem != NULL) 
		{
            pArr->printFunc(elem); // printFunc responsible for printing the elements  
        }
	}
}