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

void make_segtree(int node, int start, int end, vector<vector<int>> &segtree, vector<int> &arr){
	if(start==end){
		segtree[node].push_back(arr[start]);
		return;
	}
	int mid = (start+end)/2;
	make_segtree(node*2, start, mid, segtree, arr);
	make_segtree(node*2+1, mid+1, end, segtree, arr);
	int s1 = segtree[node*2].size(), i1 = 0;
	int s2 = segtree[node*2 + 1].size(), i2 = 0;
	while(true){
		if(i1>=s1 and i2>=s2) break;
		else if(i1>=s1 and i2<s2){
			while(i2<s2){
				segtree[node].push_back(segtree[node*2 + 1][i2]); i2++;
			}
		}
		else if(i1<s1 and i2>=s2){
			while(i1<s1){
				segtree[node].push_back(segtree[node*2][i1]); i1++;
			}
		}
		else{
			if(segtree[node*2][i1]>segtree[node*2+1][i2]) segtree[node].push_back(segtree[node*2+1][i2++]);
			else segtree[node].push_back(segtree[node*2][i1++]);
		}
	}
	return;
}

int query(int node, int start, int end, int l, int r, int val, vector<vector<int>> &segtree, vector<int> &arr){
	if(r<start or end<l) return 0;
	if(l<=start and end<=r){
		return (int)segtree[node].size() - CNT_UPPER(segtree[node],val);
	}
	int mid = (start+end)/2;
	return query(node*2, start, mid, l, r, val, segtree, arr) + query(node*2+1, mid+1, end, l, r, val, segtree, arr);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int k; cin >> k;
    vector<int> v(k);
    for(int i=0; i<k; i++) cin >> v[i];

    vector<vector<int>> mergesort_tree(4*k);
    make_segtree(1, 0, k-1, mergesort_tree, v);
    vector<int> mx(k);
    mx[0] = v[0];
    for(int i=1; i<k; i++){
        mx[i] = max(mx[i-1], v[i]);
    }
    pii ans = {-1, -1};
    for(int i=1; i<=k-3; i++){
        int t = mx[i-1];
        int q = k-1-i - query(1, 0, k-1, i+1, k-1, t, mergesort_tree, v);
        if(v[i]*2 <= q){
            ans = max(ans, pii(t, v[i]));
        }
        //if(t <= q)
    }
    if(ans.X == -1) cout << "-1\n";
    else cout << ans.X << " " << ans.Y << "\n";
    return 0;
}