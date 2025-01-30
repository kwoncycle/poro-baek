#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};


#define fi first
#define se second


ll Pow(ll a, ll b, ll m)
{
    ll res = 1;
    for (a %= m; b; b >>= 1, a = a * a % m)
        if (b & 1)
            res = res * a % m;
    return res;
}

ll DiscreteSqrt(ll A, ll P)
{
    if (A == 0)
        return 0;
    if (Pow(A, (P - 1) / 2, P) != 1)
        return -1;
    if (P % 4 == 3)
        return Pow(A, (P + 1) / 4, P);
    ll s = P - 1, n = 2, r = 0, m;
    while (~s & 1)
        r++, s >>= 1;
    while (Pow(n, (P - 1) / 2, P) != P - 1)
        n++;
    ll x = Pow(A, (s + 1) / 2, P), b = Pow(A, s, P), g = Pow(n, s, P);
    for (;; r = m)
    {
        ll t = b;
        for (m = 0; m < r && t != 1; m++)
            t = t * t % P;
        if (!m)
            return x;
        ll gs = Pow(g, 1LL << (r - m - 1), P);
        g = gs * gs % P;
        x = x * gs % P;
        b = b * g % P;
    }
}

const int MOD = 998244353;
const int w = 3;
struct mint
{
    ll x;
    mint() { x = 0; }
    mint(const ll &v)
    {
        x = (-MOD <= v && v < MOD ? v : v % MOD);
        if (x < 0)
            x += MOD;
    }

    friend mint power(mint a, ll b)
    {
        mint res(1);
        while (b)
        {
            if (b & 1)
                res = res * a;
            a = a * a;
            b >>= 1;
        }
        return res;
    }
    mint pow(ll b) const { return power(*this, b); }
    mint inv() const { return power(*this, MOD - 2); }

    mint operator-() { return mint(-x); }
    mint &operator+=(const mint &b)
    {
        if ((x += b.x) >= MOD)
            x -= MOD;
        return *this;
    }
    mint &operator-=(const mint &b)
    {
        if ((x -= b.x) < 0)
            x += MOD;
        return *this;
    }
    mint &operator*=(const mint &b)
    {
        x = (int)((ll)x * b.x % MOD);
        return *this;
    }
    mint &operator/=(const mint &b)
    {
        return (*this) *= b.inv();
    }

    friend mint operator+(mint a, const mint &b) { return a += b; }
    friend mint operator-(mint a, const mint &b) { return a -= b; }
    friend mint operator*(mint a, const mint &b) { return a *= b; }
    friend mint operator/(mint a, const mint &b) { return a /= b; }

    friend bool operator==(const mint &a, const mint &b)
    {
        return a.x == b.x;
    }
    friend bool operator!=(const mint &a, const mint &b)
    {
        return a.x != b.x;
    }

    friend istream &operator>>(istream &in, mint &a)
    {
        ll v;
        in >> v;
        a.x = (-MOD <= v && v < MOD ? v : v % MOD);
        if (a.x < 0)
            a.x += MOD;
        return in;
    }
    friend ostream &operator<<(ostream &out, const mint &a)
    {
        return out << a.x;
    }

    ll discrete_sqrt(ll a)
    {
    }

    /*experimental::optional<mint> sqrt() const
    {
        ll r = DiscreteSqrt(x, MOD);
        if (r == -1)
            return experimental::nullopt;
        else
            return r;
    }*/
};

namespace fft
{
    using real_t = double;
    using base = complex<real_t>;

