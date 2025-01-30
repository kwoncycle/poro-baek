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
    while(tt--){
        int n; cin >> n;
        vector<int> v(n);
        int truth = 0;
        for(int i=0; i<n; i++){
            cin >> v[i];
            if(v[i] != v[0]) truth = 1;
        }
        if(!truth) cout << "NO\n";
        else{
            cout << "YES\n";
            vector<int> check(n);
            vector<int> idx(n+1, -1);
            for(int i=0; i<n; i++){
                idx[v[i]] = i;
            }
            vector<pii> s;
            for(int i=1; i<=n; i++){
                if(idx[i] >= 0) check[idx[i]] = 1, s.push_back({i, idx[i]});
            }
            s.push_back(s[0]);
            for(int i=1, j=0; i<=n; i++){
                if(idx[i] == -1){
                    while(check[j] == 1) j++;
                    idx[i] = j;
                    check[j] = 1;
                }
            }
            for(int i=0; i<(int)s.size()-1; i++){
                idx[s[i].X] = s[i+1].Y;
            }
            vector<int> ans(n);
            for(int i=1; i<=n; i++){
                ans[idx[i]] = i;
            }
            for(int i:ans) cout << i << " "; cout << "\n";
        }
    }
    return 0;
}