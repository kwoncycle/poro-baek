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

vector<int> game, game_cnt;
vector<int> ans;
int tme = 0;

class djs
{
    int n;
    vector<int> par, cnt;
    vector<map<int, int>> vmp;
 
public:
    djs(int n) : n(n) {
        par.resize(n);
        vmp.resize(n);
        cnt.resize(n, 1);
        for(int i=0; i<n; i++) {
            par[i] = i;
            vmp[i][game[i]] = 1;
        }
    }
 
    int find(int v) {
        if(par[v] == v) return v;
        else return find(par[v]);
    }
 
    bool Union(int x, int y) {
        int px = find(x);
        int py = find(y);

        if(px == py) return false;
        if(cnt[px] < cnt[py]){
            par[px] = py;
            cnt[py] += cnt[px];
            for(auto [x, y]:vmp[px]){
                if(vmp[py].find(x) == vmp[py].end()) vmp[py][x] = 0;
                vmp[py][x] += y;
                if(ans[x] == -1 and vmp[py][x] == game_cnt[x]){
                    ans[x] = tme;
                }
            }
        }
        else{
            par[py] = px;
            cnt[px] += cnt[py];
            for(auto [x, y]:vmp[py]){
                if(vmp[px].find(x) == vmp[px].end()) vmp[px][x] = 0;
                vmp[px][x] += y;
                if(ans[x] == -1 and vmp[px][x] == game_cnt[x]){
                    ans[x] = tme;
                }
            }
        }
        return true;
    }
};
// Usage: djs DJS(n)
 


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, q; cin >> n >> m >> q;
    game.resize(n); game_cnt.resize(m+1);
    for(int i=0; i<n; i++){
        cin >> game[i];
        game_cnt[game[i]]++;
    }
    ans.resize(m+1, -1);
    for(int i=1; i<=m; i++){
        if(game_cnt[i] == 1) ans[i] = 0;
    }
    djs DJS(n);
    for(tme=1; tme<=q; tme++){
        int a, b; cin >> a >> b; a--; b--;
        DJS.Union(a, b);
    }

    for(int i=1; i<=m; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}