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
#include <boost/progress.hpp>

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define X first
#define Y second

using namespace std;

struct Output : std::ostream, std::streambuf
{
    Output(bool enabled) : std::ostream(this), m_enabled(enabled) {}

    int overflow(int c)  {
        if(m_enabled) std::cout.put(c);
        return 0;
    }

    bool m_enabled;
};

#define loading_bar loading_bar_invisible

int main(){
    for(int MM=2; MM<=6; MM++){
        map<vector<int>, int> mp;
        int MM16 = 1;
        for(int i=0; i<MM; i++) MM16 *= 16;
        vector<int> indexing(MM16, -1);
        int cou = 0;
        // Visible progress
        //Output out_enabled(true);
        //boost::progress_display loading_bar_visible(MM16, out_enabled);

        // Invisible progress
        Output out_disabled(false);
        boost::progress_display loading_bar_invisible(MM16, out_disabled);
        //boost::progress_display loading_bar(MM16);
        vector<vector<int>> babamba;
        vector<int> bbb;
        for(int i=0; i<MM16; i++){
            ++loading_bar;
            vector<int> v(MM);
            int i1 = i;
            for(int j=0; j<MM; j++){
                v[j] = i1 % 16; i1 /= 16;
            }
            int truth = 1;
            for(int j=0; j<MM-1; j++){
                if(v[j] == v[j+1]){
                    truth = 0; break;
                }
            }
            if(!truth){
                continue;
            }
            vector<int> v1(MM), v2(MM);
            vector<int> check(16, -1);
            int index1 = 0;

            for(int j=0; j<MM; j++){
                if(check[v[j]] == -1){
                    check[v[j]] = index1; index1++;
                }
                v1[j] = check[v[j]];
            }
            
            check = vector<int>(16, -1);
            int index2 = 0;
            for(int j=MM-1; j>=0; j--){
                if(check[v[j]] == -1){
                    check[v[j]] = index2; index2++;
                }
                v2[MM-j-1] = check[v[j]];
            }
            if(mp.find(v1) != mp.end()){
                indexing[i] = mp[v1];
                bbb[mp[v1]]++;
            }
            else if(mp.find(v2) != mp.end()){
                indexing[i] = mp[v2];
                bbb[mp[v2]]++;
            }
            else{
                mp[v1] = cou; cou++;
                indexing[i] = mp[v1];
                babamba.push_back(v1);
                bbb.push_back(1);
            }
        }
        int N = mp.size();
        vector<vector<int>> arr(N, vector<int>(N, 0));
        
        for(int i=0; i<N; i++){
            vector<int> Xa = babamba[i];
            int XN = 0;
            for(int j=MM-1; j>=0; j--){
                XN *= 16; XN += Xa[j];
            }
            loading_bar.restart(MM16);
            for(int j=0; j<MM16; j++){
                ++loading_bar;
                int XXOR = XN ^ j;
                if(!(XXOR & 0b111100000000000000000000) and MM >= 6) continue;
                if(!(XXOR & 0b000011110000000000000000) and MM >= 5) continue;
                if(!(XXOR & 0b000000001111000000000000) and MM >= 4) continue;
                if(!(XXOR & 0b000000000000111100000000) and MM >= 3) continue;
                if(!(XXOR & 0b000000000000000011110000) and MM >= 2) continue;
                if(!(XXOR & 0b000000000000000000001111) and MM >= 1) continue;
                int i1 = indexing[j];
                if(i1 == -1) continue;
                arr[i][i1] += 1;
            }
        }

        cout << "ll arr" << MM << '[' << MM << "][" << MM << "]" << " = " << "{";
        for(int i=0; i<N; i++){
            cout << "{";
            for(int j=0; j<N; j++){
                cout << arr[i][j];
                if(j < N-1) cout << ",";
            }
            cout << "}";
            if(i < N-1) cout << ",";
        }
        cout << "};";
        cout << "\n";
        cout << "ll bbb" << MM << "[" << N << "] = {"; 
        for(int i=0; i<N; i++){
            cout << bbb[i];
            if(i < N-1) cout << ",";
        }
        cout << "};\n";
    }
}