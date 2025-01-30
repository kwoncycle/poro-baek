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
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    ll n, m; cin >> n >> m;
    vector<array<int, 3>> v(m);
    vector<int> deg(m);
    vector<vector<int>> go_in(m);
    int id = 0;
    for(auto &[i,j,k]:v){
        char c; cin >> c; 
        if(c == 'L') i = 0;
        else i = 1;
        cin >> j >> k;
        j--; k--;
        if(j >= 0) deg[id]++;
        if(k >= 0) deg[id]++;

        if(j >= 0) go_in[j].push_back(id);
        if(k >= 0) go_in[k].push_back(id);
        id++;
    }

    vector<int> dag;
    queue<int> q;
    for(int i=0; i<m; i++){
        if(!deg[i]) q.push(i);
    }

    while(!q.empty()){
        int j = q.front(); q.pop();
        dag.push_back(j);
        for(int i:go_in[j]){
            deg[i]--;
            if(deg[i] == 0 and i) q.push(i);
        }
    }
    vector<ll> cnt(m, 0);
    dag.push_back(0);
    cnt[0] = n;
    reverse(dag.begin(), dag.end());
    for(int i:dag){
        if(v[i][0] == (int)0){
            if(v[i][1]>=0) cnt[v[i][1]] += (cnt[i]+1)/2;
            if(v[i][2]>=0) cnt[v[i][2]] += (cnt[i])/2;
        }
        else{
            if(v[i][2]>=0) cnt[v[i][2]] += (cnt[i]+1)/2;
            if(v[i][1]>=0) cnt[v[i][1]] += (cnt[i])/2;
        }
    }

    for(int i=0; i<m; i++){
        if(cnt[i]%2 == 1) v[i][0] = 1 - v[i][0];
        cout << (v[i][0] ? 'R' : 'L');
    }
    cout << "\n";
    
    return 0;
}