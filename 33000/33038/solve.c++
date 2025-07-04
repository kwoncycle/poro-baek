#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct solve{
    ll w, h;
    solve(){
        cin >> w >> h;
        int wi[2], hi[2], xi[2], yi[2], dx[2], dy[2];
        for(int i=0; i<2; i++){
            cin >> wi[i] >> hi[i] >> xi[i] >> yi[i] >> dx[i] >> dy[i];
        }
        
        int wsz = (w-wi[0])*(w-wi[1])/gcd((w-wi[0]),(w-wi[1]))*2, hsz = (h-hi[0])*(h-hi[1])/gcd((h-hi[0]),(h-hi[1]))*2;
        int G = gcd(wsz, hsz);
        vector<int> vx(G), vy(G);
        for(int i=0; i<wsz; i++){
            if(xi[0] == 0 or xi[0] == w-wi[0]) dx[0] *= -1;
            xi[0] += dx[0];
            if(xi[1] == 0 or xi[1] == w-wi[1]) dx[1] *= -1;
            xi[1] += dx[1];
            if(xi[0]-wi[1] < xi[1] and xi[1] < xi[0]+wi[0]) vx[i%G]++;
        }
        for(int i=0; i<hsz; i++){
            if(yi[0] == 0 or yi[0] == h-hi[0]) dy[0] *= -1;
            yi[0] += dy[0];
            if(yi[1] == 0 or yi[1] == h-hi[1]) dy[1] *= -1;
            yi[1] += dy[1];

            if(yi[0]-hi[1] < yi[1] and yi[1] < yi[0]+hi[0]) vy[i%G]++;
        }
        
        ll ans = 0;
        for(int i=0; i<G; i++){
            ans += (ll)vx[i]*vy[i];
        }
        ll ttl = (ll)hsz/G*wsz;
        ll G1 = gcd(ans, ttl);
        ttl /= G1; ans /= G1;
        cout << ans << "/" << ttl << "\n";
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        solve S;
    }
    return 0;
}