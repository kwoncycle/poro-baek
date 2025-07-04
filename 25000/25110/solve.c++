#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

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

const int MX = 1004;
int n, r, MOD, C[MX][MX], chk[MX], val[MX];

vector<int> graph[MX];
int edge0[MX*10], edge1[MX*10];

bool DFS(int node){
    if(val[node] < 0) return true;
    for(int i:graph[node]){
        if(!chk[i] and C[node][i] > 0){
            chk[i] = 1;
            if(DFS(i)) {
                C[node][i] -= MOD;
                C[i][node] += MOD;
                return true;
            }
        }
    }
    return false;
}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> r >> MOD;
    for(int i=0; i<r; i++){
        int a, b, c; cin >> a >> b >> c;
        C[a][b] = c;
        C[b][a] = -c;
        edge0[i] = a, edge1[i] = b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    while(true){
        memset(val, 0, sizeof(val));
        memset(chk, 0, sizeof(chk));
        for(int i=0; i<r; i++){
            int node0 = edge0[i], node1 = edge1[i], w = C[node0][node1];
            val[node0] += w; val[node1] -= w;
        }
        int st = -1;
        
        for(int i=1; i<=n; i++){
            if(val[i] > 0){
                st = i; break;
            }
        }
        if(st == -1) break;
        chk[st] = 1;
        DFS(st);
    }

    for(int i=0; i<r; i++){
        cout << C[edge0[i]][edge1[i]] << "\n";
    }


    return 0;
}