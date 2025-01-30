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
    int n; cin >> n;
    vector<pll> point(n*2);
    for(int i=0; i<n; i++) cin >> point[i].X >> point[i].Y;
    for(int i=0; i<n; i++) point[n+i] = point[i];
    ll now = 0, nowx = 0;;
    vector<pll> vp;
    vector<ll> v;
    set<pll> s;
    for(int i=0; i<n*2-1; i++){
        if(point[i].X != point[i+1].X) continue;
        if(point[i].Y * point[i+1].Y < 0){
            if(point[i].Y < 0){
                now = 1; nowx = point[i].X;
            }
            else{
                if(now == 1){
                    s.insert({min(nowx, point[i].X), max(nowx, point[i].X)});
                }
                now = -1;
                nowx = point[i].X;
            }
        }
    }
    vector<pii> vp2;
    for(auto xy:s){
        vp.push_back(xy);
        v.push_back(xy.X); v.push_back(xy.Y);
        vp2.push_back({xy.X, 1});
        vp2.push_back({xy.Y, 2});
    }
    sort(v.begin(), v.end());
    sort(vp2.begin(), vp2.end());
    int cnt1 = 0, cnt2 = 0;
    for(auto xy:vp){
        ll x = xy.X, y = xy.Y;
        int c1 = CNT_LOWER(v, x), c2 = CNT_LOWER(v, y);
        if(c1 + 1 == c2) cnt2++;
    }

    int sm = 0;
    for(auto p2:vp2){
        if(p2.Y == 1){
            if(sm == 0) cnt1++;
            sm++;
        }
        else sm--;
    }

    cout << cnt1 << " " << cnt2 << "\n";
    return 0;
}