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

char v[100][100];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    for(int i=0; i<100; i++){
        for(int j=0; j<100; j++) v[i][j] = 'H';
    }
    for(int i=0; i<n; i++){
        string s; cin >> s;
        for(int j=0; j<m; j++){
            v[i+25][j+25] = s[j];
        }
    }

    
    return 0;
}