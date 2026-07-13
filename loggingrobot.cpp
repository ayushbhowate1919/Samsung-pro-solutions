#include <bits/stdc++.h>
using namespace std;

void solve() {
    int roadLength;
    cin >> roadLength;

    // height -> list of positions having that height
    map<int, vector<int>> heightPositions;

    int maxHeight = 0;

    // Input for positions 1...(roadLength-1)
    for (int position = 1; position < roadLength; position++) {
        int leftHeight, rightHeight;
        cin >> leftHeight >> rightHeight;

        if (leftHeight != 0) {
            heightPositions[leftHeight].push_back(position);
            maxHeight = max(maxHeight, leftHeight);
        }

        if (rightHeight != 0) {
            heightPositions[rightHeight].push_back(position);
            maxHeight = max(maxHeight, rightHeight);
        }
    }

    // Cost required to process all trees of a particular height
    // = number of trees + (rightmost - leftmost)
    vector<int> groupCost(maxHeight + 1, 0);

    for (auto &entry : heightPositions) {
        auto &positions = entry.second;
        sort(positions.begin(), positions.end());

        int cost = positions.size();

        for (int i = 1; i < (int)positions.size(); i++)
            cost += positions[i] - positions[i - 1];

        groupCost[entry.first] = cost;
    }

    // dp[height][position]
    // Minimum remaining cost if we are currently at 'position'
    // and have to process all heights <= height.
    vector<vector<int>> dp(maxHeight + 1,
                           vector<int>(roadLength + 1, -1));

    function<int(int, int)> dfs = [&](int currentHeight, int currentPosition) {

        // No more heights left.
        if (currentHeight == 0)
        // go to end from wherever you are ; 
            return roadLength - currentPosition;

        // Skip heights that don't exist.
        if (heightPositions.find(currentHeight) == heightPositions.end())
            return dfs(currentHeight - 1, currentPosition);

        int &answer = dp[currentHeight][currentPosition];
        if (answer != -1)
            return answer;

        vector<int> &positions = heightPositions[currentHeight];

        int leftMost = positions.front();
        int rightMost = positions.back();

        // Enter from left, finish at right.
        int option1 =
            abs(currentPosition - leftMost) +
            groupCost[currentHeight] +
            dfs(currentHeight - 1, rightMost);

        // Enter from right, finish at left.
        int option2 =
            abs(currentPosition - rightMost) +
            groupCost[currentHeight] +
            dfs(currentHeight - 1, leftMost);

        return answer = min(option1, option2);
    };
   
    // start from maxHeight from posn 0 ; 
    cout << dfs(maxHeight, 0) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}