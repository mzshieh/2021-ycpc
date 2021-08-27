#include<bits/stdc++.h>

using namespace std;

int main() {
    int p, q;
    cin >> p >> q;
    int ans = 0;
    for (int i = p; i <= q; i++) {
        ans += i;
    }
    cout << ans << endl;
    return 0;
}