    void fft(vector<base> &a, bool inv)
    {
        int n = a.size(), j = 0;
        vector<base> roots(n / 2);
        for (int i = 1; i < n; i++)
        {
            int bit = (n >> 1);
            while (j >= bit)
            {
                j -= bit;
                bit >>= 1;
            }
            j += bit;
            if (i < j)
                swap(a[i], a[j]);
        }
        real_t ang = 2 * acos(real_t(-1)) / n * (inv ? -1 : 1);
        for (int i = 0; i < n / 2; i++)
        {
            roots[i] = base(cos(ang * i), sin(ang * i));
        }
        /*
           XOR Convolution : set roots[*] = 1.
           OR Convolution : set roots[*] = 1, and do following:
           if (!inv) {
           a[j + k] = u + v;
           a[j + k + i/2] = u;
           } else {
           a[j + k] = v;
           a[j + k + i/2] = u - v;
           }
         */
        for (int i = 2; i <= n; i <<= 1)
        {
            int step = n / i;
            for (int j = 0; j < n; j += i)
            {
                for (int k = 0; k < i / 2; k++)
                {
                    base u = a[j + k], v = a[j + k + i / 2] * roots[step * k];
                    a[j + k] = u + v;
                    a[j + k + i / 2] = u - v;
                }
            }
        }
        if (inv)
            for (int i = 0; i < n; i++)
                a[i] /= n; // skip for OR convolution.
    }
    template <typename T>
    void ntt(vector<T> &a, bool inv)
    {
        const int prr = 3; // primitive root
        int n = a.size(), j = 0;
        vector<T> roots(n / 2);
        for (int i = 1; i < n; i++)
        {
            int bit = (n >> 1);
            while (j >= bit)
            {
                j -= bit;
                bit >>= 1;
            }
            j += bit;
            if (i < j)
                swap(a[i], a[j]);
        }
        T ang = power(T(prr), (MOD - 1) / n);
        if (inv)
            ang = T(1) / ang;
        for (int i = 0; i < n / 2; i++)
        {
            roots[i] = (i ? (roots[i - 1] * ang) : T(1));
        }
        for (int i = 2; i <= n; i <<= 1)
        {
            int step = n / i;
            for (int j = 0; j < n; j += i)
            {
                for (int k = 0; k < i / 2; k++)
                {
                    T u = a[j + k], v = a[j + k + i / 2] * roots[step * k];
                    a[j + k] = u + v;
                    a[j + k + i / 2] = u - v;
                }
            }
        }
        if (inv)
        {
            T rev = T(1) / T(n);
            for (int i = 0; i < n; i++)
                a[i] *= rev;
        }
    }
    template <typename T>
    vector<T> multiply_ntt(
        vector<T> &v, const vector<T> &w)
    {
        vector<T> fv(v), fw(w);
        int n = 2;
        while (n < v.size() + w.size())
            n <<= 1;
        fv.resize(n);
        fw.resize(n);
        ntt(fv, 0);
        ntt(fw, 0);
        for (int i = 0; i < n; i++)
            fv[i] *= fw[i];
        ntt(fv, 1);
        vector<T> ret(n);
        for (int i = 0; i < n; i++)
            ret[i] = fv[i];
        return ret;
    }
    template <typename T>
    vector<T> multiply(
        vector<T> &v, const vector<T> &w)
    {
        vector<base> fv(v), fw(w);
        int n = 2;
        while (n < v.size() + w.size())
            n <<= 1;
        fv.resize(n);
        fw.resize(n);
        fft(fv, 0);
        fft(fw, 0);
        for (int i = 0; i < n; i++)
            fv[i] *= fw[i];
        fft(fv, 1);
        vector<T> ret(n);
        for (int i = 0; i < n; i++)
            ret[i] = (T)llround(fv[i].real());
        return ret;
    }
    template <typename T>
    vector<T> multiply_mod(
        vector<T> v, const vector<T> &w)
    {
        int n = 2;
        while (n < v.size() + w.size())
            n <<= 1;
        vector<base> v1(n), v2(n), r1(n), r2(n);
        for (int i = 0; i < v.size(); i++)
        {
            v1[i] = base(v[i] >> 15, v[i] & 32767);
        }
        for (int i = 0; i < w.size(); i++)
        {
            v2[i] = base(w[i] >> 15, w[i] & 32767);
        }
        fft(v1, 0);
        fft(v2, 0);
        for (int i = 0; i < n; i++)
        {
            int j = (i ? (n - i) : i);
            base ans1 = (v1[i] + conj(v1[j])) * base(0.5, 0);
            base ans2 = (v1[i] - conj(v1[j])) * base(0, -0.5);
            base ans3 = (v2[i] + conj(v2[j])) * base(0.5, 0);
            base ans4 = (v2[i] - conj(v2[j])) * base(0, -0.5);
            r1[i] = (ans1 * ans3) + (ans1 * ans4) * base(0, 1);
            r2[i] = (ans2 * ans3) + (ans2 * ans4) * base(0, 1);
        }
        fft(r1, 1);
        fft(r2, 1);
        vector<T> ret(n);
        for (int i = 0; i < n; i++)
        {
            T av = llround(r1[i].real());
            T bv = llround(r1[i].imag()) + llround(r2[i].real());
            T cv = llround(r2[i].imag());
            av = av << 30;
            bv = bv << 15;
            ret[i] = av + bv + cv;
        }
        return ret;
    }

} // namespace fft

