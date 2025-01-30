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
    if(n == 2){
        cout << "4\n";
        cout << "1 2 1\n";
        cout << "2 3 2\n";
        cout << "3 4 3\n";
        cout << "1 3 4\n";
        cout << "1 4 5\n";
        cout << "2 4 6\n";
        return 0;
    }

    vector<array<int, 4>> edges;
    edges.push_back({1,2,1,0});
    edges.push_back({2,3,2,0});
    edges.push_back({1,3,3,1});
    edges.push_back({1,4,4,1});
    edges.push_back({2,4,5,1});
    edges.push_back({3,4,6,0});
    int o = 3;
    int last = 4;
    for(int j=4; j<=n; j++){
        int u = edges.size();
        for(int i=o; i<u; i++){
            last++;
            edges.push_back({edges[i][0], last, (int)edges.size()+1, 0});
            edges.push_back({edges[i][1], last, (int)edges.size()+1, 1});
        }
        o = u;
    }
    cout << last << "\n";
    for(auto [a,b,c,d]:edges) {
        if(d == 0) continue;
        cout << a << " " << b << " " << 99999 - c << "\n";
    }

    for(auto [a,b,c,d]:edges) {
        if(d == 1) continue;
        cout << a << " " << b << " " << 99999 - c << "\n";
    }
    return 0;
}