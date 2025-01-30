#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <memory.h>

typedef long long LL;
int readInt();


struct Point {
    LL X, Y;
    LL DistSq(const Point& r) {
        return (X - r.X) * (X - r.X) + (Y - r.Y) * (Y - r.Y);
    }
};

struct Vector {
    LL X, Y;
    Vector() : Vector(0, 0) {}
    Vector(LL _X, LL _Y) : X(_X), Y(_Y) {}
    Vector(const Point& a) : Vector(a.X, a.Y) {}
    LL Cxp(const Vector& r) const {
        return X * r.Y - Y * r.X;
    }
    Vector operator-(const Vector& r) {
        Vector v(*this);
        v.X -= r.X;
        v.Y -= r.Y;
        return v;
    }
};

Vector operator-(const Point& a, const Point& b) {
    Vector v;
    v.X = a.X - b.X;
    v.Y = a.Y - b.Y;
    return v;
};

LL Sign(LL x) {
    return ((x > 0) ? 1LL : 0) - ((x < 0) ? 1LL : 0);
}
LL CCW(Vector v1, Vector v2) {
    return Sign(v1.Cxp(v2));
}
LL CCW(Point p0, Point p1, Point p2) {
    return CCW(p1 - p0, p2 - p0);
}

struct Polygon {
    int Count;
    Point Pts[100001];
    Vector Vts[100001];
    int YArgmax, YArgmin;
    LL AreaDouble, AreaPsum[100001];

    int Sa(int i) {
        i = i % Count;
        while (i < 1) i += Count;
        return i;
    }
    Point& operator[](int i) {
        return Pts[Sa(i)];
    }
    int Px(int i) {
        return Sa(i - 1);
    }
    int Nx(int i) {
        return Sa(i + 1);
    }

    void Prep() {
        for (int i = 1; i <= Count; i++) Vts[i] = Pts[Nx(i)] - Pts[i];

        YArgmax = YArgmin = 1;
        for (int i = 1; i <= Count; i++) {
            if (Pts[i].Y > Pts[YArgmax].Y || (Pts[i].Y == Pts[YArgmax].Y && Pts[i].X > Pts[YArgmax].X)) YArgmax = i;
            if (Pts[i].Y < Pts[YArgmin].Y || (Pts[i].Y == Pts[YArgmin].Y && Pts[i].X < Pts[YArgmin].X)) YArgmin = i;
        }

        AreaPsum[0] = 0;
        for (int i = 1; i <= Count; i++) AreaPsum[i] = AreaPsum[i - 1] + Vector(Pts[i]).Cxp(Vector(Pts[Nx(i)]));
        AreaDouble = AreaPsum[Count];
    }

    LL PartialArea(int i, int j) {
        if (i == j) return 0;
        else if (i < j) return AreaPsum[j - 1] - AreaPsum[i - 1];
        else return (AreaPsum[Count] - AreaPsum[i - 1]) + AreaPsum[j - 1];
    }

    int HitTest(Point p) { /* +1: outside, 0: on boundary, -1: inside */
        if (p.Y < Pts[YArgmin].Y || p.Y > Pts[YArgmax].Y) return +1;
        if (p.Y == Pts[YArgmin].Y && p.Y == Pts[Nx(YArgmin)].Y) {
            return (Pts[YArgmin].X <= p.X && p.X <= Pts[Nx(YArgmin)].X) ? (0) : (+1);
        }
        if (p.Y == Pts[YArgmax].Y && p.Y == Pts[Nx(YArgmax)].Y) {
            return (Pts[YArgmax].X >= p.X && p.X >= Pts[Nx(YArgmax)].X) ? (0) : (+1);
        }

        auto test_chain = [&](int lo, int hi, int sign) -> LL {
            if (lo > hi) hi += Count;
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                int m = Sa(mid);

                LL d = Pts[m].Y - p.Y;
                if (d * sign >= 0) hi = mid;
                else lo = mid + 1;
            }

            int i = Sa(lo);
            return CCW(Pts[Px(i)], Pts[i], p);
        };

