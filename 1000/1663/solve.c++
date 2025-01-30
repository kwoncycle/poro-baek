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
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll q, n; cin >> q >> n;
    char c;
    ll k;
    if(q == 3) cin >> c;
    if(q == 2) cin >> k;
    ll nx = 1, ny = 0, nz = 0;
    for(ll i=0; i<n-1; i++){
        ll n_nx = nz, n_ny = nx, n_nz = nx + ny;
        nx = n_nx;
        ny = n_ny;
        nz = n_nz;
    }
    if(q == 3){
        if(c == 'X') cout << nx << "\n";
        if(c == 'Y') cout << ny << "\n";
        if(c == 'Z') cout << nz << "\n";
        return 0;
    }
    if(q == 1){
        cout << nx+ny+nz << '\n';
        return 0;
    }

    vector<vector<vector<ll>>> cnt(3, vector<vector<ll>>(3, vector<ll>(n+2, 0)));
    cnt[0][0][1] = 1;
    cnt[1][1][1] = 1;
    cnt[2][2][1] = 1;

    for(ll i=2; i<=n; i++){
        for(ll j=0; j<3; j++){
            ll n_nx = cnt[j][2][i-1], n_ny = cnt[j][0][i-1], n_nz = cnt[j][0][i-1] + cnt[j][1][i-1];
            cnt[j][0][i] = n_nx;
            cnt[j][1][i] = n_ny;
            cnt[j][2][i] = n_nz;
        }
    }

    ll index = 0;
    for(ll i=2; i<=n; i++){
        if(index == 0){
            ll sm = 0;
            for(ll j=0; j<3; j++){
                sm += cnt[1][j][n-i+1];
            }
            if(sm >= k){
                index = 1;
                continue;
            }
            else{
                index = 2;
                k -= sm;
            }
        }
        else if(index == 1){
            index = 2;
        }
        else{
            index = 0;
        }
    }
    cout << (char)('X' + index) << '\n'; 

    return 0;
}