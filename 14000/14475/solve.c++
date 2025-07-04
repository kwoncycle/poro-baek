#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
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

int n, m, x;
int H(int node, int tm){
    return node * (2*x + 2) + tm;
}
int C(int node, int tm){
    return node * (2*x + 2) + tm + x + 1;
}
// int W(int node, int tm){
//     return node * (2*x + 3) + 2*x + 2;
// }

vector<pii> graph[4405000];
int temp[10040];
ll dst[4405000];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m >> x;
    for(int i=1; i<=n; i++) {
        cin >> temp[i];
        if(temp[i] == 1){
            graph[H(i, x)].push_back({0, C(i, x)});
            graph[C(i, x)].push_back({0, H(i, x)});
        }
    }
    for(int i=1; i<=m; i++){
        int a, b, d; cin >> a >> b >> d;
        if(temp[a] == 0){
            if(temp[b] == 0) graph[H(a, 0)].push_back({d, H(b, 0)});
            else if(temp[b] == 1) graph[H(a, 0)].push_back({d, H(b, min(x, d))});
            else {
                if(d >= x) graph[H(a, 0)].push_back({d, C(b, 0)});
            }
        }
        else if(temp[a] == 2){
            if(temp[b] == 2) graph[C(a, 0)].push_back({d, C(b, 0)});
            else if(temp[b] == 1) graph[C(a, 0)].push_back({d, C(b, min(x, d))});
            else {
                if(d >= x) graph[C(a, 0)].push_back({d, H(b, 0)});
            }
        }
        else{
            if(temp[b] == 0){
                for(int id=0; id<=x; id++){
                    graph[H(a, id)].push_back({d, H(b, 0)});
                    if(id + d >= x) graph[C(a, id)].push_back({d, H(b, 0)});
                }
            }
            else if(temp[b] == 2){
                for(int id=0; id<=x; id++){
                    graph[C(a, id)].push_back({d, C(b, 0)});
                    if(id + d >= x) graph[H(a, id)].push_back({d, C(b, 0)});
                }
            }
            else{
                for(int id=0; id<=x; id++){
                    graph[H(a, id)].push_back({d, H(b, min(x, id+d))});
                    graph[C(a, id)].push_back({d, C(b, min(x, id+d))});
                }
            }
        }

        swap(a, b);
        if(temp[a] == 0){
            if(temp[b] == 0) graph[H(a, 0)].push_back({d, H(b, 0)});
            else if(temp[b] == 1) graph[H(a, 0)].push_back({d, H(b, min(x, d))});
            else {
                if(d >= x) graph[H(a, 0)].push_back({d, C(b, 0)});
            }
        }
        else if(temp[a] == 2){
            if(temp[b] == 2) graph[C(a, 0)].push_back({d, C(b, 0)});
            else if(temp[b] == 1) graph[C(a, 0)].push_back({d, C(b, min(x, d))});
            else {
                if(d >= x) graph[C(a, 0)].push_back({d, H(b, 0)});
            }
        }
        else{
            if(temp[b] == 0){
                for(int id=0; id<=x; id++){
                    graph[H(a, id)].push_back({d, H(b, 0)});
                    if(id + d >= x) graph[C(a, id)].push_back({d, H(b, 0)});
                }
            }
            else if(temp[b] == 2){
                for(int id=0; id<=x; id++){
                    graph[C(a, id)].push_back({d, C(b, 0)});
                    if(id + d >= x) graph[H(a, id)].push_back({d, C(b, 0)});
                }
            }
            else{
                for(int id=0; id<=x; id++){
                    graph[H(a, id)].push_back({d, H(b, min(x, id+d))});
                    graph[C(a, id)].push_back({d, C(b, min(x, id+d))});
                }
            }
        }
    }

    for(int i=0; i<4405000; i++) dst[i] = 0x3f3f3f3f3f3f3fll;

    priority_queue<pll, vector<pll>, greater<pll>> pq;

    if(temp[1] == 0){
        dst[H(1, 0)] = 0;
        pq.push({0, H(1, 0)});
    }
    else if(temp[1] == 1){
        dst[H(1, x)] = 0;
        pq.push({0, H(1, x)});
    }
    else{
        dst[C(1, x)] = 0;
        pq.push({0, C(1, x)});
    }

    while(!pq.empty()){
        auto [d, node] = pq.top(); pq.pop();
        if(d > dst[node]) continue;
        for(auto &[d1, nxt]:graph[node]){
            if(d + d1 < dst[nxt]){
                dst[nxt] = d + d1;
                pq.push({d + d1, nxt});
            }
        }
    }

    ll ans = 0x3f3f3f3f3f3f3fll;
    for(int i=0; i<=x; i++){
        ans = min(ans, dst[H(n, i)]);
        ans = min(ans, dst[C(n, i)]);
    }

    cout << ans << "\n";
    return 0;
}