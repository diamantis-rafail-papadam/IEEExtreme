#include <bits/stdc++.h>
#define endl '\n'

typedef unsigned long long int ll;
using namespace std;

vector<ll> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47}; //we could also use the "Sieve of Eratosthenes" to find these prime numbers but I don't believe this is the point of this particular problem.

int calc_gold(ll id) {
    int gold = 0;
    while(id > 0) id /= primes[gold++];
    return --gold;
}

void ucs(map<ll, vector<pair<int, ll>>>& g, ll source, ll dest, map<ll, int>& dist, map<ll, ll>& prev) {
    priority_queue<pair<int, ll>, vector<pair<int, ll>>, greater<pair<int, ll>>> pq;
    dist[source] = 0;
    prev[source] = 0;
    pq.push(make_pair(0, source));

    while(!pq.empty()) {
        pair<int, ll> node = pq.top(); pq.pop();
        if(node.second == dest) break;
        for(pair<int, ll> child : g[node.second]) {
            if(node.first + child.first < dist[child.second]) {
                dist[child.second] = node.first + child.first;
                pq.push(make_pair(node.first + child.first, child.second));
                prev[child.second] = node.second;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, d, res = 0;
    ll k, x, y;
    ll source = ULLONG_MAX, dest = 0;
    map<ll, vector<pair<int, ll>>> g;
    map<ll, int> dist;
    map<ll, ll> prev;
    vector<ll> in;

    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> k;
        dist[k] = INT_MAX;
        in.push_back(k);
        source = min(source, k);
        dest = max(dest, k);
    }

    for(int i = 0; i < m; i++) {
        cin >> x >> y >> d;
        g[x].push_back(make_pair(d, y));
        g[y].push_back(make_pair(d, x));
    }

    ucs(g, source, dest, dist, prev);
    ll s = dest;
    while(prev[s] != 0) {
        res += calc_gold(s);
        s = prev[s];
    }
    res += calc_gold(source);
    cout << res << endl;

    return 0;
}
