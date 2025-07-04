#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    ll n, k;
    cin >> n >> k;
    string s; cin >> s;
    vector<int> v(n);
    for(int i=0; i<n; i++){
        if(s[i] == 'B') v[i] = 0;
        else if(s[i] == 'R') v[i] = 2;
        else v[i] = 1;
    }
    ll o = 1, u = 0;
    while(o < k) {
        o *= 3; u++;
    }

    for( ; o>0; o/=3, u--){
        while(k >= o){
            vector<int> v1(n);
            for(ll i=0; i<n; i++){
                v1[i] = (v[i] + v[(i+o)%n] + v[(n + (i-o)%n) % n]) % 3;
            }
            v = v1;
            k -= o;
        }
    }

    vector<int> ans(3);
    for(int i:v){
        ans[i]++;
    }
    cout << ans[2] << " " << ans[1] << " " << ans[0] << "\n";

    return 0;
}