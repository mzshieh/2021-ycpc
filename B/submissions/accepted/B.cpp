#include <bits/stdc++.h>
using namespace std;

namespace SuffixArray {
/*lcp[i]保存了在後綴數組中相鄰兩個後綴的最長公共前綴長度
 *sa[i]表示的是字典序排名為i的後綴是誰（字典序越小的排名越靠前）
 *rk[i]表示的是後綴我所對應的排名是多少  */

const int MAX = 2000500;
int ct[MAX], lcp[MAX], rk[MAX];
int sa[MAX], tsa[MAX], tp[MAX][2];

void suffix_array(string ip) {
    int len = ip.size();
    int alp = 256;
    fill(ct, ct + len + 256, 0);
    for (int i = 0; i < len; i++) ct[ip[i] + 1]++;
    for (int i = 1; i < alp; i++) ct[i] += ct[i - 1];
    for (int i = 0; i < len; i++) rk[i] = ct[(int)ip[i]];
    for (int i = 1; i < len; i *= 2) {
        for (int j = 0; j < len; j++) {
            if (j + i >= len)
                tp[j][1] = 0;
            else
                tp[j][1] = rk[j + i] + 1;
            tp[j][0] = rk[j];
        }
        fill(ct, ct + len + 256, 0);
        for (int j = 0; j < len; j++) ct[tp[j][1] + 1]++;
        for (int j = 1; j < len + 2; j++) ct[j] += ct[j - 1];
        for (int j = 0; j < len; j++) tsa[ct[tp[j][1]]++] = j;
        fill(ct, ct + len + 256, 0);
        for (int j = 0; j < len; j++) ct[tp[j][0] + 1]++;
        for (int j = 1; j < len + 1; j++) ct[j] += ct[j - 1];
        for (int j = 0; j < len; j++) sa[ct[tp[tsa[j]][0]]++] = tsa[j];
        rk[sa[0]] = 0;
        for (int j = 1; j < len; j++) {
            if (tp[sa[j]][0] == tp[sa[j - 1]][0] &&
                tp[sa[j]][1] == tp[sa[j - 1]][1])
                rk[sa[j]] = rk[sa[j - 1]];
            else
                rk[sa[j]] = j;
        }
    }
    for (int i = 0, h = 0; i < len; i++) {
        if (rk[i] == 0)
            h = 0;
        else {
            int j = sa[rk[i] - 1];
            h = max(0, h - 1);
            for (; ip[i + h] == ip[j + h]; h++)
                ;
        }
        lcp[rk[i]] = h;
    }
}
}  // namespace SuffixArray

namespace SparseTable {

vector<vector<int>> Sp;
int lgN;

void build(int n, int *a) {  // 0 base
    lgN = __lg(n + 1) + 1;
    Sp = vector<vector<int>>(n + 1, vector<int>(lgN));
    for (int i = 0; i < n; i++) Sp[i][0] = a[i];

    for (int h = 1; h < lgN; h++) {
        int len = 1 << (h - 1), i = 0;
        for (; i + len < n; i++)
            Sp[i][h] = min(Sp[i][h - 1], Sp[i + len][h - 1]);
        for (; i < n; i++) Sp[i][h] = Sp[i][h - 1];
    }
}
int RMQ(int l, int r) {
    int h = __lg(r - l + 1);
    int len = 1 << h;
    return min(Sp[l][h], Sp[r - len + 1][h]);
}
}  // namespace SparseTable

namespace DisjointSet {

vector<int> par;
vector<int> mn;

void init(int n) {
    par = mn = vector<int>(n);
    for (int i = 0; i < n; i++) {
        par[i] = i;
        mn[i] = i;
    }
}

int find(int x) {
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    par[x] = y;
    mn[y] = min(mn[y], mn[x]);
}

}  // namespace DisjointSet

using namespace SuffixArray;
using namespace SparseTable;
using namespace DisjointSet;

int query(int i, int j, int len) {
    int x = rk[i];
    int y = rk[j];
    if (x > y) swap(x, y);
    int l = RMQ(x + 1, y);
    if (l > len) return min(i, j);
    if (rk[i] < rk[j]) return i;
    return j;
}

int totaln = 0;
int n;
string s;

void init() {
    cin >> s;
    n = s.size();
    totaln += n;
    assert(n <= 200000);
    assert(totaln <= 2000000);
    suffix_array(s);
    build(n, lcp);
    init(n);
}

void solve() {
    vector<pair<int, int>> events;  // (lcp, pos)
    events.push_back({-1, 0});      // dummy
    for (int i = 1; i < n; i++) {
        events.push_back({lcp[i], i});
    }
    sort(events.begin(), events.end());

    vector<int> ans(n + 1);
    int pos = 0;
    for (int i = 1; i < n; i++) {
        int len = n - i;
        pos = query(pos, i, len);

        while (events.back().first >= len) {
            int y = events.back().second;
            events.pop_back();
            merge(sa[y], sa[y - 1]);
        }

        ans[len] = mn[find(pos)];
    }

    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i * (ans[i] + 1);
    }
    cout << sum << '\n';
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--) {
        init();
        solve();
    }
}
