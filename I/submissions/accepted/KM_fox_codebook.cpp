#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500 + 10;
const long long INF64 = 0x3f3f3f3f3f3f3f3fll;
int nl, nr;
int pre[MAXN];
long long slack[MAXN];
long long W[MAXN][MAXN];
long long lx[MAXN], ly[MAXN];
int mx[MAXN], my[MAXN];
bool vx[MAXN], vy[MAXN];
void augment(int u) {
    if (!u) return;
    augment(mx[pre[u]]);
    mx[pre[u]] = u;
    my[u] = pre[u];
}
void match(int x) {
    queue<int> que;
    que.push(x);
    while (1) {
        while (!que.empty()) {
            x = que.front();
            que.pop();
            vx[x] = 1;
            for (int i = 1; i <= nr; i++) {
                if (vy[i]) continue;
                long long t = lx[x] + ly[i] - W[x][i];
                if (t > 0) {
                    if (slack[i] >= t) slack[i] = t, pre[i] = x;
                    continue;
                }
                pre[i] = x;
                if (!my[i]) {
                    augment(i);
                    return;
                }
                vy[i] = 1;
                que.push(my[i]);
            }
        }
        long long t = INF64;
        for (int i = 1; i <= nr; i++)
            if (!vy[i]) t = min(t, slack[i]);
        for (int i = 1; i <= nl; i++)
            if (vx[i]) lx[i] -= t;
        for (int i = 1; i <= nr; i++) {
            if (vy[i])
                ly[i] += t;
            else
                slack[i] -= t;
        }
        for (int i = 1; i <= nr; i++) {
            if (vy[i] || slack[i]) continue;
            if (!my[i]) {
                augment(i);
                return;
            }
            vy[i] = 1;
            que.push(my[i]);
        }
    }
}

struct Point {
    long long x, y;
};

long long dist2(const Point &a, const Point &b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main() {
    int n;
    cin >> n;
    nl = nr = n;

    vector<Point> s(n), t(n);
    for (auto &p : s) cin >> p.x >> p.y;
    for (auto &p : t) cin >> p.x >> p.y;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int u = i + 1;
            int v = j + 1;
            long long w = -dist2(s[i], t[j]);
            W[u][v] = w;
            lx[u] = max(lx[u], w);
        }
    }
    for (int i = 1; i <= nl; i++) {
        for (int x = 1; x <= nl; x++) vx[x] = 0;
        for (int y = 1; y <= nr; y++) vy[y] = 0, slack[y] = INF64;
        match(i);
    }
    long long ans = 0;
    for (int i = 1; i <= nl; i++) ans += W[i][mx[i]];
    cout << -ans << '\n';
}
