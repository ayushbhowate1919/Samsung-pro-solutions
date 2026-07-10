#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n;
    ll k;
    cin >> n >> k;

    vector<pair<ll, ll>> items; // {dailyIncrease(B), initialStock(A)}

    ll totalInitialStock = 0;
    ll totalDailyIncrease = 0;

    for (int i = 0; i < n; i++) {
        ll initialStock, dailyIncrease;
        cin >> initialStock >> dailyIncrease;

        items.push_back({dailyIncrease, initialStock});

        totalInitialStock += initialStock;
        totalDailyIncrease += dailyIncrease;
    }

    // Greedy ordering:
    // Export items having smaller daily increase first.
    sort(items.begin(), items.end());

    const ll NEG_INF = -(1LL << 60);

    // dp[i][j] =
    // Maximum stock removed after considering first i items
    // and exporting exactly j of them.
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, NEG_INF));

    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {

        ll dailyIncrease = items[i - 1].first;
        ll initialStock = items[i - 1].second;

        for (int exported = 0; exported <= i; exported++) {

            // Option 1: Don't export this item.
            dp[i][exported] = max(dp[i][exported],
                                  dp[i - 1][exported]);

            // Option 2: Export this item as the "exported-th" item.
            if (exported > 0 && dp[i - 1][exported - 1] != NEG_INF) {

                ll removedStock =
                    initialStock + dailyIncrease * exported;

                dp[i][exported] = max(
                    dp[i][exported],
                    dp[i - 1][exported - 1] + removedStock
                );
            }
        }
    }

    // Check every possible number of days.
    for (int days = 0; days <= n; days++) {

        ll stockWithoutExports =
            totalInitialStock +
            totalDailyIncrease * days;

        ll minimumPossibleStock =
            stockWithoutExports - dp[n][days];

        if (minimumPossibleStock <= k) {
            cout << days << "\n";
            return;
        }
    }

    cout << -1 << "\n";
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;

    for (int tc = 1; tc <= testCases; tc++) {

        cout << "#" << tc << " ";
        solve();
    }

    return 0;
}