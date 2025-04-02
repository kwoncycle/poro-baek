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

int DP[1500001][9];
int val[3] = {1, 100, 10000};

int id1(int i,int j,int k){
    return val[0]*i + val[1]*j + val[2]*k;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s; cin >> s;
    if(s.size() == 1){
        cout << s << "\n"; return 0;
    }
    int a=0, b=0, c=0;
    for(auto i:s){
        if(i == 'A') a++;
        else if(i == 'B') b++;
        else c++;
    }

    for(int i=0; i<=2; i++){
        for(int j=0; j<=2; j++){
            if(i and i==j) continue;
            DP[val[i]+val[j]][i+j*3] = 1;
        }
    }

    for(int i=0; i<=50; i++){
        for(int j=0; j<=50; j++){
            for(int k=0; k<=50; k++){
                if(i+j+k > 2){
                    if(i){
                        for(int t=0; t<9; t++){
                            if(DP[id1(i-1,j,k)][t]) DP[id1(i,j,k)][t/3+0*3] = 1;
                        }
                    }
                    if(j){
                        for(int t=0; t<9; t++){
                            //cout << t << i << j << k << "\n";
                            if(DP[id1(i,j-1,k)][t] and t/3 != 1) DP[id1(i,j,k)][t/3+1*3] = 1;
                        }
                    }
                    if(k){
                        for(int t=0; t<9; t++){
                            if(DP[id1(i,j,k-1)][t] and t%3 != 2 and t/3 != 2) DP[id1(i,j,k)][t/3+2*3] = 1;
                        }
                    }
                }
            }
        }
    }



    int id = -1;
    for(int i=0; i<9; i++){
        if(DP[id1(a,b,c)][i]) id = i;
    }
    if(id == -1){
        cout << "-1\n"; return 0;
    }

    string ans;
    while(a+b+c > 1){
        //cout << a << " " << b << " " << c << " " << id << "\n";
        ans.push_back('A' + id/3);
        if(a and id/3 == 0) a--;
        else if(b and id/3 == 1) b--;
        else if(c and id/3 == 2) c--;
        id = id % 3;
        for(int i=0; i<9; i++){
            if(DP[id1(a,b,c)][i] and i/3 == id) {
                id = i; break;
            }
        }
    }
    if(a) ans.push_back('A');
    if(b) ans.push_back('B');
    if(c) ans.push_back('C');
    reverse(all(ans));
    cout << ans << "\n";

    for(int i=0; i<=50; i++){
        for(int j=0; j<=50; j++){
            for(int k=0; k<=50; k++){

            }
        }
    }

    return 0;
}