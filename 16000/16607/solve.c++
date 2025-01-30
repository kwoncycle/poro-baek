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
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s; cin >> s;
    int n = s.size();
    for(int i=0; i<n; i++){
        if(s[i] == 'L') s[i] = 1;
        if(s[i] == 'R') s[i] = 4;
        if(s[i] == 'U') s[i] = 2;
        if(s[i] == 'D') s[i] = 3;
    }
    vector<pll> direc = {{0,0},{-1,0},{0,1},{0,-1},{1,0}};
    for(int i=0; i<n-1; i++) if(s[i] == s[i+1]){
        cout << "impossible\n"; return 0;
    }
    vector<pll> point(n);
    pll now = {0, 0};
    vector<pll> wall;
    ll d = 1;
    for(int i=0; i<n; i++){
        if(i-2>=0 and s[i]==s[i-2] and s[i-1]+s[i] == 5){
            point[i] = point[i-2];
            now = point[i];
            if(i == n-1){
                cout <<"impossible\n"; return 0;
            }
        }
        else{
            now = {now.X + d*direc[s[i]].X, now.Y + d*direc[s[i]].Y};
            point[i] = now;
            pll w = {now.X + direc[s[i]].X, now.Y + direc[s[i]].Y};
            wall.push_back(w);
        }
        d *= 2;
    }
    for(auto &[x,y]:point){
        x -= now.X; y -= now.Y;
    }
    for(auto &[x,y]:wall){
        x -= now.X; y -= now.Y;
    }
    now = {-now.X, -now.Y};
    set<pll> spoint, swall;
    for(auto [x,y]:point) spoint.insert({x,y});
    for(auto [x,y]:wall) swall.insert({x,y});

    if((int)spoint.size() != n and false){
        cout << "impossible\n";
    }
    else{
        cout << now.X << " " << now.Y << "\n";
        cout << (int)swall.size() << "\n";
        for(auto [x,y]:swall){
            cout << x << " " << y << "\n";
        }
        //for(auto [x,y]:point) cout << x << " " << y << "\n";
    }
    return 0;
}