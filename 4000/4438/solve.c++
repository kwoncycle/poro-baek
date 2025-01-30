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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    while(true){
        int n, w, h; cin >> n >> w >> h;
        if(n == 0 and w == 0 and h == 0) break;
        w*=2; h*=2;
        vector<pii> v(n);
        for(auto &[i,j]:v){
            cin >> i >> j;
            i *= 2; j *= 2;
        }
        pii O = {w/2, h/2};
        sort(all(v), [&](pii l, pii r){
            return (l>O) == (r>O) ? (l-O)/(r-O) > 0 : (l < r);
        });
        int truth = 0;
        int id1 = 0, id2 = 0, id3 = 0, id4 = 0;
        //for(auto [i,j]:v) cout << i << " " << j <<" p\n";
        for(; id1 < n; id1++){
            if(id2 < id1) id2 = id1;
            if(id3 < id1) id3 = id1;
            if(id4 < id1) id4 = id1;
            while(((v[id1]-O)/(v[(id2+1)%n]-O) > 0 or ((v[id1]-O)/(v[(id2+1)%n]-O) == 0 and (v[id1]-O)*(v[(id2+1)%n]-O)>0)) and (id2+1)%n != id1){
                id2 = (id2 + 1);
            }
            while(((v[id1]-O)/(v[(id3+1)%n]-O) >= 0) and (id3+1)%n != id1){
                id3 = (id3 + 1);
            }
            while(((v[id1]-O)/(v[(id4+1)%n]-O) == 0 and (v[id1]-O)*(v[(id4+1)%n]-O)>0) and (id4+1)%n != id1){
                id4 = (id4 + 1);
            }
            if(id3 - id1 + 1 >= n/2 and n/2 >= id2 - id1 + 1 - (id4 - id1 + 1)){
                truth = 1;
                break;
            }
            //cout << id1 << " " << " " << id2 << " " << id3 << "\n";
        }
        assert(truth);
        //cout << id1 << " " << id2 << " " << id3 << " " << id4 << "\n";
        while(n/2 > id2 - id1 + 1 - (id4 - id1 + 1) and id4 >= id1) id4--;
        while(n/2 > id2 - id1 + 1 - (id4 - id1 + 1)) id2++;
        for(int i=id4+1; i<=id2; i++) cout << v[i%n].X/2 << " " << v[i%n].Y/2 << "\n";
    }
    return 0;
}