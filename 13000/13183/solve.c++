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
#define MOD 1000000007ll
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    // 1*h + ... + h*1 / (h(h+1)/2)
    // (1+...+h)*(h+1) - 1*1+2*2+...+h*h
    // 9h+9 - (2h+1)*3 = 3h+6?

    ll h, w; cin >> h >> w;
    cout << ((h+2)%MOD)*((w+2)%MOD)%MOD << "\n";
    return 0;
}