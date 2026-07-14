
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<string> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    const int NEG = -1e9;
    vector<vector<int>> dp(10, vector<int>(10, NEG));

    for (auto &s : arr) {
        int x = s.front() - '0';
        int y = s.back() - '0';
        int len = (int)s.size();

        vector<vector<int>> ndp = dp;

        // Start a new chain with this string
        ndp[x][y] = max(ndp[x][y], len);

        // Extend previous chains
        for (int start = 0; start < 10; start++) {
            if (dp[start][x] != NEG) {
                ndp[start][y] = max(ndp[start][y], dp[start][x] + len);
            }
        }

        dp.swap(ndp);
    }

    int ans = 0;
    for (int d = 0; d < 10; d++) {
        ans = max(ans, dp[d][d]);
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}