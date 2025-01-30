// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif
//#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define X first
#define Y second
#define GETVECTOR(n) for(int i=0; i< (n); i++) scanf("%d ",&inp[i]);
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using complex_t = complex<double>;

 
class djs
{
    int n;
    vector<int> par;
 
public:
    djs(int n) : n(n) {
        par.resize(n);
        for(int i=0; i<n; i++) par[i] = i;
    }
 
    int find(int v) {
        if(par[v] == v) return v;
        else return par[v] = find(par[v]);
    }
 
    bool Union(int x, int y) {
        int px = find(x);
        int py = find(y);
 
        if(px == py) return false;
 
        par[px] = py;
        return true;
    }
};
// Usage: djs DJS(n)

int pair2int(pii x){
    return 2000*x.X + x.Y;
}

pii int2pair(int x){
    return {x/2000, x%2000};
}
#define DEBUG 0
int main(){
    if(!DEBUG){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
    }
    int w, h; cin >> w >> h;
    vector<vector<int>> v(h+2, vector<int>(w+2, 0)), vA(h+2, vector<int>(w+2, 0)), vB(h+2, vector<int>(w+2, 0)), DPA(h+2, vector<int>(w+2, 0)), DPB(h+2, vector<int>(w+2, 0)), DP(h+2, vector<int>(w+2, 0));

    for(int i=1; i<=h; i++){
        string s; cin >> s;
        for(int j=1; j<=w; j++){
            if(s[j-1] == '#') v[i][j] = 1;
        }
    }

    for(int i=1; i<=h; i++){
        for(int j=1; j<=w; j++){
            vA[i][j] = v[i][j];
            vB[i][j] = v[i][j];
        }
    }

    for(int i=2; i<=w+1; i++) vA[0][i] = 1;
    for(int i=0; i<=w-1; i++) vB[h+1][i] = 1;
    for(int i=0; i<=h-1; i++) vA[i][w+1] = 1;
    for(int i=2; i<=h+1; i++) vB[i][0] = 1;

    vector<pii> WASD(8);
    WASD[0] = {0, 1};
    WASD[1] = {1, 0};
    WASD[2] = {0, -1};
    WASD[3] = {-1, 0};
    WASD[4] = {1, 1};
    WASD[5] = {-1, 1};
    WASD[6] = {-1, -1};
    WASD[7] = {1, -1};

    
    // merge A
    djs DJSA(4000000);
    for(int i=0; i<=h+1; i++){
        for(int j=0; j<=w+1; j++){
            if(vA[i][j] == 0) continue;
            for(pii p:WASD){
                int i1 = i + p.X, j1 = j + p.Y;
                if(i1 < 0 or i1 > h+1) continue;
                if(j1 < 0 or j1 > w+1) continue;
                if(vA[i1][j1] == 1) DJSA.Union(pair2int({i1, j1}), pair2int({i, j}));
            }
        }
    }
    for(int i=0; i<=h+1; i++){
        for(int j=0; j<=w+1; j++){
            if(vA[i][j]){
                if(DJSA.find(pair2int({i,j})) != DJSA.find(pair2int({0, w+1}))) vA[i][j] = 0;
            }
        }
    }
    
    if(DEBUG){
        for(int i=0; i<=h+1; i++){
            for(int j=0; j<=w+1; j++){
                if(vA[i][j]) cout << '#';
                else cout << '.';
            }
            cout << "\n";
        }
    }

    for(int i=0; i<=h+1; i++){
        for(int j=0; j<=w+1; j++){
            if(vA[i][j]) DPA[i][j] = 0;
            else{
                DPA[i][j] = w+1-j;
                for(pii p:WASD){
                    int i1 = i + p.X, j1 = j + p.Y;
                    if(i1 < 0 or i1 > h+1) continue;
                    if(j1 < 0 or j1 > w+1) continue;
                    if(vA[i1][j1] == 1){
                        DPA[i][j] = 1; break;
                    }
                }
            }
        }
    }

    for(int j=w+1; j>=0; j--){
        for(int i=h+1; i>=0; i--){
            int mn = DPA[i][j];
            if(j+1 <= w+1){
                mn = min(mn, DPA[i][j+1] + 1);
            }
            if(i+1 <= h+1){
                mn = min(mn, DPA[i+1][j] + 1);
            }
            if(i+1 <= h+1 and j+1 <= w+1){
                mn = min(mn, DPA[i+1][j+1] + 1);
            }
            DPA[i][j] = mn;
        }
    }

    if(DEBUG){
        for(int i=0; i<=h+1; i++){
            for(int j=0; j<=w+1; j++){
                cout << setw(2) << DPA[i][j];
            }
            cout << "\n";
        }
    }

    // merge B
    djs DJSB(4000000);
    for(int i=0; i<=h+1; i++){
        for(int j=0; j<=w+1; j++){
            if(vB[i][j] == 0) continue;
            for(pii p:WASD){
                int i1 = i + p.X, j1 = j + p.Y;
                if(i1 < 0 or i1 > h+1) continue;
                if(j1 < 0 or j1 > w+1) continue;
                if(vB[i1][j1] == 1) DJSB.Union(pair2int({i1, j1}), pair2int({i, j}));
            }
        }
    }
    for(int i=0; i<=h+1; i++){
        for(int j=0; j<=w+1; j++){
            if(vB[i][j]){
                if(DJSB.find(pair2int({i,j})) != DJSB.find(pair2int({h+1, 0}))) vB[i][j] = 0;
            }
        }
    }
    
    if(DEBUG){
        for(int i=0; i<=h+1; i++){
            for(int j=0; j<=w+1; j++){
                if(vB[i][j]) cout << '#';
                else cout << '.';
            }
            cout << "\n";
        }
    }

    for(int i=0; i<=h+1; i++){
        for(int j=0; j<=w+1; j++){
            if(vB[i][j]) DPB[i][j] = 0;
            else{
                DPB[i][j] = h+1-i;
                for(pii p:WASD){
                    int i1 = i + p.X, j1 = j + p.Y;
                    if(i1 < 0 or i1 > h+1) continue;
                    if(j1 < 0 or j1 > w+1) continue;
                    if(vB[i1][j1] == 1){
                        DPB[i][j] = 1; break;
                    }
                }
            }
        }
    }

    for(int j=w+1; j>=0; j--){
        for(int i=h+1; i>=0; i--){
            int mn = DPB[i][j];
            if(j+1 <= w+1){
                mn = min(mn, DPB[i][j+1] + 1);
            }
            if(i+1 <= h+1){
                mn = min(mn, DPB[i+1][j] + 1);
            }
            if(i+1 <= h+1 and j+1 <= w+1){
                mn = min(mn, DPB[i+1][j+1] + 1);
            }
            DPB[i][j] = mn;
        }
    }

    if(DEBUG){
        for(int i=0; i<=h+1; i++){
            for(int j=0; j<=w+1; j++){
                cout << setw(2) << DPB[i][j];
            }
            cout << "\n";
        }
    }

    for(int i=0; i<=h+1; i++) v[i][0] = 1;
    for(int i=0; i<=h+1; i++) v[i][w+1] = 1;
    for(int i=0; i<=w+1; i++) v[0][i] = 1;
    for(int i=0; i<=w+1; i++) v[h+1][i] = 1;
    v[1][1] = 1;
    v[h][w] = 1;
    for(int i=h+1; i>=0; i--){
        for(int j=w+1; j>=0; j--){
            if(v[i][j]) DP[i][j] = 0;
            else{
                int mn = min(h+1-i, w+1-j);
                if(i+1 <= h+1){
                    mn = min(mn, DP[i+1][j] + 1);
                }
                if(j+1 <= w+1){
                    mn = min(mn, DP[i][j+1] + 1);
                }
                if(i+1 <= h+1 and j+1<=w+1){
                    mn = min(mn, DP[i+1][j+1] + 1);
                }
                DP[i][j] = mn;
            }
        }
    }
    if(DEBUG){
        cout << "======================\n";
        for(int i=0; i<=h+1; i++){
            for(int j=0; j<=w+1; j++){
                cout << setw(2) << DP[i][j];
            }
            cout << "\n";
        }
        cout << "======================\n";
        for(int i=0; i<=h+1; i++){
            for(int j=0; j<=w+1; j++){
                cout << setw(2) << DPA[i][j];
            }
            cout << "\n";
        }
        cout << "======================\n";
        for(int i=0; i<=h+1; i++){
            for(int j=0; j<=w+1; j++){
                cout << setw(2) << DPB[i][j];
            }
            cout << "\n";
        }
    }

    int mn = 99999, ai, aj;
    for(int i=1; i<=h; i++){
        for(int j=1; j<=w; j++){
            if(v[i][j]) continue;
            if(max(DPA[i][j], DPB[i][j]) <= DP[i][j]){
                if(mn > max(DPA[i][j], DPB[i][j])){
                    mn = max(DPA[i][j], DPB[i][j]);
                    ai = i; aj = j;
                }
            }
        }
    }
    if(mn > 9999) cout << "Impossible\n";
    else cout << mn << " " << aj << " " << ai << "\n";
    return 0;
}