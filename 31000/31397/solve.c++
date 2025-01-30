#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define db double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

int n;
vector<pll> vp(200004);
vector<db> subset_boundary;
vector<db> subset_area;



ll cross(pll x, pll y){
    return x.Y*y.X - x.X*y.Y;
}

ll area(pll x, pll y, pll z){
    ll ans = cross(x, y) + cross(y, z) + cross(z, x);
    return abs(ans);
}

db len(pll x, pll y){
    return sqrtl((x.X-y.X)*(x.X-y.X) + (x.Y-y.Y)*(x.Y-y.Y));
}

db Area_0(db x){

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n;
    for(int i=0; i<n; i++) cin >> vp[i].X >> vp[i].Y;
    subset_boundary.resize(n+1, 0);
    subset_area.resize(n, 0);

    for(int i=1; i<=n; i++){
        subset_boundary[i] = subset_boundary[i-1] + len(vp[(i-1)%n], vp[i%n]);
    }

    for(int i=1; i<n; i++){
        db a = area(vp[0], vp[i-1], vp[i]);
        subset_area[i] = subset_area[i-1] + a;
    }
    db ttl_len = subset_boundary[n];

    int i0 = 0, i1 = 0;
    db l = 0;
    while(true){
        if(subset_boundary[i1+1] < ttl_len/2) i1++;
        else break;
    }

    // do solve
    for(i0=0; i0<n; i0++){
        // find i1
        if(subset_boundary[i0] > ttl_len/2) break;

        while(true){
            if(subset_boundary[i1+1] - subset_boundary[i0] < ttl_len/2) i1++;
            else break;
        }

        int i2 = i1;
        while(true){
            if(subset_boundary[i2+1] - subset_boundary[i0+1] < ttl_len/2) i2++;
            else break;
        }


    }

    return 0;
}