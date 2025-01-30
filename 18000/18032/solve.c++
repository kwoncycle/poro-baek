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
ll operator * (pii l, pii r){return l.X*r.X + l.Y*r.Y;};
ll operator / (pii l, pii r){return l.X*r.Y - l.Y*r.X;};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    vector<int> br(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y >> br[i];
    
    vector<pii> dir;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(br[i] < br[j]){
                dir.push_back(v[i]-v[j]);
            }
            if(br[i] > br[j]) dir.push_back(v[j] - v[i]);
        }
    }
    pii O = {0,0};
    sort(dir.begin(), dir.end(), [&](pii l, pii r){
        return (l>O) == (r>O) ? l/r > 0 : l<r;
    });

    int truth = 0;
    if(dir.size() <= 1) truth = 1;
    n = dir.size();
    for(int i=0; i<n; i++){
        int o = dir[i]/dir[(i+1)%n];
        if(o < 0){
            truth = 1; break;
        }
        if(!o){
            if(dir[i]*dir[(i+1)%n] < 0){
                truth = 1; break;
            }
        }
    }
    if(truth) cout << "Y\n";
    else cout << "N\n";
    return 0;
}