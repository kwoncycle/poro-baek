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
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n;
    cin >> n;
    vector<int> isprime(100001, 1);
    for(int i=2; i<=100000; i++){
        if(isprime[i]){
            for(int j=i+i; j<=100000; j+=i) isprime[j] = 0;
        }
    }

    vector<pii> ans;
    for(int i=1; i<=n; i+=2) ans.push_back({1, i});
    for(int i=2; i<=n; i++) if(!isprime[i]) ans.push_back({2, i});
    cout << ans.size() << "\n";
    for(auto [i,j]:ans) cout << i << " " << j << "\n";
    return 0;
}