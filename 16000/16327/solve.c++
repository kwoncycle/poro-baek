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
    ll a, b, c, n; cin >> a >> b >> c >> n;
    __int128 ni = n;
    __int128 ans = 0;
    if(ni % 2 == 0){
        ans += ni * (2 + ni/2) * (ni/2 - 1) / 2;
        ans += ni * (ni/2 - 1);
        ans /= 3;
        if(a == b and b == c) ans = ans;
        else if(a == b or b == c or a == c) ans *= 3;
        else ans *= 6;
        __int128 o = 1;
        o <<= 64;
        ans %= o;
        unsigned ll ansi = ans;
        cout << ansi << "\n";
    }
    else{
        ans += ni * (ni/2) * (ni/2+1) / 2;
        ans /= 3;
        if(a == b and b == c) ans = ans;
        else if(a == b or b == c or a == c) ans *= 3;
        else ans *= 6;
        __int128 o = 1;
        o <<= 64;
        ans %= o;
        unsigned ll ansi = ans;
        cout << ansi << "\n";
    }
    return 0;
}