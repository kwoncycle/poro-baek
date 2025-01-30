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

vector<int> arr[5], segtree[5];
/*
void make_segtree(int node, int start, int end, int target){
	if(start==end){
		segtree[target][node] = arr[target][start];
		return;
	}
	int mid = (start+end)/2;
	make_segtree(node*2, start, mid, target);
	make_segtree(node*2+1, mid+1, end, target);
	segtree[target][node] = segtree[target][node*2] + segtree[target][node*2 + 1];
	return;
}
 
void update(int node, int start, int end, int x, int val,int target){
	if(x<start or end<x) return;
	if(start == end){
		segtree[target][node] = val; return;
	}
	int mid = (start+end)/2;
	update(2*node,start,mid,x,val,target);
	update(2*node+1,mid+1,end,x,val,target);
	segtree[target][node] = segtree[target][node*2] + segtree[target][node*2+1];
}
 
int query(int node, int start, int end, int l, int r, int target){
	if(l > r) return 0;
	if(r<start or end<l) return 0;
	if(l<=start and end<=r) return segtree[target][node];
	int mid = (start+end)/2;
	return query(node*2, start, mid, l, r, target) + query(node*2+1, mid+1, end, l, r, target);
}
*/
void update(int x,int a,int t)
{
	for(;x<segtree[t].size();x+=x&-x) segtree[t][x]+=a;
}
int query(int x,int t)
{
	int a=0;
	for(;x>0;x-=x&-x) a+=segtree[t][x];
	return a;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	vector<pll> v(n);
	for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
	sort(v.begin(), v.end());

	set<ll> s1, s2;

	for(int i=0; i<n; i++){
		s1.insert(v[i].X + v[i].Y);
		s2.insert(v[i].X - v[i].Y);
	}

	vector<pli> v1, v2;
	int cnt = 0;
	for(ll i:s1) {
		v1.push_back({i,cnt}); cnt++;
	}
	cnt = 0;
	for(ll i:s2) {
		v2.push_back({i,cnt}); cnt++;
	}

	vector<pii> DOT(n);
	for(int i=0; i<n; i++){
		pli p1 = {v[i].X + v[i].Y, -1};
		DOT[i].X = CNT_LOWER(v1, p1);
		p1 = {v[i].X - v[i].Y, -1};
		DOT[i].Y = CNT_LOWER(v2, p1);
		//cout << DOT[i].X << " " << DOT[i].Y << "\n";
	}

	int n1 = v1.size(), n2 = v2.size();
	arr[1] = vector<int>(n+3, 0);
	segtree[1] = vector<int>(n+5, 0);
	arr[2] = vector<int>(n+3, 0);
	segtree[2] = vector<int>(n+5, 0);
	arr[3] = vector<int>(n+3, 0);
	segtree[3] = vector<int>(n+5, 0);
	arr[4] = vector<int>(n+3, 0);
	segtree[4] = vector<int>(n+5, 0);
	for(int i=0; i<n; i++){
		arr[3][DOT[i].X]++; arr[4][DOT[i].Y]++; 
		update(DOT[i].X+1,1,3);
		update(DOT[i].Y+1,1,4);
	}
	ll ans1 = 0, ans2 = 0;
	for(int i=0; i<n; i++){
		arr[3][DOT[i].X]--;
		update(DOT[i].X+1, -1, 3);
		arr[4][DOT[i].Y]--;
		update(DOT[i].Y+1, -1, 4);


		int sm3 = query(n1,3)-query(DOT[i].X+1,3);
		int sm4 = query(n2,4)-query(DOT[i].Y+1,4);
		int right = sm3 + sm4 - (n-i-1);

		int sm1 = query(DOT[i].X,1);
		int sm2 = query(DOT[i].Y,2);
		int left = sm1 + sm2 - i;
		ans1 += (ll)left * (ll)right;

		int smX3 = sm3 + arr[3][DOT[i].X];  //query(1,0,n1-1,DOT[i].X,n1-1,3);
		int smX4 = sm4 + arr[4][DOT[i].Y];//query(1,0,n2-1,DOT[i].Y,n2-1,4);
		int smX1 = sm1 + arr[1][DOT[i].X];//query(1,0,n1-1,0,DOT[i].X,1);
		int smX2 = sm2 + arr[2][DOT[i].Y];//query(1,0,n2-1,0,DOT[i].Y,2);

		ans2 += (ll)(n-1-smX3-smX2) * (ll)(n-1-smX1-smX4);
		//cout << v[i].X << " " << v[i].Y << " " << left << " " << right << "\n";
		arr[1][DOT[i].X]++;
		update(DOT[i].X+1, 1, 1);
		arr[2][DOT[i].Y]++;
		update(DOT[i].Y+1, 1, 2);
	}

	cout << (ll)n*(ll)(n-1)*(ll)(n-2)/(ll)6 - ans1 - ans2 << "\n";
    return 0;
}