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

#define MOD 1000000009ll


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    vector<ll> DP1(100005, 0), DP2(100005, 0);
    DP1[0] = 1;
    DP2[0] = 1;
    DP1[1] = 1;
    DP2[1] = 1;
    for(int i=2; i<=100000; i++){
        DP1[i] += DP1[i-1];
        DP1[i] += DP1[i-2];
        DP1[i] %= MOD;

        DP2[i] += DP2[i-1];
        DP2[i] += DP2[i-2];
        if(i-3 >= 0) DP2[i] += DP2[i-3];
        if(i-4 >= 0) DP2[i] += DP2[i-4];
        DP2[i] %= MOD;
    }
    int n; cin >> n;
    while(n--){
        int x; cin >> x;
        cout << DP1[x]*DP2[x]%MOD << "\n";
    }
    return 0;
}