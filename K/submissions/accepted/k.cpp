#include <bits/stdc++.h>
using namespace std;

struct Line {
    long long a, b;

    bool operator<(const Line &rhs) const {
        return a * rhs.b < rhs.a * b;
    }
};

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    int n;
    cin >> n;
    assert(1 <= n && n <= 100000);

    map<Line, set<int>> S;
    for (int i = 0; i < n; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        assert(-100000 <= a && a <= 100000);
        assert(-100000 <= b && b <= 100000);
        assert(-100000 <= c && c <= 100000);
        assert(!(a == 0 && b == 0));
        if (S[{a, b}].count(c)) {
            cout << "TOO MANY" << '\n';
            return 0;
        } else {
            S[{a, b}].insert(c);
        }
    }

    long long ans = (long long)n * (n - 1) / 2;
    for (auto &p : S) {
        int m = p.second.size();
        ans -= (long long)m * (m - 1) / 2;
    }

    if (ans > 1000000) {
        cout << "TOO MANY" << '\n';
    } else {
        cout << ans << '\n';
    }

    return 0;
}