const int maxn = 1 << 20;
template <typename T>
T fact(int n)
{
    static T F[maxn];
    static bool init = false;
    if (!init)
    {
        F[0] = T(1);
        for (int i = 1; i < maxn; i++)
        {
            F[i] = F[i - 1] * T(i);
        }
        init = true;
    }
    return F[n];
}

template <typename T>
T rfact(int n)
{
    static T F[maxn];
    static bool init = false;
    if (!init)
    {
        F[maxn - 1] = T(1) / fact<T>(maxn - 1);
        for (int i = maxn - 2; i >= 0; i--)
        {
            F[i] = F[i + 1] * T(i + 1);
        }
        init = true;
    }
    return F[n];
}
struct Poly
{
    vector<mint> v;
    Poly() {}
    Poly(mint x)
    {
        v.push_back(x);
        trim();
    }
    Poly(const vector<mint> &V)
    {
        v = V;
        trim();
    }
    Poly(const Poly &P)
    {
        v = P.v;
        trim();
    }

    bool operator==(const Poly &a) const { return v == a.v; }
    bool operator!=(const Poly &a) const { return v != a.v; }
    int deg() const { return (int)v.size() - 1; }
    bool is_zero() const { return v.size() == 0; }
    mint operator[](int i) const
    {
        return (i < 0 || i > deg()) ? mint(0) : v[i];
    }
    void trim()
    {
        while (v.size() > 0 && v.back() == mint(0))
            v.pop_back();
    }

    int lastnz() const
    {
        if (is_zero())
            return -1;
        int ret = 0;
        while (v[ret] == mint(0))
            ret++;
        return ret;
    }
    Poly reverse(int n) const
    {
        auto res = v;
        if (res.size() < n)
            res.resize(n);
        return vector<mint>(res.rbegin(), res.rbegin() + n);
    }
    Poly reverse() const { return reverse(deg() + 1); }

    Poly mod_xk(int k) const
    {
        return vector<mint>(
            v.begin(), v.begin() + min(k, (int)v.size()));
    }
    Poly div_xk(int k) const
    {
        return vector<mint>(
            v.begin() + min(k, (int)v.size()), v.end());
    }
    Poly mul_xk(int k) const
    {
        auto res = v;
        res.insert(res.begin(), k, 0);
        return res;
    }

    Poly operator-() const
    {
        Poly t = *this;
        for (auto &x : t.v)
            x = -x;
        return t;
    }
    Poly operator+=(const Poly &a)
    {
        if (v.size() < a.v.size())
            v.resize(a.v.size());
        for (int i = 0; i < a.v.size(); i++)
            v[i] += a.v[i];
        trim();
        return *this;
    }
    Poly operator-=(const Poly &a)
    {
        if (v.size() < a.v.size())
            v.resize(a.v.size());
        for (int i = 0; i < a.v.size(); i++)
            v[i] -= a.v[i];
        trim();
        return *this;
    }
    Poly operator*=(const Poly &a)
    {
        v = fft::multiply_ntt(v, a.v);
        trim();
        return *this;
    }
    Poly operator/=(const Poly &a)
    {
        return *this = div(a).fi;
    }
    Poly operator%=(const Poly &a)
    {
        return *this = div(a).se;
    }

    Poly operator+(const Poly &a) const
    {
        return Poly(*this) += a;
    }
    Poly operator-(const Poly &a) const
    {
        return Poly(*this) -= a;
    }
    Poly operator*(const Poly &a) const
    {
        return Poly(*this) *= a;
    }
    Poly operator/(const Poly &a) { return div(a).fi; }
    Poly operator%(const Poly &a) { return div(a).se; }

