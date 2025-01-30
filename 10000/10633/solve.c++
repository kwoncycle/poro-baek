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


struct cond{
    int mn, mx;
    // mn <= s <= mx
    cond(int mni, int mxi){
        mn = mni, mx = mxi;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int m, n; cin >> m >> n;
    vector<vector<cond>> v(m+1, vector<cond>(n+1, cond(-999999, 999999)));

    for(int i=1; i<=m; i++){
        int k;
        cin >> k;
        for(int j=1; j<=k; j++){
            int s, t; string c;
            cin >> s >> c >> t;
            if(c == ">="){
                v[i][s].mn = max(v[i][s].mn, t);
            }
            else{
                v[i][s].mx = min(v[i][s].mx, t);
            }
        }
    }

    int good = 1;
    for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            if(v[i][j].mn > v[i][j].mx) {
                good = 0;
            }
        }
    }

    if(!good){
        cout << "No\n"; return 0;
    }

    vector<vector<int>> graph(m+1);

    for(int i=1; i<=m; i++){
        for(int j=i+1; j<=m; j++){
            int truth = 1;
            for(int i1=1; i1<=n; i1++){
                if(v[i][i1].mx < v[j][i1].mn){
                    truth = 0;
                }
            }
            if(!truth) graph[i].push_back(j);
            truth = 1;
            for(int i1=1; i1<=n; i1++){
                if(v[j][i1].mx < v[i][i1].mn){
                    truth = 0;
                }
            }
            if(!truth) graph[j].push_back(i);
        }
    }

    //for(int i:graph[1]) cout << i << " "; cout << "\n";
    //for(int i:graph[2]) cout << i << " "; cout << "\n";

    int truth = 1;
    for(int i=1; i<=m; i++){
        truth = 1;
        vector<int> visited(m+1, 0);
        queue<int> q;
        visited[i] = 1;
        q.push(i);
        while(!q.empty()){
            int j = q.front(); q.pop();
            for(int t:graph[j]){
                if(t == i){
                    truth = 0;
                    goto escape;
                }
                if(visited[t]) continue;
                visited[t] = 1;
                q.push(t);
            }
        }
    }
    escape:
    if(truth) cout << "Yes\n";
    else cout << "No\n";

    

    return 0;
}