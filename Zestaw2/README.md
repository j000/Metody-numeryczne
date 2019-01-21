# Jarosław Rymut

## Zestaw 2

Do zestawu dołączony jest plik `Makefile`.

Wykonanie polecenia `make` utworzy programy. `make clean` usuwa wszystkie pliki
stworzone podczas kompilacji.


### Zadanie 1: `zad1.x`

Dla funkcji ciągłych najlepszym przybliżeniem jest użycie kwadratury
Gaussa-Legendre'a (o ilości punktów większej od stopnia wielomianu). Dla funkcji
nieciągłych użycie metody trapezów czy Simpsona daje zdecydowanie lepsze wyniki.

### Zadanie 2: `zad2.x`

Dla niedużego "przycięcia" nieskończoności (ograniczenie do przedziału \[0,100\])
i dużej ilości punktów metody Simspona i trapezów dają najlepsze wyniki. Przy
podniesieniu limitu zaczynają dominować błędy obliczeń. Kwadratury
Gaussa-Legendre'a dają niedokładne wyniki, jednak wymagają dużo mniejszej ilości
obliczeń. Kwadratura sinh-tanh daje zaskakująco słabe wyniki - spodziewam się
błędów w implementacji, jednak błąd praktycznie nie zmienia się w zależności
od ilości punktów użytych przy metodzie trapezów, pozwala to na znaczne
zredukowanie wymaganej ilości obliczeń.
