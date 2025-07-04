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

int ansid[52];

double DP[52][52][2552]; // DP[i][j][k] : i개만 사용, j까지만 씀, ttl = k일 확률
double ans[52];
ll C[52][52];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    for(int i=0; i<=51; i++){
        C[i][0] = 1; C[i][i] = 1;
        for(int j=1; j<i; j++) C[i][j] = C[i-1][j-1] + C[i-1][j];
    }
    int n, K, t; cin >> n >> K >> t;
    vector<pair<double, int>> v(n+1);
    for(int i=1; i<=n; i++) cin >> v[i].X >> v[i].Y;
    for(int i=1; i<=n; i++) ansid[i] = i;
    sort(ansid+1, ansid+n+1, [&](int l, int r){
        return v[l].Y < v[r].Y;
    });
    sort(v.begin()+1, v.end(), [&](pair<double, int> l, pair<double, int> r){
        return l.Y < r.Y;
    });

    for(int i=0; i<=n; i++) DP[0][i][0] = 1;
    for(int i=1; i<=n; i++){
        DP[i][0][0] = 1;
        for(int j=1; j<=n; j++){
            for(int k=0; k<=t; k++){
                DP[i][j][k] += (double)(j-i)/(double)j * DP[i][j-1][k];
                DP[i][j][k] += (double)i/(double)j * (1.0 - v[j].X)*DP[i-1][j-1][k];
                DP[i][j][k] += (double)i/(double)j * v[j].X * ((k-v[j].Y >= 0) ? DP[i-1][j-1][k-v[j].Y] : 0);
            }
        }
    }
    
    for(int i=0; i<=n; i++){
        for(int j=0; j<=n; j++){
            for(int k=1; k<=t; k++){
                DP[i][j][k] += DP[i][j][k-1];
            }
        }
    }
    for(int i=1; i<=n; i++){
        for(int k=0; k<=min(K-1, i-1); k++){
            ans[ansid[i]] += (double)C[i-1][k]*(double)C[n-i][K-k-1]/(double)C[n-1][K-1]*v[i].X*DP[k][i-1][t - v[i].Y];
        }
    }

    for(int i=1; i<=n; i++){
        cout << fixed << setprecision(12) << ans[i] << "\n";
    }

    return 0;
}