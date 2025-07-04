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

ll DP[420][420][210];
ll pre[210];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pll> val(n);
    for(int i=0; i<n; i++){
        double c; cin >> c;
        val[i].X = (int)(c*10000 + 0.5);
        val[i].Y = i;
    }

    sort(all(val));
    for(int i=0; i<n; i++){
        pre[i] = (i-1>=0 ? pre[i-1] : 0) + val[i].X;
    }

    for(int i=0; i<420; i++){
        for(int j=0; j<420; j++){
            for(int k=1; k<210; k++){
                DP[i][j][k] = 0x3f3f3f3f3f3fll;
            }
        }
    }

    for(int a=1; a<=n; a++){
        for(int t=2*n; t>=0; t--){
            for(int r=2*n; r>=0; r--){
                if(t-1 >= 0 and (t-1 or r or !(a-1)) and (t-1 + r <= a-1)) DP[t][r][a] = min(DP[t][r][a], DP[t-1][r][a-1]);
                if((t+r or t or !a) and (t+r + t <= a)) DP[t][r][a] = min(DP[t][r][a], DP[t+r][t][a] + pre[a-1]);
            }
        }
    }

    vector<array<int,3>> state;
    vector<string> ans(n);

    vector<string> T, R;
    T.push_back("");
    state.push_back({1, 0, n});
    while(true){
        auto [t,r,a] = state.back();
        if(t == 0 and r == 0 and a == 0) break;
        if(t-1 >= 0 and (t-1 or r or !(a-1)) and (t-1 + r <= a-1) and DP[t-1][r][a-1] == DP[t][r][a]){
            state.push_back({t-1, r, a-1});
            ans[val[a-1].Y] = T.back();
            T.pop_back();
        }
        else{
            state.push_back({t+r, t, a});
            for(auto &s:T){
                R.push_back(s + ".");
                s = s + "-";
            }
            T.swap(R);
        }
    }

    for(auto &s:ans) cout << s << "\n";

    return 0;
}