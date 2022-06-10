#include <stdlib.h>
#include <stdio.h>

// === UWAGA! ===
//
// Narzędzie AddressSanitizer (pozwalające wykryć m.in. błędy pisania po
// nie-swojej pamięci statycznej) jest dostępne natywnie wyłącznie dla systemów
// operacyjnych z rodziny UNIX.
// 
// Jeśli pracujesz na innym systemie operacyjnym, możesz nie mieć możliwości
// uruchomienia tego narzędzia (a nawet na systemie z rodziny UNIX może ono
// nie być zainstalowane) - wówczas pomiń rozwiązywanie CAŁEGO tego zadania.
//
// Narzędzia z pakietu Valgrind i narzędzie AddressSanitizer nie współpracują ze
// sobą. Dlatego przed próbą uruchomienia narzędzia z pakietu Valgrind wyłącz
// narzędzie AddressSanitizer komentując w pliku CMake polecenie
//    set(USE_ASAN true)
// i ponownie przeładowując projekt CMake.
// Po zakończeniu pracy z Valgrind-em ponownie włącz narzędzie AddressSanitizer
// odkomentowując w pliku CMake wspomnianą instrukcję.
//
// REF: https://github.com/google/sanitizers/issues/810

int main(void) {
    return EXIT_SUCCESS;
}
