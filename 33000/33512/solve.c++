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

vector<int> isprime(100001, 1), mb(100001, 1);

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    for(int i=2; i<=100000; i++){
        if(isprime[i]){
            for(int j=i+i; j<=100000; j+=i) isprime[j] = 0, mb[j] *= -1;
            mb[i] *= -1;
            for(ll j = (ll)i*i; j<=100000; j+=(ll)i*i) mb[j] = 0;
        }
    }
    
    int tt; cin >> tt;
    while(tt--){
        int n, k; cin >> n >> k;
        vector<int> v(100001);
        for(int i=0; i<n; i++){
            int a; cin >> a; v[a]++;
        }
        if(k >= 3){
            cout << "99999\n"; continue;
        }

        vector<ll> cnt(100001);
        for(int i=1; i<=100000; i++){
            ll o = 0;
            for(int j=i; j<=100000; j+=i){
                o += v[j];
            }
            cnt[i] = o*(o-1)/2;
        }

        for(int i=1; i<=100000; i++){
            for(int j=i+i, o=2; j<=100000; j+=i, o++){
                cnt[i] += cnt[j]*mb[o];
            }
        }
        
        int mn = 1, mx = 100000; // probably no case for cnt[1~100000] = 1
        while(!cnt[mn]) mn++;
        while(!cnt[mx]) mx--;
        if(k == 0){
            cout << mx - mn << "\n";
        }

        else if(k == 1){
            int ans = mx - mn;
            int mx1 = 100000;
            while(!v[mx1]) mx1--;
            ans = max(ans, mx1 - mn);
            ans = max(ans, mx - 1);
            cout << ans << "\n";
        }

        else if(k == 2){
            // add p,p
            int ans = mx - mn;
            for(int p=100000; p>=99991; p--){
                int mn1 = 100000;
                for(int i=1; i<=100000; i++){
                    if(v[i]){
                        mn1 = min(mn1, __gcd(p, i));
                    }
                }
                ans = max(ans, p - mn1);
            }
            int mx1 = 100000;
            while(!v[mx1]) mx1--;
            ans = max(ans, mx1 - 1);
            cout << ans << "\n";
        }
    }
    return 0;
}