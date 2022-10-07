#include <bits/stdc++.h>
#define endl '\n'

typedef long long int ll;
using namespace std;

pair<bool, vector<int>> solve1(vector<vector<int>>& customers, int pos, unordered_set<int>& not_occupied, vector<int>& dates) { //O(N!)
    if(pos == customers.size())
        return make_pair(not_occupied.empty(), dates);

    pair<bool, vector<int>> res = make_pair(false, dates);
    for(int i = customers[pos][1]; i <= customers[pos][0]; i++) {
        if(not_occupied.find(i) != not_occupied.end()) {
            dates[i-1] = customers[pos][2];
            not_occupied.erase(i);
            pair<bool, vector<int>> curr = solve1(customers, pos+1, not_occupied, dates);
            if(curr.first) res = curr;
            not_occupied.insert(i);
        }
    }

    return res;
}

void solve2(vector<vector<int>>& customers, unordered_set<int>& not_occupied, vector<int>& dates) { //O(N^2)
    sort(customers.begin(), customers.end());
    for(int i = 0; i < customers.size(); i++) {
        for(int j = customers[i][1]; j <= customers[i][0]; j++) {
            if(not_occupied.find(j) != not_occupied.end()) {
                dates[j-1] = customers[i][2];
                not_occupied.erase(j);
                break;
            }
        }
    }
}

void solve3(vector<vector<int>>& customers, set<int>& not_occupied, vector<int>& dates) { //O(N*logN)
    sort(customers.begin(), customers.end());
    for(int i = 0; i < customers.size(); i++) {
        auto it = not_occupied.lower_bound(customers[i][1]);
        if(it == not_occupied.end() || *it > customers[i][0])
            break;
        else {
            dates[*it - 1] = customers[i][2];
            not_occupied.erase(it);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--) {
        int n, li, ri;
        cin >> n;
        vector<vector<int>> customers;
        vector<int> dates(n, -1);
        set<int> not_occupied;
        for(int i = 0; i < n; i++) {
            cin >> li >> ri;
            customers.push_back({ri, li, i+1});
            not_occupied.insert(i+1);
        }

        //vector<vector<bool>> visited(n, vector<bool>(n, false));
        //pair<bool, vector<int>> ans = solve1(customers, 0, not_occupied, dates);
        //if(ans.first) dates = ans.second;
        //solve2(customers, not_occupied, dates);
        solve3(customers, not_occupied, dates);
        if(/*ans.first*/not_occupied.empty()) {
            for(int date : dates) {
                cout << date << " ";
            }
        } else {
            cout << "impossible";
        }
        cout << endl;
    }

    return 0;
}
