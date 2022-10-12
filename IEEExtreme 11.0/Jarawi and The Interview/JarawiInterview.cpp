#include <bits/stdc++.h>
#define endl '\n'

typedef long long int ll;
using namespace std;

int solve1(string& s, string& p) {
    int i = s.size() - 1;
    int j = p.size() - 1;
    int res = 0;
    while(i >= 0 && j >= 0) {
        if(s[i] == p[j]) {
            i--;
            j--;
            res++;
        } else {
            i--;
        }
    }
    return res;
}

vector<vector<int>> transform(string& s) {
    vector<vector<int>> res(26);
    for(int i = 0; i < s.size(); i++) res[s[i] - 'a'].push_back(i);
    return res;
}

int solve2(string& s, string& p, vector<vector<int>>& vs) {
    int i = s.size();
    int j = p.size() - 1;
    int res = 0;
    while(j >= 0) {
        int pos = p[j] - 'a';
        auto it = lower_bound(vs[pos].begin(), vs[pos].end(), i);
        if(it == vs[pos].begin()) break;
        j--;
        it--;
        i = *it;
        res++;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s, p;
    int q;
    cin >> s >> q;
    vector<vector<int>> vs = transform(s);
    while(q--) {
        cin >> p;
        cout << solve2(s, p, vs) << endl;
    }

    return 0;
}