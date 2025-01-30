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

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    vector<string> v(9);
    for(int i=0; i<9; i++) cin >> v[i];
    int o1=0, o2=0, o3=0;
    for(int i=0; i<9; i++){
        int o=0;
        for(int j=0; j<9; j++){
            if(v[i][j] == '1') o++;
        }
        if(o%2) o1++;
    }
    for(int i=0; i<9; i++){
        int o=0;
        for(int j=0; j<9; j++){
            if(v[j][i] == '1') o++;
        }
        if(o%2) o2++;
    }
    for(int i=0; i<9; i+=3){
        for(int j=0; j<9; j+=3){
            int o=0;
            for(int i1=i; i1<i+3; i1++){
                for(int j1=j; j1<j+3; j1++){
                    if(v[i1][j1] == '1') o++;
                }
            }
            if(o%2) o3++;
        }
    }
    cout << max(o3, max(o1, o2)) << "\n";
    return 0;
}