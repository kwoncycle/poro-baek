#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

ll DP[1000500];


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    vector<int> v(11);
    for(int i=0; i<11; i++) cin >> v[i];
    reverse(all(v));
    int sz = 1;
    for(int i:v) sz *= i;
    for(int i0=0; i0<sz; i0++){
        cin >> DP[i0];
    }
    vector<int> T(1, 1);
    for(int i:v){
        T.push_back(T.back()*i);
    }
    for(int d=0; d<11; d++){
        for(int i=0; i<sz; i++){
            if(i % T[d+1] + T[d] < T[d+1]) DP[i + T[d]] += DP[i];
        }
    }

    int qq; cin >> qq;
    while(qq--){
        vector<int> query0(11), query1(11);
        for(int &i:query0) {
            cin >> i; i-=2;
        }
        for(int &i:query1) {
            cin >> i; i--;
        }
        reverse(all(query0)); reverse(all(query1));
        ll ans = 0;
        for(int d=0; d<(1<<11); d++){
            int a = 1, id = 0;
            for(int i=0; i<11; i++){
                if((d >> i)&1){
                    id += T[i]*query1[i];
                }
                else{
                    if(query0[i] < 0){
                        a = 0; break;
                    }
                    id += T[i]*query0[i];
                    a = -a;
                }
            }
            ans += a*DP[id];
        }
        cout << ans << "\n";
    }
    return 0;
}