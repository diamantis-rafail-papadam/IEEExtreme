#include <bits/stdc++.h>
#define endl '\n'

typedef long long int ll;
using namespace std;

void buildGraph(vector<vector<double>>& rm, vector<vector<double>>& em, vector<vector<vector<pair<double, vector<int>>>>>& adjList) {
    int n = rm.size(), m = rm[0].size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i > 0) {
                double cost_up = ((rm[i][j] + rm[i-1][j]) / 2) * exp(3.5 * abs((em[i-1][j] - em[i][j]) / 10 + 0.05));
                vector<int> up = {i-1, j};
                adjList[i][j].push_back(make_pair(cost_up, up));
            }
            if(j > 0) {
                double cost_left = ((rm[i][j] + rm[i][j-1]) / 2) * exp(3.5 * abs((em[i][j-1] - em[i][j]) / 10 + 0.05));
                vector<int> left = {i, j-1};
                adjList[i][j].push_back(make_pair(cost_left, left));
            }
            if(i < n - 1) {
                double cost_down = ((rm[i][j] + rm[i+1][j]) / 2) * exp(3.5 * abs((em[i+1][j] - em[i][j]) / 10 + 0.05));
                vector<int> down = {i+1, j};
                adjList[i][j].push_back(make_pair(cost_down, down));
            }
            if(j < m - 1) {
                double cost_right = ((rm[i][j] + rm[i][j+1]) / 2) * exp(3.5 * abs((em[i][j+1] - em[i][j]) / 10 + 0.05));
                vector<int> right = {i, j+1};
                adjList[i][j].push_back(make_pair(cost_right, right));
            }
        }
    }
}

/**
 * This function is an optimized version of dijkstra's algorithm known as uniform cost search.
 */
void ucs(vector<vector<vector<pair<double, vector<int>>>>>& adjList, vector<int>& source, vector<int>& dest, vector<vector<double>>& dist) {
    priority_queue<pair<double, vector<int>>, vector<pair<double, vector<int>>>, greater<pair<double, vector<int>>>> pq;
    dist[source[0]][source[1]] = 0;
    pq.push(make_pair(0, source));

    while(!pq.empty()) {
        pair<double, vector<int>> node = pq.top(); pq.pop();
        if(node.second == dest) break;
        for(pair<double, vector<int>> child : adjList[node.second[0]][node.second[1]]) {
            if(node.first + child.first < dist[child.second[0]][child.second[1]]) {
                dist[child.second[0]][child.second[1]] = node.first + child.first;
                pq.push(make_pair(node.first + child.first, child.second));
            }
        }
    }
}

double solve(vector<vector<vector<pair<double, vector<int>>>>>& adjList, vector<vector<int>>& cp) {
    int n = adjList.size(), m = adjList[0].size();
    double res = 0;
    for(int i = 0; i < cp.size() - 1; i++) {
        vector<vector<double>> dist(n, vector<double>(m, DBL_MAX));
        ucs(adjList, cp[i], cp[i+1], dist);
        res += dist[cp[i+1][0]][cp[i+1][1]];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, p;
    cin >> n >> m >> p;
    vector<vector<int>> cp(++p, vector<int>(2)); //we will put the initial position in the control points.
    vector<vector<double>> rm(n, vector<double>(m));
    vector<vector<double>> em(n, vector<double>(m));
    vector<vector<vector<pair<double, vector<int>>>>> adjList(n, vector<vector<pair<double, vector<int>>>>(m));
    for(int i = 0; i < p; i++) cin >> cp[i][0] >> cp[i][1];
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> rm[i][j];
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> em[i][j];
    buildGraph(rm, em, adjList);

    int res = ceil(solve(adjList, cp));
    cout << res << endl;

    return 0;
}