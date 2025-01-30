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
    ll v[11][11][11], v1[11][11][11];
    v[1][1][1] = 1; v1[1][1][1] = 1;
    for(int i=1; i<=10; i++){
        for(int j=1; j<=10; j++){
            for(int k=1; k<=10; k++){
                if(i==1 and j==1 and k==1) continue;
                if(i<=j and j<=k){
                    v[i][j][k] = v[i-1][j][k] + v[i][j-1][k] + v[i][j][k-1];
                }
                else v[i][j][k] = 0;
            }
        }
    }
    for(int i=1; i<=10; i++){
        for(int j=1; j<=10; j++){
            for(int k=1; k<=10; k++){
                if(i==1 and j==1 and k==1) continue;
                v1[i][j][k] = v1[i-1][j][k] + v1[i][j-1][k] + v1[i][j][k-1];
            }
        }
    }

    for(int i=1; i<=10; i++){
        for(int j=1; j<=10; j++){
            cout << v[1][i][j] << " ";
        }
        cout << '\n';
    }
    cout << "===================\n";
    for(int i=1; i<=10; i++){
        for(int j=1; j<=10; j++){
            cout << v[2][i][j] << " ";
        }
        cout << '\n';
    }
    cout << "===================\n";
    for(int i=1; i<=10; i++){
        for(int j=1; j<=10; j++){
            cout << v[3][i][j] << " ";
        }
        cout << '\n';
    }
    cout << "===================\n";
    for(int i=1; i<=10; i++){
        for(int j=1; j<=10; j++){
            cout << v1[1][i][j] << " ";
        }
        cout << '\n';
    }
    cout << "===================\n";
    for(int i=1; i<=10; i++){
        for(int j=1; j<=10; j++){
            cout << v1[2][i][j] << " ";
        }
        cout << '\n';
    }
    cout << "===================\n";
    for(int i=1; i<=10; i++){
        for(int j=1; j<=10; j++){
            cout << v1[3][i][j] << " ";
        }
        cout << '\n';
    }

    cout << "===================\n";
    for(int i=1; i<=10; i++){
        for(int j=1; j<=10; j++){
            cout << v1[1][i][j]-v[1][i][j] << " ";
        }
        cout << '\n';
    }
    cout << "===================\n";
    for(int i=1; i<=10; i++){
        for(int j=1; j<=10; j++){
            cout << v1[2][i][j]-v[2][i][j] << " ";
        }
        cout << '\n';
    }
    cout << "===================\n";
    for(int i=1; i<=10; i++){
        for(int j=1; j<=10; j++){
            cout << v1[3][i][j]-v[3][i][j] << " ";
        }
        cout << '\n';
    }
    return 0;
}