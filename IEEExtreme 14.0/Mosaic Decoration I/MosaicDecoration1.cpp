#include <bits/stdc++.h>
#define endl '\n'

typedef long long int ll;
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, CB, CP;
    int black = 0, pink = 0, res, bi, pi;
    cin >> N >> CB >> CP;
    while(N--) {
        cin >> bi >> pi;
        black += bi;
        pink += pi;
    }
    res = ceil((double)black/10) * CB + ceil((double)pink/10) * CP;
    cout << res << endl;

    return 0;
}