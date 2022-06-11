#include "mymem.h"
#include <malloc.h>

int* create_sequence(size_t n) {

    return (int*) malloc(n * sizeof(int*));
}
