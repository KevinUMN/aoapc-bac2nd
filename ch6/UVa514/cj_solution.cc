#include <cstdio>
#include <stack>

using namespace std;

int target[1000];

int main() {

#ifdef LOCAL
  freopen("sample_input", "r", stdin);
#endif

  int n; // Number 1...n for carts into the station
  bool next; // whether to do the next case
  while(scanf("%d", &n) && n) {

    next = false;
    while (!next) {

      for (int i = 1; i <= n; ++i) {
        scanf("%d", &target[i]);
        if ( i == 1 && target[i] == 0) {
          printf("\n");
          next = true;
          break;
        }
      }

      if (!next) {
        int in = 1, out = 1;
        stack<int> station;
        bool ok = true;
        while (out <= n) {

          if (in == target[out]) {
            in++; out++;
          } else if (!station.empty() && station.top() == target[out]) {
            out++;
            station.pop();
          } else if (in <= n) {
            station.push(in);
            in++;
          } else {
            ok = false;
            break;
          }
        }
        if (ok) {
          printf("Yes\n");
        } else {
          printf("No\n");
        }
      }
    }
  }

  return 0;
}
