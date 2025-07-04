#define SIMD

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <compare>
#include <cstdio>
#include <cstring>
#include <functional>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <type_traits>
#include <vector>

#ifdef SIMD
#include <immintrin.h>
#include <smmintrin.h>
#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx,avx2")
#endif

using namespace std;

typedef long long int lli;
typedef pair<int, int> pii;
typedef pair<lli, lli> plli;
#define byte unsigned char
typedef unsigned int uint;
typedef unsigned long long int ulli;

template <typename _T> class _vector: public vector<_T> {
public:
	_vector(): vector<_T>() {}
	_vector(size_t n, const _T& val = _T()): vector<_T>(n, val) {}
	template <class InputIterator> _vector(InputIterator first, InputIterator last): vector<_T>(first, last) {}
	_vector(const vector<_T>& x): vector<_T>(x) {}
	_vector(int n): vector<_T>(n) {}
	void sort() {
		std::sort(this->begin(), this->end());
	}
	template <typename _U> void sort(std::function<_U(const _T &)> key) {
		std::sort(this->begin(), this->end(), [=] (const _T &x, const _T &y) {
			return key(x) < key(y);
		});
	}
	void sort(std::function<bool(const _T &, const _T &)> compare) {
		std::sort(this->begin(), this->end(), compare);
	}
};

#define vector _vector

typedef double real;

const real eps = 1e-8;

inline real dist(const real x1, const real y1, const real x2, const real y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

inline pair<real, real> calculate_position(const real cos_mid_angle, const real cos2, const real sin2, const real s1) {
	const real sin_mid_angle = sqrt(max(0., 1. - cos_mid_angle * cos_mid_angle));
	const real cos_other_angle = cos_mid_angle * cos2 + sin_mid_angle * sin2;
	const real alpha = cos_mid_angle;
	const real beta = sin_mid_angle;
	const real minus_gamma = cos_other_angle;
	const real minus_delta = -sqrt(max(0., 1. - cos_other_angle * cos_other_angle));
	// / a -g \/ t1 \   / s \ .
	// \ b -d /\ t2 / = \ 0 /
	// / t1 \   1 / -d g \/ s \ .
	// \ t2 / = D \ -b a /\ 0 /
	// t1 = 1/D * (-delta s)
	const real D = alpha * minus_delta - minus_gamma * beta;
	const real t1 = minus_delta * s1 / D;
	const real target_x = t1 * cos_mid_angle;
	const real target_y = t1 * sin_mid_angle;
	return make_pair(target_x, target_y);
}

inline real calculate_angle(const real cos_mid_angle, const real cos2, const real sin2, const real s1, const real s2, const real other_x, const real other_y) {
	const auto [target_x, target_y] = calculate_position(cos_mid_angle, cos2, sin2, s1);
	const real target_length = dist(other_x, other_y, target_x, target_y);
	const real calculated_cos = (other_x * (other_x - target_x) + other_y * (other_y - target_y)) / (target_length * s2);
	return calculated_cos;
}

inline real cos_angle(const real x1, const real y1, const real x2, const real y2, const real x3, const real y3) {
	const real tx1 = x1 - x2, ty1 = y1 - y2;
	const real tx2 = x3 - x2, ty2 = y3 - y2;
	return (tx1 * tx2 + ty1 * ty2) / (dist(0., 0., tx1, ty1) * dist(0., 0., tx2, ty2));
}

inline real calculate_characteristic(const real x1, const real y1, const real x2, const real y2, const real x3, const real y3, const real ux, const real uy) {
	real temp[3];
	temp[0] = cos_angle(ux, uy, x1, y1, x2, y2);
	temp[1] = cos_angle(ux, uy, x2, y2, x3, y3);
	temp[2] = cos_angle(ux, uy, x3, y3, x1, y1);
	return *max_element(temp, temp + 2) - *min_element(temp, temp + 2);
}

int main() {
	int T = 1;
	scanf("%d", &T);
	for (int tc=1; tc<=T; ++tc) {
		real x1, y1, x2, y2, x3, y3;
		scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3);
		const real s1 = dist(x1, y1, x2, y2);
		const real s2 = dist(x1, y1, x3, y3);
		const real s3 = dist(x2, y2, x3, y3);
		const real cos1 = (s1 * s1 + s2 * s2 - s3 * s3) / (2 * s1 * s2);
		const real cos2 = (s1 * s1 + s3 * s3 - s2 * s2) / (2 * s1 * s3);
		const real other_x = s2 * cos1;
		const real other_y = sqrt(s2 * s2 - other_x * other_x);
		const real sin2 = sqrt(max(0., 1. - cos2 * cos2));
		real s = max(cos1, cos2), e = 1.;
		while (s + eps < e) {
			const real cos_mid_angle = (s + e) / 2.;
			const real calculated_cos = calculate_angle(cos_mid_angle, cos2, sin2, s1, s2, other_x, other_y);
			if (calculated_cos < cos_mid_angle) {
				e = cos_mid_angle;
			} else {
				s = cos_mid_angle;
			}
		}
		const real cos_mid_angle = (s + e) / 2.;
		const auto [target_x, target_y] = calculate_position(cos_mid_angle, cos2, sin2, s1);
		const auto [costheta, sintheta] = make_pair((x2 - x1) / s1, (y2 - y1) / s1);
		const real ux1 = (costheta * target_x - sintheta * target_y) + x1;
		const real uy1 = (sintheta * target_x + costheta * target_y) + y1;
		const real c1 = calculate_characteristic(x1, y1, x2, y2, x3, y3, ux1, uy1);
		const real ux2 = (costheta * target_x + sintheta * target_y) + x1;
		const real uy2 = (sintheta * target_x - costheta * target_y) + y1;
		const real c2 = calculate_characteristic(x1, y1, x2, y2, x3, y3, ux2, uy2);
		if (c1 < c2) {
			printf("%.5lf %.5lf\n", ux1, uy1);
		} else {
			printf("%.5lf %.5lf\n", ux2, uy2);
		}
	}
	return 0;
}
