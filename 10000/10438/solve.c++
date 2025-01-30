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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    vector<ll> v(10005), pr(10005);
    pr[1] = 1;
    for(int i=2; i<=10000; i++){
        int i1 = i;
        int ans = 1;
        for(int j=2; j*j<=i1; j++){
            if(i1%j == 0){
                ans *= j-1; i1 /= j;
                for(; i1%j==0; i1/=j, ans *= j) ;
            }
        }
        if(i1 > 1) ans *= i1-1;
        pr[i] = ans;
    }
    v[1] = 2;
    for(int i=2; i<=10000; i++) v[i] = v[i-1] + 3*pr[i];
    while(tt--){
        int i, j; cin >> i >> j;
        cout << i << " ";
        if(v[j]%2 == 0) cout << v[j]/2 << "\n";
        else cout << v[j] << "/2\n";
    }

    return 0;
}