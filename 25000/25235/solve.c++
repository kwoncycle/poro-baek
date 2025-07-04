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

vector<array<int,4>> G[52][52][2]; // 0 not diff 1 after diff
vector<int> pack;
int nxt[52][256];
ll dst0[52][52][2];
int dstlow[52][52];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int s, p, t; cin >> s >> p >> t;

    pack.resize(p);
    for(auto &i:pack) cin >> i;

    for(int i=0; i<52; i++){
        for(int j=0; j<256; j++) nxt[i][j] = 51;
    }


    while(t--){
        int s1, s2; char c;
        cin >> s1 >> c >> s2;
        nxt[s1][c] = s2;
    }

    for(int i=0; i<52; i++){
        for(int j=0; j<52; j++) {
            dst0[i][j][0] = 0x3f3f3f3f3f3f3f3fll; 
            dst0[i][j][1] = dst0[i][j][0];
            dstlow[i][j] = 0x3f3f3f3f;
        }
    }

    for(int i=0; i<52; i++){
        for(char c='a'; c<='z'; c++){
            dstlow[i][nxt[i][c]] = 1;
        }
    }

    for(int k=0; k<52; k++){
        for(int i=0; i<52; i++){
            for(int j=0; j<52; j++){
                dstlow[i][j] = min(dstlow[i][j], dstlow[i][k] + dstlow[k][j]);
            }
        }
    }

    for(int i=0; i<52; i++){
        for(int j=0; j<52; j++){
            for(char c='A'; c<='Z'; c++){
                if(i==j) {
                    G[i][j][0].push_back({nxt[i][c], nxt[j][c], 0, 2});
                }
                G[i][j][1].push_back({nxt[i][c], nxt[j][c], 1, 2});
                if(i == j){ // +A, +abjdA
                    for(int d=0; d<52; d++){
                        if(i != d) {
                            G[i][j][0].push_back({nxt[i][c], nxt[d][c], 1, 2 + dstlow[i][d]});
                        }
                    }
                }
            }
            for(char c='a'; c<='z'; c++){
                if(i==j) {
                    G[i][j][0].push_back({nxt[i][c], nxt[j][c], 0, 2});
                }
                G[i][j][1].push_back({nxt[i][c], j, 1, 1});
                G[i][j][1].push_back({i, nxt[j][c], 1, 1});
            }
            if(i == j){
                for(char c0='a'; c0<='z'; c0++){
                    for(char c1='a'; c1<='z'; c1++){
                        if(c0 != c1){
                            G[i][j][0].push_back({nxt[i][c0], nxt[j][c1], 1, 2});
                        }
                    }
                }
            }
        }
    }

    dst0[1][1][0] = 0;
    priority_queue<array<ll,4>, vector<array<ll,4>>, greater<array<ll,4>>> pq;
    pq.push({0, 1, 1, 0});
    while(!pq.empty()){
        auto [d, i, j, b] = pq.top(); pq.pop();
        
        if(d > dst0[i][j][b]) continue;
        
        for(auto &[ni, nj, nb, nd]:G[i][j][b]){
            if(d + nd < dst0[ni][nj][nb]){
                dst0[ni][nj][nb] = d + nd;
                pq.push({d + nd, ni, nj, nb});
            }
        }
    }

    ll ans = 0x3f3f3f3f3f3f3f3fll;

    for(auto &i:pack){
        for(auto &j:pack){
            ans = min(ans, dst0[i][j][1]);
            ans = min(ans, dst0[i][i][0] + dstlow[i][j]);
        }
    }

    if(ans > 0x3f3f3f3ll){
        cout << "-1\n";
    }
    else cout << ans << "\n";
    return 0;
}