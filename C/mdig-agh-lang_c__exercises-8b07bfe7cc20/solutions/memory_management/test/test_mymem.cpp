#include "gmock/gmock.h"
#include "gtest/gtest.h"

extern "C" {
#include "mymem.h"
}

#include <limits.h>

TEST(BitlibTest, CreateSequence_AreValuesCorrect) {
    size_t n = 5;

    int* seq = create_sequence(n);
    // Poniższa asercja wykorzystuje funkcjonalność udostępnianą przez język C++.
    EXPECT_THAT(std::vector<uint8_t>(seq, seq + n),
                ::testing::ElementsAre(1, 2, 3, 4, 5));

    // Pamiętaj, aby zwolnić przydzieloną pamięć.
    if (seq != NULL) {
        free(seq);
    }
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

TEST(BitlibTest, CreateSequence_LooseHandleToAllocatedMemoryBlock) {
    int* seq = create_sequence(1);

    // Pamiętaj, aby spróbować zwolnić pamięć każdorazowo przed nadpisaniem
    // OSTATNIEGO uchwytu do dynamicznie zaalokowanego bloku pamięci.
    // (W tym przypadku `seq` to jedyny uchwyt, zatem wywołanie
    //   seq = create_sequence(2);
    //  spowoduje właśnie nadpisanie OSTATNIEGO uchwytu.)
    if (seq != (int*) NULL) {
        free(seq);
    }

    seq = create_sequence(2);

    if (seq != (int*) NULL) {
        free(seq);
    }
}
