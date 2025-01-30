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
using A2 = array<ll, 2>;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll h; cin >> h;
    ll a, b, c; cin >> a >> b >> c;
    if(a>c) swap(a, c);
    if(b>c) swap(b, c);
    vector<ll> dst(c+1, 0x3f3f3f3f3f3fll);
    priority_queue<A2, vector<A2>, greater<A2>> pq;
    pq.push({0, 0});
    if(a < c) pq.push({0, a});
    if(b < c) pq.push({0, b});
    while(!pq.empty()){
        auto [d, i] = pq.top();
        pq.pop();
        if(dst[i] <= d) continue;
        dst[i] = d;
        int o1, d1;
        if(i + a >= c){
            o1 = (i+a)%c;
            d1 = d + 1;
        }
        else{
            o1 = i + a;
            d1 = d;
        }

        if(dst[o1] > d1){
            pq.push({d1, o1});
        }

        if(i + b >= c){
            o1 = (i+b)%c;
            d1 = d + 1;
        }
        else{
            o1 = i + b;
            d1 = d;
        }
        if(dst[o1] > d1){
            pq.push({d1, o1});
        }
    }
    h--;
    ll ans = 0;
    for(int i=0; i<c; i++){
        // dst[i]*c+i, i+c, ... i + ac <= h
        // h-i/c+1
        if(dst[i] >= 0x3f3f3f3f3f3f - 123) continue;
        if(dst[i]*c+i > h) continue;
        ans += (h - (dst[i]*c + i))/c + 1;
    }
    cout << ans << "\n";
    return 0;
}