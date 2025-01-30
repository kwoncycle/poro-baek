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

ll DP[310][310][310][2];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> v(1, 0);
    ll ans = 0;
    for(int i=0; i<n; i++){
        int a; cin >> a;
        if(a == 0) ans += m;
        else v.push_back(a);
    }

    sort(v.begin(), v.end());
    n = v.size();
    
    ll mx = 0;
    for(int t=1; t<=n; t++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                DP[t][i][j][0] = 0x3f3f3f3f;
                DP[t][i][j][1] = 0x3f3f3f3f;
            }
        }
        for(int i=0; i<n; i++){
            if(v[i] == 0){
                DP[t][i][i][0] = 0;
                DP[t][i][i][1] = 0;
            }
        }

        for(int i=1; i<t; i++){
            for(int j=0; j+i<n; j++){
                DP[t][j][i+j][0] = min(DP[t][j+1][i+j][0] + (t-i)*(abs(v[j]-v[j+1])), DP[t][j+1][i+j][1] + (t-i)*(abs(v[j]-v[i+j])));
                DP[t][j][i+j][1] = min(DP[t][j][i+j-1][1] + (t-i)*(abs(v[i+j]-v[i+j-1])), DP[t][j][i+j-1][0] + (t-i)*(abs(v[i+j]-v[j])));
            }
        }

        for(int i=0; i+t-1<n; i++){
            mx = max(mx, m*t-DP[t][i][i+t-1][0]);
            mx = max(mx, m*t-DP[t][i][i+t-1][1]);
        }
    }

    mx -= m;
    mx += ans;
    cout << mx << "\n";
    return 0;
}