        LL v1 = test_chain(YArgmax + 1, YArgmin, -1);
        LL v2 = test_chain(YArgmin + 1, YArgmax, +1);
        if (!v1 || !v2) return 0;
        if (v1 == +1 && v2 == +1) return -1;
        return +1;
    }
    int GetTangentPointLt(Point p) { /* p must be outside the query polygon */
        auto is_up = [&](int i) -> bool {
            return CCW(p, Pts[Px(i)], Pts[i]) < 0;
        };
        if (!is_up(1) && is_up(2)) return 1;

        int lo = 2, hi = Count;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            LL det = CCW(p, Pts[mid], Pts[lo]);
            if (is_up(lo)) {
                if (!is_up(mid)) {
                    lo = mid;
                }
                else {
                    if (det > 0) lo = mid;
                    else hi = mid - 1;
                }
            }
            else {
                if (is_up(mid)) {
                    hi = mid - 1;
                }
                else {
                    if (det < 0 || (det == 0 && Nx(lo) == mid)) lo = mid;
                    else hi = mid - 1;
                }
            }
        }
        return lo;
    }
    int GetTangentPointRt(Point p) { /* p must be outside the query polygon */
        auto is_up = [&](int i) -> bool {
            return CCW(p, Pts[Px(i)], Pts[i]) < 0;
        };
        if (is_up(1) && !is_up(2)) return 1;

        int lo = 2, hi = Count;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            LL det = CCW(p, Pts[mid], Pts[lo]);
            if (is_up(lo)) {
                if (!is_up(mid)) {
                    hi = mid - 1;
                }
                else {
                    if (det > 0) lo = mid;
                    else hi = mid - 1;
                }
            }
            else {
                if (is_up(mid)) {
                    lo = mid;
                }
                else {
                    if (det < 0 || (det == 0 && Nx(lo) == mid)) lo = mid;
                    else hi = mid - 1;
                }
            }
        }
        return lo;
    }
};


int N, M, Q;
Polygon PN, PM;
Point PQ[100001];

void GatherInput() {
    N = PN.Count = readInt();
    M = PM.Count = readInt();
    Q = readInt();
    for (int i = 1; i <= N; i++) {
        PN[i].X = readInt();
        PN[i].Y = readInt();
    }
    for (int j = 1; j <= M; j++) {
        PM[j].X = readInt();
        PM[j].Y = readInt();
    }
    for (int k = 1; k <= Q; k++) {
        PQ[k].X = readInt();
        PQ[k].Y = readInt();
    }
}

int M_CCW[100001], M_CW[100001];

