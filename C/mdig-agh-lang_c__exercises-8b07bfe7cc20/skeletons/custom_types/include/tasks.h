// TODO: Zdefiniuj typ wyliczeniowy `Priority` zawierający poniższe etykiety:
//   LOW, MEDIUM, HIGH

// TODO: Zdefiniuj alias `task_id_t` na typ `unsigned int`.

// TODO: Zdefiniuj szablon struktury `Task`, reprezentujący zadanie do wykonania
//  w hipotetycznym systemie kolejkowym, zawierający poniższe pola:
//   - id (typ: task_id_t) - ID zadania
//   - priority (typ: Priority) - priorytet zadania

/**
 * Zwróć uchwyt "tylko do odczytu" do zadania o wyższym priorytecie.
 *
 * @param t1 wskaźnik do zadania #1
 * @param t2 wskaźnik zadania #2
 * @return wskaźnik do zadania o wyższym priorytecie (t1 albo t2)
 */
// TODO: Uzupełnij prototyp i implementację poniższej funkcji zgodnie z jej
//   powyższą specyfikacją. Pamiętaj o zasadach const-correctness!
choose_more_important_task();

/**
 * Zwróć tekstową reprezentację priorytetu.
 *
 * @param p priorytet
 * @return tekstowa reprezentację priorytetu [łańcuch znaków]
 */
// TODO: Uzupełnij prototyp i implementację poniższej funkcji zgodnie z jej
//   powyższą specyfikacją. Pamiętaj o zasadach const-correctness!
priority_as_str(Priority p);

/**
 * Zwiększ priorytet o jeden stopień (chyba, że priorytet jest już najwyższy z możliwych).
 *
 * @param p wskaźnik do priorytetu (tj. wskaźnik na typ Priority)
 */
// TODO: Uzupełnij prototyp i implementację poniższej funkcji zgodnie z jej
//   powyższą specyfikacją. Pamiętaj o zasadach const-correctness!
increase_priority();

/**
 * Dokonaj transformacji zadania.
 *
 * Transformacja polega na dwukrotnym wywołaniu funkcji wskazywanej przez `f`,
 * przekazanej jako argument wywołania transform_task(), każdorazowo podając
 * uchwyt do priorytetu zadania `t` jako argument funkcji wskazywanej przez `f`.
 *
 * @param t wskaźnik do zadania
 * @param f wskaźnik do funkcji przyjmującej "zwykły" wskaźnik na typ Priority
 *   (funkcja ta nie zwraca żadnej wartości)
 */
// TODO: Uzupełnij prototyp i implementację poniższej funkcji zgodnie z jej
//   powyższą specyfikacją. Pamiętaj o zasadach const-correctness!
transform_task();
