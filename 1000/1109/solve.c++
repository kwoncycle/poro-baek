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

class djs
{
    int n, m;
    vector<vector<pii>> par;
 
public:
    djs(int n, int m) : n(n), m(m) {
        par = vector<vector<pii>>(n, vector<pii>(m));
        for(int i=0; i<n; i++) for(int j=0; j<m; j++) par[i][j] = {i,j};
    }
 
    pii find(pii v) {
        if(par[v.X][v.Y] == v) return v;
        else return par[v.X][v.Y] = find(par[v.X][v.Y]);
    }
 
    bool Union(pii x, pii y) {
        pii px = find(x);
        pii py = find(y);
 
        if(px == py) return false;
 
        par[px.X][px.Y] = py;
        return true;
    }
};
// Usage: djs DJS(n)
vector<vector<int>> visited(60, vector<int>(60, 0));
vector<vector<pii>> where(60, vector<pii>(60));
vector<string> v;
vector<pii> dir8, dir4 = {{-1,0},{1,0},{0,1},{0,-1}};
int n, m;
void DFS(pii now, pii isl1){
    for(auto &[i1, j1]: dir4){
        if(0<=i1+now.X and i1+now.X<=n+1 and 0<=j1+now.Y and j1+now.Y<=m+1){
            if(!visited[i1+now.X][j1+now.Y] and !(v[i1+now.X][j1+now.Y] == 'x' and where[i1+now.X][j1+now.Y] == isl1)){
                visited[i1+now.X][j1+now.Y] = 1;
                DFS({i1+now.X, j1+now.Y}, isl1);
            }
        }
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    djs DJS(n+2, m+2);
    v.resize(n+2);
    for(int i=1; i<=n; i++) {
        cin >> v[i]; v[i] = "." + v[i] + ".";
    }
    v[0] = string(m+2, '.');
    v[n+1] = string(m+2, '.');

    int truth = 0;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++) if(v[i][j] == 'x') truth = 1;
    }

    if(!truth){
        cout << "-1\n"; return 0;
    }


    
    for(int i=-1; i<=1; i++) for(int j=-1; j<=1; j++) if(i or j) dir8.push_back({i,j});

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(v[i][j] == 'x'){
                for(auto &[i1, j1]:dir8){
                    if(v[i+i1][j+j1] == 'x'){
                        DJS.Union({i,j}, {i+i1, j+j1});
                    }
                }
            }
        }
    }

    vector<pii> island;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(DJS.find({i,j}) == pii(i,j) and v[i][j] == 'x') island.push_back({i,j});
        }
    }

    
    for(int i=0; i<=n+1; i++){
        for(int j=0; j<=m+1; j++){
            if(v[i][j] == '.') where[i][j] = {i,j};
            else where[i][j] = DJS.find({i,j});
        }
    }

    vector<vector<int>> graph_in((int)island.size()), graph_out((int)island.size()); // j in graph_in[i] -> i(   j  )i
    vector<int> deg((int)island.size());
    vector<int> level((int)island.size());
    queue<pii> q;
    for(int i=0; i<(int)island.size(); i++){
        pii isl1 = island[i];
        for(int t1=0; t1<=n+1; t1++) visited[t1] = vector<int>(m+2, 0);
        DFS({0,0}, isl1);
        for(int j=0; j<(int)island.size(); j++){
            if(i == j) continue;
            if(visited[island[j].X][island[j].Y] == 0){
                graph_in[i].push_back(j);
                graph_out[j].push_back(i);
            }
        }
    }

    queue<int> q1;
    for(int i=0; i<(int)island.size(); i++){
        deg[i] = graph_in[i].size();
        if(deg[i] == 0) q1.push(i);
    }

    while(!q1.empty()){
        int i = q1.front(); q1.pop();
        if(graph_in[i].empty()){
            level[i] = 0;
        }
        else{
            int mx = 0;
            for(int j:graph_in[i]) mx = max(mx, level[j]);
            level[i] = mx+1;
        }

        for(int j:graph_out[i]){
            deg[j]--;
            if(deg[j] == 0) q1.push(j);
        }
    }
    /*
    for(int i=0; i<(int)island.size(); i++){
        cout << island[i].X << " " << island[i].Y << " " << level[i] << "\n";
    }*/

    vector<int> cnt(100000, 0);
    int mx = 0;
    for(int i=0; i<(int)level.size(); i++){
        mx = max(mx, level[i]);
        cnt[level[i]]++;
    }
    for(int i=0; i<=mx; i++){
        cout << cnt[i] << " ";
    }
    cout << "\n";
    return 0;
}