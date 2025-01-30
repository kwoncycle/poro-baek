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

vector<int> drr = {1,0,0,1,0};
vector<int> A(25);
int route[5];
ll ans = 0;

int r, c;


void JG(int id){
    if(id == 5){
        for(int i=0; i<5; i++){
            if(A[route[i]] != drr[i]) return;
        }
        int i1=route[0]/5, i2=route[0]/5, j1=route[0]%5, j2=route[0]%5;
        pii cur = {route[0]/5, route[0]%5};
        for(int i=1; i<5; i++){
            int b1 = route[i]/5, b2 = route[i]%5;
            if(abs(b1 - cur.X) > 1){
                if(b1 < cur.X) b1 += 5;
                else b1 -= 5;
            }
            if(abs(b2 - cur.Y) > 1){
                if(b2 < cur.Y) b2 += 5;
                else b2 -= 5;
            }
            i1 = min(i1, b1);
            i2 = max(i2, b1);
            j1 = min(j1, b2);
            j2 = max(j2, b2);
            cur = {b1, b2};
        }

        if(i1 < 0) i1 += 5, i2 += 5;
        if(j1 < 0) j1 += 5, j2 += 5;
        
        int r1 = (r+4)/5, c1 = (c+4)/5;
        while((r1-1)*5 + i2 > r-1) r1--;
        while((c1-1)*5 + j2 > c-1) c1--;
        r1 = max(r1, 0);
        c1 = max(c1, 0);
        //if(r1*c1){
        //for(int i=0; i<5; i++) cout << route[i] << " ";
        //cout << " -> " << i1 << " " << i2 << " " << j1 << " " << j2 << "\n";
        //cout << r1 << " " << c1 << "\n";}
        ans += r1*c1;
        return;
    }
    for(int i=0; i<25; i++){
        if(id){
            int b1 = route[id-1]/5, b2 = route[id-1]%5;
            int i1 = i/5, i2 = i%5;

            if(route[id-1] == i) continue;
            int truth = 0;
            if(i1 == b1 and ((i2-b2+5)%5 == 1 or (i2-b2+5)%5 == 4)) truth = 1;
            if(i2 == b2 and ((i1-b1+5)%5 == 1 or (i1-b1+5)%5 == 4)) truth = 1;
            for(int j=0; j<id; j++) if(route[j] == i) truth = 0;
            if(truth){
                route[id] = i;
                JG(id+1);
            }
        }
        else{
            route[id] = i;
            JG(id+1);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> r >> c;

    c += 5;
    vector<int> v[5];
    for(int i=0; i<5; i++){
        v[i].resize(c);
    }
    
    int id = 0;
    for(int i=0; i<5; i++){
        for(int j=0; j<c; j++){
            v[i][j] = drr[id]; 
            id = (id + 1) % 5;
        }
    }

    c -= 5;

    id = 0;
    
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            A[id] = v[i][j]; id++;
        }
    }

    JG(0);
    cout << ans << "\n";
    return 0;
}