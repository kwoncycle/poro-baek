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
vector<vector<int>> mp1(4, vector<int>(4, 0));
vector<vector<int>> pathmark(4, vector<int>(4, 0));
int truth = 0;
vector<set<int>> vs(5);
int mx = 0;

vector<vector<int>> mp(4, vector<int>(4, 0));


int path_value(){
    int ans = 0, u = 1;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(pathmark[i][j] >= 20) ans += u;
            u *= 2;
        }
    }
    return ans;
}   

void find_path(int c, int i1, int i2, int now){
    int x2 = i2/4, y2 = i2%4;
    int xn2 = now/4, yn2 = now%4;
    if(abs(x2-xn2) + abs(y2-yn2) == 1){
        vs[c].insert(path_value());
    }
    if(xn2 + 1 < 4){
        if(pathmark[xn2 + 1][yn2] == 0){
            pathmark[xn2 + 1][yn2] = 20;
            find_path(c, i1, i2, (xn2 + 1)*4 + yn2);
            pathmark[xn2 + 1][yn2] = 0;
        }
    }
    if(xn2 - 1 >= 0){
        if(pathmark[xn2 - 1][yn2] == 0){
            pathmark[xn2 - 1][yn2] = 20;
            find_path(c, i1, i2, (xn2 - 1)*4 + yn2);
            pathmark[xn2 - 1][yn2] = 0;
        }
    }
    if(yn2 + 1 < 4){
        if(pathmark[xn2][yn2 + 1] == 0){
            pathmark[xn2][yn2 + 1] = 20;
            find_path(c, i1, i2, (xn2)*4 + yn2 + 1);
            pathmark[xn2][yn2 + 1] = 0;
        }
    }
    if(yn2 - 1 >= 0){
        if(pathmark[xn2][yn2 - 1] == 0){
            pathmark[xn2][yn2 - 1] = 20;
            find_path(c, i1, i2, (xn2)*4 + yn2 - 1);
            pathmark[xn2][yn2 - 1] = 0;
        }
    }
}

bool isvalid(){
    for(int c=1; c<=4; c++){
        if(c > mx) continue;
        pathmark = vector<vector<int>>(4, vector<int>(4, 0));
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                if(mp[i][j] == c){
                    pathmark[i][j] = 1;
                }
                else if(mp[i][j]) pathmark[i][j] = -1;
                else{
                    if(mp1[i][j] == c) pathmark[i][j] = 20;
                }
            }
        }
        int u = path_value();
        
        if(vs[c].empty()) return false;
        if(vs[c].find(u) == vs[c].end()){
            return false;
        }
    }
    return true;
}

void find_all(int depth){
    if(truth) return;
    if(depth == 16){
        if(isvalid()){
            truth = 1;
            return;
        }
        return;
    }
    int x = depth/4, y = depth%4;
    if(mp[x][y] != 0){
        find_all(depth + 1);
        return;
    }

    for(int i=1; i<=mx; i++){
        mp1[x][y] = i;
        find_all(depth + 1);
    }
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    
    for(int i=0; i<4; i++){
        string s; cin >> s;
        for(int j=0; j<4; j++){
            if(s[j] == 'R') mp[i][j] = 1;
            if(s[j] == 'G') mp[i][j] = 2;
            if(s[j] == 'B') mp[i][j] = 3;
            if(s[j] == 'Y') mp[i][j] = 4;
            mx = max(mx, mp[i][j]);
            mp1[i][j] = mp[i][j];
        }
    }
    
    for(int c=1; c<=4; c++){
        int i1 = -1, i2 = -1;
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                if(mp[i][j] == c){
                    if(i1 < 0){
                        i1 = i*4 + j;
                    }
                    else i2 = i*4 + j;
                }
            }
        }
        if(i1 >= 0){
            pathmark = vector<vector<int>>(4, vector<int>(4, 0));
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    if(mp[i][j] == c){
                        pathmark[i][j] = 1;
                    }
                    else if(mp[i][j]) pathmark[i][j] = -1;
                }
            }
            find_path(c, i1, i2, i1);
        }
    }
    find_all(0);
    if(truth) cout << "solvable\n";
    else cout << "not solvable\n";
    return 0;
}