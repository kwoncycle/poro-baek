#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<__int128,__int128>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (__int128)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (__int128)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

class Fraction {
public:
    __int128 numerator;   // 분자
    __int128 denominator; // 분모

    // 최대공약수를 이용한 약분
    void reduce() {
        __int128 gcd_val = gcd(numerator, denominator);
        numerator /= gcd_val;
        denominator /= gcd_val;

        // 분모가 음수인 경우 분자로 부호 이동
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    // 생성자
    Fraction(__int128 num = 0, __int128 den = 1) : numerator(num), denominator(den) {
        if (den == 0) {
            throw invalid_argument("Denominator cannot be zero.");
        }
        reduce();
    }

    // 분자와 분모를 가져오는 함수
    __int128 get_numerator() const {
        return numerator;
    }

    __int128 get_denominator() const {
        return denominator;
    }

    // 덧셈
    Fraction operator+(const Fraction& other) const {
        return Fraction(numerator * other.denominator + other.numerator * denominator,
                        denominator * other.denominator);
    }

    // 뺄셈
    Fraction operator-(const Fraction& other) const {
        return Fraction(numerator * other.denominator - other.numerator * denominator,
                        denominator * other.denominator);
    }

    // 곱셈
    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    // 나눗셈
    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw invalid_argument("Division by zero.");
        }
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }

    // 절댓값
    Fraction abs() const {
        return Fraction(numerator < 0 ? -numerator : numerator, denominator);
    }

    // 비교 연산자
    bool operator<(const Fraction& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    bool operator>(const Fraction& other) const {
        return numerator * other.denominator > other.numerator * denominator;
    }

    bool operator>=(const Fraction& other) const {
        return numerator * other.denominator > other.numerator * denominator or numerator * other.denominator == other.numerator * denominator;
    }

    bool operator==(const Fraction& other) const {
        return numerator * other.denominator == other.numerator * denominator;
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    // 출력 연산자
    friend ostream& operator<<(ostream& os, const Fraction& frac) {
        if (frac.denominator == 1) {
            os << (long long)frac.numerator;
        } else {
            os << (long long)frac.numerator << "/" << (long long)frac.denominator;
        }
        return os;
    }
};

class Vector {
public:
    vector<Fraction> data;

    Vector(const vector<Fraction>& x) : data(x) {}

    Fraction sdot() const {
        return this->dot(*this);
    }

    Fraction dot(const Vector& rhs) const {
        assert(data.size() == rhs.data.size());
        Fraction result = 0;
        for (size_t i = 0; i < data.size(); ++i) {
            result = result + data[i] * rhs.data[i];
        }
        return result;
    }

    Fraction proj_coff(const Vector& rhs) const {
        return this->dot(rhs) / this->sdot();
    }

    Vector proj(const Vector& rhs) const {
        return (*this) * this->proj_coff(rhs);
    }

    Vector operator-(const Vector& rhs) const {
        assert(data.size() == rhs.data.size());
        vector<Fraction> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] - rhs.data[i];
        }
        return Vector(result);
    }

    Vector operator*(Fraction scalar) const {
        vector<Fraction> result(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] = data[i] * scalar;
        }
        return Vector(result);
    }

    Vector& operator*=(Fraction scalar) {
        for (auto& val : data) {
            val = val * scalar;
        }
        return *this;
    }

    bool any() const {
        return any_of(data.begin(), data.end(), [](Fraction x) { return x != Fraction(0); });
    }

    void print() const {
        for (const auto& val : data) {
            cout << val << " ";
        }
        cout << endl;
    }
};

// Gram-Schmidt 정규화
vector<Vector> gramschmidt(const vector<Vector>& v) {
    vector<Vector> u;
    for (const auto& vi : v) {
        Vector ui = vi;
        for (const auto& uj : u) {
            ui = ui - uj.proj(vi);
        }
        if (ui.any()) {
            u.push_back(ui);
        }
    }
    return u;
}

// LLL Reduction
vector<vector<Fraction>> reduction(
    const vector<vector<Fraction>>& basis, Fraction delta = Fraction(3, 4)) {
    size_t n = basis.size();
    vector<Vector> basisVec, ortho;

    for (const auto& b : basis) {
        basisVec.emplace_back(b);
    }

    ortho = gramschmidt(basisVec);

    auto mu = [&](size_t i, size_t j) {
        return ortho[j].proj_coff(basisVec[i]);
    };

    size_t k = 1;
    while (k < n) {
        for (int j = k - 1; j >= 0; --j) {
            Fraction mu_kj = mu(k, j);
            if (mu_kj.abs() > Fraction(1, 2)) {
                basisVec[k] = basisVec[k] - basisVec[j] * Fraction(round((long double)mu_kj.numerator / mu_kj.denominator));
                ortho = gramschmidt(basisVec);
            }
        }

        if (ortho[k].sdot() >= (delta - mu(k, k - 1) * mu(k, k - 1)) * ortho[k - 1].sdot()) {
            ++k;
        } else {
            swap(basisVec[k], basisVec[k - 1]);
            ortho = gramschmidt(basisVec);
            k = max<size_t>(k - 1, 1);
        }
    }

    vector<vector<Fraction>> result;
    for (const auto& vec : basisVec) {
        result.push_back(vec.data);
    }

    return result;
}


int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    
    
    __int128 p1 = 422480563457ll, p2 = 386195218987ll, p1_i = 221890761292ll, p2_i = 179741841568ll, M = p1*p2;
    int tt; cin >> tt;
    while(tt--){
        cout << "? " << (ll)p1 << endl;
        ll u1; cin >> u1;
        cout << "? " << (ll)p2 << endl;
        ll u2; cin >> u2;
        __int128 u = u1*p2_i*p2 + u2*p1_i*p1;
        u %= M;
        vector<vector<Fraction>> basis = {{Fraction(1, 1), Fraction(u, 1)}, {Fraction(0, 1), Fraction(M, 1)}};
        auto ans = reduction(basis);
        __int128 q = ans[0][0].numerator, p = ans[0][1].numerator;
        cout << (ll)p << " " << (ll)q << endl;
        if(p < 0) p*=-1, q*=-1;
        assert((__int128)u1*q%p1 == p);
        assert((__int128)u2*q%p2 == p);
        assert(1 <= p and p <= 1000000000);
        assert(1 <= q and q <= 1000000000);
        cout << "! " << (ll)p << " " << (ll)q << endl;
    }
    return 0;
}