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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    ll m, l, k, s; cin >> m >> l >> k >> s;
    vector<ll> cost(m+1);
    for(int i=1; i<=m; i++) cin >> cost[i];
    vector<vector<ll>> pres(m+1);

    for(int i=0; i<l; i++){
        ll p, r; cin >> p >> r;
        pres[p].push_back(r);
    }

    for(int i=1; i<=m; i++){
        sort(pres[i].begin(), pres[i].end());
    }

    ll ans = 0;
    for(int i=1; i<=m; i++){
        if(pres[i].empty()) continue;

        ll sm = 0;
        for(ll j:pres[i]) sm += j;
        ll c1 = (sm / k) * k;
        ll cost1 = c1 * cost[i] - (c1/k) * s;
        ll cost2 = sm * cost[i] - (c1/k) * s;
        if(sm % k != 0) cost2 -= s;

        if(cost2 >= cost1){
            ans += cost2;
            continue;
        }

        vector<int> cnt(s+1, 0);
        for(int j:pres[i]){
            if(j > s) break;
            cnt[j]++;
        }

        vector<ll> knps(s*2, 0);
        knps[0] = 1;
        for(int j=1; j<=s; j++){
            if(!cnt[j]) continue;
            for(int i1=s*2-1; i1>=0; i1--){
                if(knps[i1]){
                    for(int i2=i1+j; i2<=min((int)s*2-1, i1+j*cnt[j]); i2+=j){
                        knps[i2] = 1;
                    }
                }
            }
        }
        int o = sm % k;
        while(o < 2*s and knps[o] == 0) o++;
        if(o == 2*s) ans += cost2;
        else{
            ll sm1 = sm - o;
            ll c2 = (sm1 / k) * k;
            ll cost3 = sm1 * cost[i] - (c2/k) * s;
            if(sm1 % k != 0) cost3 -= s;
            ans += max(cost2, cost3);
        }
    }

    cout << ans << "\n";
    return 0;
}