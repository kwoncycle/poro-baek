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

vector<ll> v;
vector<ll> fct(12, 1);
vector<ll> ans(12, 0), ans1(12, 0);
void S(ll n, ll sm){
    ll x = n - sm;
    if(x == 0){
        ll u = fct[n];
        for(ll i:v){
            u /= fct[i];
        }
        ans[n] += u;
        return;
    }
    for(ll i=1; i<=x; i++){
        v.push_back(i);
        S(n, sm + i);
        v.pop_back();
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    for(ll i=1; i<=11; i++) fct[i] = fct[i-1] * i;
    for(ll i=1; i<=11; i++){
        S(i, 0);
    }
    for(int i=1; i<=11; i++) {
        for(int j=1; j<=i; j++){
            ll u = fct[i];
            u /= fct[i-j]; u /= fct[j];
            ans1[i] += u*ans[j];
        }
    }
    ll n; cin >> n;
    while(n--){
        ll x; cin >> x;
        cout << ans1[x] << "\n";
    }
    return 0;
}