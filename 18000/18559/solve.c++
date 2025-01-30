#include <bits/stdc++.h>
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

#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using complex_t = complex<double>;

void fft(vector<complex_t>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
    static vector<complex_t> rt(2, 1); // (^ 10% faster if double)
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        for (int i=k;i<k+k;i++) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
    vector<int> rev(n);
    for (int i=0;i<n;i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int i=0;i<n;i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2){
        for (int i = 0; i < n; i += 2 * k) for (int j=0;j<k;j++) {
            // complex_t z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
            auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];                /// exclude-line
            complex_t z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
            a[i + j + k] = a[i + j] - z;
            a[i + j] += z;
        }
    }
}

template <typename T>vector<T> conv(const vector<T>& a, const vector<T>& b) {
    if (a.empty() || b.empty()) return {};
    vector<T> res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
    vector<complex_t> in(n), out(n);
    copy(all(a), begin(in));
    for (int i=0;i<sz(b);i++) in[i].imag(b[i]);
    fft(in);
    for (complex_t& x: in) x *= x;
    for (int i=0;i<n;i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    for (int i=0;i<sz(res);i++){
        res[i] = static_cast<T>(imag(out[i]) / (4 * n) + (is_integral_v<T> ? (imag(out[i]) > 0 ? 0.5 : -0.5) : 0));
    }
    return res;
}



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
 
ll poww(ll a,ll x,ll m){
	if(x==1) return a%m;
	if(x==0) return 1;
	ll v = poww(a, x/2, m);
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

bool cmp(vector<ll> &a, vector<ll> &b){
    if(a.size() == b.size()){
        for(int i=0; i<(int)a.size(); i++){
            if(a[i] != b[i]) return a[i] < b[i];
        }
        return 0;
    }
    return a.size() < b.size();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    vector<int> prime(100001, 1);
    for(int i=2; i<=100000; i++){
        if(prime[i] == 1){
            for(int j=i; j<=100000; j+=i){
                prime[j] = i;
            }
        }
    }
    int tt; cin >> tt;
    while(tt--){
        int n; cin >> n;
        int n1 = n;
        vector<pii> prime_n;
        int ttl = 1;
        while(n1 > 1){
            int p = prime[n1];
            int cnt = 0;
            while(n1 % p == 0){
                n1 /= p;
                cnt++;
            }
            prime_n.push_back({p, cnt});
            ttl *= cnt+1;
        }
        vector<vector<ll>> POLY;
        for(int i=0; i<ttl; i++){
            int m = 1;
            int i1 = i;
            vector<int> pr;
            for(int j=0; j<(int)prime_n.size(); j++){
                int t = i1 % (prime_n[j].Y+1);
                i1 /= (prime_n[j].Y+1);
                if(t) pr.push_back(prime_n[j].X);
                while(t--) m *= prime_n[j].X;
            }
            // m, pr
            vector<int> plusG, minusG;
            int prsz = 1 << (int)(pr.size());
            for(int j=0; j<prsz; j++){
                int cnt = 0;
                int j1 = j;
                int m1 = m;
                for(int k=0; k<(int)pr.size(); k++){
                    if(j1 % 2){
                        cnt++;
                        m1 /= pr[k];
                    }
                    j1 /= 2;
                }
                if(cnt % 2 == 0) plusG.push_back(m1);
                else minusG.push_back(m1);
            }
            vector<ll> P(1, 1);
            for(int m:plusG){
                int psz = P.size();
                vector<ll> P1(psz + m, 0);
                for(int i=0; i<psz; i++){
                    P1[i] -= P[i];
                    P1[i+m] += P[i];
                }
                P = P1;
            }
            for(int m:minusG){
                int psz = P.size();
                vector<ll> P1(psz-m, 0);
                for(int i=psz-1; i>=0; i--){
                    if(P[i] == 0) continue;
                    P1[i-m] += P[i];
                    P[i-m] += P[i];
                    P[i] = 0;
                }
                P = P1;
            }
            reverse(P.begin(), P.end());
            POLY.push_back(P);
        }
        sort(POLY.begin(), POLY.end(), cmp);
        for(auto pl:POLY){
            cout << '('; 
            for(int i=0; i<(int)pl.size(); i++){
                int d = (int)pl.size() - i - 1;
                if(pl[i] == 0) continue;
                if(pl[i] > 0 and i != 0) cout << '+';
                if(pl[i] < 0 and i != 0) cout << '-';
                if(abs(pl[i]) != 1 or d == 0) cout << abs(pl[i]);
                if(d > 0) cout << 'x';
                if(d > 1) cout << '^' << d;
            }
            cout << ')';
        }
        cout << "\n";
    }
    return 0;
}