    Poly operator*=(const mint &x)
    {
        for (auto &a : v)
            a *= x;
        trim();
        return *this;
    }
    Poly operator/=(const mint &x)
    {
        for (auto &a : v)
            a /= x;
        trim();
        return *this;
    }
    Poly operator*(const mint &x) const
    {
        return Poly(*this) *= x;
    }
    Poly operator/(const mint &x) const
    {
        return Poly(*this) /= x;
    }

    Poly inv(int n)
    {
        Poly G(v[0].inv());
        for (int i = 1; i < n; i <<= 1)
        {
            Poly F = Poly(2) - G * mod_xk(i * 2);
            G = (F * G).mod_xk(i * 2);
        }
        return G.mod_xk(n);
    }

    pair<Poly, Poly> div(const Poly &a)
    {
        assert(!a.is_zero());
        if (deg() < a.deg())
            return {Poly(0), *this};
        int d = deg() - a.deg();
        Poly Q = (reverse().mod_xk(d + 1) * a.reverse().inv(d + 1));
        Q = Q.mod_xk(d + 1).reverse(d + 1);
        return {Q, *this - Q * a};
    }

    Poly derivative()
    {
        if (deg() < 0)
            return Poly(0);
        vector<mint> ret(deg());
        for (int i = 1; i <= deg(); i++)
            ret[i - 1] = (mint(i) * v[i]);
        return ret;
    }

    Poly integral()
    {
        vector<mint> ret(deg() + 2);
        for (int i = 0; i <= deg(); i++)
            ret[i + 1] = (v[i] / mint(i + 1));
        return ret;
    }

    Poly ln(int n)
    {
        assert(v[0] == mint(1));
        Poly Q = (derivative().mod_xk(n) * inv(n));
        return Q.integral().mod_xk(n);
    }
    Poly exp(int n)
    {
        if (is_zero())
            return mint(1);
        assert(v[0] == mint(0));
        Poly G(1);
        for (int i = 1; i < n; i <<= 1)
        {
            Poly F = mod_xk(2 * i);
            G = (G * (F + Poly(1) - G.ln(2 * i))).mod_xk(2 * i);
        }
        return G.mod_xk(n);
    }
    Poly pow(ll k, int n)
    {
        if (is_zero())
            return k ? *this : Poly(1);
        int l = lastnz();
        if (l > 0)
        {
            if (k >= (ll)(n + l - 1) / l)
                return Poly(mint(0));
            else
                return div_xk(l).pow(k, n - l * k).mul_xk(l * k);
        }
        mint j = v[l];
        Poly t = (*this) / j;
        return ((t.ln(n) * mint(k)).exp(n).mod_xk(n)) * power(j, k);
    }
    /*experimental::optional<Poly> sqrt(int n) const {
    if (is_zero()) return *this;
    int i = lastnz();
    if(i%2) return experimental::nullopt;
    else if(i>0)
    {
     auto ans=div_xk(i).sqrt(n-i/2);
     return ans ? ans->mul_xk(i/2) : ans;
    }
    auto st = (*this)[0].sqrt();
    if(st)
    {
       Poly ans=*st;
       ll a=1;
       while(a<n) {
       a*=2;
       ans-=(ans-mod_xk(a)*ans.inv(a)).mod_xk(a)/2;
       }
       return ans.mod_xk(n);
    }
    return experimental::nullopt;
   }*/
    mint eval(mint x) const
    { // evaluates in single point x
        mint res(0);
        for (int i = deg(); i >= 0; i--)
        {
            res *= x;
            res += v[i];
        }
        return res;
    }
    vector<mint> eval(vector<Poly> &tree,
                      int v, int l, int r, vector<mint> &vec)
    {
        if (r - l == 1)
        {
            return {eval(vec[l])};
        }
        else
        {
            auto m = l + (r - l) / 2;
            auto A = (*this % tree[2 * v]).eval(tree, 2 * v, l, m, vec);
            auto B = (*this % tree[2 * v + 1]).eval(tree, 2 * v + 1, m, r, vec);
            A.insert(end(A), begin(B), end(B));
            return A;
        }
    }

