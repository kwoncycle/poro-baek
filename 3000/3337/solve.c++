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

int n, k;
vector<int> graph(500005), graph_inv[500005];
bitset<500005> is_c;
int visited[500005];
int dst[500005];
int nxt[500005];
int ans = 0;

void DFS(int x){
    int mn = k+1;
    for(int i:graph_inv[x]){
        if(is_c[i]) continue;
        DFS(i);
        mn = min(mn, dst[i] + 1);
    }

    dst[x] = min(dst[x], mn);
    if(dst[x] > k and !is_c[x]){
        dst[x] = 1; ans++;
    }
}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> k;
    for(int i=0; i<n; i++){
        int a, b; cin >> a >> b;
        graph[a] = b;
        graph_inv[b].push_back(a);
        dst[i+1] = 0x3f3f3f3f;
    }
    int u = 1; dst[u] = 0;
    for(int i=1; i<=k; i++){
        u = graph[u];
        dst[u] = min(dst[u], i);
    }

    for(int i=1; i<=n; i++){
        if(!visited[i]){
            int i1 = i;
            while(true){
                if(visited[i1] == i){
                    is_c[i1] = 1; visited[i1] = i1;
                    for(int st = i1; graph[st] != i1;){
                        st = graph[st];
                        is_c[st] = 1; visited[st] = i1;
                    }
                    break;
                }
                else if(!visited[i1]){
                    visited[i1] = i;
                    i1 = graph[i1];
                }
                else break;
            }
        }
    }

    for(int i=1; i<=n; i++){
        if(is_c[i] and graph_inv[i].size() > 1) DFS(i);
    }

    for(int i=1; i<=n; i++){
        if(visited[i] == i and is_c[i]){
            vector<int> v;
            int i1 = i;
            v.push_back(dst[i1]);
            while(graph[i1] != i){
                i1 = graph[i1];
                v.push_back(dst[i1]);
            }
            int nv = v.size();
            for(int j=0; j<nv; j++){
                v[(j+1)%nv] = min(v[(j+1)%nv], v[j]+1);
            }
            for(int j=0; j<nv; j++){
                v[(j+1)%nv] = min(v[(j+1)%nv], v[j]+1);
            }
            for(int j=0; j<nv; j++) v.push_back(v[j]);
            int id = 0;
            while(id < nv and v[id] <= k) id++;
            if(id >= nv) continue;
            if(nv <= k){
                ans++; continue;
            }
            int truth = 0;
            for(int i1=0, i2=k; i1<nv; i1++){
                while((i2+nv-i1)%nv < k) {
                    i2 = (i2+1)%nv;
                }
                while(v[i2] <= k){
                    i2 = (i2 + 1) % nv;
                    if(i1 == i2) {truth = 1; break;}
                }
                nxt[i1] = (nv+i2-i1)%nv;
            }
            if(truth){
                ans++; continue;
            }
            int mn = 0x3f3f3f;
            int cnt = 0;
            for(int j=0; j<nv; j++){
                if(v[j] > k){
                    cnt++;
                    int j1 = j;
                    int c = 0;
                    while(j1 < j + nv){
                        j1 += nxt[j1%nv]; c++;
                    }
                    mn = min(mn, c);
                }
                if(cnt >= k) break;
            }
            ans += mn;
        }
    }
    cout << ans << "\n";

    return 0;
}