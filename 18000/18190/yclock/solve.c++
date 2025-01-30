#include <bits/stdc++.h>
#define fi first
#define se second
#define eb emplace_back
#define sz(V) ((int)(V).size())
#define allv(V) ((V).begin()),((V).end())
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pdd;
pdd topdd(pll p) { return pdd(p.fi, p.se); }
pll operator + (pll a, pll b) { return pll(a.fi+b.fi, a.se+b.se); }
pdd operator + (pdd a, pdd b) { return pdd(a.fi+b.fi, a.se+b.se); }
pll operator - (pll a, pll b) { return pll(a.fi-b.fi, a.se-b.se); }
pdd operator - (pdd a, pdd b) { return pdd(a.fi-b.fi, a.se-b.se); }
pdd operator * (pdd a, ld b) { return pdd(a.fi*b, a.se*b); }
ll operator * (pll a, pll b) { return a.fi*b.se - b.fi*a.se; }
ld operator * (pdd a, pdd b) { return a.fi*b.se - b.fi*a.se; }
ll operator / (pll a, pll b) { return a.fi*b.fi + a.se*b.se; }
ld operator / (pdd a, pdd b) { return a.fi*b.fi + a.se*b.se; }
ll ccw(pll a, pll b, pll c) { return a*b + b*c + c*a; }
bool isbet(ll a, ll b, ll c) { return a<=b&&b<=c || c<=b&&b<=a; }
bool isbet(pll a, pll b, pll c) { return isbet(a.fi, b.fi, c.fi) && isbet(a.se, b.se, c.se) && !ccw(a, b, c); }
bool isangbet(pll a, pll c, pll b) {
	return (!(a*b) && a/b >= 0) ? (!(a*c) && a/c >= 0)
		: ((a*b >= 0) ? (a*c >= 0 && b*c <= 0) : (a*c >= 0 || b*c <= 0));
}
pdd getIntersec(pll p1, pll d1, pll p2, pll d2) {
	pll n2(d2.se, -d2.fi);
	return topdd(p1) + topdd(d1) * (ld((p2-p1)/n2) / (d1/n2));
}

int detLB(const pll P[], int N, pll p) {
	if(p.fi < P[0].fi) return -1;
	if(P[N-1].fi < p.fi) return -2;
	int s = 0, e = N-2; for(int m; s <= e;) {
		m = s+e >> 1;
		if(isbet(P[m], p, P[m+1])) return 1;
		if(p.fi < P[m].fi) e = m-1;
		else if(P[m+1].fi < p.fi) s = m+1;
		else return ccw(P[m], P[m+1], p) > 0 ? 2 : 0;
	}
	exit(-1);
}
int detUB(const pll P[], int N, pll p) {
	if(p.fi < P[N-1].fi) return -1;
	if(P[0].fi < p.fi) return -2;
	int s = 0, e = N-2; for(int m; s <= e;) {
		m = s+e >> 1;
		if(isbet(P[m], p, P[m+1])) return 1;
		if(p.fi < P[m+1].fi) s = m+1;
		else if(P[m].fi < p.fi) e = m-1;
		else return ccw(P[m], P[m+1], p) > 0 ? 0 : 2;
	}
	exit(-1);
}

int detCH(const pll P[], int LBI, int MI, int UBI, pll p) {
	int lbt = detLB(P, LBI+1, p);
	if(lbt < 0 || !lbt) return 0;
	if(1 == lbt) return 1;
	int ubt = detUB(P+MI, UBI-MI+1, p);
	if(ubt < 0 || 2 == ubt) return 0;
	if(1 == ubt) return 1;
	if(isbet(P[0], p, P[UBI])) return 1;
	if(isbet(P[LBI], p, P[MI])) return 1;
	return 2;
}

