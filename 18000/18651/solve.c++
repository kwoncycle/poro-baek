#include <bits/stdc++.h>
using namespace std;
 
#define ll __int128
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
    long long tt; cin >> tt;
    for(ll tc=1; tc<=tt; tc++){
        long long m, a, c, x0, l1, r1, l2, r2;
        cin >> m >> a >> c >> x0 >> l2 >> r2 >> l1 >> r1;
        vector<ll> T_handle(m, -1);
        ll x = x0;
        T_handle[x] = 0;
        ll T;
        ll fst = 0;
        ll fst_val = 0;
        ll ttl = r1 - l1 + 1;
        for(ll i=1; i<=m*2; i++){
            x = (a*x+c)%m;
            if(T_handle[x] >= 0){
                T = i - T_handle[x];
                fst = T_handle[x];
                fst_val = x;
                break;
            }
            T_handle[x] = i;
        }
        vector<ll> cnt1(m,0), cnt2(m,0);
        x = x0;
        for(ll i=0; i<=min((ll)r1, fst-1); i++){
            cnt1[x]++;
            x = (a*x+c)%m;
        }
        if(r1 >= fst){
            r1 -= fst;
            x = fst_val;
            for(ll i=0; i<T; i++){
                cnt1[x] += (r1-i+T)/T;
                x = (a*x+c)%m;
            }
        }
        x = x0;
        for(ll i=0; i<=min((ll)l1-1, fst-1); i++){
            cnt1[x]--;
            x = (a*x+c)%m;
        }
        if(l1-1 >= fst){
            l1 -= fst;
            x = fst_val;
            for(ll i=0; i<T; i++){
                cnt1[x] -= (l1-1-i+T)/T;
                x = (a*x+c)%m;
            }
        }

        x = x0;
        for(ll i=0; i<=min((ll)r2, fst-1); i++){
            cnt2[x]++;
            x = (a*x+c)%m;
        }
        if(r2 >= fst){
            r2 -= fst;
            x = fst_val;
            for(ll i=0; i<T; i++){
                cnt2[x] += (r2-i+T)/T;
                x = (a*x+c)%m;
            }
        }
        x = x0;
        for(ll i=0; i<=min((ll)l2-1, fst-1); i++){
            cnt2[x]--;
            x = (a*x+c)%m;
        }
        if(l2-1 >= fst){
            l2 -= fst;
            x = fst_val;
            for(ll i=0; i<T; i++){
                cnt2[x] -= (l2-1-i+T)/T;
                x = (a*x+c)%m;
            }
        }

        ll sm1 = 0;
        for(ll i=0; i<m; i++){
            sm1 += cnt2[i]*i;
        }
        for(ll i=1; i<m; i++){
            cnt2[i] = cnt2[i-1] + cnt2[i];
        }

        ll ans = sm1*ttl;
        

        for(ll i=0; i<m; i++){
            if(cnt1[i]){
                for(ll j=0; j<m; j += i+1){
                    // j~j+i+1-1
                    ll o = cnt2[min(j+i+1-1, (ll)m-1)];
                    if(j) o -= cnt2[j-1];
                    ans -= (j/(i+1))*(i+1)*cnt1[i]*o;
                }
            }
        }

        cout << "Case #" << (long long)tc << ": " << (long long)ans << "\n";
        // 0 0 1 1 1 1 2
    }
    return 0;
}