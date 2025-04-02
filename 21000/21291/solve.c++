#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s; cin >> s;
    int n = s.size();
    vector<vector<ll>> DP(n, vector<ll>(n, 0x3f3f3f3f));
    for(int d=1; d<=n; d++){
        for(int i=0; i+d-1<n; i++){
            int j = i+d-1;
            if(i == j){
                DP[i][j] = 1; continue;
            }
            for(int k=i; k+1<=j; k++){
                DP[i][j] = min(DP[i][j], DP[i][k] + DP[k+1][j]);
            }
            if(s[i] == 'A' and s[j] == 'C'){
                for(int k=i+1; k<j; k++){
                    if(s[k] == 'B'){
                        DP[i][j] = min(DP[i][j], 1 + (i+1<=k-1 ? DP[i+1][k-1] : 0) + (k+1<=j-1 ? DP[k+1][j-1] : 0));
                    }
                }
            }
        }
    }

    cout << DP[0][n-1] << "\n";
    return 0;
}