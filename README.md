# shared_pointer
Zadanie z Biblioteki Standardowej

task_w7_shared_thread_person_sort.txt:

Korzystamy z klasy Person (name/surname/age).

1) Tworzymy wektor (vec_all), w którym umieścimy 1000 losowo wygenerowanych osób.

2) Tworzymy 3 wektory, do których kopiujemy osoby z wektora vec_all.
vec_sort_surname
vec_sort_name
vec_sort_age

3) Sortujemy osoby w wektorach vec_sort_X.

Sortowanie każdego wektora ma się odbyć w osobnych wątkach.
(czyli potrzebne są nam 3 wątki).

4) Po zakończeniu sortowania, wypisujemy po 10 osób z każdego wektora w celu sprawdzenia, czy dane są posortowane poprawnie.

Uwaga: 
- w celu nie duplikowania danych, osoby w wektorach mają byc przetrzymywane przy pomocy std::shared_ptr
- ref_count powinien wynosić 4 (ponieważ dane są współdzielone w 4 wektorach).
