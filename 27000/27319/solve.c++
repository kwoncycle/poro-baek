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

ll ccw(pll p1, pll p2, pll p3){
    pll u1 = {p2.X - p1.X, p2.Y - p1.Y};
    pll u2 = {p3.X - p2.X, p3.Y - p2.Y};
    ll u3 = u1.X*u2.Y - u1.Y*u2.X;
    if(u3 > 0) return -1;
    if(u3 < 0) return 1;
    return 0;
    // clock: 1
    // ccw: -1
}


ll dst(pll p1, pll p2){
    ll x = p1.X - p2.X;
    ll y = p1.Y - p2.Y;
    return x*x + y*y;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    int n; cin >> n;
    vector<pll> v(n+4, {0,0});
    vector<ll> CW(n+4, 0);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    v[n] = v[0];
    v[n+1] = v[1];
    v[n+2] = v[2];
    v[n+3] = v[3];
    if(n % 2 == 1){
        cout << "0\n"; return 0;
    }
    int sm = 0, idx;
    for(int i=0; i<n; i++){
        CW[i] = ccw(v[i], v[i+1], v[i+2]);
        if(CW[i] == 1) CW[i] = 0;
        else {
            CW[i] = 1;
            idx = (i+1)%n;
        }
        sm += CW[i];
    }

    //cout << idx << "\n";
    if(sm != 1){
        cout << "0\n"; return 0;
    }
    int ans = 1;
    for(int i=1; i<n/2; i++){
        pll p1 = v[(i+idx+n)%n];
        pll p2 = v[(idx-i+n)%n];
        
        pll p3 = {v[idx].X - v[(idx+n/2)%n].X, v[idx].Y - v[(idx+n/2)%n].Y};
        pll p4 = {p1.X - p2.X, p1.Y - p2.Y};
        if(p3.X*p4.X + p3.Y*p4.Y != 0){
            ans = 0; 

            //cout << p3.X << " " << p3.Y << "\n";
            //cout << p4.X << " " << p4.Y << "\n";
            //cout << i << " ";
            break;
        }

        if(dst(p1, v[idx]) == dst(p2, v[idx]) and dst(p1, v[(idx+n/2)%n]) == dst(p2, v[(idx+n/2)%n])) continue;
        ans = 0; break;
        
    }
    
    cout << ans << "\n";
    
    return 0;
}