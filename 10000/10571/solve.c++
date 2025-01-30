#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pdd pair<double, double>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

double epsilon = 0.0000001;

struct Point{
    double x; double y;
    Point(double xi, double yi){
        x = xi; y = yi;
    }

    Point operator+(Point &P2){
        return Point(x+P2.x, y + P2.y);
    }

    bool operator==(Point &P2){
        if(abs(x-P2.x)+abs(y-P2.y) < epsilon) return true;
        return false;
    }

    Point operator/(double t){
        if(t == 0) return Point(0,0);
        return Point(x/t, y/t);
    }
};


double dst(Point p1, Point p2){
    return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}


bool cmp(pdd p1, pdd p2){
    if(p1.Y == p2.Y) return (p1.X < p2.X);
    return p1.Y < p2.Y;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    for(int tt1=1; tt1<=tt; tt1++){
        cout << "Case #" << tt1 << ": ";
        double x1, y1, x2, y2, x3, y3;
        cin >> x1>> y1>> x2>> y2>> x3>> y3;
        vector<pdd> vp = {{x1,y1},{x2,y2},{x3,y3}};
        sort(vp.begin(),vp.end(),cmp);
        if(vp[1].Y == vp[2].Y){
            pdd pd = vp[1]; vp[1] = vp[0]; vp[0] = pd;
        }
        if(vp[1].Y == vp[0].Y){
            pdd pd = vp[1]; vp[1] = vp[2]; vp[2] = pd;
        }
        x1 = vp[0].X; y1 = vp[0].Y; 
        x2 = vp[1].X; y2 = vp[1].Y; 
        x3 = vp[2].X; y3 = vp[2].Y; 
        Point P1(x1, y1), P2(x2, y2), P3(x3, y3);
        
        if(x1 == x2 and x1 == x3){
            vector<double> yy = {y1, y2, y3};
            sort(yy.begin(), yy.end());
            cout << fixed << setprecision(2) << x1 << " " << ((yy[0] + yy[2])/2.0) << "\n";
            continue;
        }
        Point P4 = (P1 + P2)/2.0, P5 = (P3 + P2)/2.0;
        //cout << P1.x <<" " << P1.y << " " <<P2.x <<" " << P2.y << " " <<P3.x <<" " << P3.y << " ";
        //cout << P4.x <<" " << P4.y << " " <<P5.x <<" " << P5.y << " " <<P3.x <<" " << P3.y << " ";
        
        double A1 = -(x1-x2)/(y1-y2), B1 = P4.y - A1*P4.x;
        double A2 = -(x3-x2)/(y3-y2), B2 = P5.y - A2*P5.x;
        
        //cout << A1 << " " << B1 << " " << A2 << " " << B2 << "\n";
        if(abs(A1-A2) < epsilon){
            Point P6 = (P1+P3)/2.0;
            sort(vp.begin(),vp.end());
            cout << fixed << setprecision(2) << ((vp[0].X+vp[2].X)/2.0) << " " << ((vp[0].Y+vp[2].Y)/2.0) << "\n";
            continue;
        }

        double xo = (B2-B1)/(A1-A2), yo = A1*xo+B1;
        double u = (x1-xo)*(x1-xo)+(y1-yo)*(y1-yo);
        Point O(xo, yo);

        Point P6 = (P1+P3)/2.0;
        double u1 = max(dst(P6, P1), max(dst(P6, P2), dst(P6, P3)));
        if(u1 < u){
            O = P6;
            u = u1;
        }

        P6 = (P1+P2)/2.0;
        u1 = max(dst(P6, P1), max(dst(P6, P2), dst(P6, P3)));
        if(u1 < u){
            O = P6;
            u = u1;
        }

        P6 = (P2+P3)/2.0;
        u1 = max(dst(P6, P1), max(dst(P6, P2), dst(P6, P3)));
        if(u1 < u){
            O = P6;
            u = u1;
        }

        cout << fixed << setprecision(2) << O.x << " " << O.y << "\n";

    }
    return 0;
}