//#include "gmock/gmock.h"
#include "gtest/gtest.h"

extern "C" {
#include "tasks.h"
}

TEST(TasksTest, ChooseMoreImportantTask) {
    // TODO: Zaimplementuj logikę poniższego scenariusza testowego:
    //   (1) Zdefiniuj dwa zadania: zadanie #1 o niskim priorytecie oraz
    //         zadanie #2 o średnim priorytecie.
    //   (2) Upewnij się, że wywołanie funkcji choose_more_important_task() dla
    //         zadań #1 i #2 zwróciło uchwyt do zadania #2.
    //   (3) Zmień priorytet zadania #1 na wysoki.
    //   (4) Upewnij się, że wywołanie funkcji choose_more_important_task() dla
    //         zadań #1 i #2 zwróciło uchwyt do zadania #1.
}

TEST(TasksTest, LastTwoBits) {
    // TODO: Zaimplementuj logikę poniższego scenariusza testowego:
    //   (1) Zdefiniuj zadanie o niskim priorytecie.
    //   (2) Upewnij się, że wywołanie funkcji transform_task() dla
    //         tego zadania i z uchwytem do funkcji increase_priority()
    //         zmieniło priorytet zadania na wysoki.
    //   (3) Zmień priorytet zadania na średni.
    //   (4) Upewnij się, że wywołanie funkcji transform_task() dla
    //         tego zadania i z uchwytem do funkcji increase_priority()
    //         zmieniło priorytet zadania na wysoki.
}
