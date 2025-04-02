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


int n, m;
string v[505];
vector<pii> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
pii DP[4][505][505];
int wall_dist[505][505];

bool isin(pii p){
    return 0<=p.X and p.X<n and 0<=p.Y and p.Y<m;
}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    for(int i=0; i<n; i++) cin >> v[i];

    {
    int d = 0;

    for(int i=n-1; i>=0; i--){
        for(int j=0; j<m; j++){
            if(v[i][j] == '#') continue;
            auto [x, y] = pii(i, j) + dir[d];
            if(isin({x,y}) and v[x][y] != '#'){
                DP[d][i][j] = DP[d][x][y];
            }
            else DP[d][i][j] = {i, j};
        }
    }

    d = 1;
    for(int i=0; i<n; i++){
        for(int j=m-1; j>=0; j--){
            if(v[i][j] == '#') continue;
            auto [x, y] = pii(i, j) + dir[d];
            if(isin({x,y}) and v[x][y] != '#'){
                DP[d][i][j] = DP[d][x][y];
            }
            else DP[d][i][j] = {i, j};
        }
    }

    d = 2;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == '#') continue;
            auto [x, y] = pii(i, j) + dir[d];
            if(isin({x,y}) and v[x][y] != '#'){
                DP[d][i][j] = DP[d][x][y];
            }
            else DP[d][i][j] = {i, j};
        }
    }

    d = 3;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == '#') continue;
            auto [x, y] = pii(i, j) + dir[d];
            if(isin({x,y}) and v[x][y] != '#'){
                DP[d][i][j] = DP[d][x][y];
            }
            else DP[d][i][j] = {i, j};
        }
    }
    }

    queue<pii> q;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            wall_dist[i][j] = 0x3f3f3f;
            if(v[i][j] == '#') continue;
            for(int d=0; d<4; d++){
                auto [x, y] = pii(i, j) + dir[d];
                if(isin({x,y}) and v[x][y] == '#'){
                    wall_dist[i][j] = 0; 
                    q.push({i, j});
                    break;
                }
            }
        }
    }

    while(!q.empty()){
        auto [i, j] = q.front(); q.pop();
        for(auto &[i1, j1]:dir){
            if(isin({i+i1, j+j1}) and v[i+i1][j+j1] != '#'){
                if(wall_dist[i+i1][j+j1] > wall_dist[i][j] + 1){
                    wall_dist[i+i1][j+j1] = wall_dist[i][j] + 1;
                    q.push({i+i1, j+j1});
                }
            }
        }
    }

    #define A3 array<int, 3>
    vector<vector< vector<A3> >> G(n, vector<vector<A3>>(m));

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] != '#'){
                for(auto &[i1, j1]:dir){
                    if(isin({i+i1, j+j1}) and v[i+i1][j+j1] != '#'){
                        G[i][j].push_back({i+i1, j+j1, 1});
                    }
                }
                for(int d=0; d<4; d++){
                    auto [i1, j1] = DP[d][i][j];
                    G[i][j].push_back({i1, j1, wall_dist[i][j] + 1});
                }
            }
        }
    }

    pii C, F;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == 'C') C = {i, j};
            if(v[i][j] == 'F') F = {i, j};
        }
    }

    priority_queue<A3, vector<A3>, greater<A3>> pq;
    vector<vector<int>> dist(n, vector<int>(m, 0x3f3f3ff));

    dist[C.X][C.Y] = 0;
    pq.push({0, C.X, C.Y});
    while(!pq.empty()){
        auto [d, x, y] = pq.top(); pq.pop();
        if(d > dist[x][y]) continue;
        
        for(auto &[x1, y1, d1]: G[x][y]){
            if(d1 + dist[x][y] < dist[x1][y1]){
                dist[x1][y1] = d1 + dist[x][y];
                pq.push({dist[x1][y1], x1, y1});
            }
        }
    }
    
    if(dist[F.X][F.Y] == 0x3f3f3ff) cout << "nemoguce\n";
    else cout << dist[F.X][F.Y] << "\n";

    return 0;
}