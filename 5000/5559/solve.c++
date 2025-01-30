#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define X first
#define Y second
#define GETVECTOR(n) for(int i=0; i< (n); i++) scanf("%d ",&inp[i]);
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using complex_t = complex<double>;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int m, n; cin >> m >> n;
    vector<vector<int>> v(m, vector<int>(n, 0));
    // ? : 0
    // J : 1 // O : 2 // I : 3
    for(int i=0; i<m; i++){
        string s; cin >> s;
        for(int j=0; j<n; j++) {
            if(s[j] == 'J') v[i][j] = 1;
            if(s[j] == 'O') v[i][j] = 2;
            if(s[j] == 'I') v[i][j] = 3;
        }
    }
    ll cnt = 1;
    if(v[m-1][n-1] == 0) cnt = 3;
    vector<vector<ll>> DP1(22), DP2(22), candi1(22), candi2(22);
    for(int i=2; i<=n; i++){
        for(int j=0; j<(1<<(i-1)); j++){
            if(j & (j << 1)) continue;
            int truth = 1;
            for(int k=0; k<i-1; k++){
                if(j & (1<<k)){
                    if(v[n-k-1][n+k-i] == 1 or v[n-k-1][n+k-i] == 2){
                        truth = 0; break;
                    }
                    if(v[n-k-1-1][n+k-i+1] == 1 or v[n-k-1-1][n+k-i+1] == 3){
                        truth = 0; break;
                    }
                    if(v[n-k-1-1][n+k-i] == 1){
                        truth = 0; break;
                    }
                }
            }
            if(truth) {
                candi1[i].push_back(j);
                DP1[i].push_back(0);
            }
        }
    }
    for(int i=n; i>=2; i--){
        for(int j=0; j<(1<<(i-1)); j++){
            if(j & (j << 1)) continue;
            int truth = 1;
            for(int k=0; k<i-1; k++){
                // sm = i-1
                if(j & (1<<k)){
                    if(v[i-1-k][k] == 1 or v[i-1-k][k] == 2){
                        truth = 0; break;
                    }
                    if(v[i-1-k-1][k+1] == 1 or v[i-1-k-1][k+1] == 3){
                        truth = 0; break;
                    }
                    if(v[i-1-k-1][k] == 1){
                        truth = 0; break;
                    }
                }
            }
            if(truth) {
                candi2[i].push_back(j);
                DP2[i].push_back(0);
            }
        }
    }

    for(int i=2; i<=n; i++){
        for(int j1=0; j1<(int)DP2[i].size(); j1++){
            for(int j2=0; j2<(int)DP2[i-1].size(); j2++){
                ll nj = 0, no = 0, ni = 0;
                
            }
        }
        
    }


    return 0;
}