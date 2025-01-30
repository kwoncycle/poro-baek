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
    vector<int> cnt;
 
public:
    djs(int n) : n(n) {
        par.resize(n);
        cnt = vector<int>(n, 1);
        for(int i=0; i<n; i++) par[i] = i;
    }
 
    int find(int v) {
        if(par[v] == v) return v;
        else return par[v] = find(par[v]);
    }

    int count(int v){
        return cnt[find(v)];
    }

    bool Union(int x, int y) {
        int px = find(x);
        int py = find(y);
 
        if(px == py) return false;
 
        par[px] = py;
        cnt[py] += cnt[px];
        return true;
    }
};
// Usage: djs DJS(n)


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    djs DJS(1000005);
    for(int i=0; i<n; i++){
        char q; cin >> q;
        if(q == 'Q'){
            int c; cin >> c;
            cout << DJS.count(c) << "\n";
        }
        else{
            int a,b; cin >> a >> b;
            DJS.Union(a, b);
        }
    }
    return 0;
}