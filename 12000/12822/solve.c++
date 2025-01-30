#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define ull long long
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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, p; 
    ull tmp;
    cin >> tmp; n = tmp;
    cin >> tmp; p = tmp;
    vector<pll> v(n);
    ll ans = 0;
    for(int i=0; i<n; i++){
        ull c1,c2,c3;
        cin >> c1 >> c2 >> c3;
        v[i].X = c1; 
        ans += c2;
        v[i].Y = c3;
        v[i].X -= p;
    }

    sort(v.begin(), v.end());
    if(v[0].X > 0){
        for(int i=0; i<n; i++) ans += v[i].X*v[i].Y;
        cout << (ull)ans << "\n";
        return 0;
    }
    if(v[n-1].X < 0){
        for(int i=0; i<n; i++) ans += abs(v[i].X)*v[i].Y;
        cout << (ull)ans << "\n";
        return 0;
    }
    vector<ll> pre(n), suf(n);
    pre[0] = v[0].Y;
    for(int i=1; i<n; i++) pre[i] = pre[i-1] + v[i].Y;
    suf[n-1] = v[n-1].Y;
    for(int i=n-2; i>=0; i--) suf[i] = suf[i+1] + v[i].Y;

    int i1 = 0;
    while(v[i1].X < 0) i1++;

    vector<vector<vector<ll>>> DP(n, vector<vector<ll>>(n, vector<ll>(2)));

    for(int i=0; i<i1; i++){
        for(int j=n-1; j>=i1; j--){
            if(i > 0) {
                DP[i][j][0] = min((pre[i-1]+suf[j])*(2*abs(v[i].X)) + abs(v[i].X)*v[i].Y + DP[i-1][j][1], DP[i-1][j][0] + abs(v[i].X)*v[i].Y);

            }
            else{
                DP[i][j][0] = abs(v[i].X)*v[i].Y;
                if(j == n-1) DP[i][j][0] += (2*abs(v[i].X) + v[j].X)*v[j].Y;
                else{
                    DP[i][j][0] = DP[i][j+1][0] + (2*abs(v[i].X) + v[j].X)*v[j].Y;
                }
            }

            if(j < n-1){
                DP[i][j][1] = min((pre[i]+suf[j+1])*(2*abs(v[j].X)) + abs(v[j].X)*v[j].Y + DP[i][j+1][0], DP[i][j+1][1] + abs(v[j].X)*v[j].Y);
            }
            else{
                DP[i][j][1] = abs(v[j].X)*v[j].Y;
                if(i == 0) DP[i][j][1] += (2*abs(v[j].X) + abs(v[i].X))*v[i].Y;
                else{
                    DP[i][j][1] = DP[i-1][j][1] + (2*abs(v[j].X) + abs(v[i].X))*v[i].Y;
                }
            }
            assert(DP[i][j][0] >= 0 and DP[i][j][1] >= 0);
        }
    }

    cout << (ull)(min(DP[i1-1][i1][0], DP[i1-1][i1][1]) + ans) << "\n";

    return 0;
}