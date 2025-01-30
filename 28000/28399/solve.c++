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
	int n, m, k; cin >> n >> m >> k;
	vector<vector<pil>> GRAPH(n);
	vector<int> path1(n, -1), path2(n, -1);
	for(int i=0; i<m; i++){
		int u, v; ll w;
		cin >> u >> v >> w;
		u--; v--;
		GRAPH[u].push_back({v, w});
	}
	for(int i=0; i<k; i++){
		int s,  p; cin >> s;
		vector<int> tmp(s);
		for(int j=0; j<s; j++){
			cin >> tmp[j]; tmp[j]--;
		}
		for(int j=0; j<s-1; j++) {
			path1[tmp[j]] = tmp[j+1];
			path2[tmp[j+1]] = tmp[j];
		}
	}
	priority_queue<pil, vector<pil>, greater<pil>> pq;
	vector<ll> value(2*n, 1ll << 62);
	if(path1[0] != -1 and path2[0] == -1) {
		pq.push({0, n});
		value[n] = 0;
	}
	else{ 
		pq.push({0, 0});
		value[0] = 0;
	}
	while(!pq.empty()){
		pil target = pq.top(); pq.pop();
		int e = target.Y;
		if(value[e] < target.X) continue;
		//cout << target.X << " " << e << "\n";
		//cout << GRAPH[e % n].size() << "\n";
		for(pil next : GRAPH[e % n]){
			//cout << e << " " << next.X << "\n";
			if(e < n){
				int no = next.X;
				if(path1[next.X] != -1 and path2[next.X] == -1){
					no = next.X + n;
				}
				if(next.Y + value[e] < value[no]){
					value[no] = next.Y + value[e];
					pq.push({value[no], no});
				}
			}// X: point, Y: value
			else{
				int no = next.X;
				if(path1[next.X] != -1 and path2[next.X] == -1){
					no = next.X + n;
				}
				if(path1[e % n] == next.X){
					if(path1[next.X] == -1){
						continue;
					}
					if(next.Y + value[e] < value[next.X + n]){
						value[next.X + n] = next.Y + value[e];
						pq.push({value[next.X + n], next.X + n});
					}
				}
				else{
					if(next.Y + value[e] < value[no]){
						value[no] = next.Y + value[e];
						pq.push({value[no], no});
					}	
				}
			}
		}
	}
	for(int i=0; i<n; i++){
		ll ans = min(value[i], value[i+n]);
		if(ans == 1ll << 62) ans = -1;
		cout << ans << " ";
	}
	cout << "\n";
    return 0;
}