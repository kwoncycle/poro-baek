#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

struct vec{
	ll x, y;
	vec() {}
	vec(ll x, ll y) : x(x), y(y) {}
	vec operator + (vec v) { return vec(x + v.x, y + v.y); }
	vec operator - (vec v) { return vec(x - v.x, y - v.y); }
	bool operator < (vec v) { return x == v.x? y < v.y : x < v.x; }
	ll operator * (vec v) { return x * v.y - y * v.x; }
};

struct poly{
	vec P[101010];
	ll A[101010], X[101010];
	ll n, m;
	
	void read()
	{
		ll i;
		
		for(i = 0; i < n; i ++){
			scanf("%lld%lld", &P[i].x, &P[i].y);
		}
		
		rotate(P, min_element(P, P + n), P + n);
		m = max_element(P, P + n) - P;
		P[n] = P[0];
		
		for(i = 1; i <= n; i ++){
			A[i] = A[i - 1] + P[i - 1] * P[i];
			X[i] = i;
		}
	}
	
	ll inside(vec p)
	{
		if(p < P[0] || P[m] < p) return 0;
		
		ll l = lower_bound(P, P + m, p) - P;
		ll u = lower_bound(P + m, P + n, p, [&](vec va, vec vb){
			return vb < va;
		}) - P;
		
		l = (P[l - 1] - p) * (P[l] - p);
		u = (P[u - 1] - p) * (P[u] - p);
		
		if(l > 0 && u > 0) return 2;
		else if(!l || !u) return 1;
		else return 0;
	}
	
	ll tangent(vec p, vec &vl, vec &vr)
	{
		vec v = P[0] - p;
		bool f = 0;
		
		f = (P[1] - P[0]) * v < 0 || v * (P[n - 1] - P[0]) < 0;
		if(f) v = p - P[0];
		
		ll k = lower_bound(P + 1, P + n, v, [&](vec va, vec vb){
			return (va - P[0]) * vb > 0;
		}) - P;
		
		auto cmp = [&](ll a, vec vb){
			ll t = (P[a] - vb) * (P[a + 1] - P[a]);
			return f? t > 0 : t < 0;
		};
				
		ll r = lower_bound(X, X + k, p, cmp) - X; f = !f;
		ll l = lower_bound(X + k, X + n, p, cmp) - X;
		if(!f) swap(l, r);
		
		vl = P[l] - p; vr = P[r] - p;
		
		return (l < r? A[n] : 0) - p * P[l] - P[r] * p - A[r] + A[l];
	}
	
	ld getcross(vec p, vec v)
	{
		ll k = lower_bound(P + 1, P + n, v, [&](vec va, vec vb){
			if((P[0] - p) * (va - p) > 0){
				return (P[0] - p) * vb <= 0 || vb * (va - p) <= 0;
			}
			else{
				return (va - p) * vb >= 0 && vb * (P[0] - p) >= 0;
			}
		}) - P;
		
		vec a = v, b = P[k] - P[k - 1], c = P[k] - p;
		
		return p * (p + v) * (ld)(c * b) / (a * b) - A[k]
			+ P[k - 1] * P[k] * (ld)(a * c) / (a * b);
	}
	
	ld getarea(vec p, vec vl, vec vr)
	{
		ld s = getcross(p, vr) - getcross(p, vl);
		return s < 0? s + A[n] : s;
	}
};

poly A, B;

int main()
{
	vec p, vl, vr;
	ll q;
	ld ans;
	
	scanf("%lld%lld%lld", &A.n, &B.n, &q);
	
	A.read(); B.read();
	
	for(; q --; ){
		scanf("%lld%lld", &p.x, &p.y);
		if(A.inside(p) < 2) printf("OUT\n");
		else if(B.inside(p)) printf("IN\n");
		else{
			ans = -B.tangent(p, vl, vr);
			ans += A.getarea(p, vl, vr);
			printf("%.20Lf\n", ans / 2);
		}
	}
	
	return 0;
}