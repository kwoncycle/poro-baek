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


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, d;
    cin >> n >> m >> d;
    vector<array<int,4>> edges(m);
    for(int i=0; i<m; i++){
        for(int j=0; j<3; j++) cin >> edges[i][j];
        edges[i][3] = i;
    }

    sort(edges.begin(), edges.end(), [&](array<int,4> &x, array<int,4> &y){
        if(x[2] == y[2]) return x[3] < y[3];
        return x[2] < y[2];
    });

    vector<int> G;
    djs DJS(n+1);
    for(int i=0; i<m; i++){
        if(DJS.Union(edges[i][0], edges[i][1])){
            G.push_back(i);
        }
    }

    int cnt = 0;
    for(int i:G){
        if(edges[i][3] >= n-1) cnt++;
        //cout << edges[i][0] << " " << edges[i][1] << "\n";
    }

    if(edges[G[n-2]][2] > d){
        cout << cnt << "\n";
        return 0;
    }
    if(edges[G[n-2]][3] >= n-1)
        cnt--;
    else{
        cout << cnt << "\n";
        return 0;
    }


    djs DJS1(n+1);
    vector<int> G1;
    vector<int> check(m+1, 0);
    for(int i:G){
        if(edges[i][2] == edges[G[n-2]][2] and edges[i][3] >= n-1) continue;
        check[i] = 1;
        DJS1.Union(edges[i][0], edges[i][1]);
        //G1.push_back(i);
    }


    //for(int i:G1) cout << edges[i][0]<< " " << edges[i][1] << "\n";
    int find = 0;
    for(int i=0; i<m; i++){
        if(check[i] == 0){
            if(DJS1.find(edges[i][0]) != DJS1.find(edges[i][1])){
                if(edges[i][2] <= d){
                    if(edges[i][3] < n-1) {
                        DJS1.Union(edges[i][0], edges[i][1]);
                    }
                    //cout << edges[i][0] << " " << edges[i][1] << " " << edges[i][2] << " " << edges[i][3] << "\n";
                }
            }
        }
    }

    for(int i:G){
        if(edges[i][2] == edges[G[n-2]][2] and edges[i][3] >= n-1){
            if(!DJS1.Union(edges[i][0], edges[i][1])) find = 1;
        }
    }

    cnt = cnt + 1-find;
    cout << cnt << "\n";



    return 0;
}