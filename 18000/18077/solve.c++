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
    int n, m; cin >> n >> m;
    vector<string> v(n);
    for(int i=0; i<n; i++) cin >> v[i];

    pii A;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == 'A'){
                A = {i, j}; break;
            }
        }
    }

    vector<pii> UDrange(n);
    for(int i=0; i<n; i++){
        int i1 = A.Y, i2 = A.Y;
        if(v[i][i1] != 'A' and v[i][i1] != '.'){
            UDrange[i] = {1557, -1557};
            continue;
        }
        while(i1 >= 0 and v[i][i1] == '.' or v[i][i1] == 'A') i1--; i1++;
        while(i2 < m and v[i][i2] == '.' or v[i][i2] == 'A') i2++; i2--;
        UDrange[i] = {i1, i2};
    }

    for(int i=A.X+1; i<n; i++){
        UDrange[i] = {max(UDrange[i].X, UDrange[i-1].X), min(UDrange[i].Y, UDrange[i-1].Y)};
    }

    for(int i=A.X-1; i>=0; i--){
        UDrange[i] = {max(UDrange[i].X, UDrange[i+1].X), min(UDrange[i].Y, UDrange[i+1].Y)};
    }

    ll mx = 0;
    pii l, r;
    for(int i=0; i<=A.X; i++){
        for(int j=A.X; j<n; j++){
            pii rng = {max(UDrange[i].X, UDrange[j].X), min(UDrange[i].Y, UDrange[j].Y)};
            if(rng.X > rng.Y) continue;
            pii l1 = {i, rng.X}, r1 = {j, rng.Y};
            ll A = (j-i+1)*(rng.Y-rng.X+1);
            if(A > mx) mx = A, l = l1, r = r1;
        }
    }

    for(int i=l.X; i<=r.X; i++){
        for(int j=l.Y; j<=r.Y; j++){
            assert(v[i][j] == '.' or v[i][j] == 'A');
            if(v[i][j] != 'A') v[i][j] = 'a';
        }
    }
    
    for(int i=l.X; i<=r.X; i++){
        for(int j=1; j<l.Y; j++){
            if(v[i][j] == '.'){
                if(v[i][j-1] == '.') continue;
                if('a' <= v[i][j-1] and v[i][j-1] <= 'z') v[i][j] = v[i][j-1];
                else if('A' <= v[i][j-1] and v[i][j-1] <= 'Z') v[i][j] = v[i][j-1] - 'A' + 'a';
            }
        }
        for(int j=r.Y+2; j<m; j++){
            if(v[i][j] == '.'){
                if(v[i][j-1] == '.') continue;
                if('a' <= v[i][j-1] and v[i][j-1] <= 'z') v[i][j] = v[i][j-1];
                else if('A' <= v[i][j-1] and v[i][j-1] <= 'Z') v[i][j] = v[i][j-1] - 'A' + 'a';
            }
        }
        for(int j=l.Y - 2; j>=0; j--){
            if(v[i][j] == '.'){
                if(v[i][j+1] == '.') continue;
                if('a' <= v[i][j+1] and v[i][j+1] <= 'z') v[i][j] = v[i][j+1];
                else if('A' <= v[i][j+1] and v[i][j+1] <= 'Z') v[i][j] = v[i][j+1] - 'A' + 'a';
            }
        }
        for(int j=m-2; j>=r.Y+1; j--){
            if(v[i][j] == '.'){
                if(v[i][j+1] == '.') continue;
                if('a' <= v[i][j+1] and v[i][j+1] <= 'z') v[i][j] = v[i][j+1];
                else if('A' <= v[i][j+1] and v[i][j+1] <= 'Z') v[i][j] = v[i][j+1] - 'A' + 'a';
            }
        }
    }

    for(int i=l.X+1; i<=r.X; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == '.'){
                if(v[i-1][j] == '.') continue;
                if('a' <= v[i-1][j] and v[i-1][j] <= 'z') v[i][j] = v[i-1][j];
                else if('A' <= v[i-1][j] and v[i-1][j] <= 'Z') v[i][j] = v[i-1][j] - 'A' + 'a';
            }
        }
    }
    for(int i=r.X-1; i>=l.X; i--){
        for(int j=0; j<m; j++){
            if(v[i][j] == '.'){
                if(v[i+1][j] == '.') continue;
                if('a' <= v[i+1][j] and v[i+1][j] <= 'z') v[i][j] = v[i+1][j];
                else if('A' <= v[i+1][j] and v[i+1][j] <= 'Z') v[i][j] = v[i+1][j] - 'A' + 'a';
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=1; j<m; j++){
            if(v[i][j] == '.'){
                if(v[i][j-1] == '.') continue;
                if('a' <= v[i][j-1] and v[i][j-1] <= 'z') v[i][j] = v[i][j-1];
                else if('A' <= v[i][j-1] and v[i][j-1] <= 'Z') v[i][j] = v[i][j-1] - 'A' + 'a';
            }
        }
        for(int j=m-2; j>=0; j--){
            if(v[i][j] == '.'){
                if(v[i][j+1] == '.') continue;
                if('a' <= v[i][j+1] and v[i][j+1] <= 'z') v[i][j] = v[i][j+1];
                else if('A' <= v[i][j+1] and v[i][j+1] <= 'Z') v[i][j] = v[i][j+1] - 'A' + 'a';
            }
        }
    }

    for(int i=1; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == '.'){
                if(v[i-1][j] == '.') continue;
                if('a' <= v[i-1][j] and v[i-1][j] <= 'z') v[i][j] = v[i-1][j];
                else if('A' <= v[i-1][j] and v[i-1][j] <= 'Z') v[i][j] = v[i-1][j] - 'A' + 'a';
            }
        }
    }

    for(int i=n-2; i>=0; i--){
        for(int j=0; j<m; j++){
            if(v[i][j] == '.'){
                if(v[i+1][j] == '.') continue;
                if('a' <= v[i+1][j] and v[i+1][j] <= 'z') v[i][j] = v[i+1][j];
                else if('A' <= v[i+1][j] and v[i+1][j] <= 'Z') v[i][j] = v[i+1][j] - 'A' + 'a';
            }
        }
    }

    for(int i=0; i<n; i++) cout << v[i] << "\n";

    return 0;
}