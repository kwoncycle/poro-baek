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

bool cmp(pll &p1, pll &p2){
    if(p1.Y + 45 <= p2.Y) return true;
    if(p2.Y + 45 <= p1.Y) return false;
    if(p1.Y < p2.Y){
        if(p1.X <= (p2.X << (p2.Y - p1.Y))) return true;
        else return false;
    }

    else{
        if(p2.X < (p1.X << (p1.Y - p2.Y))) return false;
        else return true;
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pll> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X;

    ll ans = 0;
    for(int i=1; i<n; i++){
        v[i].Y = v[i-1].Y;
        while(!cmp(v[i-1], v[i])) v[i].Y++;
        while(v[i].Y > 0 and cmp(v[i-1], v[i])) v[i].Y--;
        if(!cmp(v[i-1], v[i])) v[i].Y++;
        ans += v[i].Y;
    }

    cout << ans << "\n";
    return 0;
}