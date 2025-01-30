#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define X first
#define Y second
#define GETVECTOR(n) for(int i=0; i< (n); i++) scanf("%d ",&inp[i]);
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n
typedef struct p3{
	int a; int b; int c;
}p3;
 
bool cmp3(p3 p, p3 q){
	if(p.a==q.a){
		if(p.b == q.b){
			return p.c < q.c;
		}
		return p.b < q.b;
	}
	return p.a < q.a;
}
 
void make_segtree(int node, int start, int end, vector<int> &segtree, vector<int> &arr){
	if(start==end){
		segtree[node] = arr[start];
		return;
	}
	int mid = (start+end)/2;
	make_segtree(node*2, start, mid, segtree, arr);
	make_segtree(node*2+1, mid+1, end, segtree, arr);
	segtree[node] = segtree[node*2] + segtree[node*2 + 1];
	return;
}
 
void update(int node, int start, int end, int x, int val, vector<int> &segtree, vector<int> &arr){
	if(x<start or end<x) return;
	if(start == end){
		segtree[node] = val; return;
	}
	int mid = (start+end)/2;
	update(2*node,start,mid,x,val,segtree,arr);
	update(2*node+1,mid+1,end,x,val,segtree,arr);
	segtree[node] = segtree[node*2] + segtree[node*2+1];
}
 
int query(int node, int start, int end, int l, int r, vector<int> &segtree, vector<int> &arr){
	if(r<start or end<l) return 0;
	if(l<=start and end<=r) return segtree[node];
	int mid = (start+end)/2;
	return query(node*2, start, mid, l, r, segtree, arr) + query(node*2+1, mid+1, end, l, r, segtree, arr);
}
 
class djs
{
    int n;
    vector<int> par;
 
public:
    djs(int n) : n(n) {
        par.resize(n);
        for(int i=0; i<n; i++) par[i] = i;
    }
 
    int find(int v) {
        if(par[v] == v) return v;
        else return par[v] = find(par[v]);
    }
 
    bool Union(int x, int y) {
        int px = find(x);
        int py = find(y);
 
        if(px == py) return false;
 
        par[px] = py;
        return true;
    }
};
// Usage: djs DJS(n)
 
ll pow(ll a,ll x,ll m){
	if(x==1) return a%m;
	if(x==0) return 1;
	ll v = pow(a, x/2, m);
	v = v*v%m;
	if(x%2) v = v*a%m;
	return v;
}
// a^x (mod m)
 
ll modInverse(ll A, ll M){
    ll m0 = M;
    ll y = 0, x = 1;
    if (M == 1)
        return 0;
    while (A > 1) {
        ll q = A / M;
        ll t = M;
        M = A % M, A = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += m0;
    return x;
}
 
void BFS(int r, vector<int> &visited, vector<int> &dist, vector<int> &under, vector<vector<pii>> &GRAPH){
	visited[r] = 1;
	int sm = 1;
	for(pii p: GRAPH[r]){
		if(visited[p.first]) continue;
		dist[p.first] = dist[r] + p.second;
		BFS(p.first, visited, dist, under, GRAPH);
		sm += under[p.first];
	}	
}

vector<vector<int>> G;
vector<int> tp;
vector<int> dpth;

void BFS(int x){
    for(int i: G[x]){
        if(tp[x] == i) continue;
        tp[i] = x;
        dpth[i] = dpth[x] + 1;
        BFS(i);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    G = vector<vector<int>>(n);
    for(int i=0; i<n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        G[a].push_back(b); G[b].push_back(a);
    }
    tp.resize(n, -1); dpth.resize(n, 0);
    tp[0] = 0;
    BFS(0);

    vector<vector<int>> tp_table(n, vector<int>(21));
    for(int i=0; i<n; i++){
        tp_table[i][0] = tp[i];
    }

    for(int j=1; j<21; j++){
        for(int i=0; i<n; i++){
            int k = tp_table[i][j - 1];
            tp_table[i][j] = tp_table[k][j-1];
        }
    }

    int m; cin >> m;
    while(m--){
        int x, y; cin >> x >> y; x--; y--;
        int dx = dpth[x], dy = dpth[y];
        if(dx < dy){
            int r = dx; dx = dy; dy = r;
            r = x; x = y; y = r;
        }
        int d = 1 << 20;
        for(int i=20; i>=0; i--){
            if(dx-dy >= d){
                dx -= d;
                x = tp_table[x][i];
            }
            d >>= 1;
        }
        if(x == y){
            cout << x+1 << "\n"; continue;
        }

        d = 0;
        int id = 20;
        while(tp_table[x][id] == tp_table[y][id]) id--;
        for(int i=id; i>=0; i--){
            if(tp_table[x][i] != tp_table[y][i]){
                x = tp_table[x][i];
                y = tp_table[y][i];
            }
        }
        x = tp_table[x][0];
        y = tp_table[y][0];
        cout << x+1 << "\n";
    }
    return 0;
}