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


ll DP[31][31][12310];
ll v[31][31];
ll n, m;
ll k;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m >> k;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) cin >> v[i][j];
    }

    for(int i=n-1; i>=0; i--){
        for(int j=m-1; j>=0; j--){
            if(i==n-1 and j==m-1){
                DP[i][j][v[i][j]] = 1;
            }
            else{
                if(i+1 < n){
                    for(int t=0; t<=12000; t++){
                        DP[i][j][t+v[i][j]] += DP[i+1][j][t];
                    }
                }
                if(j+1 < m){
                    for(int t=0; t<=12000; t++){
                        DP[i][j][t+v[i][j]] += DP[i][j+1][t];
                    }
                }
            }
        }
    }
    ll target = 0, cur = 0;
    for(int i=12000; i>=0; i--){
        if(cur + DP[0][0][i] < k) cur += DP[0][0][i];
        else{
            target = i; break;
        }
    }
    
    k -= cur;
    string ans;
    int cx=0, cy=0;
    for(int i=0; i<n+m-2; i++){
        if(cx+1 >= n){
            cy++;
            ans = ans + "R";
        }
        else if(cy + 1 >= m){
            cx++;
            ans = ans + "D";
        }
        else{
            // D
            if(DP[cx+1][cy][target - v[cx][cy]] < k){
                k -= DP[cx+1][cy][target - v[cx][cy]];
                target -= v[cx][cy];
                cy++;
                ans = ans + "R";
            }
            else{
                //k -= DP[cx][cy+1][target - v[cx][cy]]
                target -= v[cx][cy];
                cx++;
                ans = ans + "D";
            }
        }
    }

    cout << ans << "\n";

    return 0;
}