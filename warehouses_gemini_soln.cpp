#include <bits/stdc++.h>
using namespace std;

const int INF = 1e8;

// Direction arrays for Up, Down, Left, Right
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void solve() {
    int h, w, C;
    if (!(cin >> h >> w >> C)) return;

    vector<vector<int>> grid(h, vector<int>(w));
    pair<int, int> G_pos, A_pos;
    vector<pair<int, int>> W;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) G_pos = {i, j};
            else if (grid[i][j] == 3) W.push_back({i, j});
            else if (grid[i][j] == 4) A_pos = {i, j};
        }
    }

    int num_W = W.size();
    
    // Lambda to run BFS and return a 2D distance grid from a starting point
    auto get_distances = [&](pair<int, int> start) {
        vector<vector<int>> dist(h, vector<int>(w, INF));
        queue<pair<int, int>> q;
        q.push(start);
        dist[start.first][start.second] = 0;
        
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < h && nc >= 0 && nc < w && grid[nr][nc] != 1) {
                    if (dist[nr][nc] == INF) {
                        dist[nr][nc] = dist[r][c] + 1;
                        q.push({nr, nc});
                    }
                }
            }
        }
        return dist;
    };

    // 1. Precompute all-pairs shortest paths
    vector<vector<int>> dist_from_G = get_distances(G_pos);
    vector<vector<int>> dist_from_A = get_distances(A_pos);
    
    vector<vector<vector<int>>> dist_from_W(num_W);
    for (int i = 0; i < num_W; ++i) {
        dist_from_W[i] = get_distances(W[i]);
    }

    int distGA = dist_from_G[A_pos.first][A_pos.second];
    vector<int> distG(num_W), distA(num_W);
    vector<vector<int>> distWW(num_W, vector<int>(num_W));

    for (int i = 0; i < num_W; ++i) {
        distG[i] = dist_from_G[W[i].first][W[i].second];
        distA[i] = dist_from_A[W[i].first][W[i].second];
        for (int j = 0; j < num_W; ++j) {
            distWW[i][j] = dist_from_W[i][W[j].first][W[j].second];
        }
    }

    // Edge case: No warehouses to deliver
    if (num_W == 0) {
        cout << 0 << "\n";
        return;
    }

    int num_masks = 1 << num_W;
    vector<vector<int>> dpG(num_masks, vector<int>(num_W, INF));
    vector<vector<int>> dpA(num_masks, vector<int>(num_W, INF));
    vector<int> costG(num_masks, INF), costA(num_masks, INF);

    // 2. Base Cases for single trips (First stop is a warehouse)
    for (int i = 0; i < num_W; ++i) {
        if (distG[i] != INF) dpG[1 << i][i] = distG[i] * 1; 
        if (distA[i] != INF) dpA[1 << i][i] = distA[i] * 1; 
    }

    // 3. TSP DP to build single trips
    for (int mask = 1; mask < num_masks; ++mask) {
        int goods_carried = __builtin_popcount(mask);
        for (int u = 0; u < num_W; ++u) {
            if (!(mask & (1 << u))) continue;

            for (int v = 0; v < num_W; ++v) {
                if (!(mask & (1 << v))) {
                    int nmask = mask | (1 << v);
                    int multiplier = goods_carried + 1;
                    
                    if (dpG[mask][u] != INF && distWW[u][v] != INF) {
                        dpG[nmask][v] = min(dpG[nmask][v], dpG[mask][u] + distWW[u][v] * multiplier);
                    }
                    if (dpA[mask][u] != INF && distWW[u][v] != INF) {
                        dpA[nmask][v] = min(dpA[nmask][v], dpA[mask][u] + distWW[u][v] * multiplier);
                    }
                }
            }
        }
    }

    // 4. Finalize single trip costs by driving to the Airport
    for (int mask = 1; mask < num_masks; ++mask) {
        int goods_carried = __builtin_popcount(mask);
        int multiplier = goods_carried + 1;
        for (int u = 0; u < num_W; ++u) {
            if (!(mask & (1 << u))) continue;
            
            if (dpG[mask][u] != INF && distA[u] != INF) {
                costG[mask] = min(costG[mask], dpG[mask][u] + distA[u] * multiplier);
            }
            if (dpA[mask][u] != INF && distA[u] != INF) {
                costA[mask] = min(costA[mask], dpA[mask][u] + distA[u] * multiplier);
            }
        }
    }

    // 5. Submask DP to allow multiple trips starting and ending at Airport
    vector<int> optA(num_masks, INF);
    optA[0] = 0;
    for (int mask = 1; mask < num_masks; ++mask) {
        optA[mask] = costA[mask];
        // Iterate over all valid submasks
        for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
            if (optA[sub] != INF && costA[mask ^ sub] != INF) {
                optA[mask] = min(optA[mask], optA[sub] + costA[mask ^ sub]);
            }
        }
    }

    // 6. Combine the initial trip (from Garage) with subsequent trips (from Airport)
    vector<int> final_dp(num_masks, INF);
    final_dp[0] = 0; 
    
    for (int mask = 1; mask < num_masks; ++mask) {
        final_dp[mask] = costG[mask]; 
        for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
            if (costG[sub] != INF && optA[mask ^ sub] != INF) {
                final_dp[mask] = min(final_dp[mask], costG[sub] + optA[mask ^ sub]);
            }
        }
        // Consider the edge case where the very first trip from G to A is completely empty
        if (distGA != INF && optA[mask] != INF) {
            final_dp[mask] = min(final_dp[mask], distGA + optA[mask]);
        }
    }

    // 7. Find the maximum goods successfully delivered within budget C
    int max_goods = 0;
    for (int mask = 0; mask < num_masks; ++mask) {
        if (final_dp[mask] <= C) {
            max_goods = max(max_goods, __builtin_popcount(mask));
        }
    }

    cout << max_goods << "\n";
}

int main() {
    // Fast I/O for CP
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
