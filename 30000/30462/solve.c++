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
    int n; cin >> n;
    vector<int> a(n);
    for(auto &i:a) cin >> i;
    int cur = 1;
    vector<int> ans(n);
    for(int i=0; i<n-1; i++){
        if(a[i] > a[i+1]){
            cout << "No\n"; return 0;
        }
    }
    if(a[n-1] != n+1){
        cout << "No\n"; return 0;
    }
    vector<int> check(n+1);
    for(int i=0; i<n; i++){
        if((i-1>=0 ? a[i-1] : 1) != a[i]) {
            ans[i] = (i-1>=0 ? a[i-1] : 1);
            check[ans[i]] = 1;
        }
    }

    vector<int> v;
    for(int i=1; i<=n; i++) if(!check[i]) v.push_back(i);
    reverse(v.begin(), v.end());
    for(int i=0; i<n; i++){
        if(!ans[i]) ans[i] = v.back(), v.pop_back();
    }

    int id = 1;
    for(auto &i:check) i = 1;
    for(int i=0; i<n; i++){
        check[ans[i]] = 0;
        while(id <= n and check[id] == 0) id++;
        if(a[i] != id){
            cout << "No\n"; return 0;
        }
    }
    cout << "Yes\n";
    for(auto i:ans) cout << i << " "; cout << "\n";
    return 0;
}