#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n
#define MOD 1000000007ll

ll poww(ll a, ll e){
    ll ans = 1;
    while(e > 0){
        if(e&1) ans = ans * a % MOD;
        a = a*a % MOD;
        e >>= 1;
    }
    return ans;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll tt; cin >> tt;
    while(tt--){
        ll n; cin >> n;
        vector<pii> p(n);
        for(ll i=0; i<n; i++) cin >> p[i].X >> p[i].Y;
        ll mn_x = p[0].X, mx_x = p[0].X, mn_y = p[0].Y, mx_y = p[0].Y, mnxmy = p[0].X-p[0].Y, mxxmy=p[0].X-p[0].Y, mnxpy=p[0].X+p[0].Y, mxxpy=p[0].X+p[0].Y;
        if(n == 1){
            cout << "1\n"; continue;
        }
        for(ll i=0; i<n; i++){
            mn_x = min(mn_x, p[i].X);
            mn_y = min(mn_y, p[i].Y);
            mx_x = max(mx_x, p[i].X);
            mx_y = max(mx_y, p[i].Y);
            mnxmy = min(mnxmy, p[i].X-p[i].Y);
            mxxmy = max(mxxmy, p[i].X-p[i].Y);
            mnxpy = min(mnxpy, p[i].X+p[i].Y);
            mxxpy = max(mxxpy, p[i].X+p[i].Y);
        }

        pii V[8];
        V[0] = {mnxmy+mx_y, mx_y};
        V[1] = {mxxpy-mx_y, mx_y};
        V[4] = {mnxpy-mn_y, mn_y};
        V[5] = {mxxmy+mn_y, mn_y};
        V[2] = {mx_x, mxxpy-mx_x};
        V[3] = {mx_x, mx_x - mxxmy};
        V[7] = {mn_x, mnxpy-mn_x};
        V[6] = {mn_x, mn_x - mnxmy};
        /*
        for(ll i=0; i<n; i++){
            if(p[i].Y == mx_y){
                V[0].X = min(V[0].X, p[i].X);
                V[1].X = max(V[1].X, p[i].X);
            }
            if(p[i].Y == mn_y){
                V[4].X = min(V[4].X, p[i].X);
                V[5].X = max(V[5].X, p[i].X);
            }
            if(p[i].X == mx_x){
                V[3].Y = min(V[3].Y, p[i].Y);
                V[2].Y = max(V[2].Y, p[i].Y);
            }
            if(p[i].X == mn_x){
                V[7].Y = min(V[7].Y, p[i].Y);
                V[6].Y = max(V[6].Y, p[i].Y);
            }
        }

        ll d = min(mx_x - V[1].X, mx_y - V[2].Y);
        V[1].X = mx_x - d;
        V[2].Y = mx_y - d;

        d = min(mx_x - V[5].X, V[3].Y - mn_y);
        V[5].X = mx_x - d;
        V[3].Y = mn_y + d;

        d = min(V[4].X - mn_x, V[7].Y - mn_y);
        V[4].X = mn_x + d;
        V[7].Y = mn_y + d;

        d = min(V[0].X - mn_x, mx_y - V[6].Y);
        V[0].X = mn_x + d;
        V[6].Y = mx_y - d;
        */
        //for(auto [x,y]:V) cout << x << " " << y << "\n";

        vector<ll> cnt(8);
        vector<ll> cross(8);
        for(int i=0; i<n; i++){
            vector<int> check(8);
            if(mx_y == p[i].Y) check[0] = 1;
            if(mxxpy == p[i].X + p[i].Y) check[1] = 1;
            if(mx_x == p[i].X) check[2] = 1;
            if(mxxmy == p[i].X - p[i].Y) check[3] = 1;
            if(mn_y == p[i].Y) check[4] = 1;
            if(mnxpy == p[i].X + p[i].Y) check[5] = 1;
            if(mn_x == p[i].X) check[6] = 1;
            if(mnxmy == p[i].X - p[i].Y) check[7] = 1;
            for(int j=0; j<8; j++){
                if(check[j]) cnt[j]++;
                if(check[j] and check[(j+1)%8]) cross[j] = 1;
            }
        }
        
        if(mx_x == mn_x){
            cout << poww(2, n-2) << "\n"; continue;
        }

        if(mx_y == mn_y){
            cout << poww(2, n-2) << "\n"; continue;
        }

        if(mxxmy == mnxmy){
            cout << poww(2, n-2) << "\n"; continue;
        }

        if(mxxpy == mnxpy){
            cout << poww(2, n-2) << "\n"; continue;
        }
        ll ttl = 0;
        for(ll i=0; i<8; i++) {ttl += cnt[i], ttl -= cross[i];}
        //cout << "\n";
        //for(ll i:cnt) cout << i << " "; cout << "CNT\n";
        ll allt = n;
        allt -= ttl;
        //cout << ttl << " " << allt << "\n";
        ll edgettl = 0;
        for(ll i=0; i<256; i++){
            vector<ll> v(8, 0);
            ll i1 = i;
            for(ll j=0; j<8; j++){
                if(i1&(1<<j)) v[j] = 1;
            }

            int truth = 1;
            for(ll j=0; j<8; j++){
                if(!cross[j] and v[j]) truth = 0;
                if(cnt[(j+1)%8] == 1 and v[j] == 1 and v[(j+1)%8] == 0) truth = 0;
                if(cnt[(j+1)%8] == 1 and v[j] == 0 and v[(j+1)%8] == 1) truth = 0;
            }
            
            ll u = 1;
            for(int j=0; j<8; j++){
                if(cnt[j] - v[j]*cross[j] - v[(j+7)%8]*cross[(j+7)%8] <= 0) truth = 0;
                ll o = cnt[j] - cross[j] - cross[(j+7)%8];
                if(o < 0) o = 0;
                if((1-v[j])*cross[j] or (1-v[(j+7)%8])*cross[(j+7)%8]) u = u * (poww(2, o)) % MOD;
                else u = u * (poww(2, o)-1) % MOD;
            }
            if(!truth) continue;

            //for(int j:v) cout << j << " "; cout << ": " << u << "\n";
            edgettl += u; edgettl %= MOD;
        }
        edgettl %= MOD;
        edgettl = edgettl * poww(2, allt) % MOD;
        if(edgettl < 0) edgettl += MOD;
        cout << edgettl << "\n";
    }
    return 0;
}