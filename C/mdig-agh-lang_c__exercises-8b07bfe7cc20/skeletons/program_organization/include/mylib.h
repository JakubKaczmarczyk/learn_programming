// TODO: Umieść cały kod w tym pliku wewnątrz tzw. strażnika nagłówka.

#include <stdint.h>

// TODO: Zaimplementuj poniższą funkcję zgodnie z jej specyfikacją.
//   Na początku umieść implementację w pliku nagłówkowym i spróbuj zbudować
//   program - przeanalizuj błędy, które się pojawią, i odpowiednio popraw swoje
//   rozwiązanie (przenieś definicję funkcji do pliku ŹRÓDŁOWEGO, a w pliku
//   nagłówkowym pozostaw jedynie DEKLARACJĘ).
/**
 * Zwiększ wartość wskazywaną przez argument funkcji o 1.
 *
 * @param b wskaźnik na wartość do modyfikacji
 */
 void transform(byte* b);

// TODO: Zwróć uwagę na to, jakie błędy pojawiają się, gdy definicja typu pojawia
//   się dopiero PO jego użyciu (tu: typ `byte` jest wykorzystywany w prototypie
//   funkcji `transform()`, a następnie odpowiednio popraw swoje rozwiązanie.
typedef uint8_t byte;

// TODO: Zmień poniższą instrukcję tak, aby z DEFINICJI stała się ona DEKLARACJĄ.
//   Zastanów się, w którym pliku (źródłowym czy nagłówkowym) powinna się wówczas
//   znaleźć instrukcja inicjalizacji takiej zmiennej?
/**
 * Zmienna globalna - początkowo powinna mieć wartość 1.0.
 */
double x;
