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
    vector<bitset<2000>> v(n);

    for(int i=0; i<n; i++){
        string s; cin >> s;
        for(int j=0; j<n; j++){
            if(s[j] == '1') v[i][j] = true;
        }
    }
    int q; cin >> q;
    while(q--){
        int a, b; cin >> a >> b; a--; b--;
        bitset<2000> bt = v[a]&v[b];
        int t = bt.count();
        cout << t << "\n";
    }
    return 0;
}