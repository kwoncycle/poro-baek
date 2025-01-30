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

class djs
{
    int n;
    vector<int> par;
 
public:
    djs(int n) : n(n) {
        par.resize(n);
        for(int i=0; i<n; i++) par[i] = i;
    }
 
    int find(int v) {
        if(par[v] == v) return v;
        else return par[v] = find(par[v]);
    }
 
    bool Union(int x, int y) {
        int px = find(x);
        int py = find(y);
 
        if(px == py) return false;
 
        par[px] = py;
        return true;
    }
};
// Usage: djs DJS(n)

vector<int> color;
vector<vector<int>> graph;

void BFS(int i, int p){
    for(int j:graph[i]){
        if(j == p) continue;
        if(color[j] == -1){
            color[j] = 1 - color[i];
            BFS(j, i);
        }
    }
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    graph = vector<vector<int>>(n+1);
    color = vector<int>(n+1, -1);
    vector<pair<pii, ll>> edge(m);
    for(int i=0; i<m; i++){
        int v, w, x; cin >> v >> w >> x;
        edge[i] = {{v,w}, x};
    }
    if(k % 2 == 1){
        int truth = 1;
        for(auto e:edge){
            if(e.Y % k) truth = 0;
        }
        if(truth) cout << "Yes\n";
        else cout << "No\n";
        return 0;
    }

    else{
        int truth = 1;
        for(auto e:edge){
            if((2 * e.Y) % k) truth = 0;
        }
        if(!truth){
            cout << "No\n"; return 0;
        }

        djs DJS(n+1);
        for(int i=0; i<m; i++){
            int v = edge[i].X.X, w = edge[i].X.Y, x = edge[i].Y;
            if(((x*2)/k) % 2 == 0){
                DJS.Union(v, w);
            }
        }

        for(int i=0; i<m; i++){
            int v = edge[i].X.X, w = edge[i].X.Y, x = edge[i].Y;
            if(((x*2)/k) % 2 == 1){
                int iv = DJS.find(v), iw = DJS.find(w);
                graph[iw].push_back(iv);
                graph[iv].push_back(iw);
            }
        }
        for(int i=1; i<=n; i++){
            if(color[DJS.find(i)] != -1) continue;
            color[DJS.find(i)] = 0;
            BFS(DJS.find(i), -1);
        }
        for(int i=0; i<m; i++){
            int v = edge[i].X.X, w = edge[i].X.Y, x = edge[i].Y;
            if(((x*2)/k) % 2 == 1){
                int iv = DJS.find(v), iw = DJS.find(w);
                if(color[iv] == color[iw]) truth = 0;
            }
        }
        if(truth) cout << "Yes\n";
        else cout << "No\n";
        return 0;
    }
    return 0;
}