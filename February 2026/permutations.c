#include <stdlib.h>
#include "geometry_functions.h"
#include "variables.h"

void permute(int size_array, int permutation_index) {  //permutation_index can be thought of as an "offset" since absolute zero ie. the first of x! permutations
    int *array = malloc((sizeof(int) * size_array)); //allocate size_array * int_size bytes to our array
    int *factoradic_notation = malloc(sizeof(int) * size_array);

    //fill in our array from 1 up until size_array
    for(int i = 0; i < size_array; i++) {
        array[i] = i + 1;
    }

    //from permutation index to factoradic notation through successive division
    int dividend = permutation_index;
    for(int i = 1; i <= size_array; i++) {
        factoradic_notation[size_array-i] = dividend % i;
        dividend = dividend / i;
    }

    //turn factoradic into permutation
    for(int i = 0; i < size_array; i++) {
        temporary_route[i] = array[factoradic_notation[i]];

        //delete elements once used (we'e permutating so each only gets used once)
        for(int j = factoradic_notation[i]; j < size_array - i - 1; j++) {
            array[j] = array[j + 1];
        }
    }

    //what follows now is executed once our permutation is generated
    check_optimal_route(size_array);

    free(array);                //clean up the mess we made in the heap
    free(factoradic_notation);
    return;
}
