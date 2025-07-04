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

// bool isin(string &s1, string &s2){ // is s2 \in s1?
//     if(s2.size() > s1.size()) return false;
//     int n1 = s1.size(), n2 = s2.size();
//     for(int i=0; i+n2-1 < n1; i++){
//         int truth = 1;
//         for(int j=i; j<i+n2; j++){
//             if(s1[j] != s2[j-i]){
//                 truth = 0; break;
//             }
//         }
//         if(truth) return true;
//     }
//     return false;
// }

bool isin(string &s, string &t) {
    int n=s.size(),m=t.size();
    vector<int>pi(m,0);
    for(int i=1,j=0;i<m;i++) {
    while(j>0&&t[i]!=t[j]) j = pi[j-1];
        if(t[i]==t[j]) pi[i]=++j;
    }
    vector<int>ret; // s[ret]==t[0]
    for(int i=0,j=0;i<n;i++) {
        while(j>0&&s[i]!=t[j]) j=pi[j-1];
        if(s[i]==t[j]) j++;
    if(j==m) return true; // ret.push_back(i-m+1), j=pi[j-1];
    }
    return false;
    //return ret;
}


ll n, q;
vector<string> v;

bool isend(string &s1, string &s2){ // is ....s2 == s1?
    if(s2.size() > s1.size()) return false;
    for(int i=0; i<s2.size(); i++){
        if(s2[s2.size()-1-i] != s1[s1.size()-1-i]) return false;
    }
    return true;
}

unordered_set<string> st;

bool issafe(string &s1){
    if(st.find(s1) == st.end()) return true;
    return false;
}

const ll MOD = 1000000007;
typedef vector<vector<ll>> vvl;
void mul(vvl &A, vvl &B, vvl &ans){
    int o = A.size();
    for(int i=0; i<o; i++){
        for(int j=0; j<o; j++){
            ans[i][j] = 0;
        }
    }
    for(int i=0; i<o; i++){
        for(int j=0; j<o; j++){
            for(int k=0; k<o; k++){
                ans[i][j] = (ans[i][j] + A[i][k]*B[k][j]) % MOD;
            }
        }
    }
}

void poww(vvl &A, ll e, vvl &ans){
    int o = A.size();
    vvl C = ans;
    for(int i=0; i<o; i++){
        for(int j=0; j<o; j++){
            ans[i][j] = 0;
        }
        ans[i][i] = 1;
    }
    while(e){
        if(e&1){
            mul(A, ans, C);
            ans = C;
        }
        mul(A, A, C);
        A = C;
        e >>= 1;
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> q;
    v.resize(q);
    for(int i=0; i<q; i++){
        int o; cin >> o;
        cin >> v[i];
    }
    sort(all(v), [&](string s1, string s2){
        return s1.size() < s2.size();
    });
    vector<string> v1;
    for(auto &s:v){
        int truth = 1;
        for(auto &s1:v1){
            if(isin(s, s1)) {
                truth = 0; break;
            }
        }
        if(truth) v1.push_back(s);
    }
    v = v1;

    for(auto &s:v){
        st.insert(s);
    }

    vector<string> state;
    vector<int> banned(26);
    for(auto &s:v){
        int o = s.size();
        if(o == 1) banned[s[0]-'a'] = 1;
        for(int i=2; i<o; i++){
            state.push_back(s.substr(0, i));
            state.push_back(s.substr(o-i, i));
        }
    }
    sort(all(state));
    state.erase(unique(all(state)), state.end());

    for(int i=0; i<26; i++) state.push_back(string(1, 'a'+i));
    map<string, int> mp;
    for(int i=0; i<(int)state.size(); i++) mp[state[i]] = i;
    vector<vector<ll>> MT(state.size(), vector<ll>(state.size(), 0));
    for(int i=0; i<(int)state.size(); i++){
        if(state[i].size() > 1){
            string u = state[i].substr(0, state[i].size() - 1);
            MT[i][mp[u]] = 1;
            for(int j=0; j<(int)state.size(); j++){
                if(isend(state[j], u)){
                    state[j].push_back(state[i].back());
                    if(!issafe(state[j])){
                        MT[i][j] = (MT[i][j] + MOD - 1) % MOD;
                    }
                    state[j].pop_back();
                }
            }
        }
        else{
            if(!banned[state[i][0]-'a']){
                for(int j=state.size()-26; j<=state.size()-1; j++){
                    MT[i][j] = 1;
                }
                for(int j=0; j<(int)state.size(); j++){
                    state[j].push_back(state[i].back());
                    if(!issafe(state[j])){
                        MT[i][j] = (MT[i][j] + MOD - 1) % MOD;
                    }
                    state[j].pop_back();
                }
            }
        }
    }

    vector<vector<ll>> ans(state.size(), vector<ll>(state.size(), 0));
    //for(auto s:state) cout << s << "\n";
    poww(MT, n-1, ans);

    ll ttl = 0;
    for(int i=state.size()-26; i<state.size(); i++){
        for(int j=state.size()-26; j<state.size(); j++){
            if(!banned[j - (state.size()-26)]){
                ttl = (ttl + ans[i][j]) % MOD;
            }
        }
    }
    cout << ttl << "\n";

    return 0;
}