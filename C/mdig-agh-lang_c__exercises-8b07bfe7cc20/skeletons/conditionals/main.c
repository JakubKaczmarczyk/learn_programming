#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// TODO: Najpierw zbuduj program bez flag kompilacji wychwytujących pewne błędy:
//  Zakomentuj instrukcję `add_compile_options` w pliku "SetCommonConfig.cmake".
//    (dopisz na początku wiersza znak '#')
//  Wybierz z menu CLion: File > Reload CMake Project
//  Spróbuj uruchomić program - uda się to bez problemu.
//  Teraz odkomentuj instrukcję `add_compile_options` i ponownie przeładuj projekt CMake.
//  Tym razem kompilator zgłosi szereg problemów związanych z potencjalnymi
//    problemami z instrukcjami warunkowymi (prawdopodobnie zawierającymi błędy
//    SEMANTYCZNE).
//  Zwróć uwagę, że każdorazowo CLion sygnalizuje problematyczne miejsca za pomocą:
//    - podkreślenia czerwonym wężykiem
//    - podkreślenia szarym wężykiem i wyszarzenia
//    - podświetlenia na żółto
//    - ...
//  Popraw poniższe funkcje tak, aby działały one zgodnie ze specyfikacją.

/**
 * Zwróć wartość bezwzględną argumentu.
 * @param x liczba całkowita
 * @return wartość bezwzględna z `x`
 */
int my_abs(int x) {
    if (x < 0) {
        return -x;
    }
    return x;

}

/**
 * Zwróć wartość bezwzględną argumentu.
 * @param x liczba całkowita
 * @return wartość bezwzględna z `x`
 */
int my_abs2(int x) {
    if (x < 0) {
        x = -x;
        printf("MY_ABS2: argument was negative\n");
    }
    return x;
}

int main(void) {
    bool b = true;

    // TODO: Zmień poniższe wyrażenie inicjalizujące tak, aby zmienna otrzymała
    //   odpowiednio wartość odpowiadającą literze:
    //     - "t" gdy zmienna `b` ma wartość PRAWDA
    //     - "f" gdy zmienna `b` ma wartość FAŁSZ
    char cnd = (char) (b ? 't' : 'f');
    printf("%c\n\n", cnd);

    int x = 1;
    printf("my_abs(%d) = %d\n", x, my_abs(x));
    printf("my_abs2(%d) = %d\n\n", x, my_abs2(x));

    x = -1;
    printf("my_abs(%d) = %d\n", x, my_abs(x));
    printf("my_abs2(%d) = %d\n", x, my_abs2(x));

    // WDN
    int day_nr = 3;

    printf("Day: ");
    switch (day_nr) {
        case 1:
            printf("pn");
            break;
        case 2:
            printf("wt");
            break;
        case 3:
            printf("sr");
            break;
        case 4:
            printf("cz");
            break;
        case 5:
            printf("pt");
            break;
        case 6:
            printf("sb");
            break;
        case 7:
            printf("ni");
            break;
        default:
            printf("blad");
            break;
    }
    printf("\n");

    // IF 1
    int var_a = 7;
    int var_b = 4;
    printf("czy rowne: %d\n",(int) (var_a==var_b ? 1 : 0));

    // logop 1
    int a3 = 1;
    int b3 = -2;
    int c3 = 7;
    if (a3 > 0 && b3 > 0 && c3 > 0) {
        printf("Trzy dodatnie!\n");
    } else if ((a3 > 0 && b3 > 0 && c3 <= 0) || (a3 > 0 && b3 <= 0 && c3 > 0) || (a3 <= 0 && b3 > 0 && c3 > 0)) {
        printf("Dwie dodatnie!\n");
    } else {
        printf("Nic :(\n");
    }

    int y = 3;
    if ( y >= 2 && y < 7 && y != 5) {
        printf("ok\n");
    } else {
        printf("not ok\n");
    }

    int z = 7;
    if(z % 2 == 0) {
        printf("even\n");
    } else {
        printf("odd\n");
    }
    return EXIT_SUCCESS;
}
