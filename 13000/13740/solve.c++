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

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    string s; cin >> s;
    int id = 0;
    for(int i=0; i<n; i++){
        if(v[id] > v[i]) id = i;
    }

    LINE now = {pii(0,-100), v[id]};
    char c = 'R';
    vector<int> visited(n, 0);
    visited[id] = 1;
    vector<int> ans(n, 0);
    ans[0] = id;
    for(int i=0; i<n-2; i++){
        id = -1;
        if(s[i] == 'L' and c == 'R'){
            for(int j=0; j<n; j++){
                if(!visited[j]){
                    if(id == -1) id = j;
                    if((v[id]-now[1])/(v[j]-now[1]) < 0) id = j;
                    
                }
            }
            ans[i+1] = id;
            now = {now[1], v[id]};
            visited[id] = 1;
            c = 'L';
        }
        else if(s[i] == 'R' and c == 'R'){
            for(int j=0; j<n; j++){
                if(!visited[j]){
                    if(id == -1) id = j;
                    if((v[id]-now[1])/(v[j]-now[1]) > 0) id = j;
                    
                }
            }
            ans[i+1] = id;
            now = {now[1], v[id]};
            visited[id] = 1;
            c = 'R';
        }
        else if(s[i] == 'L' and c == 'L'){
            for(int j=0; j<n; j++){
                if(!visited[j]){
                    if(id == -1) id = j;
                    if((v[id]-now[1])/(v[j]-now[1]) < 0) id = j;
                    
                }
            }
            ans[i+1] = id;
            now = {now[1], v[id]};
            visited[id] = 1;
            c = 'L';
        }
        else if(s[i] == 'R' and c == 'L'){
            for(int j=0; j<n; j++){
                if(!visited[j]){
                    if(id == -1) id = j;
                    if((v[id]-now[1])/(v[j]-now[1]) > 0) id = j;
                    
                }
            }
            ans[i+1] = id;
            now = {now[1], v[id]};
            visited[id] = 1;
            c = 'R';
        }
    }
    id = 0;
    while(visited[id]) id++;
    ans[n-1] = id;
    for(int i:ans) cout << i+1 << " "; cout << "\n";
    return 0;
}