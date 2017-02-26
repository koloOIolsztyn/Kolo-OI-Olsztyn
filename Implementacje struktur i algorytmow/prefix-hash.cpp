// Michal Naruniec

// Imperatywna implementacja sprawdzania rownosci dwoch podslow
// jednego ciagu znakow w czasie stalym z uzyciem prefiksowej tablicy haszy.

// Traktujemy podslowa jako liczby w pewnym systemie liczbowym.
// Haszem jest taka liczba przedstawiona w systemie dziesietnym.

#include <cstdio>
#include <vector>
#include <string>
#include <cassert>

#define ull unsigned long long
#define ul unsigned long

using namespace std;

// Podstawa systemu liczbowego, Liczba pierwsza.
const ull base = 211LL;

// Hasze sa duze, wiec musimy je modulowac. Uzywamy duzej liczby pierwszej.
// Prawdopodobienstwo ze rozne dwa slowa beda mialy ten sam hasz
// jest odwrotnie proporcjonalne do modulatora.
// Nie zalecam automatycznego modulowania long longow, testy na OIu czesto to wykrywaja
// i moze to stworzyc bledy w kodzie.
const ull modulator = 1000000009LL;


// Trzymamy wejscie, hasze i potegi podstawy w zmiennych globalnych.
// Jeśli chcemy analizować wiele wyrazów na raz, przekazywalibysmy docelowe wektory
// do funkcji przez referencje.
string input;

// Prehash[i] to hasz prefiksu slowa input konczacego sie znakiem input[i]
// (wliczajac ten znak).
// Hasze sa ulozone rosnaco pod wzgledem najwyzszej potegi podstawy,
// tzn. pierwszy znak podslowa jest przemnozony przez base^0.
vector<ull> prehash;

// powers[i] to base^i
vector<ull> powers;

// Funkcja wypelnia wektory prehash i powers na podstawie slowa input.
void calc_prehash() {
    // Czyscimy wektory ze starych danych, jesli jakies byly.
    prehash.clear();
    powers.clear();

    ull current_hash = 0;
    ull current_base = 1;
    for(ul i = 0; i < input.size(); i++) {
        powers.push_back(current_base);

        current_hash += (current_base * input[i]);
        current_hash %= modulator;
        prehash.push_back(current_hash);

        current_base *= base;
        current_base %= modulator;
    }
}

// Tylko porownywanie slow tej samej dlugosci ma sens.
// Zakladam dla uproszczenia, ze dane wejsciowe sa poprawne.
bool equals(ul beg1, ul beg2, ul length) {
    if(beg1 == beg2) return true;

    if(beg1 > beg2) return equals(beg2, beg1, length);

    // Dodajemy modulatory, bo w przeciwnym razie hasz moglby wyjsc ujemny.
    ull hash1 = prehash[beg1 + length - 1] + modulator;
    if(beg1 != 0) hash1 -= prehash[beg1 - 1];

    ull hash2 = prehash[beg2 + length - 1] + modulator;
    if(beg2 != 0) hash2 -= prehash[beg2 - 1];

    // Dopasowanie poteg w haszach.
    hash1 *= powers[beg2 - beg1];

    hash1 %= modulator;
    hash2 %= modulator;

    return hash1 == hash2;

}

int main() {
    input = "abaab";
    calc_prehash();

    assert(equals(0, 0, 5));
    assert(equals(0, 2, 1));
    assert(equals(0, 3, 2));
    assert(!equals(0, 1, 1));
    assert(!equals(0, 2, 3));

    printf("Program zakonczyl sie poprawnie\n");
    return 0;
}