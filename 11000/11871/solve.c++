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
    vector<ll> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
    int ans = 0;
    for(int i=0; i<n; i++){
        if(v[i]%2 == 1) v[i] = (v[i]+1)/2;
        else v[i] = v[i]/2 - 1;
        ans ^= v[i];
    }

    if(ans == 0) cout << "cubelover\n";
    else cout << "koosaga\n";
    return 0;
}