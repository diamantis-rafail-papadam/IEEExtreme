#include <bits/stdc++.h>
#define endl '\n'

typedef long long int ll;
using namespace std;

map<pair<int, int>, ll> memo;

ll solve(vector<pair<int, int>>& stations, int i, int c, int l) {
    if(l < 0) return __LONG_LONG_MAX__;
    if(i == stations.size() - 1) return 0;
    pair<int, int> state = make_pair(i, l);
    if(memo.find(state) != memo.end()) return memo[state];
    
    ll option1 = solve(stations, i + 1, c, l - stations[i+1].first);
    ll option2 = solve(stations, i + 1, c, c - stations[i+1].first) + (c - l) * stations[i].second + 500;
    return memo[state] = min(option1, option2);
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        int s, c, f, r;
        cin >> s >> c >> r;
        ll cost = c * r;
        vector<pair<int, int>> stations;
        for(int i = 0; i < s; i++) {
            cin >> f >> r;
            stations.push_back(make_pair(f, r));
        }
        ll extra_cost = solve(stations, 0, c, c - stations[0].first);
        memo.clear();
        cout << cost + extra_cost << endl;
    }

    return 0;
}