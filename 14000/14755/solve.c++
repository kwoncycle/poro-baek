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

const ll MOD = 998244353;
const ll A = 1557, Ai = 106428107;
const int MX = 200500;


string s;
int n;
int powA[MX], powAi[MX];
ll PH[MX], PHi[MX]; // prefix sum of hash
int far[MX], fari[MX];


void pre(){
    powA[0] = 1; powAi[0] = 1;
    for(int i=1; i<MX; i++){
        powA[i] = (ll)powA[i-1] * A % MOD;
        powAi[i] = (ll)powAi[i-1] * Ai % MOD;
    }
    for(int i=0; i<n; i++){
        PH[i] = ((i-1>=0 ? PH[i-1] : 0) + (ll)s[i]*powA[i]) % MOD;
        PHi[i] = ((i-1>=0 ? PHi[i-1] : 0) + (ll)s[i]*powAi[i]) % MOD;
    }
}

ll getH(int l, int r){
    ll o = PH[r] - (l-1>=0 ? PH[l-1] : 0);
    o = o * powAi[l] % MOD;
    if(o < 0) o += MOD;
    return o;
}
ll getHi(int l, int r){
    ll o = PHi[r] - (l-1>=0 ? PHi[l-1] : 0);
    o = o * powA[r] % MOD;
    if(o < 0) o += MOD;
    return o;
}

int reach[MX], reachi[MX];
vector<int> event_in[MX], event_out[MX];
bool isable(int t){
    memset(reach, -1, sizeof(reach));
    memset(reachi, -1, sizeof(reachi));
    for(int i=0; i<MX; i++) event_in[i].clear(), event_out[i].clear();

    for(int i=0; i<n; i++){
        if(far[i] >= t){
            int i1 = i-far[i]+1, i2 = i-t+1;
            event_in[i1].push_back(i);
            event_out[i2+1].push_back(i);
        }
    }
    set<int> st;
    for(int i=0; i<n; i++){
        for(int &j:event_in[i]) st.insert(j);
        for(int &j:event_out[i]) st.erase(j);
        if(!st.empty()){
            reach[i] = *st.begin() - i + 1;
        }
    }
    st.clear();
    for(int i=0; i<MX; i++) event_in[i].clear(), event_out[i].clear();

    for(int i=0; i<n; i++){
        if(fari[i] >= t){
            int i1 = i+fari[i]-1, i2 = i+t-1;
            event_in[i2].push_back(i);
            event_out[i1+1].push_back(i);
        }
    }
    for(int i=0; i<n; i++){
        for(int &j:event_in[i]) st.insert(j);
        for(int &j:event_out[i]) st.erase(j);
        if(!st.empty()){
            reachi[i] = i - *st.rbegin() + 1;
        }
    }

    for(int i=1; i<n-2; i++){
        if(reachi[i] == -1 or reach[i+1] == -1) continue;
        int ttl = reach[i+1] + reachi[i];
        if(ttl <= i+1 and ttl <= n-i-1) return true;
    }
    return false;
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> s;
    n = s.size();
    if(n < 4){
        cout << "-1\n"; return 0;
    }
    pre();

    for(int i=0; i<n; i++){
        if(s[i] != s[0]){
            far[i] = -1;
        }
        else{
            int st = 1, ed = i+2;
            while(st + 1 < ed){
                int md = (st + ed) / 2;
                if(getH(0, md-1) == getHi(i-md+1, i)) st = md;
                else ed = md;
            }
            far[i] = st;
        }

        if(s[i] != s[n-1]){
            fari[i] = -1;
        }
        else{
            int st = 1, ed = n-i+1;
            while(st + 1 < ed){
                int md = (st + ed) / 2;
                if(getH(i, i+md-1) == getHi(n-md, n-1)) st = md;
                else ed = md;
            }
            fari[i] = st;
        }
    }

    if(!isable(1)){
        cout << "-1\n"; return 0;
    }
    int st = 1, ed = n;
    while(st + 1 < ed){
        int md =  (st + ed) / 2;
        if(isable(md)) st = md;
        else ed = md;
    }
    cout << st << "\n";

    return 0;
}