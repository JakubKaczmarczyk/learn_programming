#include "ptrlib.h"

#include <stddef.h>

void swap(int* a, int* b) {
    if (a != NULL && b != NULL) {
        int t = *a;
        *a = *b;
        *b = t;
    }
}
