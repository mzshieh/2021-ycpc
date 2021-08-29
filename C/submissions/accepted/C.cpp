#include <bits/stdc++.h>
using namespace std;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  
  vector<vector<vector<int>>> valid(8);
  for (int i = 1; i <= 7; i++) {
    vector<int> vec(i);
    iota(vec.begin(), vec.end(), 0);
    do {
      vector<bool> ok(i, 0);
      int p = 0;
      bool legal = true;
      for (int x = 1; x < i; x++) {
        ok[p] = 1;
        if (ok[vec[p]])
          legal = false;
        p = vec[p];
      }
      if (legal)
        valid[i].push_back(vec);
    } while (next_permutation(vec.begin(), vec.end()));
  }

  int t; cin >> t; while (t--) {
    int n, m; cin >> n >> m;
    vector<int> eR(n, -1), eW(n, -1);
    while (m--) {
      char c; int u, v;
      cin >> c >> u >> v; u--, v--;
      if (c == 'R')
        eR[u] = v;
      else
        eW[u] = v;
    }

    vector<int> R(n);
    iota(R.begin(), R.end(), 0);
    int ans = 0;
    do {
      bool ok = true;
      for (int i = 0; i < n; i++) {
        if (eR[i] == -1 or eR[i] == R[i])
          continue;
        ok = false;
        break;
      }

      vector<int> R_in(n);
      for (int i = 0; i < n; i++)
        R_in[R[i]] = i;
      
      if (not ok)
        continue;

      for (auto &W : valid[n]) {

        ok = true;
        for (int i = 0; i < n; i++) {
          if (eW[i] == -1 or eW[i] == R_in[W[i]])
            continue;
          ok = false; 
          break;
        }
        if (not ok)
          continue;

        vector<bool> ok(n, 0);
        int p = 0;
        bool legal = true;

        for (int x = 1; x < n; x++) {
          ok[p] = 1;
          if (ok[W[p]])
            legal = false;
          p = W[p];
        }
        if (legal)
          ans++;
      }
    } while (next_permutation(R.begin(), R.end()));
    cout << ans << '\n';
  }

}
