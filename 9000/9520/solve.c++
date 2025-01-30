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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<vector<ll>> v(n, vector<ll>(n, 0));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) cin >> v[i][j];
    }

    vector<vector<ll>> DP(n, vector<ll>(n, 0x3f3f3f3f3f3f));
    DP[0][0] = 0;
    DP[0][1] = v[0][1];
    DP[1][0] = v[1][0];
    for(int i=1; i<n; i++){
        for(int j=0; j<i-1; j++){
            DP[i][j] = min(DP[i][j], DP[i-1][j] + v[i][i-1]);
            DP[j][i] = min(DP[j][i], DP[i][j]);
            DP[i][j] = DP[j][i];
        }

        for(int j=0; j<i-1; j++){
            DP[i][i-1] = min(DP[i][i-1], v[i][j] + DP[j][i-1]);
            DP[i-1][i] = min(DP[i-1][i], DP[i][i-1]);
            DP[i][i-1] = DP[i-1][i];
        }
    }
    
    ll mn = 0x3f3f3f3f3f3f;
    for(int i=0; i<n; i++) mn = min(mn, DP[i][n-1]);
    cout << mn << "\n";
    return 0;
}