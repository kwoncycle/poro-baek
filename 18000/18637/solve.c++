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

int indx = 0, pos = 0;
string s;
vector<int> ith_index(23, 0), start_index(23, 0);

int cnt = 0;
void sh(){
    s.push_back('s'); cnt++;
}

void l(){
    s.push_back('l'); cnt++;
}

void L(){
    s.push_back('L'); cnt++;
}

void r(){
    s.push_back('r'); cnt++;
}

void R(){
    s.push_back('R'); cnt++;
}

void f(){
    s.push_back('f'); cnt++;
}

void x(){
    s.push_back('x'); cnt++;
}

void mv(int loc){
    if(loc > pos){
        while(loc > pos){
            l(); pos++;
        }
    }
    else{
        while(loc < pos){
            r(); pos--;
        }
    }
}

void switch1(int p1){
    mv(p1);
    sh();
    f();
}
// assume that x - 1 position is 0
void copy_digit(int loc){
    sh();
    x();
    L();
    // pos+1
    pos++;
    mv(loc + 1);
    f();
    l(); pos++;
    sh();
    f();
    r(); f(); pos--;
    r(); f(); pos--;
    // if x: 0
    // p s -> 1 1 1
    // if x: 1
    // p 1, move -> 1 1 0
}

void mv_digit(int p1, int p2){
    mv(p1); copy_digit(p2);
}

void multiplicate(int p1, int p2, int p3){
    // set v[p3] = v[p1]*v[p2]
    // 0 1
    mv(p1);
    sh();
    x(); pos++;
    R();
    // if v[p1] = 0, ps=
    // if v[p1] = 1, p=s
    mv(p2+2);
    R();
    // if v[p2] = 1 and v[p1] = 1, p==s
    if(abs(pos - 3) < abs(pos - 1483)){
        mv(5);
        L();
        mv(4);
        L();
        mv(6);
        L();
        mv(5);
        L();
        mv(p3+1);
        f();
        sh(); f();
        l(); f(); pos++;
    }
    else{
        mv(1485);
        L();
        mv(1484);
        L();
        mv(1486);
        L();
        mv(1485);
        L();
        mv(p3+1);
        f();
        sh(); f();
        l(); f(); pos++;
    }
}