    vector<mint> eval(vector<mint> x)
    {
        // evaluate polynomial in (x1, ..., xn)
        int n = x.size();
        if (is_zero())
        {
            return vector<mint>(n, mint(0));
        }
        vector<Poly> tree(4 * n);
        build(tree, 1, 0, x.size(), x);
        return eval(tree, 1, 0, x.size(), x);
    }
    static Poly build(vector<Poly> &res, int v,
                      int L, int R, vector<mint> &vec)
    {
        if (R - L == 1)
        {
            return res[v] = vector<mint>{-vec[L], 1};
        }
        else
        {
            int M = L + (R - L) / 2;
            return res[v] = build(res, 2 * v, L, M, vec) * build(res, 2 * v + 1, M, R, vec);
        }
    }
    Poly inter(vector<Poly> &tree, int idx, int l, int r,
               int ly, int ry, vector<mint> &vecx, vector<mint> &vecy)
    {
        if (r - l == 1)
        {
            return {vecy[ly] / v[0]};
        }
        else
        {
            auto m = l + (r - l) / 2;
            auto my = ly + (ry - ly) / 2;
            auto A = (*this % tree[2 * idx]).inter(tree, 2 * idx, l, m, ly, my, vecx, vecy);
            auto B = (*this % tree[2 * idx + 1]).inter(tree, 2 * idx + 1, m, r, my, ry, vecx, vecy);
            return A * tree[2 * idx + 1] + B * tree[2 * idx];
        }
    }
    static Poly inter(vector<mint> x, vector<mint> y)
    {
        int n = x.size();
        vector<Poly> tree(4 * n);
        return build(tree, 1, 0, x.size(), x).derivative().inter(tree, 1, 0, x.size(), 0, y.size(), x, y);
    }
    Poly invborel() const
    { // ak *= k!
        auto res = *this;
        for (int i = 0; i <= deg(); i++)
        {
            res.v[i] *= fact<mint>(i);
        }
        return res;
    }

    Poly borel() const
    { // ak /= k!
        auto res = *this;
        for (int i = 0; i <= deg(); i++)
        {
            res.v[i] *= rfact<mint>(i);
        }
        return res;
    }
    static Poly ones(size_t n)
    { // P(x) = 1 + x + ... + x^{n-1}
        return vector<mint>(n, 1);
    }
    static Poly expx(size_t n)
    { // P(x) = e^x (mod x^n)
        return ones(n).borel();
    }
    Poly mulx(mint a) const
    {
        // component-wise multiplication with a^k
        mint cur = 1;
        Poly res(*this);
        for (int i = 0; i <= deg(); i++)
        {
            res.v[i] *= cur;
            cur *= a;
        }
        return res;
    }
    Poly shift(mint a) const
    { // P(x + a)
        if (is_zero())
            return *this;
        Poly Q = expx(deg() + 1).mulx(a).reverse() * invborel();
        return Q.div_xk(deg()).borel();
    }
};

#define pPP pair<Poly, Poly>

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    ll n, r; cin >> n >> r;
    vector<pll> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;

    vector<pPP> A;
    for(int i=0; i<n; i++){
        vector<mint> v1 = {-v[i].X, 1}, v2 = {-v[i].Y};
        Poly a1(v1), a2(v2);
        A.push_back({a1, a2});
    }

    while(A.size() > 1){
        vector<pPP> A1;
        for(int i=0; i<(int)A.size(); i+=2){
            if(i+1 < (int)A.size()){
                Poly P1 = A[i].X * A[i+1].X - A[i].Y * A[i+1].Y;
                Poly P2 = A[i].Y * A[i+1].X + A[i].X * A[i+1].Y;
                A1.push_back({P1, P2});
            }
            else A1.push_back(A[i]);
        }
        A = A1;
    }

    vector<mint> Ax = A[0].X.v, Ay = A[0].Y.v;
    while(Ax.size() < Ay.size()) Ax.push_back(0);
    while(Ay.size() < Ax.size()) Ay.push_back(0);
    mint ans = 0;
    for(int i=0; i<(int)Ax.size(); i++){
        ans += mint(r).pow(2*i) * (Ax[i]*Ax[i] + Ay[i]*Ay[i]) / mint(i+1);
    }

    cout << ans.x << "\n";

    


    return 0;
}