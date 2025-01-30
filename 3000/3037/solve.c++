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

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

#define MOD 1000000007

int DP[1001][10001];
int DP_sm[1001][10001];
// DP[i][j]: 1~i개 사용 혼란 j개
// DP_sm[i][j]: \sum DP[i][0] .. DP[i][j]

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, c;
    cin >> n >> c;
    DP[1][0] = 1;
    for(int j=0; j<=c; j++){
        DP_sm[1][j] = (j-1>=0 ? DP_sm[1][j-1] : 0) + DP[1][j];
    }
    for(int i=2; i<=n; i++){
        for(int j=0; j<=c; j++){
            DP[i][j] = DP_sm[i-1][j] - (j-(i-1)-1>=0 ? DP_sm[i-1][j-(i-1)-1] : 0);
            DP[i][j] %= MOD; 
            DP_sm[i][j] = (j-1>=0 ? DP_sm[i][j-1] : 0) + DP[i][j];
            DP_sm[i][j] %= MOD;
        }
    }

    if(DP[n][c] < 0) DP[n][c] += MOD;
    cout << DP[n][c] << "\n";
    return 0;
}