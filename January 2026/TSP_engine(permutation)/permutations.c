#include "main.h"
#include <stdlib.h>

void permute(int total_symbols, int permutation_index, int output_array[]) {
    int *array = malloc(sizeof(int) * total_symbols); //allocate total_symbols * int_size bytes to our array
    int *factoradic_notation = malloc(sizeof(int) * total_symbols);

    //fill in our array from 1 up until total_symbols
    for(int i = 0; i < total_symbols; i++) {
        array[i] = i + 1;
    }

    //from permutation index to factoradic notation through successive division
    int dividend = permutation_index;
    for(int i = 1; i <= total_symbols; i++) {
        factoradic_notation[total_symbols-i] = dividend % i;
        dividend = dividend / i;
    }

    //turn factoradic into permutation
    for(int i = 0; i < total_symbols; i++) {
        output_array[i] = array[factoradic_notation[i]];

        //delete elements once used (we'e permutating so each only gets used once)
        for(int j = factoradic_notation[i]; j < total_symbols - i - 1; j++) {
            array[j] = array[j + 1];
        }
    }

    //what follows now is executed once our permutation is generated
    check_optimal_route(output_array, total_symbols);

    free(array);                //clean up the mess we made in the heap
    free(factoradic_notation);
    return;
}
