#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 200005;

vector<int> g[N];
ll a[N], sub[N], dp[N], tot, ans;

void dfs1(int u, int p, int d) {
    sub[u] = a[u];
    dp[1] += 1LL * d * a[u];

    for (int v : g[u]) {
        if (v == p) continue;
        dfs1(v, u, d + 1);
        sub[u] += sub[v];
    }
}

void dfs2(int u, int p) {
    ans = max(ans, dp[u]);

    for (int v : g[u]) {
        if (v == p) continue;
        dp[v] = dp[u] + tot - 2 * sub[v];
        dfs2(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tot += a[i];
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs1(1, 0, 0);
    dfs2(1, 0);

    cout << ans;
}