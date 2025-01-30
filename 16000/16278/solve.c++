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

#define MOD 998244353

ll poww(ll a, ll e){
    ll ans = 1;
    while(e){ 
        if(e&1) ans = ans * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    vector<ll> fct(100001, 1), fctinv(100001, 1);
    for(int i=1; i<=100000; i++){
        fct[i] = fct[i-1] * i % MOD;
    }

    fctinv[100000] = poww(fct[100000], MOD - 2);
    for(int i=100000; i>=1; i--){
        fctinv[i-1] = fctinv[i] * i % MOD;
    }
    assert(fctinv[0] == 1);
    while(tt--){
        int n; cin >> n;
        vector<int> v(n);
        for(int i=0; i<n; i++) cin >> v[i];
        vector<int> odd, even;
        for(int i=0; i<n; i++){
            int o = v[i] % 11;
            int cnt = 0;
            while(v[i]){
                cnt++; v[i] /= 10;
            }
            if(cnt%2 == 1) odd.push_back(o);
            else even.push_back(o);
        }

        if(odd.size() == 0){
            int sm = 0;
            for(int i:even) sm += i;
            sm %= 11;
            if(sm == 0){
                ll ans = 1;
                for(int i=1; i<=n; i++) ans = ans * i % MOD;
                cout << ans << "\n";
            }
            else cout << "0\n";
            continue;
        }

        vector<vector<vector<int>>> DP_even((int)even.size()+1, vector<vector<int>>((int)even.size()+1, vector<int>(11, 0))), DP_odd((int)odd.size()+1, vector<vector<int>>((int)odd.size()+1, vector<int>(11, 0))); // DP[i][j] : odd자리 i even자리 j
        if(!odd.empty()){
            DP_odd[0][1][odd[0]] = 1;
            DP_odd[1][0][(11-odd[0]) % 11] = 1;
            for(int i=1; i<(int)odd.size(); i++){
                for(int j=0; j<=i+1; j++){
                    for(int t=0; t<11; t++){
                        DP_odd[j][i+1-j][t] = ( (i-j >= 0 ? DP_odd[j][i-j][(11 + t - odd[i])%11] : 0) + (j-1 >= 0 ? DP_odd[j-1][i+1-j][(t + odd[i])%11] : 0) ) % MOD;
                    }
                }
            }
        }

        if(!even.empty()){
            DP_even[0][1][even[0]] = 1;
            DP_even[1][0][(11 - even[0]) % 11] = 1;
            for(int i=1; i<(int)even.size(); i++){
                for(int j=0; j<=i+1; j++){
                    for(int t=0; t<11; t++){
                        DP_even[j][i+1-j][t] = ( (i-j >= 0 ? DP_even[j][i-j][(11 + t - even[i])%11] : 0) + (j-1 >= 0 ? DP_even[j-1][i+1-j][(t + even[i])%11] : 0) ) % MOD;
                    }
                }
            }
        }
        
        else{
            int t1 = ((int)odd.size() + 1)/2, t2 = (int)odd.size()/2;
            ll u = DP_odd[t1][t2][0];
            u = u * fct[t1] % MOD * fct[t2] % MOD;
            cout << u << "\n";
            continue;
        }

        int t1 = ((int)odd.size() + 1)/2, t2 = (int)odd.size()/2;
        int ne = ((int)odd.size() + 2)/2, no = ((int)odd.size()+1)/2;
        int es = even.size();
        ll ans = 0;
        for(int t=0; t<11; t++){
            ll u = DP_odd[t1][t2][t];
            u = u * fct[t1] % MOD * fct[t2] % MOD;
            for(int i=0; i<=es; i++){
                ll o = DP_even[i][es-i][(11-t)%11];
                ll evencase = fct[i + ne - 1] * fctinv[ne - 1] % MOD;
                ll oddcase = fct[es-i + no - 1] * fctinv[no - 1] % MOD;
                ans += (u*o%MOD) * (evencase*oddcase%MOD) % MOD;
                ans %= MOD;
            }
        }

        cout << ans << "\n";



    }
    return 0;
}