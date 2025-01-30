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

pll egcd(ll x, ll y){// return a,b s.t x*a-y*b = gcd(x,y)
    ll x_origin = x, y_origin = y;
    ll x1 = 1, y1 = 0, x2 = 0, y2 = 1;
    if(x < y) {
        swap(x,y);
        swap(x1,x2);
        swap(y1,y2);
    }
    while(y){
        ll u = x/y;
        x1 -= x2*u;
        y1 -= y2*u;
        x %= y;
        swap(x,y);
        swap(x1,x2);
        swap(y1,y2);
    }

    y1 %= x_origin;
    if(y1 < 0) y1 += x_origin;
    x1 = (y_origin*y1 + 1) / x_origin;
    return {x1,y1};
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int tt; cin >> tt;
    while(tt--){
        ll x, y; cin >> x >> y;

        ll o = __gcd(x,y);
        if((x+y)/o >= 50000){
            ll x1 = x/o, y1 = y/o;
            auto [i,j] = egcd(x1, y1);
            cout << "3\n";
            cout << "0 0\n";
            cout << x << " " << y << "\n";
            cout << j << " " << i << "\n";
        }

        else{
            cout << "4\n";
            cout << "0 0\n";
            cout << x-1 << " " << y << "\n";
            cout << x/o << " " << y/o << "\n";
            cout << x << " " << y-1 << "\n";
        }
    }
}