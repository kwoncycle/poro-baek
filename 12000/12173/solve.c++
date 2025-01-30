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
    int tt; cin >> tt;
    for(int tc=1; tc<=tt; tc++){

        int x, r, c; cin >> x >> r >> c;
        if(r > c) swap(r, c);
        cout << "Case #" << tc << ": ";
        if(x >= r*2+1 or x >= c*2+1){
            cout << "RICHARD\n";
            continue;
        }
        if(x > r and x > c){
            cout << "RICHARD\n";
            continue;
        }
        if(r*c%x != 0){
            cout << "RICHARD\n";
            continue;
        }
        if(x >= 7){
            cout << "RICHARD\n";
            continue;
        }

        if(x <= 3){
            cout << "GABRIEL\n";
            continue;
        }

        if(x == 4){
            if(r <= 2 or c <= 2){
                cout << "RICHARD\n";
            }
            else cout << "GABRIEL\n";
        }

        else if(x == 5){
            if(r + c == 8) cout << "RICHARD\n";
            else cout << "GABRIEL\n";
        }

        else{
            if(r <= 3) cout << "RICHARD\n";
            else {
                cout << "GABRIEL\n";
            }
        }

        //cout << "GABRIEL\n";
        // 4 5 6

    }
    return 0;
}