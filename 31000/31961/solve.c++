#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define all(x) (x).begin(), (x).end()

int DP[5005][5005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, x, y; cin >> n >> x >> y;
    vector<array<int, 4>> v(n);
    for(auto &[i,j,k,l]:v) cin >> i >> j >> k >> l;
    vector<pii> cur(1, {x,y});
    DP[0][0] = 1;
    for(int i=0; i<n; i++){
        vector<pii> ncur;
        for(auto &[px,py]:cur){
            if(v[i][0] <= px and px <= v[i][1] and v[i][2] <= py and py <= v[i][3]){
                if(DP[px+1-x][py-y] == 0) {
                    ncur.emplace_back(px+1, py);
                    DP[px+1-x][py-y] = 1;
                }
                if(DP[px-x][py+1-y] == 0) {
                    ncur.emplace_back(px, py+1);
                    DP[px-x][py+1-y] = 1;
                }
            }
            else{
                ncur.push_back({px, py});
            }
        }
        cur.swap(ncur);
    }
    int ans = 0;
    for(auto &[px,py]:cur){
        ans = max(ans, px-x + py-y);
    }
    cout << ans << "\n";
    return 0;
}