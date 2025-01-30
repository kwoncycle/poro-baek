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
int n;
pii int2pii(int x){
    x -= n+1;
    int x0 = x/n + 1;
    int y0 = x%n + 1;
    return {x0, y0};
}

int pii2int(pii p){
    return p.X*n+p.Y;
}

#define piii pair<int, pii>

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n;
    vector<vector<int>> v(n+2, vector<int>(n+2, 0));
    // 0 air // 1 wall // 2 mirror // 3 door 
    vector<int> posend;
    for(int i=1; i<=n; i++){
        string s; cin >> s;
        for(int j=1; j<=n; j++){
            if(s[j-1] == '*') v[i][j] = 1;
            else if(s[j-1] == '!') v[i][j] = 2;
            else if(s[j-1] == '#') {
                v[i][j] = 3;
                posend.push_back(pii2int({i, j}));
            }
        }
    }

    vector<vector<int>> graph((n+2)*(n+2));
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(v[i][j] == 1) continue;
            int j1 = j;
            while(j1 <= n and v[i][j1] != 1) j1++;
            vector<int> tmpv;
            for(int j2=j; j2<j1; j2++){
                if(v[i][j2] == 2 or v[i][j2] == 3) tmpv.push_back(j2);
            }
            for(int j2=0; j2<(int)tmpv.size(); j2++){
                for(int j3=j2+1; j3<(int)tmpv.size(); j3++){
                    int u1 = pii2int({i, tmpv[j2]});
                    int u2 = pii2int({i, tmpv[j3]});
                    graph[u1].push_back(u2);
                    graph[u2].push_back(u1);
                }
            }
            j = j1 - 1;
        }
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(v[j][i] == 1) continue;
            int j1 = j;
            while(j1 <= n and v[j1][i] != 1) j1++;
            vector<int> tmpv;
            for(int j2=j; j2<j1; j2++){
                if(v[j2][i] == 2 or v[j2][i] == 3) tmpv.push_back(j2);
            }
            for(int j2=0; j2<(int)tmpv.size(); j2++){
                for(int j3=j2+1; j3<(int)tmpv.size(); j3++){
                    int u1 = pii2int({tmpv[j2], i});
                    int u2 = pii2int({tmpv[j3], i});
                    graph[u1].push_back(u2);
                    graph[u2].push_back(u1);
                }
            }
            j = j1 - 1;
        }
    }

    vector<vector<int>> dst(n+2, vector<int>(n+2, 99999999));
    pii xy = int2pii(posend[0]);
    dst[xy.X][xy.Y] = 0;

    priority_queue<piii> pq;
    pq.push({0, xy});
    while(!pq.empty()){
        auto t1 = pq.top();
        int d = t1.X;
        pii pos = t1.Y;
        pq.pop();
        if(dst[pos.X][pos.Y] < d) continue;
        dst[pos.X][pos.Y] = d;
        int pos_int = pii2int(pos);
        for(int nxt:graph[pos_int]){
            pii pos_nxt = int2pii(nxt);
            if(dst[pos_nxt.X][pos_nxt.Y] > d + 1) {
                dst[pos_nxt.X][pos_nxt.Y] = d+1;
                pq.push({d+1, pos_nxt});
            }
        }
    }
    /*
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cout << dst[i][j] << " ";
        }
        cout << "\n";
    }*/
    pii xy1 = int2pii(posend[1]);
    cout << dst[xy1.X][xy1.Y] - 1 << "\n";
    
    return 0;
}