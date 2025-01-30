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
    ll w, h; cin >> w >> h;
    vector<ll> v(w);
    for(int i=0; i<w; i++) cin >> v[i];
    int button = 1;
    vector<ll> cnt(w+3, 0);
    for(int i=0; i<w-1; i++){
        if((v[i] + cnt[i] + h) % 2 == 1){
            cnt[i]++; cnt[i+1] = cnt[i];
        }
        cnt[i+2] = max(0ll, cnt[i+1] - 1);
    }
    for(int i=0; i<w; i++){
        if((v[i] + cnt[i] <= h) and (h - v[i] - cnt[i]) % 2 == 0) continue;
        button = 0; break;
    }
    if(cnt[w-1] >= 2) button = 0;
    if(button) cout << "possible\n";
    else cout << "impossible\n";
    return 0;
}