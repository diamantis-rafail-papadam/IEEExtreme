#include <bits/stdc++.h>
#define endl '\n'

typedef long long int ll;
using namespace std;

vector<int> ans;

vector<int> get_ans(vector<vector<pair<string, int>>>& V, vector<int>& candidate_ans) {
    for(int i = 0; i < 5; i++) {
        if(V[i][ans[i]].first == V[i][candidate_ans[i]].first) continue;
        else if(V[i][ans[i]].first < V[i][candidate_ans[i]].first)
            return ans;
        else
            return candidate_ans;
    }
    return ans;
}

int solve(vector<vector<pair<string, int>>>& V, int B) { //O(P*G*log(S*F*C))
    map<int, vector<int>> hm1, hm2;
    int res = 0, sum = 0;
    for(int p = 0; p < V[0].size(); p++) {
        sum += V[0][p].second;
        for(int g = 0; g < V[1].size(); g++) {
            sum += V[1][g].second;
            hm1[sum] = {p, g};
            sum -= V[1][g].second;
        }
        sum -= V[0][p].second;
    }

    sum = 0;
    for(int s = 0; s < V[2].size(); s++) {
        sum += V[2][s].second;
        for(int f = 0; f < V[3].size(); f++) {
            sum += V[3][f].second;
            for(int c = 0; c < V[4].size(); c++) {
                sum += V[4][c].second;
                hm2[sum] = {s, f, c};
                sum -= V[4][c].second;
            }
            sum -= V[3][f].second;
        }
        sum -= V[2][s].second;
    }

    for(auto el : hm1) {
        int target = B - el.first;
        auto it = hm2.upper_bound(target);
        if(it == hm2.begin()) continue;
        int curr = (el.first + (--it)->first);
        if(curr <= B) {
            if(curr > res) {
                res = curr;
                ans = {el.second[0], el.second[1], (it->second)[0], (it->second)[1], (it->second)[2]};
            } else if(curr == res) {
                vector<int> candidate_ans = {el.second[0], el.second[1], (it->second)[0], (it->second)[1], (it->second)[2]};
                ans = get_ans(V, candidate_ans);
            }
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int B, size, w;
    cin >> B;
    string s;
    vector<vector<pair<string, int>>> V;
    
    for(int i = 0; i < 5; i++) {
        vector<pair<string, int>> curr_v;
        cin >> size;
        while(size--) {
            cin >> s >> w;
            curr_v.push_back(make_pair(s, w));
        }
        V.push_back(curr_v);
    }

    int res = solve(V, B);
    for(int i = 0; i < 5; i++) cout << V[i][ans[i]].first << endl;

    return 0;
}