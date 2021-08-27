#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> d(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        d[u]++;
        d[v]++;
    }
    double ans = 0;
    for (int i = 0; i < n; i++) {
        ans += a[i] * d[i];
    }
    ans *= k;
    ans /= (2 * n - 2);
    cout << fixed << ans << '\n';

    return 0;
}
