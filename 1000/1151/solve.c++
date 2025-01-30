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
#define pdd pair<double,double>
#define d3 array<double, 3>

double area(pdd p1, pdd p2, pdd p3){
    double ans = (p1.X*p2.Y - p2.X*p1.Y) + (p2.X*p3.Y - p3.X*p2.Y) + (p3.X*p1.Y - p1.X*p3.Y);
    ans = abs(ans)/2.0;
    return ans;
}

pdd dot(d3 p1, d3 p2){
    d3 dt = {p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2]};
    double ratio = p2[2]/(p2[2]-p1[2]);
    for(int i=0; i<3; i++) dt[i] *= ratio;
    return {p2[0] - dt[0], p2[1] - dt[1]};
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    double x1, y1, z1, x2, y2, z2;
    cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

    double lx1, ly1, lz1;
    cin >> lx1 >> ly1 >> lz1;
    if(z1 >= lz1 and z2 >= lz1){
        cout << "0\n"; return 0;
    }

    if((z1 >= lz1) != (z2 >= lz1)){
        if(x1 != x2 and y1 != y2){
            cout << "-1\n"; return 0;
        }

        if(x1 == x2 and y1 == y2){
            cout << "0\n"; return 0;
        }

        if(x1 == x2 and y1 != y2){
            if(lx1 == x1){
                cout << "0\n";
            }
            else cout << "-1\n";
            return 0;
        }

        if(x1 != x2 and y1 == y2){
            if(ly1 == y1){
                cout << "0\n";
            }
            else cout << "-1\n";
            return 0;
        }
    }

    double ans = 0;
    // xy

    //pdd test = dot({x1,y1,z1}, {lx1,ly1,lz1});
    //cout << test.X << " " << test.Y << '\n';

    if((z1 < lz1) != (lz1 < z2)){
        double kz = abs(z1 - lz1) <= abs(z2 - lz1) ? z1:z2;
        
        vector<pdd> vz = {
            dot({x1,y1,kz},{lx1,ly1,lz1}),
            dot({x1,y2,kz},{lx1,ly1,lz1}),
            dot({x2,y1,kz},{lx1,ly1,lz1}),
            dot({x2,y2,kz},{lx1,ly1,lz1})    
        };

        //for(pdd x:vz) cout << x.X << " " << x.Y << "\n";

        ans += area(vz[0], vz[3], vz[1]);
        ans += area(vz[0], vz[3], vz[2]);
    }
    //cout << ans << "\n";
    // yz

    if((x1 < lx1) != (lx1 < x2)){
        double kx = abs(x1 - lx1) <= abs(x2 - lx1) ? x1:x2;
        
        vector<pdd> vx = {
            dot({kx,y1,z1},{lx1,ly1,lz1}),
            dot({kx,y1,z2},{lx1,ly1,lz1}),
            dot({kx,y2,z1},{lx1,ly1,lz1}),
            dot({kx,y2,z2},{lx1,ly1,lz1})    
        };

        ans += area(vx[0], vx[3], vx[1]);
        ans += area(vx[0], vx[3], vx[2]);
    }
    //cout << ans << "\n";
    // xz
    
    if((y1 < ly1) != (ly1 < y2)){
        double ky = abs(y1 - ly1) <= abs(y2 - ly1) ? y1:y2;
        
        vector<pdd> vy = {
            dot({x1,ky,z1},{lx1,ly1,lz1}),
            dot({x1,ky,z2},{lx1,ly1,lz1}),
            dot({x2,ky,z1},{lx1,ly1,lz1}),
            dot({x2,ky,z2},{lx1,ly1,lz1})    
        };

        ans += area(vy[0], vy[3], vy[1]);
        ans += area(vy[0], vy[3], vy[2]);
    }
    cout << fixed << setprecision(8) << ans << "\n";

    return 0;
}