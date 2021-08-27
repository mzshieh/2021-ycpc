#include <bits/stdc++.h>
using namespace std;

vector<int> solve(long long n) {
    assert(1ll <= n && n <= 1e18);
    vector<int> ans;

    for (long long x = 1; x * (x + 1) <= n; x++) {
        if (n% (x * x + x) == 0) {
            ans.push_back(x);
        }
    }

    return ans;
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

        if (ans.size() == 0) {
            cout << "-1" << '\n';
        }
        for (size_t i = 0; i < ans.size(); i++) {
            cout << ans[i] << (i + 1 == ans.size() ? '\n' : ' ');
        }
    }

    return 0;
}
