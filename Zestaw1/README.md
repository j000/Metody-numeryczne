# Jarosław Rymut

## Zestaw 1

Do zestawu dołączony jest plik `Makefile`.

Wykonanie polecenia `make` utworzy programy i wykresy. `make clean` usuwa
wszystkie pliki stworzone podczas kompilacji.

### Zadanie 1a: `plot.sin1.png`

Z wykresu dokładnie widać, że maksymalny błąd względny występuje w okolicach 0.
Natomiast największy błąd bezwzględny występuje w ostatnim przedziale
(π/3 ≤ x ≤ π/2), gdzie przybliżenie "ścina" krzywiznę sinusa.

### Zadanie 1b: `plot.sin2.png`

Błąd względny znów jest największy w okolicach 0 (ze względu na sposób licznia),
jednak jest on dużo mniejszy niż w przypadku sin1 (~10 razy mniejszy). Błąd
bezwzględny występuje w tym samym przedziale, jednak jest on na poziomie 0.0003
(~100 razy mniejszy niż w przypadku sin1).

### Zadanie 3a: `plot.sin3.png`

Użyłem rozwinięcia Taylora stopnia 9. Błędy są znacząco mniejsze niż
w poprzednich przypadkach i występują w okolicach pi/2. Błędy są pomijalne,
rzędu 3.5e-6.

### Zadanie 3b: `plot.sin4.png` (nie robi się automatycznie)

Poległem przy wielomianach Bernsteina. Albo to miało być coś innego, albo
moja implementacja to totalna porażka.

### Zadanie 4:

Wszystkie pliki `plot.sin*.cpp` obsługują pełny zakres liczb. Po drobnych
zmianach w kodzie można wygenerować większe wykresy.

### Zadanie 6: `plot.sin1b.png`

Węzły Czebyszewa: Biorąc taką samą liczbę punktów (5: w 0, w pi/2 oraz 3 węzły
Czebyszewa na środku) nie poprawiamy dokładności, ale największe błędy występują
w innym miejscu - na środku przedziału.

### Zadanie 7:

Wszystkie przybliżenia oparte na tablicy punktów (sin1, sin1b, sin2) dają wyniki
we właściwym przedziale [0;1]. Aby mieć pewność, że zawsze tak będzie możemy:

  - skorzystać z przybliżenia sinx == x dla bardzo małych x
  - "przyciąć" wartość do 1. dla wartości zbliżonych do pi/2
