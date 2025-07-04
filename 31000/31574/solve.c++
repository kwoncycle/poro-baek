#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll SZ = 100005;
ll pos[SZ];
char dir[SZ];
ll n, l, t; 
ll where(ll i){
    ll x = pos[i];
    if(dir[i] == 'R') x += t;
    else x += 2*l - t;
    x %= 2*l;
    if(x >= l) x = 2*l-x;
    return x;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> l >> t;
    t %= 2*l;
    for(ll i=1; i<=n; i++){
        cin >> pos[i] >> dir[i];
    }
    ll who; cin >> who;
    ll ans = 0;
    for(ll i=1; i<=n; i++){
        if(where(i) <= where(who)) ans++;
    }
    vector<int> id(n);
    for(int i=1; i<=n; i++) id[i-1] = i;
    sort(id.begin(), id.end(), [&](int l, int r){
        return pos[l] < pos[r];
    });
    cout << id[ans-1] << "\n";
    return 0;
}