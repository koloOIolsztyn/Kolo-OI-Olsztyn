// Michal Naruniec

// Prosta imperatywna implementacja Find-Union.
// Mozna ja rozszerzyc o mozliwosc robienia wielu roznych lasow,
// pamietania wszystkich wierzcholkow w danym zbiorze,
// tworzenia wierzcholkow o wlasnych nazwach,
// zabezpieczania sie przed blednymi argumentami itp.

#include <cstdio>
#include <vector>
#include <cassert>

// Normalnie raczej zle sie patrzy na takie aliasy, ale tutaj dopuscimy.
#define ul unsigned long


using namespace std;

// Drugi indeks to numer wierzcholka,
// wartosc[0] - numer ojca w drzewie
// wartosc[1] - ranga wierzcholka.
// Nie grzebiemy recznie w wektorze poza funkcjami do obslugi.
vector<ul> structure[2];

// Zwraca referencje, czyli dzialania na wyniku funkcji beda zapamietywanie w strukturze
ul& Rank(ul node) {
    return structure[1][node];
}

ul& Parent(ul node) {
    return structure[0][node];
}

// Zwraca id nowego zbioru 1-elementowego
ul Init() {
    structure[0].push_back(structure[0].size());
    structure[1].push_back(0);
    return structure[0].size() - 1;
}

ul Find(ul node) {
    // Warunek stopu
    if(Parent(node) == node) return node;

    // Rekurencyjne znalezienie reprezentanta zbioru
    ul return_value = Find(Parent(node));

    // Optymalizacja z przepinaniem
    Parent(node) = return_value;

    return return_value;
}

// Nie mozna napisac union mala litera!
void Union(ul left, ul right) {
    // Znalezienie reprezentantow
    left = Find(left);
    right = Find(right);

    // Optymalizacja z rangami
    if(Rank(left) < Rank(right)) Union(right, left);
    else {
        Parent(right) = left;
        if(Rank(left) == Rank(right)) ++Rank(left);
    }
}


int main() {

    ul a = Init(), b = Init(), c = Init();

    // Asercja, przerywa program z bledem gdy nie jest spelniona
    assert(Find(a) != Find(b));
    assert(Find(b) != Find(c));
    assert(Find(a) != Find(c));

    Union(a, b);

    assert(Find(a) == Find(b));
    assert(Find(b) != Find(c));
    assert(Find(a) != Find(c));

    ul d = Init();

    Union(c, d);

    assert(Find(a) != Find(d));
    assert(Find(c) == Find(d));

    Union(a, d);

    assert(Find(b) == Find(c));


    printf("Poprawne zakonczenie.\n");
    return 0;
}