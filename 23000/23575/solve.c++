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
    ll a, b, c; cin >> a >> b >> c;
    ll num2 = 1ll << 60;
    ll u = __gcd(a+b, num2);
    vector<pii> ans;
    int cnt = 0;/*
    while(true){
        ll x; cin >> x;
        if(x == 1){
            if(a <= b){
                b -= a; a *= 2;
            }
            else{
                a -= b; b *= 2;
            }
        }
        if(x == 2){
            if(c <= b){
                b -= c; c *= 2;
            }
            else{
                c -= b; b *= 2;
            }
        }
        if(x == 3){
            if(a <= c){
                c -= a; a *= 2;
            }
            else{
                a -= c; c *= 2;
            }
        }
        cout << a << " " << b  << " " << c <<"\n";
    }*/
    ll mxa = 1;
    set<ll> xx;
    while(a != u and b != u){
        //cout << a << " " << b << "\n";
        if(a <= b){
            b -= a; a *= 2;
        }
        else{
            a -= b; b *= 2;
        }
        if(xx.find(a) != xx.end()) break;
        xx.insert(a);
        //ans.push_back({1, 2});
        cnt++;
        mxa = max(mxa, __gcd(a, num2));
        if(cnt > 300000) break;
    }
    cout << cnt << "\n";
    cout << mxa << "\n";
    return 0;
}

// 239 102 35 3 1