void set_ith(){
    ith_index[0] = 0;
    ith_index[1] = 1;
    ith_index[2] = 1;
    ith_index[3] = 3;
    ith_index[4] = 5;
    ith_index[5] = 9;
    ith_index[6] = 14;
    ith_index[7] = 22;
    ith_index[8] = 32;
    ith_index[9] = 46;
    ith_index[10] = 63;
    ith_index[11] = 85;
    ith_index[12] = 110;
    ith_index[13] = 139;
    ith_index[14] = 170;
    ith_index[15] = 204;
    ith_index[16] = 239;
    ith_index[17] = 276;
    ith_index[18] = 313;
    ith_index[19] = 351;
    start_index[0] = 0;
    start_index[1] = 1;
    start_index[2] = 1;
    start_index[3] = 3;
    start_index[4] = 5;
    start_index[5] = 9;
    start_index[6] = 14;
    start_index[7] = 22;
    start_index[8] = 32;
    start_index[9] = 46;
    start_index[10] = 63;
    start_index[11] = 85;
    start_index[12] = 110;
    start_index[13] = 139;
    start_index[14] = 170;
    start_index[15] = 204;
    start_index[16] = 239;
    start_index[17] = 276;
    start_index[18] = 313;
    start_index[19] = 351;
}
#define PRINT_SIZE 160
int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    //string s; cin >> s;
    for(int TC=0; TC<1024; TC++){
        vector<int> v(500001, 0);
        const int RIGHT_MAX = 500000;
        int loc = RIGHT_MAX, shadow = loc;
        indx = 0, pos = 0;
        s.clear(); s = "";
        ith_index = vector<int>(23, 0); start_index = vector<int>(23, 0);

        int cnt = 0;
        int tc1 = TC;
        for(int i=0; i<10; i++){
            v[RIGHT_MAX-i] = tc1&1;
            tc1 /= 2;
        }
        //for(int i=20; i>=0; i--) cout << v[RIGHT_MAX-i]; cout << "  ";
        for(int i=0; i<9; i++) {
            l(); pos++;
        }
        for(int i=9; i>=0; i--){
            mv(i); copy_digit(24 + i*3); 
            mv(i); copy_digit(i);
        }
        switch1(3);
        switch1(1483);
        //multiplicate(21, 24, 0);

        // 1101 1101   2*2^5, 2^6
        // ith: 20*i+50+j
        set_ith();
        for(int i=0; i<10; i++){
            int index = 2*i;
            multiplicate(24+i*3, 24+i*3, 60 + 3*ith_index[index]);
            ith_index[index]++;
            for(int j=i+1; j<10; j++){
                index = i+j+1;
                multiplicate(24+i*3, 24+j*3, 60 + 3*ith_index[index]);
                ith_index[index]++;
            }
        }
        for(int i=0; i<=18; i++){
            for(int j=start_index[i]; j + 1<start_index[i+1]; j++){
                multiplicate(60+3*j, 60+3*(j+1), 60+3*ith_index[i+1]); ith_index[i+1]++;
                mv_digit(60+3*j, 60+3*(j+1));
            }
        }
        for(int j=start_index[19]; j + 1<ith_index[19]; j++){
            mv_digit(60+3*j, 60+3*(j+1));
        }

        mv_digit(1, 1);
        switch1(3);
        for(int i=0; i<20; i++){
            if(i == 1) continue;
            mv_digit(60+3*(ith_index[i]-1), i);
        }
        
        
        mv(1500);
        for(int i=1500; i>=20; i--) mv_digit(i,i);
        //for(int i=0; i<20; i++) cout << start_index[i] << " " << ith_index[i] << "\n";
        //return 0;
        /*
        for(int i=0; i<20; i++) cout << "ith_index[" << i << "] = " << ith_index[i] << ";\n"; // 19 max, 20 ㄴㄴ
        for(int i=0; i<22; i++) ith_index[i+1] += max(0, ith_index[i]-1);
        for(int i=0; i<20; i++) cout << "ith_index[" << i << "] = " << ith_index[i] << ";\n"; // 19 max, 20 ㄴㄴ
        for(int i=0; i<22; i++){
            ith_index[i+1] += ith_index[i];
        }
        for(int i=21; i>=0; i--) ith_index[i+1] = ith_index[i]; ith_index[0] = 0;
        for(int i=0; i<20; i++) cout << "ith_index[" << i << "] = " << ith_index[i] << ";\n"; // 19 max, 20 ㄴㄴ
        return 0; */
        int cnt0 = 0;
        while(true){
            /*cnt0++;
            if(cnt - cnt0 < 200){
            for(int i=RIGHT_MAX - PRINT_SIZE; i <= RIGHT_MAX; i++) cout << v[i];
            cout << "\n";
            for(int i=RIGHT_MAX - PRINT_SIZE; i <= RIGHT_MAX; i++) cout << (RIGHT_MAX-i)%10;
            cout << "    " << cnt << "\n";
            for(int i=RIGHT_MAX - PRINT_SIZE; i <= RIGHT_MAX; i++) {
                if(i == loc) cout << "P";
                else if(i == shadow) cout << "S";
                else cout << " ";
            }
            cout << "\n";
            }*/
            char c; 
            if(indx >= (int)s.size()){
                break; //cin >> c;
            }
            else{
                c = s[indx]; indx++;
            }
            if(c == 's'){
                shadow = loc - 1;
            }
            else if(c == 'l'){
                loc -= 1;
                shadow -= 1;
            }
            else if(c == 'r'){
                loc += 1;
                shadow += 1;
                if(loc > RIGHT_MAX or shadow > RIGHT_MAX){
                    cout << "Error on command r\n"; return 0;
                }
            }
            else if(c == 'L'){
                if(v[loc] == 1) loc -= 1;
                if(shadow >= 0 and v[shadow] == 1) shadow -= 1;
            }
            else if(c == 'R'){
                if(v[loc] == 1) loc += 1;
                if(shadow >= 0 and v[shadow] == 1) shadow += 1;
                if(loc > RIGHT_MAX or shadow > RIGHT_MAX){
                    cout << "Error on command r\n"; return 0;
                }
            }
            else if(c == 'x'){
                loc ^= shadow; shadow ^= loc; loc ^= shadow;
            }
            else if(c == 'f'){
                v[loc] = 1 - v[loc];
                v[loc - 1] = 1 - v[loc - 1];
                if(shadow != loc) v[shadow] = 1 - v[shadow];
            }
        }
        tc1 = TC*TC;
        int JOAT = 0;
        for(int i=0; i<=20; i++){
            if(v[RIGHT_MAX-i] != (tc1&1)) JOAT = 1;
            tc1 /= 2;
        }
        if(JOAT){
            cout << TC << "\n"; break;
        }
        //for(int i=20; i>=0; i--) cout << v[RIGHT_MAX-i]; cout << "\n"; cout << "\n";
        break;
    }
    cout << s << "\n";
    return 0;
}