#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define lw -0x3f3f3f3f3f3fll

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<array<ll, 2>> v(m+1);
    for(int i=1; i<=m; i++) cin >> v[i][0] >> v[i][1];

    vector<vector<array<ll, 5>>> DP(n+1, vector<array<ll, 5>>(m+1, {lw,lw,lw,lw,lw}));
    // DP[i][j] : i개 고르고 j번째 index

    DP[0][0][0] = 0;
    for(int j=1; j<=m; j++){
        for(int i=0; i<=n; i++){
            // 0
            ll o = DP[i][j][0];
            if(j - 1 >= 0) o = max(o, DP[i][j-1][0]);
            if(i - 1 >= 0 and j - 1 >= 0) o = max(o, DP[i-1][j-1][0]);
            if(i - 1 >= 0 and j - 1 >= 0) o = max(o, DP[i-1][j-1][1] - (v[j][0] + v[j][1]));
            if(i - 1 >= 0 and j - 1 >= 0) o = max(o, DP[i-1][j-1][2] + (v[j][0] + v[j][1]));
            if(i - 1 >= 0 and j - 1 >= 0) o = max(o, DP[i-1][j-1][3] - (v[j][0] - v[j][1]));
            if(i - 1 >= 0 and j - 1 >= 0) o = max(o, DP[i-1][j-1][4] + (v[j][0] - v[j][1]));
            DP[i][j][0] = o;

            // 1
            o = DP[i][j][1];
            if(j - 1 >= 0) o = max(o, DP[i][j-1][0] + (v[j][0] + v[j][1]));
            if(j - 1 >= 0) o = max(o, DP[i][j-1][1]);
            DP[i][j][1] = o;

            // 2
            o = DP[i][j][2];
            if(j - 1 >= 0) o = max(o, DP[i][j-1][0] - (v[j][0] + v[j][1]));
            if(j - 1 >= 0) o = max(o, DP[i][j-1][2]);
            DP[i][j][2] = o;

            // 3
            o = DP[i][j][3];
            if(j - 1 >= 0) o = max(o, DP[i][j-1][0] + (v[j][0] - v[j][1]));
            if(j - 1 >= 0) o = max(o, DP[i][j-1][3]);
            DP[i][j][3] = o;

            // 4
            o = DP[i][j][4];
            if(j - 1 >= 0) o = max(o, DP[i][j-1][0] - (v[j][0] - v[j][1]));
            if(j - 1 >= 0) o = max(o, DP[i][j-1][4]);
            DP[i][j][4] = o;
        }
    }

    cout << DP[n][m][0] << "\n";
    return 0;
}