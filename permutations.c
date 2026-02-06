#include "main.h"

void permute(int size, int array[], int printing_size) {     //printing_size is actual number of elements in the array, size is just there to count down each recursion
    int temp;

    if(size == 1) {     //when we have finished making one permutation, do this
        check_optimal_route(array, printing_size);
        return;
    }

    for(int i = 0; i < size; i++){
        permute(size - 1, array, printing_size);

        if(size % 2 == 0) {     //even
            temp = array [i];
            array[i] = array[size - 1];
            array[size - 1] = temp;
        }

        if(size % 2 == 1) {     //odd
            temp = array[0];
            array[0] = array[size - 1];
            array[size - 1] = temp;
        }
    }
    return;
}
