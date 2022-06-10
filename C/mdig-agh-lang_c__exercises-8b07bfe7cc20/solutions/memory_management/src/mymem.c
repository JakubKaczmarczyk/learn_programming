#include "mymem.h"

#include <stdlib.h>
#include <assert.h>

int* create_sequence(size_t n) {
    int* seq = (int*) malloc(n * sizeof(int));

    // Zawsze należy sprawdzić, czy funkcji malloc() faktycznie udało się
    // przydzielić blok pamięci. Jeśli program ma działać poprawnie wyłącznie
    // wówczas, gdy się to uda, można dodać odpowiedni warunek z użyciem
    // instrukcji assert():
    //   assert(seq != NULL);
    // Natomiast w tym przypadku, zgodnie ze specyfikacją funkcji, należy
    //   zwrócić pusty wskaźnik.
    if (seq != NULL) {
        for (size_t i = 0; i < n; ++i) {
            seq[i] = (int) (i + 1);
        }
    }
    return seq;
}
