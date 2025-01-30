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
        cout << "-1\n"; return 0;
    }
    cout << 100 << "\n"; 
    if(n % 2 == 1){
        vector<vector<int>> mp(100, vector<int>(100, 0));
        for(int i=0; i<n/2 + 1; i++){
            mp[99-i][0] = 1;
            mp[99][i] = 1;
        }
        for(int i=0; i<100; i++){
            for(int j=0; j<100; j++){
                if(mp[i][j]) cout << "o";
                else cout << ".";
            }
            cout << "\n";
        }
    }
    else{
        vector<vector<int>> mp(100, vector<int>(100, 0));
        for(int i=0; i<n/2; i++){
            mp[99-i][0] = 1;
            mp[99][i] = 1;
        }
        mp[98][1] = 1;
        for(int i=0; i<100; i++){
            for(int j=0; j<100; j++){
                if(mp[i][j]) cout << "o";
                else cout << ".";
            }
            cout << "\n";
        }
    }
    return 0;
}