#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	vector<vector<int>> v(n+2, vector<int>(n+2, -100000));
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++) cin >> v[i][j];
	}
	/*
	for(int i=0; i<n+2; i++) v[0][i] = -100000;
	for(int i=0; i<n+2; i++) v[i][0] = -100000;
	for(int i=0; i<n+2; i++) v[n+1][i] = -100000;
	for(int i=0; i<n+2; i++) v[i][n+1] = -100000;*/
	int mx = 0;
	for(int h=0; h<=100; h++){
		vector<vector<int>> visited(n+2, vector<int>(n+2, 0));
		queue<pii> q;
		int cnt = 0;
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				if(visited[i][j] == 0 and v[i][j] > h){
					visited[i][j] = 1;
					q.push({i, j});
					while(!q.empty()){
						int x = q.front().X, y = q.front().Y; q.pop();
						if(visited[x-1][y] == 0 and v[x-1][y] > h){
							visited[x-1][y] = 1; q.push({x-1,y});
						}
						if(visited[x+1][y] == 0 and v[x+1][y] > h){
							visited[x+1][y] = 1; q.push({x+1,y});
						}
						if(visited[x][y+1] == 0 and v[x][y+1] > h){
							visited[x][y+1] = 1; q.push({x,y+1});
						}
						if(visited[x][y-1] == 0 and v[x][y-1] > h){
							visited[x][y-1] = 1; q.push({x,y-1});
						}
					}
					cnt++;
				}
			}
		}
		if(mx < cnt) mx = cnt;
	}
	cout << mx << "\n";
    return 0;
}