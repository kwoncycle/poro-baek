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

int DP[505][505];
vector<int> graph[505];
int deg[505];
vector<int> order;
int G[500005];
int color[504];


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    for(int i=0; i<m; i++){
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
    }
    for(int i=1; i<=n; i++){
        sort(all(graph[i]));
        graph[i].erase(unique(all(graph[i])), graph[i].end());
        for(int j:graph[i]) deg[j]++;
    }

    int id = 0;
    queue<int> q;
    for(int i=1; i<=n; i++){
        if(deg[i] == 0) q.push(i);
    }
    while(!q.empty()){
        int node = q.front(); q.pop();
        order.push_back(node);
        for(int i:graph[node]){
            deg[i]--;
            if(!deg[i]) q.push(i);
        }
    }
    reverse(all(order));

    for(int i:order){
        if(graph[i].empty()) DP[i][i] = 0;
        else{
            for(int nxt:graph[i]){
                G[DP[nxt][nxt]] = 1;
            }
            id = 0;
            while(G[id]) id++;
            DP[i][i] = id;
            for(int nxt:graph[i]){
                G[DP[nxt][nxt]] = 0;
            }
        }
    }

    for(int i:order){
        for(int j:order){
            if(i == j) continue;
            for(int nxt:graph[i]){
                G[DP[nxt][j]] = 1;
            }
            for(int nxt:graph[j]){
                G[DP[i][nxt]] = 1;
            }
            id = 0;
            while(G[id]) id++;
            DP[i][j] = id;
            for(int nxt:graph[i]){
                G[DP[nxt][j]] = 0;
            }
            for(int nxt:graph[j]){
                G[DP[i][nxt]] = 0;
            }
        }
    }

    int ans = 0;
    int k; cin >> k;
    while(k--){
        int v, c; cin >> v >> c;
        if(!color[c]) color[c] = v;
        else{
            ans ^= DP[color[c]][v];
            color[c] = 0;
        }
    }
    for(int i=1; i<=n; i++){
        if(color[i]) ans ^= DP[color[i]][color[i]];
    }

    if(ans) cout << "Young\n";
    else cout << "Cheol\n";


    return 0;
}