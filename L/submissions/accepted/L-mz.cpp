#include <bits/stdc++.h>
using namespace std;

vector<int> solve(long long n) {
    assert(1ll <= n && n <= 1e18);
    set<int> ans;

    for (long long x = 1; x * x * x <= n; x++) {
        if (n % x == 0 && n % (x + 1) == 0) {
            ans.insert(x);
        }
    }
    if (n > 1)
    for (long long k = 1; k * k * k <= n ; k++) {
        long long m = n / k;
        if (n % k) continue;
        long long x = (sqrt(1 + 4 * m) - 1) / 2;

        if (x * (x + 1) == m) {
            ans.insert(x);
        }
    }

    return vector<int>(ans.begin(), ans.end());
}

int main() {
    int t;
    long long n;

    cin >> t;
    assert(1 <= t && t <= 100);

    for (int cs = 1; cs <= t; cs++) {
        cin >> n;
        vector<int> ans = solve(n);
        sort(ans.begin(), ans.end());

        if (ans.size() == 0){
            cout << "-1" << '\n';
        }
        for (size_t i = 0; i < ans.size(); i++) {
            cout << ans[i] << (i + 1 == ans.size() ? '\n' : ' ');
        }
    }

    return 0;
}
