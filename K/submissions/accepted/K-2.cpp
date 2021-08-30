#include <bits/stdc++.h>
using namespace std;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n; cin >> n;
  vector<int> x, y;
  for (int i = 0; i < n; i++) {
    int X, Y; cin >> X >> Y;
    x.push_back(X - Y);
    y.push_back(X + Y);
  }
  sort(x.begin(), x.end());
  sort(y.begin(), y.end());

  long long ans = 0;
  for (int i = 0; i < n; i++) {
    ans += abs(x[i] - x[n / 2]);
    ans += abs(y[i] - y[n / 2]);
  }

  cout << ans / 2 << '\n';
}
