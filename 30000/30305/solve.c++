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

string v[104];

string U[104];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    for(int i=0; i<n; i++) cin >> v[i];

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) v[i][j] = '#' + '.' - v[i][j];
    }

    int truth = 1;
    for(int i=0; i<n-1; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == '#' and v[i+1][j] == '.') truth = 0;
        }
    }
    if(truth){
        cout << n << " " << m << "\n";
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++) cout << v[i][j];
            cout << '\n';
        }
        return 0;
    }

    truth = 1;
    for(int i=0; i<n-1; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == '.' and v[i+1][j] == '#') truth = 0;
        }
    }
    if(truth){
        cout << n << " " << m << "\n";
        for(int i=n-1; i>=0; i--){
            for(int j=m-1; j>=0; j--) cout << v[i][j];
            cout << "\n";
        }
        return 0;
    }

    truth = 1;
    for(int i=0; i<n; i++){
        for(int j=0; j<m-1; j++){
            if(v[i][j] == '.' and v[i][j+1] == '#') truth = 0;
        }
    }
    if(truth){
        cout << m << " " << n << "\n";
        for(int j=m-1; j>=0; j--){
            for(int i=0; i<n; i++) cout << v[i][j];
            cout << "\n";
        }
        return 0;
    }

    truth = 1;
    for(int i=0; i<n; i++){
        for(int j=0; j<m-1; j++){
            if(v[i][j] == '#' and v[i][j+1] == '.') truth = 0;
        }
    }
    if(truth){
        cout << m << " " << n << "\n";
        for(int j=0; j<m; j++){
            for(int i=n-1; i>=0; i--) cout << v[i][j];
            cout << "\n";
        }
        return 0;
    }

    cout << "impossible\n";

    return 0;
}