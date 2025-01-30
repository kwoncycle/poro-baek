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

vector<vector<int>> v;
int good = 0;
void BT(int id, int n, vector<int>&dag, vector<int>&color){
    if(id == n) {
        good = 1; return;
    }
    int c = 7;
    for(int j=0; j<id; j++){
        if(v[id][dag[j]]) c &= 7 - color[dag[j]];
    }
    if(c == 7){
        color[dag[id]] = 1;
        BT(id+1, n, dag, color);
    }
    else{
        if(c == 0) return;
        if(c&1){
            color[dag[id]] = 1;
            BT(id+1, n, dag, color);
            color[dag[id]] = 0;
        }
        if(c&2){
            color[dag[id]] = 2;
            BT(id+1, n, dag, color);
            color[dag[id]] = 0;
        }
        if(c&4){
            color[dag[id]] = 4;
            BT(id+1, n, dag, color);
            color[dag[id]] = 0;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    while(true){
        int n; cin >> n;
        if(!n) break;
        v = vector<vector<int>>(n, vector<int>(n, 0));
        int truth = 0;
        for(int i=0; i<n; i++){
            string s; cin >> s;
            int id = s[0]-'A';
            for(int j=2; j<(int)s.size(); j++){
                truth = 1;
                int i1 = s[j]-'A';
                v[id][i1] = 1;
            }
        }
        if(!truth){
            cout << "1 channel needed.\n";
            continue;
        }
        vector<int> color(n, -1);
        queue<int> q;
        for(int i=0; i<n; i++){
            if(color[i] < 0){
                color[i] = 0;
                q.push(i);
                while(!q.empty()){
                    int id = q.front(); q.pop();
                    for(int j=0; j<n; j++){
                        if(v[id][j]){
                            if(color[j] < 0){
                                color[j] = 1 - color[id];
                                q.push(j);
                            }
                        }
                    }
                }
            }
        }
        truth = 1;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(v[i][j] and color[i] == color[j]) truth = 0;
            }
        }
        if(truth){
            cout << "2 channels needed.\n";
            continue;
        }

        truth = 1;
        vector<int> dag;
        fill(color.begin(), color.end(), 0);
        for(int i=0; i<n; i++){
            if(!color[i]){
                color[i] = 1;
                dag.push_back(i);
                q.push(i);
                while(!q.empty()){
                    int id = q.front(); q.pop();
                    for(int j=0; j<n; j++){
                        if(v[id][j] and !color[j]){
                            color[j] = 1;
                            dag.push_back(j);
                            q.push(j);
                        }
                    }
                }
            }
        }
        fill(color.begin(), color.end(), 0);
        good = 0;
        BT(0, n, dag, color);

        if(good){
            cout << "3 channels needed.\n";
        }
        else{
            cout << "4 channels needed.\n";
        }
    }
    return 0;
}