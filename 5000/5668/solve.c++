#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
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

struct CHT{
    vector<pii> stk; // (a, b)
    void insert(pii p){
        while(stk.size() >= 2 and cx(stk[stk.size()-2], p) > cx(stk[stk.size()-1], p)) stk.pop_back();
        stk.push_back(p);
    }
    double cx(pii p1, pii p2){
        return (double)(p2.Y - p1.Y) / (double)(p1.X - p2.X);
    }
    ll query(ll x){
        if(stk.size() == 1) return stk[0].X * x + stk[0].Y;
        int st = 0, ed = stk.size() - 1;
        if(x < cx(stk[st], stk[st + 1])){
            return stk[0].X * x + stk[0].Y;
        }
        while(st + 1 < ed){
            int md = (st + ed) / 2;
            if(cx(stk[md], stk[md + 1]) < x) st = md;
            else ed = md;
        }
        return stk[st + 1].X * x + stk[st + 1].Y;
    }
} C;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, k;
    while(cin >> n >> k){
        vector<pii> v(n+1); // x w
        for(int i=n; i>=1; i--) cin >> v[i].X >> v[i].Y;
        vector<vector<ll>> DP(k+1, vector<ll>(n+1));
        vector<ll> wxsm(n+1), wsm(n+1);

        for(int i=1; i<=n; i++){
            DP[1][i] = DP[1][i-1] + v[i].Y * (v[1].X - v[i].X);
            wxsm[i] = wxsm[i-1] + v[i].X * v[i].Y;
            wsm[i] = wsm[i-1] + v[i].Y;
        }
        

        for(int i=2; i<=k; i++){
            C.stk.clear();
            for(int j=1; j<=n; j++){
                if(j > i){
                    DP[i][j] = C.query(wsm[j]) - wxsm[j];
                }
                if(j < n){
                    ll a = v[j+1].X;
                    ll b = -wsm[j] * v[j+1].X + wxsm[j] + DP[i-1][j];
                    C.insert({a, b});
                }
            }
        }
        cout << DP[k][n] << "\n";
    }
    return 0;
}