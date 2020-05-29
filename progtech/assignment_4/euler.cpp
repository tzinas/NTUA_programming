#include <stdio.h>
#include <iostream>
#include <algorithm>

#define MAXN 10005

using namespace std;

int A[MAXN];

int main() {
  int N, M;

  scanf("%d %d", &N, &M);
  for (int i=0; i<N; i++) {
    A[i] = 0;
  }
  for (int i=1; i<=M; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    A[a]++;
    A[b]++;
  }

  int count_odd = 0, odd_1 = -1, odd_2 = -1;

  for (int i=0; i<N; i++) {
    if (A[i] % 2 == 1) {
      count_odd++;
      if (odd_1 < 0) {
        odd_1 = i;
      }
      else if (odd_2) {
        odd_2 = i;
      }
    }
  }

  if (count_odd == 0) {
    printf("CYCLE\n");
  }
  else if (count_odd == 2){
    printf("PATH %d %d\n", min(odd_1, odd_2), max(odd_1, odd_2));
  }
  else {
    printf("IMPOSSIBLE\n");
  }
  return 0;
}
