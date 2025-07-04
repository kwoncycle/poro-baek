#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

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

double DP[1002][1002];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int r, c, p; cin >> r >> c >> p;
    for(int i=0; i<=1000; i++){
        DP[0][i] = 0x3f3f3f3f;
        DP[i][0] = 0x3f3f3f3f;
    }
    for(int i=1; i<=r; i++){
        for(int j=1; j<=c; j++){
            if(i == 1 and j == 1) DP[i][j] = 0;
            else{
                double m0 = DP[i][j-1], m1 = DP[i-1][j];
                if(m0 > m1) swap(m0, m1);
                m1 = min(m1, m0+1.0);
                DP[i][j] = m0 + (m1-m0)*(m1-m0)/4.0 + (m1-m0)*(1-(m1-m0))/2.0;
            }
        }
    }

    cout << fixed << setprecision(12) << DP[r][c]*(double)p << "\n";
    return 0;
}