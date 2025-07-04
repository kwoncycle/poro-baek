#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

string table[4][10] = {
    {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"}
    ,{"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"}
    ,{"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"}
    ,{"", "M", "MM", "MMM"}
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll M, D, C, L, X, V, I;
    cin >> M >> D >> C >> L >> X >> V >> I;
    ll M1 = M, D1 = D, C1 = C, L1 = L, X1 = X, V1 = V, I1 = I;
    ll st = 0, ed = 1e18 + 1e9;
    while(st + 1 < ed){
        ll md = (st + ed) / 2;
        int truth = 1;
        ll cm = min(C, max(0ll, M - md*3));
        ll dc3 = md - cm;
        ll xc = min(X, max(0ll, C - dc3*3 - cm));
        ll lx3 = md - xc;
        ll ix = min(I, max(0ll, X - lx3*3 - xc));
        ll vi3 = md - ix;
        if(md*3 + cm < M or cm + dc3*3 + xc < C or dc3 < D or xc + lx3*3 + ix < X or lx3 < L or vi3 < V or vi3*3 + ix < I) truth = 0;
        if(cm < 0 or md < cm) truth = 0;
        if(dc3 < 0 or md < dc3) truth = 0;
        if(xc < 0 or md < xc) truth = 0;
        if(lx3 < 0 or md < lx3) truth = 0;
        if(ix < 0 or md < ix) truth = 0;
        if(vi3 < 0 or md < vi3) truth = 0;
        if(truth) ed = md;
        else st = md;
    }

    vector<vector<ll>> v(4, vector<ll>(10, 0));
    ll s0 = 0, s1 = 0, s2 = 0, s3 = 0;

    ll T = ed;
    v[3][3] = min(T, M/3); M -= 3*v[3][3]; s3 += v[3][3];
    while(s3 + 1 <= T and M >= 2) v[3][2]++, M-=2, s3++;
    while(s3 + 1 <= T and M >= 1) v[3][1]++, M-=1, s3++;
    v[3][0] = T;
    for(int i=1; i<10; i++) v[3][0] -= v[3][i];

    v[2][9] = M; M = 0; C -= v[2][9]; s2 = v[2][9];
    v[2][8] = min({T-s2, C/3, D}); D -= v[2][8]; C -= v[2][8]*3; s2 += v[2][8];
    v[2][7] = min({T-s2, C/2, D}); D -= v[2][7]; C -= v[2][7]*2; s2 += v[2][7];
    v[2][6] = min({T-s2, C/1, D}); D -= v[2][6]; C -= v[2][6]*1; s2 += v[2][6];
    v[2][5] = min({T-s2, D}); D -= v[2][5]; s2 += v[2][5];

    v[2][3] = min({T-s2, C/3}); C -= v[2][3]*3; s2 += v[2][3];
    v[2][2] = min({T-s2, C/2}); C -= v[2][2]*2; s2 += v[2][2];
    v[2][1] = min({T-s2, C/1}); C -= v[2][1]*1; s2 += v[2][1];
    v[2][0] = T;
    for(int i=1; i<10; i++) v[2][0] -= v[2][i];

    v[1][9] = C; C = 0; X -= v[1][9]; s1 = v[1][9];
    v[1][8] = min({T-s1, X/3, L}); L -= v[1][8]; X -= v[1][8]*3; s1 += v[1][8];
    v[1][7] = min({T-s1, X/2, L}); L -= v[1][7]; X -= v[1][7]*2; s1 += v[1][7];
    v[1][6] = min({T-s1, X/1, L}); L -= v[1][6]; X -= v[1][6]*1; s1 += v[1][6];
    v[1][5] = min({T-s1, L}); L -= v[1][5]; s1 += v[1][5];

    v[1][3] = min({T-s1, X/3}); X -= v[1][3]*3; s1 += v[1][3];
    v[1][2] = min({T-s1, X/2}); X -= v[1][2]*2; s1 += v[1][2];
    v[1][1] = min({T-s1, X/1}); X -= v[1][1]*1; s1 += v[1][1];
    v[1][0] = T;
    for(int i=1; i<10; i++) v[1][0] -= v[1][i];

    v[0][9] = X; X = 0; I -= v[0][9]; s0 = v[0][9];
    v[0][8] = min({T-s0, I/3, V}); V -= v[0][8]; I -= v[0][8]*3; s0 += v[0][8];
    v[0][7] = min({T-s0, I/2, V}); V -= v[0][7]; I -= v[0][7]*2; s0 += v[0][7];
    v[0][6] = min({T-s0, I/1, V}); V -= v[0][6]; I -= v[0][6]*1; s0 += v[0][6];
    v[0][5] = min({T-s0, V}); V -= v[0][5]; s0 += v[0][5];

    v[0][3] = min({T-s0, I/3}); I -= v[0][3]*3; s0 += v[0][3];
    v[0][2] = min({T-s0, I/2}); I -= v[0][2]*2; s0 += v[0][2];
    v[0][1] = min({T-s0, I/1}); I -= v[0][1]*1; s0 += v[0][1];
    v[0][0] = T;
    for(int i=1; i<10; i++) v[0][0] -= v[0][i];
    vector<ll> val;
    for(int i=0; i<4; i++){
        val.push_back(v[i][0]);
        for(int j=1; j<10; j++) {
            v[i][j] += v[i][j-1];
            val.push_back(v[i][j]);
        }
    }
    val.push_back(T); val.push_back(0);
    sort(all(val));
    val.erase(unique(all(val)), val.end());

    // for(int i=0; i<4; i++){
    //     for(ll j:v[i]) cout << j << " "; cout << "\n";
    // }

    assert(!(M or D or C or L or X or V or I));
    cout << T << "\n";
    cout << val.size() - 1 << "\n";
    for(int i=0; i<(int)val.size()-1; i++){
        ll v0 = val[i], v1 = val[i+1] - 1; v0++;
        string U;
        for(int j=3; j>=0; j--){
            if(v0 <= v[j][0]) continue;
            for(int k=1; k<10; k++){
                if(v[j][k-1] < v0 and v0 <= v[j][k]){
                    U += table[j][k]; break;
                }
            }
        }
        for(char c:U){
            if(c == 'M') M1 -= v1 - v0 + 2;
            else if(c == 'D') D1 -= v1 - v0 + 2;
            else if(c == 'C') C1 -= v1 - v0 + 2;
            else if(c == 'L') L1 -= v1 - v0 + 2;
            else if(c == 'X') X1 -= v1 - v0 + 2;
            else if(c == 'V') V1 -= v1 - v0 + 2;
            else if(c == 'I') I1 -= v1 - v0 + 2;
        }
        cout << U << " " << v1 - v0 + 2 << "\n";
    }
    //cout << M1 << " " << D1 << " " << C1 << " " << L1 << " " << X1 << " " << V1 << " " << I1 << "\n";
    assert(M1 == 0 and D1 == 0 and C1 == 0 and L1 == 0 and X1 == 0 and V1 == 0 and I1 == 0);
    return 0;
}