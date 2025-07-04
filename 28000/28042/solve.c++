#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<ll,ll> pll;

#define X first
#define Y second

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, p, h;
    cin >> n >> p >> h; 
    p--; h--;
    vector<pll> state(n+1);
    state[n] = {h, 1ll << n};
    for(ll i=n-1; i>=0; i--){
        if(state[i+1].X < (1ll << i)) state[i] = {state[i+1].X, 1ll << i};
        else state[i] = {(1ll << (i+1)) - 1 - state[i+1].X, 1ll << i};
    }
    for(ll i=1; i<=n; i++){
        if(state[i-1].X == state[i].X){
            cout << (p < (1ll << (n-i)) ? 'R' : 'L');
            p %= (1ll << (n-i));
        }
        else{
            cout << (p < (1ll << (n-i)) ? 'L' : 'R');
            p = ((1ll << (n-i+1)) - p - 1) % (1ll << (n-i));
        }
    }
    cout << "\n";
    return 0;
}