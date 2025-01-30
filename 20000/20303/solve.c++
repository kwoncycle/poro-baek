#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <iomanip>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define X first
#define Y second
#define GETVECTOR(n) for(int i=0; i< (n); i++) scanf("%d ",&inp[i]);
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
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
	ll n,m,k; cin >> n >> m >> k;
	djs DJS(n);
	vector<ll> c(n);
	for(int i=0; i<n; i++) cin >> c[i];
	while(m--){
		int a, b; cin >> a >> b; a--; b--;
		DJS.Union(a, b);
	}
	vector<pll> sm(n, {0,0});
	for(int i=0; i<n; i++){
		sm[DJS.find(i)].X += c[i];
		sm[DJS.find(i)].Y += 1;
	}
	vector<vector<ll>> DP(n + 1, vector<ll>(k, 0));
	for(int i=0; i<n; i++){
		for(int j=0; j<k; j++){
			DP[i+1][j] = max(DP[i+1][j], DP[i][j]);
			if(j + sm[i].Y < k) DP[i+1][j + sm[i].Y] = max(DP[i+1][j + sm[i].Y], DP[i][j] + sm[i].X);
		}
	}
	ll mx = 0;
	for(int i=0; i<k; i++) mx = max(mx, DP[n][i]);
	cout << mx << "\n";
    return 0;
}