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
int L = 0x3f3f3f3f, R = L, U = L, D = L;

void JSH(){
    int o = U^D^L^R;
    if((U^o) <= U){
        cout << "top " << U - (U^o) << endl;
        U = U^o;
    }
    else if((D^o) <= D){
        cout << "bottom " << D - (D^o) << endl;
        D = D^o;
    }
    else if((L^o) <= L){
        cout << "left " << L - (L^o) << endl;
        L = L^o;
    }
    else if((R^o) <= R){
        cout << "right " << R - (R^o) << endl;
        R = R^o;
    }
    assert((U^D^L^R) == 0);
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); //cout.tie(nullptr);
    int r, c, k; cin >> r >> c >> k;
    
    while(k--){
        int a, b; cin >> a >> b;
        U = min(U, a-1);
        D = min(D, r-a);
        L = min(L, b-1);
        R = min(R, c-b);
    }

    

    if(U^D^L^R){
        JSH();
    }
    else{
        cout << "pass" << endl;
    }

    while(true){
        string q; cin >> q;
        if(q[0] == 'y') return 0;

        int n; cin >> n;

        if(q[0] == 'r'){
            R -= n;
        }
        else if(q[0] == 'l'){
            L -= n;
        }
        else if(q[0] == 't'){
            U -= n;
        }
        else if(q[0] == 'b'){
            D -= n;
        }
        JSH();
    }

    return 0;
}