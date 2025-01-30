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
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    int m; cin >> m;
    vector<int> v(m);
    for(int i=0; i<m; i++){
        cin >> v[i];
    }
    int mx = max(v[0], n - v[m-1]);
    for(int i=0; i<m-1; i++){
        mx = max(mx, (v[i+1]-v[i]+1)/2);
    }
    cout << mx << "\n";
    return 0;
}