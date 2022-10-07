#include <bits/stdc++.h>
#define endl '\n'

typedef long long int ll;
using namespace std;

bool cycle(vector<vector<int>>& adjList, vector<bool>& visited, set<int>& available, int prev, int curr) {
    if(visited[curr])
        return true;

    visited[curr] = true;
    available.erase(curr);
    int res = false;
    for(int child : adjList[curr])
        if(child != prev)
            res = res || cycle(adjList, visited, available, curr, child);

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--) {
        int n, m, v1, v2;
        bool res = false;
        cin >> n >> m;
        vector<vector<int>> adjList(n);
        set<int> available;
        vector<bool> visited(n);
        for(int i = 0; i < m; i++) {
            cin >> v1 >> v2;
            adjList[v1].push_back(v2);
            adjList[v2].push_back(v1);
        }
        for(int i = 0; i < n; i++) available.insert(i);
        while(!available.empty()) {
            for(int j = 0; j < n; j++) visited[j] = false;
            int node = *available.begin();
            res = res || cycle(adjList, visited, available, -1, node);
            available.erase(node);
        }
        cout << res << endl;
    }

    return 0;
}