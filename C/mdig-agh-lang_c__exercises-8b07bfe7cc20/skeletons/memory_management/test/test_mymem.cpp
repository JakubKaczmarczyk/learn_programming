#include "gmock/gmock.h"
#include "gtest/gtest.h"

extern "C" {
#include "mymem.h"
}

#include <limits.h>

// TODO: Wyłącz narzędzie AddressSanitizer (zob. plik main.c).
//  Uruchom poniższy test za pomocą pakietu Valgrind. Zwróć uwagę na problem
//     "Leak_DefinitelyLost" sygnalizujący wyciek pamięci.
//     Dalsza analiza komunikatów (w sekcji "vg_replace_malloc.c", w sekcji
//     "20 bytes...") wskazuje wystąpienie funkcji malloc(), która nie posiada
//     odpowiadającego jej wywołania funkcji zwalniającej przydzieloną pamięć.
//   Teraz dopisz odpowiedni kod zwalniający (potencjalnie) przydzielony blok
//     pamięci i ponownie uruchom test - problem powinien zniknąć.
//   Włącz narzędzie AddressSanitizer (zob. plik main.c)
TEST(BitlibTest, CreateSequence_AreValuesCorrect) {
    size_t n = 5;

    int* seq = create_sequence(n);
    // Poniższa asercja wykorzystuje funkcjonalność udostępnianą przez język C++.
    EXPECT_THAT(std::vector<uint8_t>(seq, seq + n),
                ::testing::ElementsAre(1, 2, 3, 4, 5));

}

TEST(BitlibTest, CreateSequence_TooLarge) {
    int* seq = create_sequence(ULONG_MAX);

    EXPECT_EQ(seq, (int*) NULL);

    // Pamiętaj, aby próbować zwalniać pamięć tylko wówczas, gdy wskaźnik
    // faktycznie wskazuje na jakiś blok pamięci do potencjalnego zwolnienia...
    if (seq != (int*) NULL) {
        free(seq);
    }
}

// TODO: Wyłącz narzędzie AddressSanitizer (zob. plik main.c).
//  Uruchom poniższy test za pomocą pakietu Valgrind. Zwróć uwagę na problem
//     "Leak_DefinitelyLost" sygnalizujący wyciek pamięci.
//     Dalsza analiza komunikatów (w sekcji "vg_replace_malloc.c", w sekcji
//     "20 bytes...") wskazuje wystąpienie funkcji malloc(), która nie posiada
//     odpowiadającego jej wywołania funkcji zwalniającej przydzieloną pamięć.
//   Teraz dopisz odpowiedni kod zwalniający (potencjalnie) przydzielony blok
//     pamięci PO instrukcji
//       int* seq = create_sequence(1);
//     natomiast PRZED wykonaniem instrukcji
//       seq = create_sequence(2);
//     i ponownie uruchom test - problem powinien zniknąć.
//   Włącz narzędzie AddressSanitizer (zob. plik main.c)
TEST(BitlibTest, CreateSequence_LooseHandleToAllocatedMemoryBlock) {
    int* seq = create_sequence(1);

    seq = create_sequence(2);

    if (seq != (int*) NULL) {
        free(seq);
    }
}
