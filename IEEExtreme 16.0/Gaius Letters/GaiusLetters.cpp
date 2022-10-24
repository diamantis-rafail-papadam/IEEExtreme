#include <bits/stdc++.h>
#define endl '\n'
#define ROTKEY 14

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s, res = "";
    getline(cin, s);
    for(int i = 0; i < s.size(); i++) {
        bool lc = (s[i] >= 'a' && s[i] <= 'z');
        bool uc = (s[i] >= 'A' && s[i] <= 'Z');
        bool letter = lc || uc;
        int mod = 26;
        if(letter) {
            int offset = lc ? 'a' : 'A';
            int dec = (s[i] - offset + ROTKEY) % 26;
            if(dec < 0) dec += 26;
            dec = dec % 26 + offset;
            res += dec;
        } else {
            res += s[i];
        }
    }

    cout << res << endl;

    return 0;
}