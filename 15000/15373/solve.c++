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

int cnt2(int i, int p){
    int sm = 0;
    while(i){
        i /= p; sm += i;
    }
    return sm;
}

int ans[200005];
int pm[200005];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    ans[1] = 1;
    pm[1] = 1;
    for(int i=2; i<=200000; i++){
        if(pm[i] == 0){
            for(int j=i; j<=200000; j+=i){
                if(pm[j] == 0) pm[j] = i;
            }
        }
    }

    for(int i=2; i<=200000; i++){
        int i1 = i;
        int a = ans[i-1];
        while(i1 > 1){
            int p = pm[i1];
            while(i1 % p == 0) i1 /= p;
            int o = cnt2(i, p);
            while(o*2 > cnt2(a, p)) a++;
        }
        ans[i] = a;
    }


    int tt; cin >> tt;
    while(tt--){
        ll n; cin >> n;
        cout << ans[n] << "\n";

    }
    return 0;
}