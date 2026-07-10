#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
vector<int> value;
vector<vector<int>> tree;

// subtreeWeight[node] = Sum of values in the subtree of 'node'
// (with respect to the current root)
vector<ll> subtreeWeight;

// currentAnswer = weighted distance sum for the current root
ll currentAnswer = 0;

// maximum answer over all possible roots
ll maximumAnswer = 0;

/*
    First DFS:
    1. Compute currentAnswer for root = 0
    2. Compute subtreeWeight[] for every node
*/
void calculateInitialValues(int node, int parent, int depth)
{
    currentAnswer += 1LL * depth * value[node];

    subtreeWeight[node] = value[node];

    for (int child : tree[node])
    {
        if (child == parent)
            continue;

        calculateInitialValues(child, node, depth + 1);

        subtreeWeight[node] += subtreeWeight[child];
    }
}

/*
    Second DFS (Rerooting)

    We move the root from 'node' to each of its children.

    Suppose:
        node
         |
       child

    Let
        A = subtreeWeight[child]
        B = remaining tree

    Changes:
        1. Nodes in A become 1 closer.
        2. Nodes in B become 1 farther.
*/
void reroot(int node, int parent)
{
    maximumAnswer = max(maximumAnswer, currentAnswer);

    for (int child : tree[node])
    {
        if (child == parent)
            continue;

        //-------------------------------
        // Move root: node -> child
        //-------------------------------

        // Nodes inside child's subtree become 1 closer
        currentAnswer -= subtreeWeight[child];

        // Remove child's subtree from node
        subtreeWeight[node] -= subtreeWeight[child];

        // Remaining nodes become 1 farther
        currentAnswer += subtreeWeight[node];

        // Child now contains the whole tree
        subtreeWeight[child] += subtreeWeight[node];

        reroot(child, node);

        //-------------------------------
        // Restore original state
        //-------------------------------

        subtreeWeight[child] -= subtreeWeight[node];

        currentAnswer -= subtreeWeight[node];

        subtreeWeight[node] += subtreeWeight[child];

        currentAnswer += subtreeWeight[child];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    value.resize(n);
    subtreeWeight.assign(n, 0);
    tree.assign(n, {});

    for (int i = 0; i < n; i++)
        cin >> value[i];

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;

        --u;
        --v;

        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    // Root the tree at node 0
    calculateInitialValues(0, -1, 0);

    // Try every node as root
    reroot(0, -1);

    cout << maximumAnswer << '\n';

    return 0;
}