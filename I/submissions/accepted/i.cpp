#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

struct KM { // O(n^3) KM from sunmoon
    void init(const vector<Point> &s, const vector<Point> &t) {
        n = s.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                long long dx = s[i].x - t[j].x;
                long long dy = s[i].y - t[j].y;
                g[i][j] = -(dx * dx + dy * dy);
            }
        }
    }

    static const int MAXN = 500;
    static const long long INF = 1ll << 60;
    long long g[MAXN][MAXN], lx[MAXN], ly[MAXN], slack_y[MAXN];
    int px[MAXN], py[MAXN], match_y[MAXN], par[MAXN];
    int n;
    void adjust(int y) {
        match_y[y] = py[y];
        if (px[match_y[y]] != -2) adjust(px[match_y[y]]);
    }
    bool dfs(int x) {
        for (int y = 0; y < n; ++y) {
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
    long long km() {
        fill(ly, ly + n, 0);
        fill(match_y, match_y + n, -1);
        for (int x = 0; x < n; ++x) {
            lx[x] = -INF;
            for (int y = 0; y < n; ++y) {
                lx[x] = max(lx[x], g[x][y]);
            }
        }
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) slack_y[y] = INF;
            fill(px, px + n, -1);
            fill(py, py + n, -1);
            px[x] = -2;
            if (dfs(x)) continue;
            bool flag = 1;
            while (flag) {
                long long cut = INF;
                for (int y = 0; y < n; ++y) {
                    if (py[y] == -1 && cut > slack_y[y]) {
                        cut = slack_y[y];
                    }
                }
                for (int j = 0; j < n; ++j) {
                    if (px[j] != -1) lx[j] -= cut;
                    if (py[j] != -1)
                        ly[j] += cut;
                    else
                        slack_y[j] -= cut;
                }
                for (int y = 0; y < n; ++y) {
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
        for (int y = 0; y < n; ++y) {
            if (g[match_y[y]][y] != -INF) {
                ans += g[match_y[y]][y];
            }
        }
        return ans;
    }
};

int main() {
    int n;
    cin >> n;
    vector<Point> s(n), t(n);
    for (auto &p : s) cin >> p.x >> p.y;
    for (auto &p : t) cin >> p.x >> p.y;
    KM solver;
    solver.init(s, t);
    long long ans = -solver.km();
    cout << ans << '\n';
    return 0;
}
