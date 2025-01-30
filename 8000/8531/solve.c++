#include <bits/stdc++.h>
using namespace std;
 
#define ll __int128
#define lo unsigned long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

vector<ll> YBS(ll a1, ll a2){
    vector<ll> ans;
    ans.push_back(a1/a2);
    a1 %= a2;
    swap(a1, a2);
    while(a2){
        ans.push_back(a1/a2);
        a1 %= a2;
        swap(a1, a2);
    }
    //for(ll i:ans) cout << i << " "; cout << "\n";
    return ans;
}

pll YBS2ll(vector<ll> &ybs){
    ll n = ybs.size();
    pll cur = {1, ybs[n-1]};
    for(ll i=n-2; i>=0; i--){
        cur = {cur.Y, cur.X + cur.Y*ybs[i]};
        cur = {cur.X/__gcd(cur.X, cur.Y), cur.Y/__gcd(cur.X, cur.Y)};
        if(i == 0){
            cur = {cur.Y, cur.X};
        }
    }
    //cout << cur.X << " " << cur.Y <<"\n";
    return cur;
}

#define DEBUG 1

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    unsigned long long nu, au; cin >> nu >> au;
    ll n, a; n = nu, a = au;
    //cout << n << " " << a << " " << a+1 << "\n";
    if((n <= (1ll<<20)) and DEBUG){
        vector<pll> ans1;
        for(ll i=1; i<=n; i++){
            ll o2 = (a+1)*i/(n*n);
            ll o1 = (a*i-1)/(n*n)+1;
            for(ll j=o1; j<=o2; j++) {
                if(__gcd(i,j)==1)
                ans1.push_back({j, i});
            }
        }
        cout << (ans1.size()) << "\n";
        for(auto &[x,y]:ans1){
            if((lo)x != 0) cout << (lo)x << " " << (lo)y << "\n";
            else cout << "18446744073709551616" << " " << (lo)y << "\n";
        } 
        return 0;
    }
    if(a%(n*n) == 0){
        cout << "1\n";
        cout << (lo)(a/(n*n)) << " " << 1 << "\n";
        return 0;
    }
    if((a+1)%(n*n) == 0){
        cout << "1\n";
        cout << (lo)((a+1)/(n*n)) << " " << 1 << "\n";
        return 0;
    }
    if((n*n)%a == 0){
        ll t = n*n/a;
        if(t <= n){
            cout << "1\n";
            cout << "1 " << (lo)t << "\n";
        }
        else{
            cout << "0\n";
        }
        return 0;
    }
    if((n*n)%(a+1) == 0){
        ll t = n*n/(a+1);
        if(t <= n){
            cout << "1\n";
            cout << "1 " << (lo)t << "\n";
        }
        else{
            cout << "0\n";
        }
        return 0;
    }
    vector<ll> na1 = YBS(a, n*n), na2 = YBS(a+1, n*n);
    ll id = 0;
    while(na1[id] == na2[id]) id++;
    vector<ll> newna(id+1);
    for(ll i=0; i<id; i++) newna[i] = na1[i];
    
    vector<pll> anslist;
    for(ll i=min(na1[id],na2[id]) + 1; i<=max(na1[id],na2[id]); i++){
        //cout << i << " ";
        newna[id] = i;
        pll ans = YBS2ll(newna);
        //cout << ans.X << " " << ans.Y << "\n";
        if(ans.Y <= n) anslist.push_back(ans);
        else break;
    }
    cout << (anslist.size()) << "\n";
    for(auto &[x,y]:anslist) cout << (lo)x << " " << (lo)y << "\n";
    //newna[id] = na1[id] + 1;
    //YBS2ll(newna);
    //YBS(7, 4);
    return 0;
}