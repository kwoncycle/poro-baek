#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

string ans;
pii cur = {50, 50};
int mp[100][100];
int dst[100][100];
vector<pii> dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // LURD

void L(){ cur = cur + dir[0]; ans += 'L'; }
void U(){ cur = cur + dir[1]; ans += 'U'; }
void R(){ cur = cur + dir[2]; ans += 'R'; }
void D(){ cur = cur + dir[3]; ans += 'D'; }

bool mv(pii o){ // true succeed
    for(int i=0; i<100; i++){
        for(int j=0; j<100; j++) dst[i][j] = 0x3f3f3f;
    }
    queue<pii> q;
    dst[cur.X][cur.Y] = 0;
    q.push(cur);
    while(!q.empty()){
        auto [x, y] = q.front(); q.pop();
        for(auto &[x1, y1]:dir){
            if(!mp[x+x1][y+y1] and dst[x+x1][y+y1] > dst[x][y] + 1){
                dst[x+x1][y+y1] = dst[x][y] + 1;
                q.push({x+x1, y+y1});
            }
        }
    }
    if(dst[o.X][o.Y] == 0x3f3f3f) return false;
    string s;
    while(dst[o.X][o.Y]){
        for(int i=0; i<4; i++){
            if(dst[o.X + dir[i].X][o.Y + dir[i].Y] + 1 == dst[o.X][o.Y]){
                s.push_back((i+2)%4);
                o = o + dir[i];
                break;
            }
        }
    }
    reverse(all(s));
    for(int i:s){
        if(i==0) L();
        else if(i==1) U();
        else if(i==2) R();
        else if(i==3) D();
    }
    return true;
}

void mv_LR(pii o1, pii o2){
    assert(mp[o1.X][o1.Y] == 1); assert(o1.Y == o2.Y);
    if(o1.X < o2.X){
        mv(o1 + dir[0]);
        for(int i=0; i<o2.X-o1.X; i++) {
            R();
            mp[cur.X][cur.Y] = 0;
            mp[cur.X + 1][cur.Y] = 1;
        }
    }
    else if(o1.X > o2.X){
        mv(o1 + dir[2]);
        for(int i=0; i<o1.X-o2.X; i++) {
            L();
            mp[cur.X][cur.Y] = 0;
            mp[cur.X - 1][cur.Y] = 1;
        }
    }
}

void mv_UD(pii o1, pii o2){
    assert(mp[o1.X][o1.Y] == 1); assert(o1.X == o2.X);
    if(o1.Y < o2.Y){
        mv(o1 + dir[3]);
        for(int i=0; i<o2.Y-o1.Y; i++) {
            U();
            mp[cur.X][cur.Y] = 0;
            mp[cur.X][cur.Y + 1] = 1;
        }
    }
    else if(o1.Y > o2.Y){
        mv(o1 + dir[1]);
        for(int i=0; i<o1.Y-o2.Y; i++) {
            D();
            mp[cur.X][cur.Y] = 0;
            mp[cur.X][cur.Y - 1] = 1;
        }
    }
}

vector<pii> T = {{49, 70}, {50, 70}, {51, 70}, {50, 69}, {50, 68}};

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    for(int i=0; i<100; i++) mp[i][0] = 1, mp[0][i] = 1, mp[99][i] = 1, mp[i][99] = 1;
    for(int i=0; i<5; i++){
        int x, y; cin >> x >> y;
        mp[x + 50][y + 50] = 1;
    }
    int truth = 1;
    for(auto [x,y]:dir){
        if(!mp[50+x][50+y]) truth = 0;
    }
    if(truth){
        if(mp[50][53] or mp[51][52] or mp[49][52]){
            D(); mp[50][49] = 0; mp[50][48] = 1;
        }
        else{
            U(); mp[50][51] = 0; mp[50][52] = 1;
        }
    }
    truth = 1;
    for(int i=35; i<=65; i++){
        for(int j=35; j<=65; j++){
            truth = 1;
            for(auto [x,y]:dir){
                if(!mp[i+x][j+y]) truth = 0;
            }
            if(truth){
                assert(cur != pii(i,j));
                {
                    int x = i, y = j;
                    mv({x, y+2});
                    D();
                    mp[cur.X][cur.Y] = 0; mp[cur.X][cur.Y-1] = 1;
                    pii o;
                    for(i=35; i<=65; i++){
                        for(j=35; j<=65; j++){
                            if(x-1 <= i and i <= x+1 and y-1 <= j and j <= y+1) continue;
                            if(mp[i][j]){
                                o = {i, j};
                                goto outt1;
                            }
                        }
                    }
                    outt1:
                    if(o.Y > y){
                        mv_UD(o, {o.X, o.Y + 5});
                        o = {o.X, o.Y + 5};
                        mv_LR(o, {x+5, o.Y});
                        o = {x+5, o.Y};
                        mv_UD(o, {o.X, y-2});
                        o = {o.X, y-2};
                        mv_LR(o, {x, y-2});
                        cout << ans << "\n"; return 0;
                    }
                    else{
                        mv_UD(o, {o.X, y-2});
                        o = {o.X, y-2};
                        mv_LR(o, {x, y-2});
                        cout << ans << "\n"; return 0;
                    }
                }
            }
        }
    }
    for(int ti=0; ti<5; ti++){
        pii o;
        for(int j=65; j>=35; j--){
            for(int i=35; i<=65; i++){
                if(mp[i][j]){
                    o = {i,j}; goto outt;
                }
            }
        }
        outt:
        mv_UD(o, {o.X, 62});
        mv_LR({o.X, 62}, {T[ti].X, 62});
        mv_UD({T[ti].X, 62}, T[ti]);
    }
    cout << ans << "\n";

    return 0;
}