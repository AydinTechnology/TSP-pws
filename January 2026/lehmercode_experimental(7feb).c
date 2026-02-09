//basic usage - suppose you want to permute set A. Change total_symbols to #A and permutation_index to anything in between 0 and (#A)!-1
//compile with: gcc lehmercode_experimental.c -o lehmercode_experimental

#include <stdio.h>
#include <stdlib.h>

int total_symbols = 9;
int permutation_index = 0;

int main() {
    int *array = malloc(sizeof(int) * total_symbols); //allocate total_symbols * int_size bytes to our array
    int *permutation_array = malloc(sizeof(int) * total_symbols);
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
        permutation_array[i] = array[factoradic_notation[i]];

        //delete elements once used (we'e permutating so each only gets used once)
        for(int j = factoradic_notation[i]; j < total_symbols - i - 1; j++) {
            array[j] = array[j + 1];
        }
    }

    //print our resulting permutation etc
    for(int i = 0; i < total_symbols; i++) {
        printf("%i ", factoradic_notation[i]);
    }
    printf("\n");
    for(int i = 0; i < total_symbols; i++) {
        printf("%i ", permutation_array[i]);
    }

    free(array);                //clean up the mess we made in the heap
    free(permutation_array);
    free(factoradic_notation);
    return 0;
}
