#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "mylib.h"  // Dodane tylko po to, aby zademonstrować błąd wielokrotnej
                    //   definicji (gdy plik nagłówkowy zawiera definicje
                    //   funkcji lub zmiennych).

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
