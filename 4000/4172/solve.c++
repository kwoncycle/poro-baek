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
    vector<ll> v(1000004, 0);
    v[0] = 1;
    for(ll i=1; i<=1000000; i++){
        v[i] += v[int((double)i - sqrt(i))];
        v[i] += v[(int)logl(i)];
        v[i] += v[(int)((double)i * sin(i) * sin(i))];
        v[i] %= 1000000;
    }
    while(true){
        int x; cin >> x;
        if(x < 0) break;
        cout << v[x] << "\n";
    }
    return 0;
}