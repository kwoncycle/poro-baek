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
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    int w, h; cin >> w >> h;
    int wd, hd; cin >> wd >> hd;
    vector<vector<int>> v(h+2, vector<int>(w+2, 0));
    for(int i=0; i<h+2; i++){
        v[i][0] = 1;
        v[i][w+1] = 1;
    }
    for(int i=0; i<w+2; i++){
        v[0][i] = 1;
        v[h+1][i] = 1;
    }
    for(int i=1; i<=hd; i++){
        for(int j=1; j<=wd; j++){
            v[i][j] = 1;
        }
    }
    for(int i=1; i<=hd; i++){
        for(int j=1; j<=wd; j++){
            v[i][w+1-j] = 1;
        }
    }
    for(int i=1; i<=hd; i++){
        for(int j=1; j<=wd; j++){
            v[h+1-i][j] = 1;
        }
    }
    for(int i=1; i<=hd; i++){
        for(int j=1; j<=wd; j++){
            v[h+1-i][w+1-j] = 1;
        }
    }

    pii now = {1, wd+1};
    vector<pii> dir = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    int id = 1;
    int qq; cin >> qq;
    for(int i=0; i<qq; i++){
        v[now.X][now.Y] = 2;
        int nx = now.X, ny = now.Y;
        int found = 0;
        for(int j=id-1; j<id+3; j++){
            if(v[nx + dir[(j+4)%4].X][ny + dir[(j+4)%4].Y] == 0){
                id = (j+4)%4; found = 1; break;
            }
        }
        if(!found) break;
        now = {nx + dir[id].X, ny + dir[id].Y};
    }
    cout << now.Y << "\n" << now.X << "\n";
    return 0;
}