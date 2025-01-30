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

#define MX 1005

int n;
vector<vector<int>> graph(MX);
vector<int> under(MX);
vector<int> visited(MX);
vector<pii> tree(MX);
vector<int> where(MX);
void DFS(int x){
    under[x] = 1;
    for(int i:graph[x]){
        if(!visited[i]){
            visited[i] = 1;
            DFS(i);
            under[x] += under[i];
        }
    }
}

void DFS_fill(int x, vector<int> idx){
    int mn = idx[0];
    where[x] = mn;
    sort(idx.begin()+1, idx.end(), [&](int l, int r){
        return (tree[l] - tree[mn])/(tree[r] - tree[mn]) > 0;
    });
    assert(idx[0] == mn);
    int id = 1;
    for(int i:graph[x]){
        if(!visited[i]){
            vector<int> tmp;
            for(int j=0; j<under[i]; j++){
                tmp.push_back(idx[id++]);
            }
            visited[i] = 1;
            DFS_fill(i, tmp);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n;
    vector<pii> edge(n-1);
    for(int i=0; i<n-1; i++){
        int a,b; cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
        edge[i] = {a,b};
    }

    for(int i=0; i<n; i++){
        cin >> tree[i].X >> tree[i].Y;
    }

    fill(visited.begin(), visited.end(), 0);
    visited[0] = 1;
    DFS(0);

    
    vector<int> idx;
    for(int i=0; i<n; i++) idx.push_back(i);
    sort(idx.begin(), idx.end());

    fill(visited.begin(), visited.end(), 0);
    visited[0] = 1;
    DFS_fill(0, idx);

    for(int i=0; i<n-1; i++){
        cout << where[edge[i].X] << " " << where[edge[i].Y] << "\n";
    }
    return 0;
}