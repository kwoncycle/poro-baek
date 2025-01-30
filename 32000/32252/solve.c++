#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()



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
 

struct solve{
    int n, m, s, e;
    vector<vector<array<int, 2>>> graph;
    solve(){
        cin >> n >> m >> s >> e;
        graph.resize(n+1);
        vector<array<int, 3>> edge(m);
        djs DJS(n+10);
        for(auto &[i,j,k]:edge) {
            cin >> i >> j >> k;
            if(k==0) DJS.Union(i, j);
        }

        for(auto &[u, v, c]:edge){
            //if(DJS.find(u) == DJS.find(s)) u = s;
            //if(DJS.find(v) == DJS.find(s)) v = s;
            graph[u].push_back({c, v});
            graph[v].push_back({c, u});
        }

        if(DJS.find(s) == DJS.find(e)){
            assert(false);
            cout << "0\n"; return;
        }

        for(int i=1; i<=n; i++){
            sort(all(graph[i]));
        }

        queue<int> q;
        vector<int> dst(n+1, 0x3f3f3f3f);
        vector<pii> par(n+1, {-1, -1});
        for(int i=1; i<=n; i++){
            if(DJS.find(i) == DJS.find(s)){
                dst[i] = 0;
                q.push(i);
            }
        }
        while(!q.empty()){
            int i = q.front(); q.pop();
            for(auto [v, j]:graph[i]){
                if(dst[j] == 0x3f3f3f3f){
                    dst[j] = dst[i] + 1;
                    par[j] = {v, i};
                    q.push(j);
                }
                else assert(dst[j] <= dst[i] + 1);
            }
        }
        vector<int> ans;
        while(dst[e] > 0){
            assert(par[e].X != -1);
            assert(e != -1);
            ans.push_back(par[e].X);
            e = par[e].Y;
        }
        assert(dst[e] == 0 and DJS.find(e) == DJS.find(s));
        reverse(ans.begin(), ans.end());
        assert(!ans.empty());
        assert(ans[0]);
        //for(int i=1; i<=n; i++) cout << dst[i] << " "; cout << "\n";
        for(int i:ans) {
            assert(i >= 0 and i <= 1);
            cout << i;
        } cout << "\n";
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve ss;
    return 0;
}