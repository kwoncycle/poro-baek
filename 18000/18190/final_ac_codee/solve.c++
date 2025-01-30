#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<ll, ll>
#define pll pair<ll, ll>
#define X first
#define Y second
#define CNT_LOWER(v, n) (ll)(lower_bound((v).begin(), (v).end(), (n)) - (v).begin())
#define CNT_UPPER(v, n) (ll)(upper_bound((v).begin(), (v).end(), (n)) - (v).begin())
#define pff pair<frac, frac>
#define pdd pair<long double, long double>
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator+(pii l, pii r) { return {l.X + r.X, l.Y + r.Y}; };
pii operator-(pii l, pii r) { return {l.X - r.X, l.Y - r.Y}; };
ll operator*(pii l, pii r) { return (ll)l.X * r.X + (ll)l.Y * r.Y; };
ll operator/(pii l, pii r) { return (ll)l.X * r.Y - (ll)l.Y * r.X; };
ll ccw(pii a, pii b, pii c) { return (b - a) / (c - a); }

struct frac
{
    __int128 first, second;
    frac()
    {
        X = 0;
        Y = 0;
    }
    frac(__int128 x1, __int128 y1)
    {
        X = x1, Y = y1;
        __int128 gd = __gcd(X, Y);
        X /= gd;
        Y /= gd;
    }
    frac operator+(const frac r)
    {
        __int128 gd = __gcd(Y, r.Y);
        return frac((__int128)X * (r.Y / gd) + (__int128)(Y / gd) * r.X, (__int128)Y * (r.Y / gd));
    }

    frac operator-(const frac r)
    {
        __int128 gd = __gcd(Y, r.Y);
        return frac((__int128)X * (r.Y / gd) - (__int128)(Y / gd) * r.X, (__int128)(Y / gd) * r.Y);
    }

    frac operator*(const frac r)
    {
        return frac((__int128)X * r.X, (__int128)Y * r.Y);
    }

    frac operator*(const __int128 d)
    {
        return frac((__int128)X * d, (__int128)Y);
    }

    frac operator/(const __int128 d)
    {
        return frac((__int128)X, (__int128)Y * d);
    }
};

frac operator/(pff l, pff r)
{
    return (l.X * r.Y) - (l.Y * r.X);
}



pii lr(pii p, vector<pii> &v){
    ll nv = v.size(), i1 = 0;
    pii ans;
    if((v[i1]-p)/(v[(i1+1)%nv]-v[i1]) == 0) i1 = (i1+1) % nv;
    if((v[i1]-p)/(v[(i1+1)%nv]-v[i1]) > 0){
        for(ll T = (1<<20); T >= 1; T >>= 1){
            if(T >= nv) continue;
            ll id = (i1 + T) % nv;
            if((v[id]-p) / (v[(id+1)%nv]-v[id]) >= 0 and (v[i1] - p) / (v[id] - p) >= 0) i1 = id;
        }
        i1 = (i1 + 1) % nv;
        ans.X = i1;
        if((v[i1]-p)/(v[(i1+1)%nv]-v[i1]) == 0) i1 = (i1+1) % nv;
        for(ll T = (1<<16); T >= 1; T >>= 1){
            if(T >= nv) continue;
            ll id = (i1 + T) % nv;
            if((v[id]-p) / (v[(id+1)%nv]-v[id]) < 0 and (v[i1] - p) / (v[id] - p) < 0) i1 = id;
        }
        i1 = (i1 + 1) % nv;
        ans.Y = i1;
        return ans;
    }
    else{
        for(ll T = (1<<20); T >= 1; T >>= 1){
            if(T >= nv) continue;
            ll id = (i1 + T) % nv;
            if((v[id]-p) / (v[(id+1)%nv]-v[id]) < 0 and (v[i1] - p) / (v[id] - p) < 0) i1 = id;
        }
        i1 = (i1 + 1) % nv;
        ans.Y = i1;
        if((v[i1]-p)/(v[(i1+1)%nv]-v[i1]) == 0) i1 = (i1+1) % nv;
        for(ll T = (1<<16); T >= 1; T >>= 1){
            if(T >= nv) continue;
            ll id = (i1 + T) % nv;
            if((v[id]-p) / (v[(id+1)%nv]-v[id]) >= 0 and (v[i1] - p) / (v[id] - p) >= 0) i1 = id;
        }
        i1 = (i1 + 1) % nv;
        ans.X = i1;
        return ans;
    }
}

