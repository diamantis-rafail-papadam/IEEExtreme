#include <bits/stdc++.h>
#define endl '\n'
#define MOD (ll)(1e9 + 7)
#define MAX_SIZE 1e6

typedef long long int ll;
using namespace std;

int main() {
    ll N, M, el, maximum = 0, res = 0;
    cin >> N >> M;
    vector<ll> dp(MAX_SIZE + 1, 1);
    for(int i = 1; i <= MAX_SIZE; i++) dp[i] = ((2 * dp[i-1]) % MOD);
    for(int i = 0; i < N; i++) {
        cin >> el;
        res = (res + dp[el]) % MOD;
        maximum = max(maximum, el);
    }
    cout << (M == 1 ? res : dp[maximum]) << endl;

    return 0;
}