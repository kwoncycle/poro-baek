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

#define A3 array<int, 3>

struct solve{
    int n, m, k;
    vector<vector<int>> graph;
    vector<int> visit;
    vector<A3> dragon;
    vector<vector<int>> dv;
    ll ans = 0;
    solve(){
        cin >> n >> m >> k;
        if(n == 0 and m == 0 and k == 0)exit(0);
        graph.resize(n+1);
        visit.resize(n+1, 0);
        dragon.resize(k);
        dv.resize(n+1);
        while(m--){
            int a, b; cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        for(int i=0; i<k; i++){
            for(int j=0; j<3; j++) cin >> dragon[i][j];  // 0 c 1 s 2 n
            dv[dragon[i][0]].push_back(i);
        }

        for(int i=1; i<=n; i++){
            if(!visit[i]){
                vector<int> d_idx;
                visit[i] = 1;
                DFS(i, d_idx);

                sort(d_idx.begin(), d_idx.end(), [&](int l, int r){
                    return dragon[l][2] == dragon[r][2] ? dragon[l][1] > dragon[r][1] : dragon[l][2] > dragon[r][2];
                });

                ll cnt = 0;
                for(int di:d_idx){
                    if(dragon[di][2] < cnt) break;
                    ll cnt1 = cnt + dragon[di][1];
                    ll cnt2 = dragon[di][2] + 1;
                    cnt = min(cnt1, cnt2);
                }

                ans += cnt;
            }
        }

        cout << ans << "\n";
    }

    void DFS(int node, vector<int> &d_idx){
        for(int i: dv[node]) d_idx.push_back(i);
        for(int i:graph[node]){
            if(!visit[i]){
                visit[i] = 1;
                DFS(i, d_idx);
            }
        }
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    while(true){
        solve s;
    }
    return 0;
}