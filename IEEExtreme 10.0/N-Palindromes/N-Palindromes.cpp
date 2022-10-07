#include <bits/stdc++.h>
#define endl '\n'
#define MOD 1000000007

typedef long long ll;
using namespace std;

ll dp[501][251][251] = {0};

int count_dif(string s, int mid) {
    int dif = 0;
    for(int i = 1; i <= mid; i++) dif += (s[i - 1] != s[s.size() - i]);
    return dif;
}

ll solve(string s, int n, int k, int d) {
    if(n < 0 || k < 0 || d < 0)          return 0;
    if(n == 0 && k == 0 && d == 0)       return 1;
    if(dp[n][k][d] != -1)                return dp[n][k][d];
    if(k - 1 == s.size() - k)            return dp[n][k][d] = (25 * solve(s, n-1, k-1, d) + solve(s, n, k-1, d)) % MOD;
    if(s[k - 1] == s[s.size() - k])      return dp[n][k][d] = (25 * solve(s, n-2, k-1, d) + solve(s, n, k-1, d)) % MOD;
    else                                 return dp[n][k][d] = (24 * solve(s, n-2, k-1, d-1) + 2 * solve(s, n-1, k-1, d-1)) % MOD;
}

ll solve_iterative(string s, int N, int K, int D) {
    dp[0][0][0] = 1;
    for(int n = 0; n <= N; n++) {
        for(int k = 1; k <= K; k++) {
            for(int d = 0; d <= D; d++) {
                if(k - 1 == s.size() - k) {
                    dp[n][k][d] = dp[n][k-1][d];
                    if(n > 0) dp[n][k][d] += 25*dp[n-1][k-1][d];
                } else if(s[k - 1] == s[s.size() - k]) {
                    dp[n][k][d] = dp[n][k-1][d];
                    if(n > 1) dp[n][k][d] += 25*dp[n-2][k-1][d];
                } else if(s[k - 1] != s[s.size() - k]) {
                    if(n > 0 && d > 0) dp[n][k][d] = 2*dp[n-1][k-1][d-1];
                    if(n > 1 && d > 0) dp[n][k][d] += 24*dp[n-2][k-1][d-1];
                }
                dp[n][k][d] %= MOD;
            }
        }
    }
    return dp[N][K][D];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--) {
        int n;
        string s;
        cin >> n >> s;
        int mid = (s.size() + 1) / 2;
        int d = count_dif(s, mid);
        for(int i = 0; i <= n; i++) for(int ii = 0; ii <= mid; ii++) for(int iii = 0; iii <= d; iii++) dp[i][ii][iii] = -1;
        ll res = solve(s, n, mid, d);
        //ll res = solve_iterative(s, n, mid, d);
        cout << res << endl;
    }

    return 0;
}