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
    ll d, p, q; cin >> d >> p >> q;
    if(p > q) swap(p, q);
    if(d < p){
        cout << p << "\n"; return 0;
    }
    if(q < 30000){
        ll mn = 0x3f3f3f3f3f3f3fll;
        for(int i=0; i<=q; i++){
            if(p*i >= d) mn = min(mn, p*i);
            else{
                ll o = ((d - p*i + q - 1)/q)*q;
                mn = min(mn, o + p*i);
            }
        }
        cout << mn << "\n";
    }
    else{
        ll mn = 0x3f3f3f3f3f3f3fll;
        for(int i=0; i<=40000; i++){
            if(q*i >= d) mn = min(mn, q*i);
            else{
                ll o = ((d - q*i + p - 1)/p)*p;
                mn = min(mn, o + q*i);
            }
        }
        cout << mn << "\n";
    }
    return 0;
}