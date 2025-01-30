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


int ccw(pii p1, pii p2, pii p3){
    ll T1 = ((ll)(p2.X - p1.X)*(p3.Y - p2.Y) - (ll)(p2.Y - p1.Y)*(p3.X - p2.X));
    if(T1 > 0) return 1; // counter clockwise
    if(T1 < 0) return -1; // clockwise
    return 0;
}

bool isInTriangle_noedge(pii a, pii b, pii c, pii p){
    int u1 = ccw(a, p, b);
    int u2 = ccw(b, p, c);
    int u3 = ccw(c, p, a);
    return abs(u1 + u2 + u3) == 3; 
}

bool isOnLine(pii a, pii b, pii p){
    if(ccw(a, b, p)) return false;
    if((ll)(a.X - p.X)*(b.X - p.X) >= 0 and (ll)(a.Y - p.Y)*(b.Y - p.Y) >= 0) return false;
    return true;
}

bool isInTriangle(pii a, pii b, pii c, pii p){
    if(isInTriangle_noedge(a, b, c, p)) return true;
    if(isOnLine(a, b, p)) return true;
    if(isOnLine(b, c, p)) return true;
    if(isOnLine(c, a, p)) return true;
    return false;
}

int isInshell(pii p, vector<pii> &shell){ // edge not included
    if(
        ccw(shell[0], shell[1], p) != 1 or
        ccw(p, shell.back(), shell[0]) != 1
    )
        return -1;
    
    if(shell.size() == 3){
        if(isInTriangle_noedge(shell[0], shell[1], shell[2], p)) return 1;
        else return -1;
    }

    int s = 0, e = (int)shell.size() - 1; // s: ccw(-1), e : cw(1)
    while(s + 1 < e){
        int m = (s + e)/2;
        int t = ccw(shell[m], shell[0], p);
        if(t == 0){
            if(isOnLine(shell[m], shell[0], p)){
                return m;
            }
            else{
                return -1;
            }
        }
        if(t == -1) s = m;
        if(t == 1) e = m;
    }
    if(isInTriangle_noedge(shell[s], shell[e], shell[0], p)) return e;
    else return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    return 0;
}