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

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    vector<int> a;
    for(int i=0; i<10; i++) a.push_back(i);
    for(auto i:a) i++;
    for(auto &i:a) cout << i << " "; cout << "\n";
    vector<pii> v;
    for(int i=0; i<10; i++) v.push_back({i, i*i});
    for(auto &[x, y]:v) x = 1;
    for(auto &x:v) cout << x.X << " " << x.Y << "\n";

    vector<array<int, 3>> vp;
    for(int i=0; i<10; i++){
        vp.push_back({10-i, 2*i, i*i});
    }
    sort(vp.begin(), vp.end());

    for(int i=0; i<10; i++) cout << vp[i][0] << " " << vp[i][1] << " " << vp[i][2] << "\n";
    return 0;
}