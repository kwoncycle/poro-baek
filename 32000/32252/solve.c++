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
            graph[u].push_back({c, v});
            graph[v].push_back({c, u});
        }

        if(DJS.find(s) == DJS.find(e)){
            cout << "0\n"; return;
        }

        vector<int> q;
        vector<pii> par(n+1, {-1, -1});
        vector<int> level(n+1, -1);
        for(int i=1; i<=n; i++){
            if(DJS.find(i) == DJS.find(s)){
                q.push_back(i);
                level[i] = s;
            }
        }
        
        int id = 0;
        vector<array<int, 2>> V0, V1;
        while(id < (int)q.size()){
            int i1 = id;
            while(i1 < (int)q.size() and level[q[i1]] == level[q[id]]){
                for(auto [val, j]:graph[q[i1]]){
                    if(val == 0 and level[j] == -1){
                        V0.push_back({j, q[i1]});
                    }
                    else if(val == 1 and level[j] == -1){
                        V1.push_back({j, q[i1]});
                    }
                }
                i1++;
            }
            int lv = -1;
            for(auto &[i, before]:V0){
                if(level[i] == -1){
                    if(lv == -1) lv = i;
                    level[i] = lv;
                    par[i] = {0, before};
                    q.push_back(i);
                }
            }
            lv = -1;
            for(auto &[i, before]:V1){
                if(level[i] == -1){
                    if(lv == -1) lv = i;
                    level[i] = lv;
                    par[i] = {1, before};
                    q.push_back(i);
                }
            }
            id = i1;
            V0.clear();
            V1.clear();
        }
        vector<int> ans;
        while(level[e] != level[s]){
            ans.push_back(par[e].X);
            e = par[e].Y;
        }
        reverse(ans.begin(), ans.end());
        for(int i:ans) {
            cout << i;
        } 
        cout << "\n";
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve s;
    return 0;
}