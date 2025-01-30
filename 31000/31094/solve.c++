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

vector<array<int, 4>> edges;
vector<vector<int>> graph;
vector<int> depth;
vector<int> par; // edges
vector<vector<int>> parse_table; 
vector<int> nearest;
vector<int> par_edge;
vector<ll> loss;


void DFS(int x){
    for(int i:graph[x]){
        if(depth[i]) continue;
        depth[i] = depth[x] + 1;
        DFS(i);
    }
}


int lca(int x, int y){
    if(depth[x] != depth[y]){
        if(depth[x] < depth[y]) swap(x, y);
        while(depth[x] > depth[y]){
            int o = 1, idx = 0;
            while(depth[y] <= depth[x] - o*2){
                o *= 2; idx++;
            }
            x = parse_table[x][idx];
        }
    }

    if(x == y) return x;
    while(x != y){
        if(par[x] == par[y]){
            x = par[x]; y = par[y];
        }
        else{
            int idx = 0;
            while(parse_table[x][idx + 1] != parse_table[y][idx + 1]) idx++;
            x = parse_table[x][idx];
            y = parse_table[y][idx];
        }
    }
    return x;

}

void DFS_near(int x){
    if(par[x] != -1 and edges[par_edge[x]][3] >= 2){
        nearest[x] = x;
    }
    for(int i:graph[x]){
        if(depth[i] < depth[x]) continue;
        nearest[i] = nearest[x];
        DFS_near(i);
    }
}

void DFS_loss(int x){
    if(par[x] != -1){
        loss[x] = loss[par[x]] + edges[par_edge[x]][2];
    }
    for(int i:graph[x]){
        if(depth[i] < depth[x]) continue;
        DFS_loss(i);
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    edges.resize(n-1);
    for(int i=0; i<n-1; i++) cin >> edges[i][0] >> edges[i][1] >> edges[i][2] >> edges[i][3];
    graph.resize(n+1);
    depth.resize(n+1);
    par.resize(n+1);
    parse_table = vector<vector<int>>(n+1, vector<int>(20, -1));
    nearest.resize(n+1, -1);
    par_edge.resize(n+1);
    loss.resize(n+1);
    for(int i=0; i<n-1; i++){
        graph[edges[i][0]].push_back(edges[i][1]);
        graph[edges[i][1]].push_back(edges[i][0]);
    }

    depth[1] = 1;
    DFS(1);
    for(int i=0; i<n-1; i++){
        int o = edges[i][0];
        if(depth[o] < depth[edges[i][1]]) o = edges[i][1];
        par[o] = edges[i][0] + edges[i][1] - o;
        par_edge[o] = i;
    }
    par[1] = -1;
    for(int i=1; i<=n; i++) parse_table[i][0] = par[i];
    for(int d=1; d<20; d++){
        for(int i=1; i<=n; i++){
            if(parse_table[i][d-1] == -1) continue;
            parse_table[i][d] = parse_table[parse_table[i][d-1]][d-1];
        }
    }

    DFS_near(1);
    DFS_loss(1);

    int qq; cin >> qq;
    while(qq--){
        ll a, b, e; cin >> a >> b >> e;
        int o = lca(a, b);
        int cnt = 0;
        int a1 = a;
        vector<int> path;
        path.push_back(a);
        while(cnt < 64){
            int a2 = par[nearest[a1]];
            if(depth[a2] < depth[o]) break;
            path.push_back(nearest[a1]);
            path.push_back(a2);
            a1 = a2;
            cnt++;
        }
        path.push_back(o);

        vector<int> path1;
        path1.push_back(b);
        int b1 = b;
        while(cnt < 64){
            int b2 = par[nearest[b1]];
            if(depth[b2] < depth[o]) break;
            path1.push_back(nearest[b1]);
            path1.push_back(b2);
            b1 = b2;
            cnt++;
        }
        path1.push_back(o);

        if(cnt >= 64){
            cout << "0\n"; continue;
        }

        
        for(int i=0; i<(int)path.size()-1; i++){
            if(path[i] == path[i+1]) continue;
            else if(par[path[i]] == path[i+1]){
                auto &[asdf, asdf1, r, z] = edges[par_edge[path[i]]];
                e = (max(e-r, 0ll))/z;
            }
            else{
                ll o = loss[path[i]] - loss[path[i+1]];
                e = max(e - o, 0ll);
            }
        }

        for(int i=(int)path1.size()-2; i>=0; i--){
            if(path1[i] == path1[i+1]) continue;
            else if(par[path1[i]] == path1[i+1]){
                auto &[asdf, asdf1, r, z] = edges[par_edge[path1[i]]];
                e = (max(e-r, 0ll))/z;
            }
            else{
                ll o = loss[path1[i]] - loss[path1[i+1]];
                e = max(e - o, 0ll);
            }
        }

        cout << e << "\n";


    }


    return 0;
}