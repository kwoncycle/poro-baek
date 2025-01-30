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

vector<vector<vector<int>>> vshp(3, vector<vector<int>>(10, vector<int>(10, 0)));
vector<array<pii, 2>> bound(3);

bool isable(array<pii, 3> d1){
    vector<array<pii, 2>> b(3);
    for(int i=0; i<3; i++) b[i] = bound[i];
    for(int i=0; i<3; i++){
        for(int j=0; j<2; j++) {
            b[i][j].X += d1[i].X;
            b[i][j].Y += d1[i].Y;
        }
    }

    for(int i=0; i<3; i++){
        for(int j=i+1; j<3; j++){
            if((b[i][1].X < b[j][0].X or b[j][1].X < b[i][0].X) or (b[i][1].Y < b[j][0].Y or b[j][1].Y < b[i][0].Y)) continue;
            return false;
        }
    }
    return true;
}

bool not_intersect(array<pii, 3> d1){
    for(int i=0; i<3; i++){
        if(d1[i].X > 10 or d1[i].Y > 10) return false;
    }
    for(int i=0; i<3; i++){
        for(int j=i+1; j<3; j++){
            for(int x=0; x<10; x++){
                for(int y=0; y<10; y++){
                    if(vshp[i][x][y] == 0) continue;
                    int nx = x + d1[i].X - d1[j].X;
                    int ny = y + d1[i].Y - d1[j].Y;
                    if(0 <= nx and nx < 10 and 0 <= ny and ny < 10){
                        if(vshp[j][nx][ny]) return false;
                    }
                }
            }
        }
    }
    return true;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n1, n2, n3; cin >> n1 >> n2 >> n3;
    int mnx = 10, mny = 10, mxx = 0, mxy = 0;
    for(int i=0; i<n1; i++){
        int x, y; cin >> x >> y;
        vshp[0][x][y] = 1;
        mxx = max(mxx, x);
        mxy = max(mxy, y);
        mnx = min(mnx, x);
        mny = min(mny, y);
    }
    bound[0][0] = {mnx, mny};
    bound[0][1] = {mxx, mxy};

    mnx = 10, mny = 10, mxx = 0, mxy = 0;
    for(int i=0; i<n2; i++){
        int x, y; cin >> x >> y;
        vshp[1][x][y] = 1;
        mxx = max(mxx, x);
        mxy = max(mxy, y);
        mnx = min(mnx, x);
        mny = min(mny, y);
    }
    bound[1][0] = {mnx, mny};
    bound[1][1] = {mxx, mxy};

    mnx = 10, mny = 10, mxx = 0, mxy = 0;
    for(int i=0; i<n3; i++){
        int x, y; cin >> x >> y;
        vshp[2][x][y] = 1;
        mxx = max(mxx, x);
        mxy = max(mxy, y);
        mnx = min(mnx, x);
        mny = min(mny, y);
    }
    bound[2][0] = {mnx, mny};
    bound[2][1] = {mxx, mxy};

    queue<pair<array<pii, 3>, int>> q;
    pair<array<pii, 3>, int> x1 = {{make_pair(0,0),{0,0},{0,0}}, 0};
    set<array<pii, 3>> st;
    st.insert(x1.X);
    q.push(x1);
    while(!q.empty()){
        pair<array<pii, 3>, int> now = q.front(); q.pop();
        if(!not_intersect(now.X)) continue;
        if(now.Y > 20) continue;
        if(isable(now.X)){
            cout << now.Y << "\n"; return 0;
        }
        now.Y++;
        for(int i=0; i<3; i++){
            if(now.X[i].X >= 0){
                now.X[i].X++;
                if(st.find(now.X) == st.end() ) {
                    st.insert(now.X);
                    q.push(now);
                }
                now.X[i].X--;
            }
            if(now.X[i].Y >= 0){
            now.X[i].Y++;
            if(st.find(now.X) == st.end() ) {
                    st.insert(now.X);
                    q.push(now);
                }
            now.X[i].Y--;
            }
            if(now.X[i].X <= 0){
            now.X[i].X--;
            if(st.find(now.X) == st.end() ) {
                    st.insert(now.X);
                    q.push(now);
                }
            now.X[i].X++;
            }
            if(now.X[i].X <= 0){
            now.X[i].Y--;
            if(st.find(now.X) == st.end() ) {
                    st.insert(now.X);
                    q.push(now);
                }
            now.X[i].Y++;
            }
        }
    }
    cout << -1 << '\n';
    return 0;
}