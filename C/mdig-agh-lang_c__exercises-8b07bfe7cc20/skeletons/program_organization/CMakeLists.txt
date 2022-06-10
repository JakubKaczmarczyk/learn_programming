cmake_minimum_required(VERSION 3.13)

set(PROJECT_ID program_organization)

# UWAGI:
#
# *) Bieżącym katalogiem dla tego pliku CMakeLists.txt jest główny katalog
#     projektu - to istotne podczas podawania względnych ścieżek do plików.
#
# *) Definiując listy ścieżek do plików musisz jawnie podać każdy pojedynczy
#      plik - nie możesz wskazać od razu całego folderu.[1]
#
# *) Poszczególne elementy w liście rozdzielamy dowolną kombinacją znaków
#      białych (tj. spacji, tabulatorów i znaków nowej linii), ale NIE
#      przecinkami (czy innymi znakami drukowanymi).
#    Przykład #1 - oddzielanie spacjami: set(SOURCE_FILES plik1.c plik2.c)
#    Przykład #2 - oddzielanie znakami nowej linii (i spacjami):
#      set(SOURCE_FILES
#           plik1.c
#           plik2.c
#           )
#
# [1] Technicznie jest to możliwe (zob. file - GLOB:
#       https://cmake.org/cmake/help/latest/command/file.html#glob|]]),
#       jednak to zła praktyka, o czym informuje dokumentacja narzędzia CMake.

set(SOURCE_FILES
        # TODO: Uzupełnij - podaj ścieżki WZGLĘDNE do "podstawowych" plików źródłowych.
        #   Chodzi o te pliki, które zawierają logikę głównego programu (np.
        #   napisanych przez Ciebie bibliotek), a nie kod testów jednostkowych.
        )

set(SOURCES_FILES_TESTS
        # TODO: Uzupełnij - podaj ścieżki WZGLĘDNE do plików źródłowych testów jednostkowych.
        #   Chodzi o "nasze" pliki źródłowe (w folderze test/), a NIE o pliki
        #   frameworku Google Testing Framework!
        )

# TODO: Zobacz, gdzie w pliku `SetCommonConfig.cmake` wykorzystywane są powyższe zmienne (tj. `SOURCE_FILES` i `SOURCES_FILES_TESTS`).
include(../SetCommonConfig.cmake)
