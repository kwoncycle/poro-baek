#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define X first
#define Y second

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pll> ab, ab1, ab_same;
    ll ttl = 0;
    for(int i=0; i<n; i++){
        int x,y; cin >> x >> y;
        ttl += y-x;
        if(x < y) ab.push_back({x,y});
        else if(x > y) ab1.push_back({y,x});
        else ab_same.push_back({y,x});
    }
    sort(ab.begin(),ab.end());
    sort(ab1.begin(),ab1.end());
    ll now = 0;
    int ans = 1;
    for(auto xy:ab){
        now -= xy.X;
        if(now < 0) ans = 0;
        now += xy.Y;
    }
    for(auto xy:ab_same){
        if(now < xy.X) ans = 0;
    }
    for(auto xy:ab1){
        ttl -= xy.X;
        if(ttl < 0) ans = 0;
        ttl += xy.Y;
    }
    cout << ans << '\n';
    return 0;
}