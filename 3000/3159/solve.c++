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
template <typename T>
vector<vector<T>> V2(size_t n1) {
    return vector<vector<T>>(n1);
}

template <typename T>
vector<vector<T>> V2(size_t n1, size_t n2, T a) {
    return vector<vector<T>>(n1, vector<T>(n2, a));
}

// 3D 벡터 생성 함수
template <typename T>
vector<vector<vector<T>>> V3(size_t n1) {
    return vector<vector<vector<T>>>(n1);
}

template <typename T>
vector<vector<vector<T>>> V3(size_t n1, size_t n2) {
    return vector<vector<vector<T>>>(n1, vector<vector<T>>(n2));
}

template <typename T>
vector<vector<vector<T>>> V3(size_t n1, size_t n2, size_t n3, T a) {
    return vector<vector<vector<T>>>(n1, vector<vector<T>>(n2, vector<T>(n3, a)));
}
#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;

    auto v = V2<int>(2, n, 0);
    string s;
    cin >> s;
    for(int i=0; i<n; i++) v[0][i] = s[i] - '0';
    cin >> s;
    for(int i=0; i<n; i++) v[1][i] = s[i] - '0';

    auto DP = V2<int>(4, n, 0);
    
    int bitcnt[4] = {0,1,1,2};
    for(int i=0; i<4; i++){
        int i1 = i;
        i1 ^= (v[0][0] + 2*v[1][0]);
        DP[i][0] = bitcnt[i];
        if(i1 == 0) DP[i][0] += 0;
        else DP[i][0] += 1;
    }

    for(int j=1; j<n; j++){
        for(int i1=0; i1<4; i1++){
            int u = i1;
            u ^= v[0][j] + 2*v[1][j];
            int add = bitcnt[i1] + (u ? 1 : 0), mn = 0x3f3f3f3f;
            for(int i0=0; i0<4; i0++){
                int a = DP[i0][j-1];
                if(i1&1 and i0&1) a--;
                if(i1&2 and i0&2) a--;
                mn = min(mn, a);
            }
            DP[i1][j] = add + mn;
        }
    }

    int ans = 0x3f3f3f3f;

    for(int i=0; i<4; i++){
        ans = min(ans, DP[i][n-1]);
    }

    cout << ans << "\n";


    // DP: 00, 01, 11
    return 0;
}