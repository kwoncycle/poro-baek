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

ll cnt(ll i, ll k){
    // 1 1, 2 2, 3 3, 4 4, 5 5, 6 5, 7 5
    return ((i-1)/7)*5 + min(5ll, (i-1)%7 + 1) + min(i, k);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, k; cin >> n >> k;
    vector<pll> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    sort(v.begin(), v.end());
    ll st = -1, ed = 0x3f3f3f3f3f3fll; // st no ed good
    while(st + 1 < ed){
        ll md = (st + ed) / 2;
        ll use = 0, late = 0;
        for(int i=0; i<n; i++){
            //cout << use << " " << v[i].X << " " << cnt(v[i].X, md) << "\n";
            if(cnt(v[i].X, md) - use >= v[i].Y) use += v[i].Y;
            else{
                ll o = v[i].Y - (cnt(v[i].X, md) - use);
                ll st1 = v[i].X, ed1 = v[i].X + o*2 + 15;
                while(st1 + 1 < ed1){
                    ll md1 = (st1 + ed1) / 2;
                    if(cnt(md1, md) >= use + v[i].Y) ed1 = md1;
                    else st1 = md1;
                }
                late += ed1 - v[i].X;
                use += v[i].Y;
            }
            //cout << use << " ";
        }
        if(late <= k) ed = md;
        else st = md;
        //cout << late << "\n";
        //break;
    }
    if(ed == 0x3f3f3f3f3f3fll) cout << "-1\n";
    else cout << ed << "\n";
    return 0;
}