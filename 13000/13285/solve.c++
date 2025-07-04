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

struct DSU{
    pii par[103][103];
    DSU(int n, int m){
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                par[i][j] = {i, j};
            }
        }
    }
    pii find(pii r){
        if(par[r.X][r.Y] == r) return r;
        return par[r.X][r.Y] = find(par[r.X][r.Y]);
    }

    bool U(pii l, pii r){
        l = find(l); r = find(r);
        if(l == r) return false;
        par[l.X][l.Y] = r;
        return true;
    }
};

const int b0[8] = {1, 0, -1, -1, -1, 0, 1, 1};
const int b1[8] = {1, 1, 1, 0, -1, -1, -1, 0};
const int w0[4] = {1, 0, -1, 0};
const int w1[4] = {0, 1, 0, -1};

ll hashconst[300000];

#define MOD 164002245929869069ll

struct solve{
    int n, m;
    string s[103];
    vector<pii> graph[103][103];
    ll val;
    solve(){ // get tree-hash
        cin >> n >> m;
        if(n == 0 and m == 0) exit(0);
        s[0] = string(m+2, '.');
        s[n+1] = string(m+2, '.');
        for(int i=1; i<=n; i++){
            cin >> s[i];
            s[i] = '.' + s[i] + '.';
        }
        DSU D(n+2, m+2);
        for(int i=0; i<=n+1; i++){
            D.par[i][0] = {0, 0};
            D.par[i][m+1] = {0, 0};
        }
        for(int j=0; j<=m; j++){
            D.par[0][j] = {0, 0};
            D.par[n+1][j] = {0, 0};
        }
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                if(s[i][j] == '.'){ // white
                    for(int t=0; t<4; t++){
                        if(s[i+w0[t]][j+w1[t]] == '.'){
                            D.U({i,j}, {i+w0[t], j+w1[t]});
                        }
                    }
                }
                else{
                    for(int t=0; t<8; t++){
                        if(s[i+b0[t]][j+b1[t]] == '#'){
                            D.U({i,j}, {i+b0[t], j+b1[t]});
                        }
                    }
                }
            }
        }

        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                pii p1 = D.find({i, j});
                if(s[i][j] == '.'){ // white
                    for(int t=0; t<4; t++){
                        if(s[i+w0[t]][j+w1[t]] != '.'){
                            pii p2 = D.find({i+w0[t], j+w1[t]});
                            graph[p1.X][p1.Y].push_back(p2);
                            graph[p2.X][p2.Y].push_back(p1);
                        }
                    }
                }
                else{
                    for(int t=0; t<8; t++){
                        if(s[i+b0[t]][j+b1[t]] != '#'){
                            pii p2 = D.find({i+b0[t], j+b1[t]});
                            graph[p1.X][p1.Y].push_back(p2);
                            graph[p2.X][p2.Y].push_back(p1);
                        }
                    }
                }
            }
        }
        for(int i=0; i<=n+1; i++){
            for(int j=0; j<=m+1; j++){
                if(!graph[i][j].empty()){
                    sort(all(graph[i][j]));
                    graph[i][j].erase(unique(all(graph[i][j])), graph[i][j].end());
                }
            }
        }
        val = DFS(D.find({0, 0}), {-1, -1});
    }

    ll DFS(pii node, pii par){
        vector<ll> V;
        for(auto &p:graph[node.X][node.Y]){
            if(p == par) continue;
            ll o = DFS(p, node);
            V.push_back(o);
        }
        sort(all(V));
        return hashvec(V);
    }

    ll hashvec(vector<ll> &v){
        if(v.empty()) return 0x888481557ll;
        ll cur = 0;
        for(int i=0; i<(int)v.size(); i++){
            cur += (__int128)v[i]*hashconst[i]%MOD; if(cur >= MOD) cur -= MOD;
        }
        return cur;
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    srand(time(0));
    for(int i=0; i<300000; i++){
        hashconst[i] = (ll)rand() * rand() + rand();
    }
    while(true){
        solve S1, S2;
        if(S1.val == S2.val) cout << "yes\n";
        else cout << "no\n";
    }
    return 0;
}