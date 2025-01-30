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

int p[1000001];
int nxt[1000001];
int chk[1000001];
int cnt(int i){
    if(i == 0) return 0;
    if(i == 1) return 1;
    int cntt = 1;
    while(i > 1){
        int o = p[i];
        int u = 1;
        while(i%o == 0) i /= o, u++;
        cntt *= u;
    }
    return cntt;
}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    p[1] = 1;
    for(int i=2; i<=1000000; i++){
        if(p[i] == 0){
            for(int j=i; j<=1000000; j+=i){
                p[j] = i;
            }
        }
    }
    
    int n, k; cin >> n >> k;
    
    for(int i=0; i<n; i++) nxt[i] = (i + cnt(i)) % n;
    for(int i=0; i<n; i++){
        if(chk[i] == 0){
            int i1 = i;
            vector<int> v;
            while(chk[i1] == 0){
                chk[i1] = -1;
                v.push_back(i1);
                i1 = nxt[i1];
            }
            if(chk[i1] == -1){
                int i2 = i1;
                int cnt = 0;
                while(nxt[i2] != i1){
                    i2 = nxt[i2]; cnt++;
                }
                cnt++;
                i2 = i1;
                while(nxt[i2] != i1){
                    chk[i2] = cnt;
                    i2 = nxt[i2];
                }
                chk[i2] = cnt;
            }
            while(!v.empty() and chk[v.back()] != -1) v.pop_back();
            reverse(v.begin(), v.end());
            for(int j=0; j<(int)v.size(); j++) chk[v[j]] = chk[i1] + j + 1;
            
        }
    }
    ll U = 0x3f3f3f3f3f3f3f3fll;
    vector<ll> val(n, U);
    vector<int> p(n);
    for(int i=0; i<n; i++) p[i] = i;
    sort(p.begin(), p.end(), [&](int l, int r){
        return chk[l] > chk[r];
    });
    for(int i:p){
        if(val[i] == U and chk[i] >= k){
            int i1 = i;
            ll o = 0;
            for(int j=0; j<k; j++){
                o += i1;
                i1 = nxt[i1];
            }
            val[i] = o;
            int st = i, ed = i1;
            while(true){
                o -= st; o += ed;
                st = nxt[st], ed = nxt[ed];
                
                if(val[st] != U or chk[st] < k) break;
                val[st] = o;
            }
        }
    }

    int st = 0;
    for(int i=0; i<n; i++){
        if(val[i] < val[st]) st = i;
    }

    //for(int i=0; i<n; i++) cout << nxt[i] << " "; cout << " nxt\n";
    //for(int i=0; i<n; i++) cout << chk[i] << " "; cout << " chk\n";
    //for(int i=0; i<n; i++) cout << val[i] << " "; cout << " chk\n";

    for(int i=0; i<n; i++){
        if(chk[i] >= k){
            int i1 = i;
            ll sm = 0;
            for(int j=0; j<k; j++){
                sm += i1;
                i1 = nxt[i1];
            }
        }
    }

    if(val[st] == U) cout << "-1\n";
    else{
        for(int i=0; i<k; i++){
            cout << st << " ";
            st = nxt[st];
        }
        cout << "\n";
    }

    //for(int i=0; i<=1)

    return 0;
}