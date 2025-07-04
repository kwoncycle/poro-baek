#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); //cout.tie(nullptr);
    ll a, b, c; cin >> a >> b >> c;
    if(a <= c){
        while(true){
            string s; cin >> s;
            if(s != "end"){
                cout << "airline" << endl;
            }
            else break;
        }
        return 0;
    }

    ll ttl = 0, cnt = 0;
    int buy = 0;
    while(true){
        string s; cin >> s; cnt++;
        if(s != "end"){
            if(buy){
                cout << "self" << endl;
                continue;
            }
            ll mn = min(a*cnt, b+c*cnt);
            if(ttl + b+c <= mn*2){
                cout << "buy" << endl;
                ttl += b+c; buy = 1;
            }
            else {
                cout << "airline" << endl;
                ttl += a;
            }
        }
        else break;
    }

    return 0;
}