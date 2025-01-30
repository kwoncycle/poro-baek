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

int n;
string s;

#define MOD 29069759534131ll
//#define MOD 998244353ll
#define A 15571557ll
#define Ai 17307477624892ll
//#define Ai 449375313ll

ll powA[1000005], powAi[1000005];
ll hashsm[1000005];
ll gethash(ll i, ll j){
    //cout << hashsm[j] << "j\n";
    //cout << powAi[i] << "powAi\n";
    ll o = (__int128)((hashsm[j] - (i-1>=0 ? hashsm[i-1] : 0)))*powAi[i]%MOD;
    //cout << o << "\n";
    if(o < 0) o += MOD;
    return o;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    powA[0] = 1, powAi[0] = 1;
    for(int i=1; i<=1000000; i++){
        powA[i] = (__int128)powA[i-1] * A % MOD;
        powAi[i] = (__int128)powAi[i-1] * Ai % MOD;
    }

    assert((__int128)powA[144444]*powAi[144444]%MOD == 1);

    cin >> s;
    n = s.size();
    if(n == 1){
        cout << "1\n"; return 0;
    }
    for(int i=0; i<n; i++){
        hashsm[i] = (__int128)((__int128)(i-1>=0 ? hashsm[i-1] : 0) + (__int128)powA[i] * (__int128)s[i]) % MOD;
    }

    //for(int i=0; i<n; i++) cout << gethash(i,i) << "hash\n";
    //cout << gethash(0,0) << " " << gethash(5,5) << "ahn\n";

    ll cnt = 0;
    int id = 0;
    while(id <= (n-1)/2){
        //cout << id << "\n";
        int truth = 0;
        int id1 = -1;
        for(int i=id; i<=(n-2)/2; i++){
            if(gethash(id, i) == gethash(n-1-i, n-1-id)){
                id1 = i;
                truth = 1; break;
            }
        }
        if(truth){
            cnt += 2;
            id = id1 + 1;
        }
        else{
            cnt++; break;
        }
    }

    cout << cnt << "\n";


    return 0;
}