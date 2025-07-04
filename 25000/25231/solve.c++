#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

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

int n, m;
string s[505];
pii G[505][505], where[505][505];
int visited[505][505], deg[505][505], depth[505][505], DP[505][505];
vector<pii> Gi[505][505];

pii sparse[505][505][20];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    s[0] = string(m+2, '.');
    s[n+1] = string(m+2, '.');
    for(int i=1; i<=n; i++){
        cin >> s[i]; s[i] = "." + s[i] + ".";
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(s[i][j] == 'v') {
                deg[i+1][j]++;
                G[i][j] = {i+1, j}; Gi[i+1][j].push_back({i,j});
            }
            else if(s[i][j] == '^') {
                deg[i-1][j]++;
                G[i][j] = {i-1, j}; Gi[i-1][j].push_back({i,j});
            }
            else if(s[i][j] == '>') {
                deg[i][j+1]++;
                G[i][j] = {i, j+1}; Gi[i][j+1].push_back({i,j});
            }
            else if(s[i][j] == '<') {
                deg[i][j-1]++;
                G[i][j] = {i, j-1}; Gi[i][j-1].push_back({i,j});
            }
        }
    }
    vector<pii> order;
    queue<pii> q;
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            pii cur = {i,j}, nxt;
            while(!deg[cur.X][cur.Y] and s[cur.X][cur.Y] != '#' and s[cur.X][cur.Y] != '.' and !visited[cur.X][cur.Y]){
                visited[cur.X][cur.Y] = 1;
                nxt = cur;
                cur = G[cur.X][cur.Y];
                deg[cur.X][cur.Y]--;
            }
            if(s[cur.X][cur.Y] == '#' or s[cur.X][cur.Y] == '.'){
                q.push(nxt); where[nxt.X][nxt.Y] = nxt;
            }
        }
    }
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(!visited[i][j] and deg[i][j]){
                pii cur = {i, j}; q.push({i, j});
                vector<pii> circle;
                while(true){
                    cur = G[cur.X][cur.Y];
                    where[cur.X][cur.Y] = {i,j};
                    visited[cur.X][cur.Y] = 1;
                    circle.push_back(cur);
                    if(cur == pii{i,j}) break;
                    
                }
                vector<pii> nw;
                for(auto &c:circle){
                    for(auto &p:Gi[c.X][c.Y]){
                        if(where[p.X][p.Y] != pii{i,j}) {
                            nw.push_back(p);
                        }
                        Gi[c.X][c.Y].clear();
                    }
                }
                Gi[i][j] = nw;
            }
        }
    }
    
    while(!q.empty()){
        pii node = q.front(); q.pop(); order.push_back(node);
        for(auto p:Gi[node.X][node.Y]) {
            q.push(p);
            depth[p.X][p.Y] = depth[node.X][node.Y] + 1;
        }
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            sparse[i][j][0] = G[i][j];
        }
    }

    for(int d=1; d<20; d++){
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                sparse[i][j][d] = sparse[sparse[i][j][d-1].X][sparse[i][j][d-1].Y][d-1];
            }
        }
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(s[i][j] == '#'){
                vector<pii> v = {{i+1, j}, {i-1, j}, {i, j+1}, {i, j-1}};
                vector<pii> v1;
                for(auto &[x,y]:v){
                    if(s[x][y] != '#' and s[x][y] != '.') v1.push_back({x, y});
                }
                sort(all(v1), [&](pii l, pii r){
                    return depth[l.X][l.Y] > depth[r.X][r.Y];
                });
                int sz = v1.size();
                for(int i1=0; i1<sz; i1++){
                    int truth = 1;
                    for(int j1=i1+1; j1<sz; j1++){
                        pii cur = v1[i1];
                        if(depth[v1[i1].X][v1[i1].Y] > depth[v1[j1].X][v1[j1].Y]){
                            int o = depth[v1[i1].X][v1[i1].Y] - depth[v1[j1].X][v1[j1].Y];
                            for(int d=0; d<20; d++){
                                if((o>>d)&1){
                                    cur = sparse[cur.X][cur.Y][d];
                                }
                            }
                        }
                        if(depth[cur.X][cur.Y] != 0){
                            if(cur == v1[j1]){
                                truth = 0; break;
                            }
                        }
                        else{
                            if(where[cur.X][cur.Y] == where[v1[j1].X][v1[j1].Y]){
                                truth = 0; break;
                            }
                        }
                    }
                    if(truth){
                        //cout << i << "," << j << " added " << v1[i1].X << "," << v1[i1].Y << "\n";
                        DP[v1[i1].X][v1[i1].Y]++;
                    }
                }
            }
        }
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(where[i][j] != pii(0,0)){
                if(where[i][j] != pii(i,j)) DP[where[i][j].X][where[i][j].Y] += DP[i][j];
            }
        }
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(where[i][j] != pii(0,0)){
                DP[i][j] = DP[where[i][j].X][where[i][j].Y];
            }
        }
    }
    for(auto &[x,y]:order){
        if(depth[x][y]){
            DP[x][y] += DP[G[x][y].X][G[x][y].Y];
        }
    }

    int mx = 0;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++) mx = max(mx, DP[i][j]);
    }
    cout << mx << "\n";

    return 0;
}