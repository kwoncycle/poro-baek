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

int chk[1004], p0[1004], p1[1004], T[3][1004];
vector<int> G[1004];

void DFS(int node, int ban){
    for(int i:G[node]){
        if(chk[i] or i == ban) continue;
        chk[i] = 1;
        DFS(i, ban);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    for(int i=1; i<=n; i++){
        cin >> p0[i] >> p1[i];
        G[p0[i]].push_back(i);
        G[p1[i]].push_back(i);
    }

    for(int i=1; i<=n; i++){
        memset(T, 0, sizeof(T));

        memset(chk, 0, sizeof(chk));
        chk[i] = 1;
        DFS(i, -1);
        for(int j=1; j<=n; j++){
            if(chk[j]) T[0][j] = 1;
        }

        memset(chk, 0, sizeof(chk));
        chk[p0[i]] = 1;
        DFS(p0[i], i);
        for(int j=1; j<=n; j++){
            if(chk[j]) T[1][j] = 1;
        }

        memset(chk, 0, sizeof(chk));
        chk[p1[i]] = 1;
        DFS(p1[i], i);
        for(int j=1; j<=n; j++){
            if(chk[j]) T[2][j] = 1;
        }

        int truth = 0;
        for(int j=1; j<=n; j++){
            if(T[0][j] and T[1][j] and T[2][j]){
                truth = 1; break;
            }
        }
        if(truth) cout << "Y";
        else cout << "N";
    }
    cout << "\n";

    return 0;
}