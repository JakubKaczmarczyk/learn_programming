# README #

## Zawartość repozytorium ##

Repozytorium zawiera poniższe foldery:

  * folder `skeletons` – zawiera foldery z projektami-szkieletami zadań laboratoryjnych (do uzupełnienia w ramach zajęć)  
  * folder `solutions` – zawiera foldery z projektami-rozwiązaniami  
  * folder `docs` – zawiera pliki użyte do tworzenia dokumentacji projektów (np. pliki `.uml` zawierające opis diagramu UML dla [PlantUML](http://www.plantuml.com/))

## Konfiguracja ##

Aby móc poprawnie zbudować dany projekt:

  * Pobierz [archiwum](https://github.com/google/googletest/releases/) frameworku Google Testing Framework (GTF) i 
  wypakuj je w dowolnie wybranym miejscu na dysku.
  * Otwórz plik _SetCommonConfig.cmake_ (w folderach `skeletons` i `solutions`) i zmień wartość zmiennej `GTEST_ROOT` na ścieżkę (obojętne czy względną, czy bezwzględną) do głównego folderu z plikami GTF. Domyślna konfiguracja zakłada, że folder GTF o nazwie _googletest-master_ znajduje się w głównym folderze repozytorium (na tym samym poziomie, co foldery `skeletons` i `solutions`).

## Korzystanie z rozwiązań ##

Zamieszczone rozwiązania mają pomóc Ci **po zakończonej pracy nad zadaniem** skonfrontować swoje rozwiązanie z rozwiązaniem wzorcowym.

Q: **Dlaczego nie powinenem/powinnam zaglądać do rozwiązań w trakcie wykonywania zadania?**

A: Gdyż proces rozwiązywania ewentualnych napotkanych problemów pozwoli Ci lepiej ugruntować wiedzę – nie mówiąc o satysfakcji z pokonywania trudności!  _(Amerykańscy naukowcy zapewne już to udowodnili ;)_  
Masz jakiś problem?! – Poproś prowadzącego zajęcia o pomoc!
