#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

vector<ll> v;
ll sm = 0;
ll n, m;
ll ans = 0;
ll fct[13];

void JG(ll d, ll sm){
    if(d >= n){
        if(sm == n){
            vector<ll> cnt1(m, 0), cnt2(m, 0);
            for(ll i=0; i<n; i++){
                cnt1[v[i]%m]++;
                cnt2[i%m] += v[i];
            }
            ll o = 1;
            for(ll i=0; i<m; i++){
                if(cnt1[i] != cnt2[i]) return;
                o *= fct[cnt1[i]];
            }
            for(ll i=0; i<n; i++){
                o /= fct[v[i]];
            }
            ans += o;
            
        }
        return;
    }

    for(ll i=0; i<=n-sm; i++){
        v.push_back(i);
        JG(d+1, sm+i);
        v.pop_back();
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    if(m > 2*n) m = 2*n;
    fct[0] = 1;
    for(ll i=1; i<=12; i++) fct[i] = fct[i-1] * i;
    JG(0, 0);
    cout << ans << "\n";
    return 0;
}