void Solve() {
    PN.Prep();
    PM.Prep();

    /* preprocess, CCW */
    for (int i = 1; i <= PN.Count; i++) {
        LL cxp_i = CCW(PM[M], PM[1], PN[i]);
        LL cxp_i1 = CCW(PM[M], PM[1], PN[PN.Nx(i)]);
        if ((cxp_i == 0 && PN[i].DistSq(PM[1]) < PN[i].DistSq(PM[M])) || (cxp_i < 0 && cxp_i1 > 0)) {
            M_CCW[1] = i;
            break;
        }
    }
    for (int j = 2; j <= M; j++) {
        int k = M_CCW[j - 1];
        while (CCW(PM[PM.Px(j)], PM[j], PN[PN.Nx(k)]) <= 0) k = PN.Nx(k);
        M_CCW[j] = k;
    }

    /* preprocess, CW */
    for (int i = 1; i <= PN.Count; i++) {
        LL cxp_i = CCW(PM[1], PM[M], PN[i]);
        LL cxp_i1 = CCW(PM[1], PM[M], PN[PN.Px(i)]);
        if ((cxp_i == 0 && PN[i].DistSq(PM[M]) < PN[i].DistSq(PM[1])) || (cxp_i > 0 && cxp_i1 < 0)) {
            M_CW[M] = i;
            break;
        }
    }
    for (int j = M - 1; j >= 1; j--) {
        int k = M_CW[j + 1];
        while (CCW(PM[PM.Nx(j)], PM[j], PN[PN.Px(k)]) >= 0) k = PN.Px(k);
        M_CW[j] = k;
    }

    /* query */
    for (int k = 1; k <= Q; k++) {
        const Point& p = PQ[k];
        if (PN.HitTest(p) >= 0) printf("OUT\n");
        else if (PM.HitTest(p) <= 0) printf("IN\n");
        else {
            auto x = PM.GetTangentPointLt(p); /* x is more CCW than y w.r.t. p */
            auto y = PM.GetTangentPointRt(p);
            LL ans_int = 0;
            double ans_double = 0;

            /* find corresponding triangle area */
            int xo, yo;
            xo = [&]() -> int {
                int lo = M_CW[x], hi = M_CW[PM.Px(x)];
                if (lo < hi) lo += PN.Count;
                while (lo > hi) {
                    int mid = (lo + hi) / 2;
                    if (CCW(p, PM[x], PN[mid]) < 0) hi = mid + 1;
                    else lo = mid;
                }
                return PN.Sa(lo);
            }();
            yo = [&]() -> int {
                int lo = M_CCW[y], hi = M_CCW[PM.Nx(y)];
                if (lo > hi) hi += PN.Count;
                while (lo < hi) {
                    int mid = (lo + hi + 1) / 2;
                    if (CCW(p, PM[y], PN[mid]) > 0) hi = mid - 1;
                    else lo = mid;
                }
                return PN.Sa(lo);
            }();

            /* count fixed area: xo -> yo -> y -> x -> xo */
            ans_int += PN.PartialArea(xo, yo);
            ans_int += Vector(PN[yo]).Cxp(Vector(PM[y]));
            ans_int -= PM.PartialArea(x, y);
            ans_int += Vector(PM[x]).Cxp(Vector(PN[xo]));

            /* count variable area, about x */
            [&]() {
                Vector A = PM[x] - p;
                Vector B = PN[xo] - PM[x];
                Vector C = PN[xo - 1] - PM[x];
                Vector D = B - C;
                auto [v, w] = std::make_pair(-A.Y * B.X + A.X * B.Y, A.X * D.Y - D.X * A.Y);
                if (w < 0) v = -v, w = -w; /* v and w has the same sign */
                if (v < 0 || v > w) *((int*)0) = 0;

                LL Area = C.Cxp(B);
                LL q = 0, m = 0;
                for (LL i = 0, q0 = v / w, m0 = v % w; i < 63; i++) {
                    if (Area & (1LL << i)) {
                        q += q0;
                        m += m0;
                        while (m >= w) q++, m -= w;
                    }
                    q0 *= 2;
                    m0 *= 2;
                    while (m0 >= w) q0++, m0 -= w;
                }
                ans_int += q;
                ans_double += m / (double)w;
            }();
            [&]() {
                Vector A = PM[y] - p;
                Vector B = PN[yo] - PM[y];
                Vector C = PN[yo + 1] - PM[y];
                Vector D = B - C;
                auto [v, w] = std::make_pair(-A.Y * B.X + A.X * B.Y, A.X * D.Y - D.X * A.Y);
                if (w < 0) v = -v, w = -w; /* v and w has the same sign */
                if (v < 0 || v > w) *((int*)0) = 0;

                LL Area = B.Cxp(C);
                LL q = 0, m = 0;
                for (LL i = 0, q0 = v / w, m0 = v % w; i < 63; i++) {
                    if (Area & (1LL << i)) {
                        q += q0;
                        m += m0;
                        while (m >= w) q++, m -= w;
                    }
                    q0 *= 2;
                    m0 *= 2;
                    while (m0 >= w) q0++, m0 -= w;
                }
                ans_int += q;
                ans_double += m / (double)w;
            }();

            /* print */
            LL total = PN.AreaDouble - PM.AreaDouble;
            ans_int = total - ans_int;
            ans_double = -ans_double;

            const LL base = 1000000000000LL;
            LL part_int = ans_int / 2;
            LL part_frac = std::round((ans_double / 2) * base);
            if (ans_int & 1) part_frac += base / 2;
            while (part_frac < 0) part_int -= 1, part_frac += base;
            while (part_frac >= base) part_int += 1, part_frac -= base;
            printf("%lld.%012lld\n", part_int, part_frac);
        }
    }
}

char buf[1048576];
int main() {
    setvbuf(stdout, buf, _IOFBF, sizeof(buf));
    GatherInput();
    Solve();
    return 0;
}

namespace fio {
    const int BSIZE = 1048576;
    char buffer[BSIZE];
    auto p = buffer + BSIZE;
    size_t count = 0;
    inline char readChar() {
        if (p == buffer + BSIZE) {
            count = fread(buffer, 1, BSIZE, stdin);
            p = buffer;
        }
        if (p == buffer + count) {
            return 0;
        }
        char c = *p++;
        return c;
    }
    int readInt() {
        char c = readChar();
        if (c == 0) return -1;
        while (c < '-') {
            c = readChar();
            if (c == 0) return -1;
        }
        bool negative = false;
        if (c == '-') {
            negative = true;
            c = readChar();
            if (c == 0) return -1;
        }
        int ret = 0;
        while (c >= '0') {
            ret = ret * 10 + c - '0';
            c = readChar();
            if (c == 0) break;
        }
        return negative ? -ret : ret;
    }
}
int readInt() {
    return fio::readInt();
}