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
int ln[6];

int v2i(vector<int> &v){
    int r = 0;
    for(int i=0; i<6; i++){
        r *= ln[i]; r += v[i];
    }
    return r;
}

vector<int> i2v(int r){
    vector<int> v(6, 0);
    for(int i=5; i>=0; i--){
        v[i] = r % ln[i];
        r /= ln[i];
    }
    return v;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> ln[0] >> ln[1] >> ln[2] >> ln[3] >> ln[4] >> ln[5];
    vector<int> puzzle(ln[0]*ln[1]*ln[2]*ln[3]*ln[4]*ln[5]);
    int sz = puzzle.size();
    int loc;
    for(int i=0; i<sz; i++){
        cin >> puzzle[i]; puzzle[i]--;
        if(puzzle[i] == -1) loc = i;
    }
    for(int i=0; i<6; i++){
        vector<int> v1 = i2v(loc);
        while(v1[i] + 1 < ln[i]){
            vector<int> v2 = v1;
            v2[i]++;
            int u2 = v2i(v2);
            int u1 = v2i(v1);
            v1[i]++;
            int tmp = puzzle[u1]; puzzle[u1] = puzzle[u2]; puzzle[u2] = tmp;
        }
        loc = v2i(v1);
    }

    //for(int i=0; i<sz; i++) cout << puzzle[i] << " "; cout << "\n";

    int cnt = 0;
    for(int i=0; i<6; i++) if(ln[i] == 1) cnt++;
    if(cnt == 5){
        int truth = 1;
        for(int i=0; i<6; i++){
            vector<int> v(6, 0);
            if(ln[i] > 1){
                for(int j=0; j<ln[i]-1; j++){
                    v[i] = j;
                    int u = v2i(v);
                    if(puzzle[u] != j) truth = 0;
                }
            }
        }
        if(truth) cout << "2ez\n";
        else cout << "eokkkkkk\n";
        return 0;
    }

    cnt = 0;
    for(int i=0; i<sz-1; i++){
        if(puzzle[i] >= i) continue;
        int u = puzzle[i];
        int tmp = puzzle[u]; puzzle[u] = puzzle[i]; puzzle[i] = tmp; i--; cnt++;
    }
    if(cnt % 2 == 0) cout << "2ez\n";
    else cout << "eokkkkkk\n";
    return 0;
}