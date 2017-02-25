#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
  int n, m, input;
  scanf("%d %d", &n, &m);
  vector<vector<bool> > masks(n, vector<bool> (m)); 
  for(int i = 0; i < m; i++) {
    for(int j = 1; j <= n; j++) {
      scanf("%d", &input);
      masks[input - 1][i] = (j <= (n / 2));
    }
  }
  sort(masks.begin(), masks.end());
  printf(adjacent_find(masks.begin(), masks.end()) == masks.end() ? "TAK\n" : "NIE\n");
  return 0;
}