// Michal Naruniec
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
  int n, m, input;
  scanf("%d %d", &n, &m);
  
  // Inicjalizacja dwuwymariowego wektora booli o rozmiarze n x m.
  vector<vector<bool> > masks(n, vector<bool> (m)); 
  for(int i = 0; i < m; i++) {
    for(int j = 1; j <= n; j++) {
      scanf("%d", &input);
      
      // Przypisanie do druzyn - true to gra w druzynie 1.
      masks[input - 1][i] = (j <= (n / 2));
    }
  }
  // Sortowanie wektorow po domyslnym komparatorze.
  sort(masks.begin(), masks.end());
  
  // Funkcja znajdujaca 2 sasiednie, rowne wiersze.
  printf(adjacent_find(masks.begin(), masks.end()) == masks.end() ? "TAK\n" : "NIE\n");
  return 0;
}