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

#define vll vector<vector<ll>>
#define MOD 1000000007
ll n;
vector<vector<ll>> graph(14);
vector<vector<int>> dist(14, vector<int>(14, 0x3f3f3f));


void mul(vll &M, vll &M1, vll &ans){
    for(int i=0; i<196; i++){
        for(int j=0; j<196; j++) ans[i][j] = 0;
    }
    for(int i=0; i<196; i++){
        for(int j=0; j<196; j++){
            for(int k=0; k<196; k++){
                ans[i][j] = (ans[i][j] + M[i][k]*M1[k][j]) % MOD;
            }
        }
    }
}

void poww(vll &M, ll e, vll &ans){
    vll A(196, vector<ll>(196, 0));
    for(int i=0; i<196; i++) ans[i][i] = 1;
    while(e){
        if(e&1){
            mul(M, ans, A);
            ans = A;
        }
        e >>= 1;
        mul(M, M, A);
        M = A;
    }
}


int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    graph[0].push_back(1);
    graph[1].push_back(0);
    graph[1].push_back(2);
    graph[2].push_back(4);
    graph[3].push_back(0);
    graph[3].push_back(1);
    graph[3].push_back(4);
    graph[4].push_back(6);
    graph[4].push_back(7);
    graph[5].push_back(3);
    graph[6].push_back(3);
    graph[6].push_back(7);
    graph[6].push_back(8);
    graph[6].push_back(9);
    graph[6].push_back(10);
    graph[7].push_back(9);
    graph[8].push_back(5);
    graph[9].push_back(13);
    graph[9].push_back(10);
    graph[10].push_back(8);
    graph[10].push_back(12);
    graph[11].push_back(8);
    graph[12].push_back(8);
    graph[12].push_back(11);
    graph[13].push_back(12);

    for(int i=0; i<14; i++){
        for(int j:graph[i]) dist[i][j] = 1;
    }

    for(int i=0; i<14; i++) dist[i][i] = 0;
    for(int u=0; u<14; u++)
    for(int i=0; i<14; i++){
        for(int j=0; j<14; j++){
            for(int k=0; k<14; k++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    vll M(196, vector<ll>(196, 0));
    for(int i=0; i<196; i++){
        for(int j=0; j<196; j++){
            int i1 = i%14, i2 = i/14, j1 = j%14, j2 = j/14;
            if(dist[i1][i2] >= 3 and dist[i2][i1] >= 3 and dist[j1][j2] >= 3 and dist[j2][j1] >= 3 and dist[i1][j1] == 1 and dist[i2][j2] == 1){
                M[i][j] = 1;
            }
        }
    }
    cin >> n;
    ll ans0 = 0;
    vll ans(196, vector<ll>(196, 0));
    poww(M, n, ans);
    for(int i=0; i<196; i++){
        ans0 += ans[3*14+10][i]; ans0 %= MOD;
    }
    cout << ans0 << "\n";
    
    
    
    return 0;
}