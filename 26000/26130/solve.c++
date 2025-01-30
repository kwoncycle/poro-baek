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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> ans_min(n, vector<int>(m));
    vector<vector<vector<pii>>> graph(n+1, vector<vector<pii>>(m));
    vector<vector<vector<pii>>> graph1(n+1, vector<vector<pii>>(m));
    // out : n, 0
    stack<pii> zeros; zeros.push({n,0});
    stack<pii> ones;
    vector<pii> dir(k);
    for(int kk=0; kk<k; kk++){
        int wx, wy; cin >> wx >> wy; dir[kk] = {wx, wy};
        int t; cin >> t;
        vector<vector<int>> v(n, vector<int>(m, 0));
        for(int j=0; j<t; j++){
            int x,y; cin >> x >> y;
            x--; y--;
            ones.push({x, y});
            v[x][y] = 1;
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                int i1 = i - wx, j1 = j - wy;
                if(v[i][j] == 0){
                    if(0<=i1 and i1<n and 0<=j1 and j1<m){
                        graph[i1][j1].push_back({i, j});
                        graph1[i][j].push_back({i1, j1});
                    }
                    else{
                        graph[n][0].push_back({i, j});
                    }
                }
                else{
                    if(0<=i1 and i1<n and 0<=j1 and j1<m){
                        zeros.push({i1, j1});
                    }
                }
            }
        }
    }

    while(!ones.empty()){
        auto [x,y] = ones.top(); ones.pop();
        if(ans_min[x][y] == 1) continue;
        ans_min[x][y] = 1;
        for(auto [x1, y1]:graph1[x][y]){
            if(ans_min[x1][y1] == 0){
                ones.push({x1, y1});
            }
        }
    }

    vector<vector<int>> ans_max(n, vector<int>(m, 1));
    vector<vector<int>> visited(n+1, vector<int>(m, 0));
    while(!zeros.empty()){
        auto [x,y] = zeros.top(); zeros.pop();
        if(visited[x][y]) continue;
        visited[x][y] = 1;
        if(x < n) ans_max[x][y] = 0;
        for(auto &[x1, y1]: graph[x][y]){
            if(!visited[x1][y1]) zeros.push({x1, y1});
        }
    }
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(ans_min[j][i] == 0) cout << '.';
            else cout << '#';
        }
        cout << "\n";
    }
    cout << "\n";
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(ans_max[j][i] == 0) cout << '.';
            else cout << '#';
        }
        cout << "\n";
    }
    return 0;
}