int getTangent(const pll P[], int N, pll p, int up) {
	auto sgn = [&](ll c) { return c > 0 ? up : (c ? -up : 0); };
	auto f = [&](pll x, pll a, pll b, pll c) {
		return sgn((a-x)*(b-x)) <= 0
			&& sgn((b-x)*(c-x)) >= 0;
	};

	if(f(p, P[1], P[0], P[N-1])) return 0;
	int s = 0, e = N;
	for(int m; s+1 < e;) {
		m = s+e >> 1;
		if(f(p, P[m-1], P[m], P[m+1])) return m;
		if(sgn((P[s]-p)*(P[s+1]-p)) < 0) {
			if(sgn((P[m]-p)*(P[m+1]-p)) > 0) e = m;
			else if(sgn((P[m]-p)*(P[s]-p)) > 0) s = m;
			else e = m;
		} else if(sgn((P[m]-p)*(P[m+1]-p)) < 0) s = m;
		else if(sgn((P[m]-p)*(P[s]-p)) < 0) s = m;
		else e = m;
	}
	if(s && f(p, P[s-1], P[s], P[s+1])) return s;
	if(e != N && f(p, P[e-1], P[e], P[e+1])) return e;
	exit(-1);
}

void getLRMP(const pll P[], const pll RP[], int N, pll p, int &lmpi, int &rmpi) {
	lmpi = N - getTangent(RP, N, p, -1) - 1;
	rmpi = getTangent(P, N, p, 1);
}

int getInterRay(const pll P[], int N, pll p, pll x) {
	int s = 0, e = N-1; for(int m; s < e;) {
		m = s+e+1 >> 1;
		if(isangbet(P[0]-p, P[m]-p, x-p)) s = m;
		else e = m-1;
	}
	return s;
}

ll getArea(const pll P[], const ll S[], int N, int s, int e) {
	return (s <= e ? S[e] - S[s] : S[N] - S[s] + S[e]) + (P[e] * P[s]);
}

const int MAXN = 100055;
const int MAXM = 100055;

ll SA[MAXN], SB[MAXM];
pll A[MAXN], B[MAXM], RB[MAXM];

int AMI, ALBI, AUBI;
int BMI, BLBI, BUBI;
int N, M, Q;

ld solve(pll p) {
	int lmpi, rmpi;
	getLRMP(B, RB, M, p, lmpi, rmpi);
	pll lmp = B[lmpi], rmp = B[rmpi];

	ll area1 = ((rmp-p) * (lmp-p)) - getArea(B, SB, M, lmpi, rmpi);

	int lti = getInterRay(A, N, p, lmp), rti = getInterRay(A, N, p, rmp);
	ll area2 = getArea(A, SA, N, lti+1, rti) + ((A[lti+1]-p)*(A[rti]-p));

	pdd ltp = getIntersec(A[lti], A[lti+1]-A[lti], p, lmp-p)
	  , rtp = getIntersec(A[rti], A[rti+1]-A[rti], p, rmp-p);

	ld area3 = (ltp-topdd(p))*topdd(A[lti+1]-p);
	ld area4 = topdd(A[rti]-p)*(rtp-topdd(p));
    
	ld res[4] = { ld(area1), ld(area2), area3, area4 };
	sort(res, res+4);
	return ((SA[N] - SB[M]) - (((res[0] + res[1]) + res[2]) + res[3])) / 2;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> N >> M >> Q;
	for(int i = 0; i < N; i++) cin >> A[i].fi >> A[i].se;
	for(int i = 0; i < M; i++) cin >> B[i].fi >> B[i].se;
	rotate(A, min_element(A, A+N), A+N);
	rotate(B, min_element(B, B+M), B+M);
	AMI = int(max_element(A, A+N) - A);
	BMI = int(max_element(B, B+M) - B);
	A[N] = A[0]; B[M] = B[0];
	ALBI = A[AMI].fi == A[AMI-1].fi ? AMI-1 : AMI;
	AUBI = A[N].fi == A[N-1].fi ? N-1 : N;
	BLBI = B[BMI].fi == B[BMI-1].fi ? BMI-1 : BMI;
	BUBI = B[M].fi == B[M-1].fi ? M-1 : M;
	for(int i = 0; i < M; i++) RB[i] = B[i];
	reverse(RB, RB+M); RB[M] = RB[0];

	for(int i = 1; i <= N; i++) SA[i] = SA[i-1] + (A[i-1] * A[i]);
	for(int i = 1; i <= M; i++) SB[i] = SB[i-1] + (B[i-1] * B[i]);

	for(pll p; Q--;) {
		cin >> p.fi >> p.se;
		if(detCH(B, BLBI, BMI, BUBI, p)) puts("IN");
		else if(detCH(A, ALBI, AMI, AUBI, p) < 2) puts("OUT");
		else printf("%.15lf\n", double(solve(p)));
	}
	return 0;
}