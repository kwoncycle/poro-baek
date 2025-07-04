#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

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

int chk[500005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n; cin >> n;
    vector<ll> v;
    for(int i=0; i<n; i++){
        ll a; cin >> a;
        if(a) v.push_back(a);
    }
    n = v.size();
    if(n == 0){
        cout << "0\n"; return 0;
    }
    if(n == 1){
        cout << v[0] << "\n"; return 0;
    }

    ll st = 0, ed = 10000000000050ll;
    while(st + 1 < ed){
        ll m = (st + ed) / 2;
        int truth = 0;
        memset(chk, 0, sizeof(chk));
        for(int i=0; i<n and !truth; i++){
            if(chk[i]) continue;
            if(v[i] > m) continue;
            chk[i] = 1;
            int i0 = (i+n-1)%n, i1 = (i+1)%n;
            ll cur = v[i] + m;
            while(true){
                if(i0 == i1){
                    if(cur >= v[i0]){
                        chk[i0] = 1; cur += v[i0];
                        truth = 1;
                    }
                    break;
                }
                if(cur >= v[i0]){
                    cur += v[i0];
                    chk[i0] = 1;
                    i0 = (i0 + n - 1) % n;
                    continue;
                }
                if(cur >= v[i1]){
                    cur += v[i1];
                    chk[i1] = 1;
                    i1 = (i1 + 1) % n;
                    continue;
                }
                break;
            }
        }
        if(truth) ed = m;
        else st = m;
    }
    cout << ed << "\n";
    return 0;
}