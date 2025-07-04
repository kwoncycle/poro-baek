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

string s[1001];
int val[1001][1001];
vector<int> graph[1000011];
int order[1000011], par[1000011], up[1000011], iscut[1000011];
int edge = 0;
int clk = 0;

void DFS(int node){
    clk++;
    order[node] = clk;
    up[node] = order[node];
    int cnt = 0;
    for(int i:graph[node]){
        if(i == par[node]) continue;
        if(order[i] == 0){
            cnt++;
            par[i] = node;
            DFS(i);
            if(up[i] >= order[node] and node != 1){
                iscut[node] = 1;
            }
            up[node] = min(up[node], up[i]);
        }
        else{
            up[node] = min(up[node], order[i]);
        }
    }
    if(node == 1 and cnt >= 2) iscut[node] = 1;
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    for(int i=0; i<n; i++) cin >> s[i];
    int id = 1;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(s[i][j] == '#'){
                val[i][j] = id; 
                id++;
            }
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1; j++){
            if(val[i][j] > 0 and val[i][j+1] > 0){
                edge++;
                graph[val[i][j]].push_back(val[i][j+1]);
                graph[val[i][j+1]].push_back(val[i][j]);
            }
        }
    }
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n; j++){
            if(val[i][j] > 0 and val[i+1][j] > 0){
                edge++;
                graph[val[i][j]].push_back(val[i+1][j]);
                graph[val[i+1][j]].push_back(val[i][j]);
            }
        }
    }

    DFS(1);
    vector<pii> ans;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(val[i][j] > 0){
                if(edge - (int)graph[val[i][j]].size() == id - 3 and !iscut[val[i][j]]) ans.push_back({i, j});
            }
        }
    }
    cout << ans.size() << "\n";
    for(auto &[i,j] : ans) cout << i+1 << " " << j+1 << "\n";
    return 0;
}