ll n, m;
vector<pii> polyA, polyB;

pff cross_point(LINE l1, LINE l2)
{
    l1[1] = l1[1] - l1[0];
    l2[1] = l2[1] - l2[0];
    __int128 k1 = (l2[0] - l1[0]) / l2[1], k2 = (l1[1] / l2[1]);
    if (k2 < 0)
        k1 *= -1, k2 *= -1;
    assert(0 <= k1 and k1 <= k2);
    return {frac(l1[0].X * k2 + l1[1].X * k1, k2), frac(l1[0].Y * k2 + l1[1].Y * k1, k2)};
}

bool cross(LINE l1, LINE l2)
{
    if (l1[1] / l2[1])
    {
        ll k1 = (l2[0] - l1[0]) / l2[1], k2 = (l1[1] / l2[1]);
        ll t1 = (l1[0] - l2[0]) / l1[1], t2 = (l2[1] / l1[1]);
        if (k2 < 0)
            k1 *= -1, k2 = t2;
        else
            t1 *= -1, t2 = k2;
        return (0 <= k1 and k1 <= k2 and 0 <= t1 and t1 <= t2);
    }
    else
    {
        if ((l2[0] - l1[0]) / l1[1] or (l2[0] - l1[0]) / l2[1])
            return false;
        return !(max(l1[0], l1[0] + l1[1]) < min(l2[0], l2[0] + l2[1]) or max(l2[0], l2[0] + l2[1]) < min(l1[0], l1[0] + l1[1]));
    }
}

bool isin_A(pii p, vector<pii> &v)
{ // strictly in
    if ((v[1] - v[0]) / (p - v[0]) <= 0)
        return false;
    if ((v.back() - v[0]) / (p - v[0]) >= 0)
        return false;

    ll st = 1, ed = v.size() - 1;
    while (st + 1 < ed)
    {
        ll md = (st + ed) >> 1;
        if ((v[md] - v[0]) / (p - v[0]) <= 0)
            ed = md;
        else
            st = md;
    }

    return !cross({v[st], v[ed] - v[st]}, {v[0], p - v[0]});
}

bool isin_B(pii p, vector<pii> &v)
{ // weakly in
    if ((v[1] - v[0]) / (p - v[0]) < 0)
        return false;
    if ((v.back() - v[0]) / (p - v[0]) > 0)
        return false;
    if ((v.back() - v[0]) / (p - v[0]) == 0)
    {
        if (cross({v[0], v.back() - v[0]}, {p, p - p}))
            return true;
        else
            return false;
    }

    ll st = 1, ed = v.size() - 1;
    while (st + 1 < ed)
    {
        ll md = (st + ed) >> 1;
        if ((v[md] - v[0]) / (p - v[0]) < 0)
            ed = md;
        else
            st = md;
    }
    if (cross({v[st], v[ed] - v[st]}, {v[0], p - v[0]}))
    {
        if (cross({v[st], v[ed] - v[st]}, {p, p - p}))
            return true;
        else
            return false;
    }
    return true;
}

