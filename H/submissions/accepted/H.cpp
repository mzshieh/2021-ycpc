#include<bits/stdc++.h>

using namespace std;

int main() {
    static char buf[104857600] = {};
    fgets(buf, 104857600, stdin);
    int n, m, d;
    sscanf(buf, "%d %d %d",&n, &m, &d);
    unordered_set<string> training;
    for (int i = 0; i < n; i++) {
        fgets(buf, 104857600, stdin);
        training.insert(string(buf));
    }
    for (int i = 0; i < m; i++) {
        fgets(buf, 104857600, stdin);
        if (training.count(string(buf))) puts("BAD");
        else puts("GOOD");
    }
    return 0;
}
