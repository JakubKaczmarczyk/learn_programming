#ifndef MYMEM_H_
#define MYMEM_H_

#include <stddef.h>

/**
 * Zwróć adres tablicy reprezentującej ciąg liczb całkowitych: 1, 2, ..., n
 *
 * @param n maksymalny element ciągu (liczba całkowita dodatnia)
 * @return adres tablicy reprezentującej ciąg albo wskaźnik pusty, jeśli
 *   nie udało się zarezerwować bloku pamięci
 */
extern int* create_sequence(size_t n);

#endif /* MYMEM_H_ */
