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

// TODO: Wyłącz dodatkowe flagi kompilacji, zbuduj i uruchom program. Zwróć
//     uwagę, że zostało wyświetlone jedynie ostrzeżenie:
//       warning: function returns address of local variable [-Wreturn-local-addr]
//     wynikające z próby zwrócenia adresu zmiennej lokalnej, która jest usuwana
//     w trakcie opuszczania ciała funkcji.
//   Jednak ostrzeżenie nie przeszkodziło w dokończeniu procesu budowania, za
//     to próba uruchomienia programu kończy się błędem.
//   Wyłącz narzędzie AddressSanitizer (zob. plik main.c).
//   Uruchom program z użyciem pakietu Valgrind - pokaże się problem "InvalidRead"
//     w pliku "main.c":
//     "Address 0x0 is not stack'd, malloc'd or (recently) free'd"
//   Błąd ten jednak nie pozwala na szybką identyfikację problemu.
//   Po skompilowaniu programu z uwzględnieniem dodatkowych flag kompilacji
//     jesteśmy zmuszeni zainterweniować - zakomentuj funkcję create_array() oraz
//     poniższe linie w funkcji main():
//       int* arr = create_array(5);
//       printf("%d\n", arr[0]);
//   Włącz narzędzie AddressSanitizer (zob. plik main.c)
//   Wciąż jednak pozostaje błąd próby dostępu do elementu tablicy spoza zakresu,
//     który ciężko zdiagnozować. Jeśli pracujesz na systemie z rodziny UNIX
//     możesz użyć narzędzia AddressSanitizer, dostępnego m.in. w ramach pakietu
//     GCC, po dodaniu odpowiednich flag dla kompilatora i konsolidatora.
//     Ponownie zbuduj program. Po uruchomieniu programu w oknie "Run" pojawi
//     się karta "Sanitizer" - po rozwinięciu pozycji "main.c" zobaczysz
//     przyczynę błędu:
//       Stack-buffer-overflow on address ...
//     Po kliknięciu na pierwszą pozycję od góry (zawierającą na początku ikonę
//     ramek) zobaczysz w oknie podglądu w którym wierszu znajduje się problematyczna
//     instrukcja.
//   Po wykonaniu powyższych kroków usuń poniższą definicję funkcji `create_array()`
//     oraz zakomentuj całe ciało funkcji main() z wyjątkiem instrukcji `return`.
int* create_array(int n) {
    int arr[n];
    return arr;
}

int main(void) {
    int* arr = create_array(5);
    printf("%d\n", arr[0]);

    int arr2[] = {1, 2, 3};
    for (size_t i = 0; i <= 4; ++i) {
        arr2[i] = 1;  // BŁĄD: Odwołanie się do elementu arr2[4].
    }
    printf("%d\n", arr2[0]);
    return EXIT_SUCCESS;
}
