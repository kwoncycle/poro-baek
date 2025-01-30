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
    while(true){
        int n; cin >> n;
        if(n < 0) break;

        vector<vector<int>> v(n, vector<int>(n, 0));
        for(int i=0; i<n; i++){
            string s; cin >> s;
            for(int j=0; j<n; j++){
                v[i][j] = s[j] - '0';
            }
        }

        vector<vector<ll>> DP(n, vector<ll>(n, 0));
        DP[0][0] = 1;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(v[i][j] == 0) continue;
                if(i + v[i][j] < n){
                    DP[i+v[i][j]][j] += DP[i][j];
                }
                if(j + v[i][j] < n){
                    DP[i][j + v[i][j]] += DP[i][j];
                }
            }
        }
        cout << DP[n-1][n-1] << "\n";
    }
    return 0;
}