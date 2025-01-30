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
    int n; cin >> n;
    vector<int> v(n+1);
    vector<int> deg(n+1, 1);
    priority_queue<int> pq;
    for(int i=1; i<=n-2; i++){
        cin >> v[i];
        deg[v[i]]++;
    }
    for(int i=1; i<=n; i++){
        if(deg[i] == 1) pq.push(i);
    }

    vector<pii> ans;
    for(int d=1; d<=n-2; d++){
        if(pq.empty()){
            cout << "-1\n"; return 0;
        }
        int o = pq.top(); pq.pop();
        deg[o]--;
        deg[v[d]]--;
        ans.push_back({o, v[d]});
        if(deg[v[d]] == 1) pq.push(v[d]);
    }
    vector<int> dg1;
    for(int i=1; i<=n; i++) {
        if(deg[i] == 1) dg1.push_back(i);
        else if(deg[i] == 0) continue;
        else{
            cout << "-1\n"; return 0;
        }
    }
    if(dg1.size() != 2){
        cout << "-1\n"; return 0;
    }
    ans.push_back({dg1[0], dg1[1]});
    for(auto &[i, j]:ans){
        if(i > j) swap(i, j);
    }
    sort(ans.begin(), ans.end());
    for(auto [i,j]:ans) cout << i << " " << j << "\n";
    return 0;
}