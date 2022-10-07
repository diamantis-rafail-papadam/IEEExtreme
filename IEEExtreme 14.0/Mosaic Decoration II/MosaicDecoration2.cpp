#include <bits/stdc++.h>
#define endl '\n'

typedef long long int ll;
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll W, H, A, B, M, C;
    ll res = 0;
    cin >> W >> H >> A >> B >> M >> C;
    ll hor = ceil((double) W / A);
    ll ver = ceil((double) H / B);
    ll tiles = hor * ver;
    res += ceil((double) tiles / 10) * M;

    ll hor_extra = hor * A - W;
    ll ver_extra = ver * B - H;
    res += (H * (hor_extra > 0) + W * (ver_extra > 0)) * C;
    
    cout << res << endl;
    return 0;
}