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
    int tt; cin >> tt;
    vector<ll> layer(1000000);
    int id = 1;
    for(int i=1; i<=500; i++){
        for(int j=1; j<=i; j++){
            layer[id] = i; id++;
        }
    }
    for(int ttt=1; ttt<=tt; ttt++){
        double b; 
        int l, n;
        cin >> b >> l >> n;
        b *= 3;
        vector<vector<double>> v(l+2);
        for(int i=1; i<=l+1; i++){
            v[i] = vector<double>((i+1)*i/2 + 1, 0.0);
        }
        v[1][1] = b;
        for(int i=1; i<=l; i++){
            for(int j=1; j<=(i+1)*i/2; j++){
                if(v[i][j] >= 1.0){
                    double u = v[i][j] - 1.0;
                    u /= 3.0;
                    v[i][j] = 1.0;
                    v[i+1][j] += u;
                    v[i+1][j + layer[j]] += u;
                    v[i+1][j + layer[j] + 1] += u;
                }
            }
        }
        cout << "Case #" << ttt << ": ";
        cout << fixed << setprecision(10) << (double)(v[l][n]*(250.000)) << "\n";
    }
    return 0;
}