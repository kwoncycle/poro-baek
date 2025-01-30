#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;

bitset<N> a, b;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    string s, t; cin >> s >> t;
    for (int i = 0; i < s.size(); i++) if (s[i] ^ '0') a[i].flip();
    for (int i = 0; i < t.size(); i++) if (t[i] ^ '0') b[i].flip();
    
    int q; cin >> q;
    vector<array<int, 3>> query(q);
    for(int i=0; i<q; i++) cin >> query[i][0] >> query[i][1] >> query[i][2];
    vector<int> idx(q);
    for(int i=0; i<q; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int l, int r){
        return query[l][0] < query[r][0];
    });
    int cur = 0;
    for(int i:idx){
        if(query[i][0] > cur){
            a >>= query[i][0]-cur;
            cur = query[i][0];
        }
        query[i][0] = ((a ^ (b>>query[i][1])) << (N - query[i][2])).count();
    }
    for(int i=0; i<q; i++) cout << query[i][0] << "\n";
}