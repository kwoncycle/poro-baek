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
	ll n; cin >> n;
	vector<ll> v(n), inv(n);
	ll ans = 0;
	for(ll i=0; i<n; i++){
		cin >> v[i]; v[i]--;
		inv[v[i]] = i;
	}
	vector<ll> front(n, -1), back(n, -1);
	set<ll> s;
	for(ll i=0; i<n; i++){
		if(i == 0){
			ans = (inv[i]+1)*(n-inv[i]);
			s.insert(inv[i]);
			front[inv[i]] = -2; back[inv[i]] = -3;
			cout << ans << "\n";
		}
		else{
			ll r = inv[i];
			if(*s.begin() > r){
				ll frn = *s.begin();
				front[frn] = r;
				front[r] = -2;
				back[r] = frn;
				ll frn1 = n;
				if(back[frn] != -3) frn1 = back[frn];
				if(frn1 == n){
					ans += (r+1)*(n - r);
				}
				else{
					if(v[frn1] > v[frn]) ans += (r+1)*(n - r);
					else{
						ans += (r+1)*(frn1 - r);
					}
				}
				cout << ans << "\n";
			}
			
			else if(*s.rbegin() < r){
				ll bck = *s.rbegin();
				front[r] = bck;
				back[r] = -3;
				back[bck] = r;
				ll bck1 = -1;
				if(front[bck] != -2) bck1 = front[bck];
				if(bck1 == -1){
					ans += (r+1)*(n - r);
				}
				else{
					if(v[bck1] > v[bck]) ans += (r+1)*(n - r);
					else{
						ans += (r - bck1)*(n-r);
					}
				}
				cout << ans << "\n";
			}

			else{
				ll frn = *s.upper_bound(r);
				ll bck = front[frn];
				ll frn1 = back[frn];
				if(frn1 == -3) frn1 = n;
				ll bck1 = front[bck];
				if(bck1 == -2) bck1 = -1;
				//cout << bck1 << " " << bck << " " << frn << " " << frn1 << "\n"; 
				front[frn] = r; back[bck] = r;
				front[r] = bck; back[r] = frn;

				// 2 3, 2, 3, -
				ans += (r - bck1)*(frn1 - r);
				// 1 2
				if(bck1 == -1) int asdf = 1;
				else{
					if(v[bck1] > v[bck]) ans += (bck1 + 1)*(frn - r);
				}

				// 3 4
				if(frn1 == -1) int asdf = 1;
				else{
					if(v[frn1] > v[frn]) ans += (r - bck)*(n - frn1);
				}

				// 1 2 3
				if(bck1 == -1) int asdf = 1;//ans += (bck1 + 1)*(frn1 - frn);
				else{
					vector<ll> v1, v2;
					v1.push_back(v[bck1]);
					v1.push_back(v[bck]);
					v1.push_back(v[frn]);
					v2.push_back(v[bck1]);
					v2.push_back(v[bck]);
					v2.push_back(v[r]);
					v2.push_back(v[frn]);
					//for(ll i:v2) cout << i << " ";
					//cout << "HI\n";
					ll cnt1 = 2, cnt2 = 2;
					if((v1[0] > v1[1]) == (v1[1] < v1[2])) cnt1++;
					if((v2[0] > v2[1]) == (v2[1] < v2[2])) cnt2++;
					if((v2[1] > v2[2]) == (v2[2] < v2[3])) cnt2++;
					ans += (cnt2 - cnt1) * (bck1 + 1)*(frn1 - frn);
				}

				// 2 3 4
				if(frn1 == n) int asdf = 1;//ans += (bck - bck1)*(n - frn1);
				else{
					vector<ll> v1, v2;
					v1.push_back(v[bck]);
					v1.push_back(v[frn]);
					v1.push_back(v[frn1]);
					v2.push_back(v[bck]);
					v2.push_back(v[r]);
					v2.push_back(v[frn]);
					v2.push_back(v[frn1]);
					ll cnt1 = 2, cnt2 = 2;
					if((v1[0] > v1[1]) == (v1[1] < v1[2])) cnt1++;
					if((v2[0] > v2[1]) == (v2[1] < v2[2])) cnt2++;
					if((v2[1] > v2[2]) == (v2[2] < v2[3])) cnt2++;
					ans += (cnt2 - cnt1) * (bck - bck1)*(n - frn1);
				}

				// 1 2 3 4
				vector<ll> v1, v2;
				if(bck1 == -1 or frn1 == n) int asdf = 1;
				else{
					v1.push_back(v[bck1]);
					v2.push_back(v[bck1]);
					v1.push_back(v[bck]);
					v2.push_back(v[bck]);
					v2.push_back(v[r]);
					v1.push_back(v[frn]);
					v2.push_back(v[frn]);
					v1.push_back(v[frn1]);
					v2.push_back(v[frn1]);
					ll cnt1 = 2, cnt2 = 2;
					for(int i=0; i<(int)v1.size() - 2; i++){
						if((v1[i] > v1[i+1]) == (v1[i+1] < v1[i+2])) cnt1++;
					}
					for(int i=0; i<(int)v2.size() - 2; i++){
						if((v2[i] > v2[i+1]) == (v2[i+1] < v2[i+2])) cnt2++;
					}
					//cout << cnt2 << " X " << cnt1 << "\n"; 
					ans += (cnt2 - cnt1) * (bck1 + 1) * (n - frn1);
				}
				//if(t1) ans += (n-r)*(bck+1);
				//if(t2) ans += (r+1)*(n-frn);
				cout << ans << "\n";
			}
			s.insert(r);
		}
	}
    return 0;
}