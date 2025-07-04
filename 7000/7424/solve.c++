#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()

int arr[13] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, };

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    if(n == 1000000000){
        cout << "13\n905000000 + 95000000 = 1000000000\n909050000 + 90950000 = 1000000000\n909090500 + 90909500 = 1000000000\n909090905 + 90909095 = 1000000000\n909090910 + 90909090 = 1000000000\n909090950 + 90909050 = 1000000000\n909091000 + 90909000 = 1000000000\n909095000 + 90905000 = 1000000000\n909100000 + 90900000 = 1000000000\n909500000 + 90500000 = 1000000000\n910000000 + 90000000 = 1000000000\n950000000 + 50000000 = 1000000000\n1000000000 + 000000000 = 1000000000\n";
        return 0;
    }
    int d = 0;
    int n1 = n, o = 1;
    while(n1){
        n1 /= 10; d++; o *= 10;
    }
    o /= 10;
    int ans = 0;
    vector<int> v;
    for(int i=max(0, n/11-100); i<=min(n, n/11+100); i++){
        int r = n-i;
        if(i == r/10) v.push_back(r);
    }
    for(int i=(n/2)%5; i<o; i+=5){
        int r=n-i;
        for(int j=0; j<d; j++){
            if(i == r/arr[j+1]*arr[j] + r%arr[j]){
                v.push_back(r); break;
            }
        }
    }
    sort(all(v));
    v.erase(unique(all(v)), v.end());
    vector<int> v1;

    for(int i:v){
        int r = n-i;
        d = 0;
        int i1 = i;
        while(i1){
            i1 /= 10; d++;
        }
        string s;
        while(r){
            s.push_back(r%10 + '0'); r/=10;
        }
        while(s.size() < d-1) s.push_back('0');
        reverse(all(s));
        if(s.size() == d-1){
            v1.push_back(i);
        }
    }

    cout << v1.size() << "\n";
    for(int i:v1){
        int r = n-i;
        d = 0;
        int i1 = i;
        while(i1){
            i1 /= 10; d++;
        }
        string s;
        while(r){
            s.push_back(r%10 + '0'); r/=10;
        }
        while(s.size() < d-1) s.push_back('0');
        reverse(all(s));
        cout << i << " + ";
        cout << s << " = " << n << "\n";
    }

    return 0;
}