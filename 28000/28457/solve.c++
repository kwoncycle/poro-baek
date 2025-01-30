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


ll n, s, w, g;
vector<array<ll, 3>> board; 
int loc = 0;


struct goldenkey{
    int idx;
    vector<array<int, 2>> deck;
    goldenkey(){}

    void get_input(){
        deck.resize(g);
        for(int i=0; i<g; i++) cin >> deck[i][0] >> deck[i][1];
    }

    array<int, 2> choose(){
        int i = idx; idx = (idx + 1) % g;
        return deck[i];
    }
} KEY;

struct dice{
    int sz, id;
    vector<array<int, 2>> v;
    dice(){ id = 0; };
    void get_input(){
        cin >> sz;
        v.resize(sz);
        for(int i=0; i<sz; i++) cin >> v[i][0] >> v[i][1];
    }
    array<int, 2> role(){
        if(id >= sz) return {-1, -1};
        int i = id; id += 1;
        return v[i];
    }
} DICE;

struct social{
    ll cur = 0;
    social(){};
    void donate(int i){
        cur += i;
    }
    ll take(){
        ll i = cur; cur = 0;
        return i;
    }
} SOCIAL;


int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> s >> w >> g;
    KEY.get_input();
    board.resize(n*4-4);
    for(int i=0; i<4*n-4; i++){
        if(i%(n-1) == 0) {
            board[i] = {0, -1, 1};
            continue;
        }
        char c; cin >> c;
        if(c == 'G'){
            board[i] = {c, -1, 1};
        }
        else{
            int p; cin >> p;
            board[i] = {c, p, 0}; // 0 무소유 1 소유
        }
    }
    DICE.get_input();

    string ans = "WIN";

    while(true){
        auto [n1, n2] = DICE.role();
        back:
        if(n1 < 0) break;
        for(int i=0; i<n1+n2; i++){
            loc++; if(loc >= 4*n-4) loc -= 4*n-4;
            if(loc == 0){
                s += w;
            }
        }
        if(loc % (n-1) == 0){
            if(loc == 0) continue;
            else if(loc == (n-1)){
                for(int i=0; i<3; i++){
                    auto [n1, n2] = DICE.role();
                    if(n1 < 0) goto outt;
                    if(n1 == n2){
                        break;
                    }
                }
            }
            else if(loc == (n-1)*2){
                s += SOCIAL.take();
            }
            else if(loc == (n-1)*3){
                loc = 0; s += w;
            }
        }

        else if(board[loc][0] == 'G'){
            auto [type, x] = KEY.choose();
            if(type == 1){
                s += x;
            }
            else if(type == 2){
                s -= x;
                if(s < 0){
                    cout << "LOSE\n"; return 0;
                }
            }
            else if(type == 3){
                s -= x;
                SOCIAL.donate(x);
                if(s < 0){
                    cout << "LOSE\n"; return 0;
                }
            }
            else{
                n1 = x, n2 = 0; goto back;
            }
        }

        else{
            if(board[loc][2] == 0 and board[loc][1] <= s){
                s -= board[loc][1];
                board[loc][2] = 1;
            }
        }
    }

    outt:
    for(int i=0; i<4*n-4; i++){
        if(board[i][2] == 0){
            cout << "LOSE\n"; return 0;
        }
    }
    cout << "WIN\n";
    return 0;
}