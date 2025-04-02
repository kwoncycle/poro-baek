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

int deg[100005];
vector<int> graph[100005];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    int k1 = k;
    set<pii> st;
    for(int i=0; i<m; i++){
        int a,b; cin >> a >> b;
        st.insert({a, b});
    }
    for(auto [i,j]:st) {
        graph[i].push_back(j);
        deg[j]++;
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    priority_queue<int> used;
    for(int i=1; i<=n; i++){
        if(!deg[i]) pq.push(i);
    }
    vector<pii> edge;
    vector<int> ans;
    while(k){
        if(pq.size() > 1){
            used.push(pq.top()); pq.pop();
            k--;
        }
        else if(pq.size() == 1){
            int o = pq.top();
            if(used.empty() or used.top() < o){
                pq.pop();
                ans.push_back(o);
                for(int i:graph[o]){
                    deg[i]--;
                    if(!deg[i]) pq.push(i);
                }
            }
            else{
                pq.pop();
                k--;
                used.push(o);
            }
        }
        else{
            if(used.empty()) break;
            int o = used.top();
            used.pop();
            if(!ans.empty()) edge.push_back({ans.back(), o});
            ans.push_back(o);
            for(int i:graph[o]){
                deg[i]--;
                if(!deg[i]) pq.push(i);
            }
        }
    }
    // for(int i:ans) cout << i << " "; cout << "\n";
    // {
    //     vector<int> v1;
    //     while(!pq.empty()){
    //         v1.push_back(pq.top()); cout << pq.top() << " "; pq.pop();
    //     }
    //     cout << "pq\n";
    //     for(int i:v1) pq.push(i);
    // }
    // {
    //     vector<int> v1;
    //     while(!used.empty()){
    //         v1.push_back(used.top()); cout << used.top() << " "; used.pop();
    //     }
    //     cout << "used\n";
    //     for(int i:v1) used.push(i);
    // }
    while(true){
        while(!pq.empty()){
            int o = pq.top(); pq.pop();
            ans.push_back(o);
            for(int i:graph[o]){
                deg[i]--;
                if(!deg[i]) pq.push(i);
            }
        }
        if(!used.empty()){
            int o = used.top(); used.pop();
            if(!ans.empty()) edge.push_back({ans.back(), o});
            ans.push_back(o);
            for(int i:graph[o]){
                deg[i]--;
                if(!deg[i]) pq.push(i);
            }
        }
        if(pq.empty() and used.empty()) break;
    }
    for(int i:ans) cout << i << " "; cout << "\n";
    cout << edge.size() << "\n";
    for(auto [i,j]:edge) cout << i << " " << j << "\n";
    assert((int)edge.size() <= k1);
    return 0;
}