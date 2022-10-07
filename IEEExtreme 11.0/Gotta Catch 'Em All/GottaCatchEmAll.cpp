#include <bits/stdc++.h>
#define endl '\n'

typedef long long int ll;
using namespace std;

int solve1(vector<vector<int>>& map, int i, int j) { //O(2 ^ (r + c - 2))
    int r = map.size(), c = map[i].size();
    if(i == r || j == c)
        return INT_MAX;
    if(i == r - 1 && j == c - 1)
        return 1;
    int down = solve1(map, i + 1, j);
    int right = solve1(map, i, j + 1);
    return max(min(down, right) - map[i][j], 1);
}

int solve2(vector<vector<int>>& map, int i, int j, vector<vector<int>>& dp) { //O(r * c)
    int r = map.size(), c = map[i].size();
    if(i == r || j == c)
        return INT_MAX;
    if(i == r - 1 && j == c - 1)
        return 1;
    if(dp[i][j] != -1)
        return dp[i][j];
    int down = solve2(map, i + 1, j, dp);
    int right = solve2(map, i, j + 1, dp);
    return dp[i][j] = max(min(down, right) - map[i][j], 1);
}

int solve3(vector<vector<int>>& map) { //O(r * c)
    int r = map.size(), c = map[0].size();
    vector<vector<int>> res(r, vector<int>(c));
    for(int i = r - 1; i >= 0; i--) {
        for(int j = c - 1; j >= 0; j--) {
            if(i == r - 1 && j == c - 1)
                res[i][j] = 1;
            else if(i == r - 1)
                res[i][j] = max(res[i][j+1] - map[i][j], 1);
            else if(j == c - 1)
                res[i][j] = max(res[i+1][j] - map[i][j], 1);
            else
                res[i][j] = max(min(res[i][j+1], res[i+1][j]) - map[i][j], 1);
        }
    }
    return res[0][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c;
    cin >> r >> c;
    vector<vector<int>> map(r, vector<int>(c));
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            cin >> map[i][j];

    //solution 1
    //int ans = solve1(map, 0, 0);

    //solution 2
    //vector<vector<int>> dp(r, vector<int>(c, -1));
    //int ans = solve2(map, 0, 0, dp);

    //solution 3
    int ans = solve3(map);

    cout << ans << endl;
    return 0;
}
