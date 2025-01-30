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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        int n, d; cin >> n >> d;
        
        vector<int> shop(n+1);
        for(int i=1; i<=n; i++) cin >> shop[i];
        sort(shop.begin()+1, shop.end(), greater<int>());
        ll ans = 0;
        for(int tt=n; tt>=1; tt--){
            vector<vector<int>> v(n+1, vector<int>(d+1));
            v[0][0] = 1;            
            for(int i=1; i<=tt-1; i++){
                // A + shop[i] <= d, A + shop[i] + shop[n] > d
                // d - shop[i] - shop[n] + 1 <= A <= d-shop[i]

                for(int A=max(0, d-shop[i]-shop[n]+1); A<=d-(i<n ? shop[i] : 0); A++){
                    ans += v[i-1][A];
                }
                for(int j=d; j>=0; j--) v[i][j] = v[i-1][j];
                for(int j=d; j>=shop[i]; j--){
                    v[i][j] += v[i-1][j-shop[i]];
                }
            }
            d -= shop[tt];
            if
        }
        for(int i=1; i<=n; i++){
            //for(int j=0; j<=d; j++) cout << v[i][j] << " ";
            //cout << "\n";
        }
        cout << ans << "\n";
    }
    return 0;
}