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

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

#define MOD 1000000007

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X;
    for(int i=0; i<n; i++) cin >> v[i].Y;

    sort(v.begin(), v.end(), [&](pii l, pii r){
        return l.X == r.X ? l.Y-l.X < r.Y-r.X : l.X < r.X;
    });
    map<ll, int> mp;
    ll ans = 1;
    int cnt = 0;
    mp[0] = 1;
    for(int i=0; i<n; i++){
        
        int i1 = i;
        while(i1<n and v[i].X == v[i1].X){
            if(v[i1].X == v[i1].Y) cnt++;
            if(mp.find(v[i1].Y-v[i1].X) == mp.end()){
                cout << "0\n"; return 0;
            }
            ans = ans * mp[v[i1].Y-v[i1].X] % MOD;
            i1++;
        }
        i1 = i;
        while(i1<n and v[i].X == v[i1].X){
            if(mp.find(v[i1].Y) == mp.end()) mp[v[i1].Y] = 0;
            mp[v[i1].Y]++;
            i1++;
        }
        i = i1-1;
    }
    if(cnt != 1) ans = 0;
    cout << ans << "\n";
    return 0;
}