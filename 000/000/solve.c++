#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef array<pll, 2> LINE;
#define X first
#define Y second
#define all(x) (x).begin(), (x).end()

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    int n = rnd.next(2, 100'000);
    
    unordered_set<pll> st;
    while(st.size() < n){
        ll x = rnd.next(-1'000'000'000, 1'000'000'000);
        ll y = rnd.next(-1'000'000'000, 1'000'000'000);
        st.insert({x, y});
    }
    vector<pll> points;
    for(auto &p : st){ // I think this is randomly sorted cause it's unordered_set....but let's shuffle it again.
        points.push_back(p);
    }
    rnd.shuffle(all(points));
    
    pll log0, log1;
    while(true){
        log0.X = rnd.next(-1'000'000'000, 1'000'000'000);
        log0.Y = rnd.next(-1'000'000'000, 1'000'000'000);
        log1.X = rnd.next(-1'000'000'000, 1'000'000'000);
        log1.Y = rnd.next(-1'000'000'000, 1'000'000'000);
        bool truth = 1;
        for(auto p : points){
            if((log1 - log0) / (p - log0) == 0){ // determine whether p is on the extended-line of log
                if((log1 - p) * (log0 - p) <= 0){ // determine whether p is on the log
                    truth = 0; break;
                }
            }
        }
        if(truth) break;
    }
    
    cout << n << "\n";
    for(auto &[x, y] : points){
        cout << x << " " << y << "\n";
    }
    cout << log0.X << " " << log0.Y << " " << log1.X << " " << log1.Y << "\n";
    return 0;
}
