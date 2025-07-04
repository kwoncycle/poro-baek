#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pii pair<int, int>
#define pll pair<ll, ll>
#define X first
#define Y second
#define CNT_LOWER(v, n) (int)(lower_bound((v).begin(), (v).end(), (n)) - (v).begin())
#define CNT_UPPER(v, n) (int)(upper_bound((v).begin(), (v).end(), (n)) - (v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator+(pii l, pii r) { return {l.X + r.X, l.Y + r.Y}; };
pii operator-(pii l, pii r) { return {l.X - r.X, l.Y - r.Y}; };
ll operator*(pii l, pii r) { return (ll)l.X * r.X + (ll)l.Y * r.Y; };
ll operator/(pii l, pii r) { return (ll)l.X * r.Y - (ll)l.Y * r.X; };

ll modmul(ll a, ll b, ll M)
{
    // return (__int128)a*b%M;
    ll ret = a * b - M * ll(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ll modpow(ll b, ll e, ll mod)
{
    ll ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2)
        if (e & 1)
            ans = modmul(ans, b, mod);
    return ans;
}

bool is_prime(ll n)
{ // millar rabin
    if (n < 2 || n % 6 % 4 != 1)
        return (n | 1) == 3;
    ll A[] = {2, 3, 5, 7, 11, 13, 17, 19, 23},
       s = __builtin_ctzll(n - 1), d = n >> s;
    for (ll a : A)
    { // ^ count trailing zeroes
        ll p = modpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = modmul(p, p, n);
        if (p != n - 1 && i != s)
            return 0;
    }
    return 1;
}

ll Pollard_Rho(ll n)
{
    ll x = rand() % (n - 2) + 2;
    ll y = x;
    ll c = rand() % (n - 1) + 1;
    while (1)
    {
        x = (modmul(x, x, n) + c) % n;
        y = (modmul(y, y, n) + c) % n;
        y = (modmul(y, y, n) + c) % n;
        ll d = __gcd(abs(y - x), n);
        if (d == 1)
            continue;
        if (is_prime(d))
            return d;
        else
            return Pollard_Rho(d);
    }
}

void getFactor(ll n, vector<ll> &v)
{
    while (!(n & 1))
    {
        n >>= 1;
        v.push_back(2);
    }
    while (n != 1 && !is_prime(n))
    {
        ll d = Pollard_Rho(n);
        while (n % d == 0)
        {
            n /= d;
            v.push_back(d);
        }
    }
    if (n != 1)
        v.push_back(n);
    sort(v.begin(), v.end());
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    ll a, n; cin >> a >> n;
    if(a == 1){
        cout << "-1\n"; return 0;
    }
    vector<ll> res;
    getFactor(a, res);

    vector<pll> v;
    int n1 = res.size();
    for(int i=0; i<n1; i++){
        int i1 = i;
        while(i1 < n1 and res[i1] == res[i]){
            i1++;
        }
        v.push_back({res[i], i1-i});
        i = i1-1;
    }

    n1 = v.size();
    for(int i=n1-1; i>=0; i--){
        __int128 ans = 1;
        for(int j=0; j<i; j++){
            for(int k=0; k<v[j].Y and ans <= n; k++){
                ans *= v[j].X;
            }
        }
        for(int j=i; j<=i; j++){
            for(int k=0; k<v[j].Y+1 and ans <= n; k++){
                ans *= v[j].X;
            }
        }
        for(int j=i+1; j<n1; j++){
            for(int k=0; k<1 and ans <= n; k++){
                ans *= v[j].X;
            }
        }
        if(ans <= n){
            cout << (long long)ans << "\n"; return 0;
        }
    }
    cout << "-1\n";
    return 0;
}