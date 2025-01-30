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
using A2 = array<int,2>;

#define ITEM 99999988
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    int xd, yd; cin >> xd >> yd;
    vector<vector<int>> mp(n+2, vector<int>(m+2, 0));
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            mp[i][j] = 99999999;
        }
    }

    int k; cin >> k;
    vector<A2> items;
    for(int i=0; i<k; i++){
        int x, y; cin >> x >> y;
        mp[x][y] = 99999999;
        items.push_back({x, y});
    }
    int t; cin >> t;
    vector<vector<A2>> wv(n*m+1);
    for(int i=0; i<t; i++){
        int x, y, w; cin >> x >> y >> w;
        mp[x][y] = w;
        wv[w].push_back({x,y});
    }
    vector<vector<int>> dst(n+2, vector<int>(m+2, 0));
    priority_queue<pair<ll, A2>> pq;
    vector<A2> dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    pq.push({mp[xd][yd], {xd,yd}});
    while(!pq.empty()){
        auto x1 = pq.top(); pq.pop();
        ll d = x1.X;
        auto [x, y] = x1.Y;
        if(dst[x][y] >= d) continue;
        dst[x][y] = d;
        for(auto &[i1, j1]: dir){
            if(x+i1 == 0 or x+i1 >= n+1) continue;
            if(y+j1 == 0 or y+j1 >= m+1) continue;
            if(dst[x+i1][y+j1] >= mp[x+i1][y+j1]) continue;
            if(dst[x+i1][y+j1] < d and mp[x+i1][y+j1] >= d){
                pq.push({d, {x+i1, y+j1}});
            }
            else if(dst[x+i1][y+j1] < d and mp[x+i1][y+j1] < d){
                pq.push({mp[x+i1][y+j1], {x+i1, y+j1}});
            }
        }
    }

    vector<int> csts;
    for(int i=0; i<k; i++){
        csts.push_back(dst[items[i][0]][items[i][1]]);
    }
    sort(csts.begin(), csts.end());
    int idx = 0;
    for(int i=0; i<k; i++){
        if(csts[i] > idx+1) idx++;
    }

    cout << idx << "\n";
    /*
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            for(auto &[i1, j1]:dir){
                if(mp[i][j] >= 9999999 and mp[i1+i][j1+j] >= 9999999){
                    DJS.Union({i,j}, {i+i1,j+j1});
                }
            }
        }
    }
    for(int i=n*m; i>=1; i--){
        for(auto &[x,y]:wv[i]){
            for(auto &[x1, y1]:dir){
                if(mp[x+x1][y+y1] >= i){
                    //cout << x+x1 << " " << y+y1 << " " << x << " " << y << " " << i << "\n";
                    DJS.Union({x+x1, y+y1}, {x, y});
                }
            }
        }
        for(auto &[x,y]:wv[i]){
            for(auto &[x1, y1]:dir){
                if(mp[x+x1][y+y1] >= i){
                    if(DJS.find({x+x1, y+y1}) == DJS.find({xd, yd})){
                        mx_jr[x+x1][y+y1] = max(i, mx_jr[x+x1][y+y1]);
                    }
                }
            }
        }
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            cout << mx_jr[i][j] << " ";
        }
        cout << "\n";
    }*/
    return 0;
}