#include <bits/stdc++.h>
using namespace std;

#define MAXN 500
#define INF LLONG_MAX
long long n;
long long g[MAXN][MAXN], lx[MAXN], ly[MAXN], slack_y[MAXN];
long long match_y[MAXN];  //要保證g是完全二分圖
bool vx[MAXN], vy[MAXN];
bool dfs(long long x, bool adjust = 1) {  // DFS找增廣路，is=1表示要擴充
    if (vx[x]) return 0;
    vx[x] = 1;
    for (long long y = 0; y < n; ++y) {
        if (vy[y]) continue;
        long long t = lx[x] + ly[y] - g[x][y];
        if (t == 0) {
            vy[y] = 1;
            if (match_y[y] == -1 || dfs(match_y[y], adjust)) {
                if (adjust) match_y[y] = x;
                return 1;
            }
        } else if (slack_y[y] > t)
            slack_y[y] = t;
    }
    return 0;
}
inline long long km() {
    memset(match_y, -1, sizeof(long long) * n);
    memset(ly, 0, sizeof(long long) * n);
    for (long long x = 0; x < n; ++x) {
        lx[x] = -INF;
        for (long long y = 0; y < n; ++y) {
            lx[x] = max(lx[x], g[x][y]);
        }
    }
    for (long long x = 0; x < n; ++x) {
        for (long long y = 0; y < n; ++y) slack_y[y] = INF;
        memset(vx, 0, sizeof(bool) * n);
        memset(vy, 0, sizeof(bool) * n);
        if (dfs(x)) continue;
        bool flag = 1;
        while (flag) {
            long long cut = INF;
            for (long long y = 0; y < n; ++y) {
                if (!vy[y] && cut > slack_y[y]) cut = slack_y[y];
            }
            for (long long j = 0; j < n; ++j) {
                if (vx[j]) lx[j] -= cut;
                if (vy[j])
                    ly[j] += cut;
                else
                    slack_y[j] -= cut;
            }
            for (long long y = 0; y < n; ++y) {
                if (!vy[y] && slack_y[y] == 0) {
                    vy[y] = 1;
                    if (match_y[y] == -1 || dfs(match_y[y], 0)) {
                        flag = 0;  //測試成功，有增廣路
                        break;
                    }
                }
            }
        }
        memset(vx, 0, sizeof(bool) * n);
        memset(vy, 0, sizeof(bool) * n);
        dfs(x);  //最後要記得擴充增廣路
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
