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

string s[104];
int chk[104][104];
vector<pii> ans;

vector<pii> dir = {{0,0}, {0,-1}, {-1,0}, {-1,-1}};

void DFS(int x, int y, pii st, int turn){
    vector<pii> order;
    order.push_back(st);
    order.push_back(pii(2*x+1-st.X, 2*y+1-st.Y));
    order.push_back(pii(2*x+1-st.X, st.Y));
    order.push_back(pii(st.X, 2*y+1-st.Y));
    if(turn){
        reverse(all(order));
        rotate(order.begin(), order.begin() + 3, order.end());
    }
    assert(order[0] == st);

    for(auto &p:order){
        for(auto &[dx, dy]:dir){
            if(!chk[p.X + dx][p.Y + dy] and s[p.X + dx][p.Y + dy] == 'X'){
                chk[p.X + dx][p.Y + dy] = 1;
                DFS(p.X + dx, p.Y + dy, p, turn);
            }
        }
        ans.push_back(p);
        turn = 1 - turn;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int w, h; cin >> w >> h;
    for(int i=1; i<=h; i++) {
        cin >> s[i];
        s[i] = '.' + s[i] + '.';
    }
    s[0] = string(w+2, '.');
    s[h+1] = string(w+2, '.');

    for(int i=1; i<=h; i++){
        for(int j=1; j<=w; j++){
            if(!chk[i][j] and s[i][j] == 'X'){
                chk[i][j] = 1;
                DFS(i, j, {i, j}, 0);
            }
        }
    }

    cout << ans.size() - 1 << "\n";
    for(auto [x,y]:ans) cout << y-1 << " " << x-1 << "\n";

    for(int i=0; i<ans.size()-1; i++){
        if(i%2 == 0){
            assert(abs(ans[i].X-ans[i+1].X) == 1 and abs(ans[i].Y - ans[i+1].Y) == 1);
        }
        else{
            assert(abs(ans[i].X-ans[i+1].X) + abs(ans[i].Y - ans[i+1].Y) == 1);
        }
    }


    return 0;
}