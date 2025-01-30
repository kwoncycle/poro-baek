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

vector<pii> ed = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> v(n+2, vector<int>(m+2, -1)), tme(n+2, vector<int>(m+2, 9999999));
    queue<array<int,3>> q;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++) {
            cin >> v[i][j];
            if(v[i][j] == 1 or v[i][j] == 2) {
                q.push({i,j,0});
                tme[i][j] = 0;
            }
        }
    }

    while(!q.empty()){
        auto [i1, j1, t] = q.front(); q.pop();
        if(v[i1][j1] == 3 or v[i1][j1] == -1 or v[i1][j1] >= 10 or tme[i1][j1] < t) continue;
        v[i1][j1] *= 10;
        tme[i1][j1] = t;
        for(auto [ni, nj]:ed){
            if(v[i1+ni][j1+nj] == -1) continue;
            if(v[i1+ni][j1+nj] >= 10) continue;
            if(v[i1+ni][j1+nj] == 3) continue;
            if(tme[i1+ni][j1+nj] < t+1) continue;
            v[i1+ni][j1+nj] |= v[i1][j1]/10;
            tme[i1+ni][j1+nj] = t+1;
            q.push({i1+ni, j1+nj, t+1}); 
        }
    }

    /*
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++) cout << v[i][j] << " "; cout << '\n';
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++) cout << tme[i][j] << " "; cout << '\n';
    }*/

    int cnt1 = 0, cnt2 = 0, cnt3 = 0;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(v[i][j] == -1) continue;
            if(v[i][j] == 3) cnt3++;
            else if(v[i][j] == 20) cnt2++;
            else if(v[i][j] == 10) cnt1++;
        }
    }
    cout << cnt1 << " " << cnt2 << " " << cnt3 << "\n";

    return 0;
}