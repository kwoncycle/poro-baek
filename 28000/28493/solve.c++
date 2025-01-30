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

vector<ll> x, a, b;
ll n;

long double mx(long double na){
    // if na determined, max of nb+na
    long double mx = 0x3f3f3f3f3f3f3f3fll;
    for(int i=0; i<n; i++) mx = min(mx, (long double)((long double)x[i]-na*(long double)a[i])/(long double)b[i]);
    return mx + na;
}

ll mx_ll(ll na){
    //cout << na <<": ";
    // if na determined, max of nb+na
    ll mx = 0x3f3f3f3f3f3f3f3fll;
    if(na < 0) return -999;
    for(int i=0; i<n; i++) {
        if(x[i]-na*a[i] < 0) return -999;
        mx = min(mx, (ll)(x[i]-na*a[i])/(ll)b[i]);
    }
    if(mx < 0) return -999;
    //cout << mx + na << "\n";
    return mx + na;
}

long double search3(long double a, long double b){
    if((b-a) <= 0.000001){
        return b;
    }

    long double p1 = (a+a+b)/(long double)3, p2 = (a+b+b)/(long double)3;
    long double mp1 = mx(p1), mp2 = mx(p2);
    if(mp1 < mp2) a = p1;
    else b = p2;
    
    return search3(a, b);
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n;
    x.resize(n);
    a.resize(n);
    b.resize(n);
    
    long double amx = 0x3f3f3f3f3f3f3f3fll;
    ll amx_ll = 0x3f3f3f3f3f3f3f3fll;
    for(int i=0; i<n; i++) cin >> x[i];
    for(int i=0; i<n; i++) cin >> a[i];
    for(int i=0; i<n; i++) cin >> b[i];
    int tt = 1;
    for(int i=0; i<n; i++) if(a[i] != b[i]) tt = 0;
    if(tt){
        ll mxt = 0;
        mxt = max(mxt, mx_ll(0));
        cout << mxt << "\n";
        return 0;
    }
    if(mx_ll(0) <= 0){
        cout << "0\n"; return 0;
    }
    for(int i=0; i<n; i++){
        amx = min(amx, (long double)x[i]/(long double)a[i]);
        amx_ll = min(amx_ll, x[i]/a[i]);
    }


    long double o = search3(0, amx);
    //o = mx(o);
    ll u = (ll)o;
    ll mxv = 0;
    for(int i=-7; i<=7; i++){
        mxv = max(mxv, mx_ll(u+i));
    }
    for(int i=-7; i<=7; i++){
        mxv = max(mxv, mx_ll(i));
    }
    for(int i=-7; i<=0; i++){
        mxv = max(mxv, mx_ll(amx_ll+i));
    }
    cout << mxv << "\n";

    return 0;
}