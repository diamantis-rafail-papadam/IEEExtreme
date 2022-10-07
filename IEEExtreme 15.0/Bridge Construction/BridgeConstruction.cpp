#include <bits/stdc++.h>
#define endl '\n'

typedef long long int ll;
using namespace std;

void addEdge(vector<vector<int>>& adjList, int x, int y) {
    adjList[x].push_back(y);
    adjList[y].push_back(x);
}

int calcDepth(vector<vector<int>>& island, int dad, int node) {
    int res = 0;
    for(int child : island[node])
        if(child != dad)
            res = max(res, calcDepth(island, node, child) + 1);
    return res;
}

int findMax(vector<int>& depth) {
    int res = INT_MIN;
    for(int d : depth)
        res = max(res, d);
    return res;
}

pair<int, int> findMinIndex(vector<int>& depth) {
    int minimum = INT_MAX;
    int min_index = -1;
    for(int i = 0; i < depth.size(); i++) {
        if(depth[i] < minimum) {
            minimum = depth[i];
            min_index = i + 1;
        }
    }
    return make_pair(min_index, minimum);
}

vector<int> solve1(vector<vector<int>>& island1, vector<vector<int>>& island2) { //O(N1^2 + N2^2)
    int n1 = island1.size(), n2 = island2.size();
    vector<int> depth1(n1, INT_MAX), depth2(n2, INT_MAX);
    for(int i = 0; i < n1; i++) {
        vector<bool> visited1(n1, false);
        depth1[i] = calcDepth(island1, -1, i);
    }
    for(int i = 0; i < n2; i++) {
        vector<bool> visited2(n2, false);
        depth2[i] = calcDepth(island2, -1, i);
    }

    int max1 = findMax(depth1);
    int max2 = findMax(depth2);
    pair<int, int> min1 = findMinIndex(depth1);
    pair<int, int> min2 = findMinIndex(depth2);
    return {max(min1.second + min2.second + 1, max(max1, max2)), min1.first, min2.first};
}

vector<int> findMid(vector<vector<int>>& island) { //This function is based on this video "https://www.youtube.com/watch?v=nzF_9bjDzdc"
    int n = island.size();
    vector<int> degree(n);
    vector<int> leaves;
    for(int i = 0; i < n; i++) {
        degree[i] = island[i].size();
        if(degree[i] == 1) leaves.push_back(i);
    }
    int c = n - leaves.size();
    while(c) {
        vector<int> new_leaves;
        for(int leaf : leaves) {
            for(int neighbour : island[leaf]) if(--degree[neighbour] == 1) new_leaves.push_back(neighbour);
            degree[leaf] = 0;
        }
        leaves.clear();
        for(int new_leaf : new_leaves) leaves.push_back(new_leaf);
        c -= leaves.size();
    }
    return leaves;
}

vector<int> solve2(vector<vector<int>>& island1, vector<vector<int>>& island2) { //O(N1 + N2)
    vector<int> mid1 = findMid(island1);
    vector<int> mid2 = findMid(island2);
    int d1 = calcDepth(island1, -1, mid1[0]);
    int d2 = calcDepth(island2, -1, mid2[0]);
    return {max(d1 + d2 + 1, max(2*d1 - (mid1.size()==2), 2*d2 - (mid2.size()==2))), mid1[0]+1, mid2[0]+1};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--) {
        int n1, n2, x, y;
        cin >> n1;
        vector<vector<int>> island1(n1);
        for(int i = 0; i < n1 - 1 ; i++) {
            cin >> x >> y;
            addEdge(island1, x-1, y-1);
        }
        cin >> n2;
        vector<vector<int>> island2(n2);
        for(int i = 0; i < n2 - 1; i++) {
            cin >> x >> y;
            addEdge(island2, x-1, y-1);
        }

        //vector<int> ans = solve1(island1, island2);
        vector<int> ans = solve2(island1, island2);

        cout << ans[0] << endl;
        cout << ans[1] << " " << ans[2] << endl;
    }

    return 0;
}