ll crossA(pii p, pii u, vector<pii> &v)
{
    ll i1 = 0;
    ll nv = v.size();
    for (ll T = (1 << 16); T >= 1; T >>= 1)
    {
        if ((u - p) / (v[i1] - p) == 0)
        {
            if ((u - p) * (v[i1] - p) > 0)
                return i1;
            else
                i1 = (i1 + 1) % nv;
        }
        ll id = (i1 + T) % nv;
        if ((u - p) / (v[id] - p) > 0)
        {
            if ((u - p) / (v[i1] - p) > 0)
            {
                if ((v[i1] - p) / (v[id] - p) > 0)
                    i1 = id;
            }
            else
            {
                continue;
            }
        }
        else
        {
            if ((u - p) / (v[i1] - p) > 0)
            {
                i1 = id;
            }
            else
            {
                if ((v[i1] - p) / (v[id] - p) > 0)
                    i1 = id;
            }
        }
    }
    return i1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll qq;
    cin >> n >> m >> qq;
    polyA.resize(n), polyB.resize(m);
    for (ll i = 0; i < n; i++)
        cin >> polyA[i].X >> polyA[i].Y;
    for (ll i = 0; i < m; i++)
        cin >> polyB[i].X >> polyB[i].Y;
    // everything * 2
    ll area_B = 0;
    for (ll i = 0; i < m; i++)
    {
        area_B += polyB[i] / polyB[(i + 1) % m];
    }
    vector<ll> A_pre(n), A_suf(n), B_pre(m), B_suf(m);
    A_pre[0] = polyA[0] / polyA[1];
    for (ll i = 1; i < n; i++)
    {
        A_pre[i] = A_pre[i - 1] + polyA[i] / polyA[(i + 1) % n];
    }

    A_suf[n - 1] = polyA[n - 1] / polyA[0];
    for (ll i = n - 2; i >= 0; i--)
    {
        A_suf[i] = A_suf[i + 1] + polyA[i] / polyA[(i + 1) % n];
    }

    B_pre[0] = polyB[0] / polyB[1];
    for (ll i = 1; i < m; i++)
    {
        B_pre[i] = B_pre[i - 1] + polyB[i] / polyB[(i + 1) % m];
    }

    B_suf[m - 1] = polyB[m - 1] / polyB[0];
    for (ll i = m - 2; i >= 0; i--)
    {
        B_suf[i] = B_suf[i + 1] + polyB[i] / polyB[(i + 1) % m];
    }

    while (qq--)
    {
        pii p;
        cin >> p.X >> p.Y;
        bool a = isin_A(p, polyA), b = isin_B(p, polyB);
        if (!a)
        {
            cout << "OUT\n";
            continue;
        }
        if (b)
        {
            cout << "IN\n";
            continue;
        }
        auto [li, ri] = lr(p, polyB);
        ll la = crossA(p, polyB[li], polyA), ra = crossA(p, polyB[ri], polyA);
        pff pl = cross_point({polyA[la], polyA[(la + 1) % n]}, {p, polyB[li]}), pr = cross_point({polyA[ra], polyA[(ra + 1) % n]}, {p, polyB[ri]});
        pff p1 = {{p.X, 1}, {p.Y, 1}};
        pii plb = polyB[li];
        pii prb = polyB[ri];

        ll area_minus = p / prb + plb / p;
        if (true)
        {
            if (li > ri)
            {
                area_minus -= B_suf[li];
                if (ri - 1 >= 0)
                    area_minus -= B_pre[ri - 1];
            }
            else
            {
                if (li - 1 >= 0)
                    area_minus += B_pre[li - 1];
                if (ri - 1 >= 0)
                    area_minus -= B_pre[ri - 1];
            }
        }

        if (la == ra)
        {
            frac area = p1 / pr + pr / pl + pl / p1;
            area = area - frac(area_B + area_minus, 1);
            area = area / 2;
            cout << fixed << setprecision(10) << (long double)area.X / (long double)area.Y << "\n";
        }
        else if ((ra + 1) % n == la)
        {
            pff pc1 = {{polyA[la].X, 1}, {polyA[la].Y, 1}};

            frac area = p1 / pr + pr / pc1 + pc1 / pl + pl / p1;
            area = area - frac(area_B + area_minus, 1);
            area = area / 2;
            cout << fixed << setprecision(10) << (long double)area.X / (long double)area.Y << "\n";
        }
        else
        {

            ll areall = 0;
            if ((ra + 1) % n <= la)
            {
                if (la - 1 >= 0)
                    areall += A_pre[la - 1];
                if (ra != n - 1)
                    areall -= A_pre[ra];
            }
            else
            {
                areall = A_suf[(ra + 1) % n];
                if (la - 1 >= 0)
                    areall += A_pre[la - 1];
            }
            pff pcl1 = {{polyA[la].X, 1}, {polyA[la].Y, 1}}, pcr1 = {{polyA[(ra + 1) % n].X, 1}, {polyA[(ra + 1) % n].Y, 1}};
            frac area = pcl1 / pl + pl / p1 + p1 / pr + pr / pcr1;
            area = area + frac(areall - area_B - area_minus, 1);
            area = area / 2;
            cout << fixed << setprecision(10) << (long double)area.X / (long double)area.Y << "\n";
        }
    }

    return 0;
}