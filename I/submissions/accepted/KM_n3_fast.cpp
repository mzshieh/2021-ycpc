#include <bits/stdc++.h>
using namespace std;

#define MAXN 502
#define INF LLONG_MAX
long long g[MAXN][MAXN], lx[MAXN], ly[MAXN], slack_y[MAXN];
long long px[MAXN], py[MAXN], match_y[MAXN], par[MAXN];
long long n;
void adjust(long long y) {  // 把增廣路上所有邊反轉
    match_y[y] = py[y];
    if (px[match_y[y]] != -2) adjust(px[match_y[y]]);
}
bool dfs(long long x) {  // DFS找增廣路
    for (long long y = 0; y < n; ++y) {
        if (py[y] != -1) continue;
        long long t = lx[x] + ly[y] - g[x][y];
        if (t == 0) {
            py[y] = x;
            if (match_y[y] == -1) {
                adjust(y);
                return 1;
            }
            if (px[match_y[y]] != -1) continue;
            px[match_y[y]] = y;
            if (dfs(match_y[y])) return 1;
        } else if (slack_y[y] > t) {
            slack_y[y] = t;
            par[y] = x;
        }
    }
    return 0;
}
inline long long km() {
    memset(ly, 0, sizeof(long long) * n);
    memset(match_y, -1, sizeof(long long) * n);
    for (long long x = 0; x < n; ++x) {
        lx[x] = -INF;
        for (long long y = 0; y < n; ++y) {
            lx[x] = max(lx[x], g[x][y]);
        }
    }
    for (long long x = 0; x < n; ++x) {
        for (long long y = 0; y < n; ++y) slack_y[y] = INF;
        memset(px, -1, sizeof(long long) * n);
        memset(py, -1, sizeof(long long) * n);
        px[x] = -2;
        if (dfs(x)) continue;
        bool flag = 1;
        while (flag) {
            long long cut = INF;
            for (long long y = 0; y < n; ++y)
                if (py[y] == -1 && cut > slack_y[y]) cut = slack_y[y];
            for (long long j = 0; j < n; ++j) {
                if (px[j] != -1) lx[j] -= cut;
                if (py[j] != -1)
                    ly[j] += cut;
                else
                    slack_y[j] -= cut;
            }
            for (long long y = 0; y < n; ++y) {
                if (py[y] == -1 && slack_y[y] == 0) {
                    py[y] = par[y];
                    if (match_y[y] == -1) {
                        adjust(y);
                        flag = 0;
                        break;
                    }
                    px[match_y[y]] = y;
                    if (dfs(match_y[y])) {
                        flag = 0;
                        break;
                    }
                }
            }
        }
    }
    long long ans = 0;
    for (long long y = 0; y < n; ++y)
        if (g[match_y[y]][y] != -INF) ans += g[match_y[y]][y];
    return ans;
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
    cin >> n;
    vector<Point> s(n), t(n);
    for (auto &p : s) cin >> p.x >> p.y;
    for (auto &p : t) cin >> p.x >> p.y;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g[i][j] = -dist2(s[i], t[j]);
        }
    }
    cout << -km() << '\n';
    return 0;
}
