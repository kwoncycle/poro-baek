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

int mn[1100005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, k; cin >> n >> k;
    for(int i=2; i<=n+1; i++){
        if(i == k+1) continue;
        mn[i] = k+1 + i+1;
    }

    for(int p=2; p<=k+1; p++){
        ll n1 = k+1;
        vector<int> v;
        while(n1){
            v.push_back(n1 % p);
            n1 /= p;
        }
        reverse(all(v));
        if(v.size() >= 3){
            int o = *max_element(all(v)); o++;
            for(int i=o; ; i++){
                ll ans = 0;
                for(int j:v){
                    ans *= i; ans += j;
                }
                if(ans > n+1) break;
                mn[ans] = min(mn[ans], p + i);
            }
        }
        else break;
    }
    int a = k+1;

    for(int a1=1; a1<=1010; a1++){
        int a2 = a%a1;
        int a12mx = max(a1, a2);
        for(int b=a-a1, q=(b-a2)/a1; b>=2 and q > a12mx; b-=a1, q--){
            int t = min((q-a2-1) / (a1+1), q-a1-1);
            mn[b] = min(mn[b], 2*q - 2*t + (a-b)/a1);
        }
        int q = (a-a2)/a1;
        if(q <= a12mx) continue;
        int t = min((q-a2-1) / (a1+1), q-a1-1);
        for(int b=a+a1, z=(b-a)/a1 + 2*q - 2*t; b<=n+1; b+=a1, z++){
            mn[b] = min(mn[b], z);
        }
    }

    ll ans = 0;
    for(int i=2; i<=n+1; i++) ans += mn[i];
    cout << ans << '\n';
    //for(int i=1; i<=n+1; i++) cout << mn[i] << " "; cout << "\n";
    return 0;
}