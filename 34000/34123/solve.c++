#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<int> p(200005, 0);
    for(int i=2; i<=200001; i++){
        if(!p[i]){
            for(int j=i; j<=200001; j+=i) p[j] = i;
        }
    }

    vector<int> p2(200005, 0);
    for(int i=2; i<=200000; i++){
        int o = i/p[i];
        if(p[o] == o) p2[i] = 1;
    }

    vector<int> available(100005, 0);
    available[4] = 0;
    available[6] = 0;
    for(int i=8; i<=100000; i+=2){
        for(int j=i-1; j>=5; j-=2){
            if(p2[i+j]){
                available[i] = j-1;
                break;
            }
        }
    }

    if(n == 3){
        cout << "1\n";
        cout << "1 3\n";
        return 0;
    }

    if(n <= 2){
        cout << "0\n";
        return 0;
    }
    n -= n%2;
    vector<pii> ans;
    while(n != 4 and n != 6){
        int o = available[n];
        for(int i=o+1; i<=(n+o+1)/2; i++){
            ans.push_back({i, n+o+1-i});
        }
        n = o;
    }
    if(n == 4){
        ans.push_back({1, 3});
        ans.push_back({2, 4});
    }
    if(n == 6){
        ans.push_back({3, 6});
        ans.push_back({1, 5});
        ans.push_back({2, 4});
    }

    cout << (int)ans.size() << "\n";
    for(auto [x,y]:ans){
        cout << x << " " << y << "\n";
    }
    return 0;
}