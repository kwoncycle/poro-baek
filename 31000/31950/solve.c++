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

string F2;
const ll MOD = 998244353;
struct solve{
    string s;
    solve(){
        cin >> s;
        for(int i=0; i+s.size()-1 < (int)F2.size(); i++){
            int truth = 1;
            for(int j=0; j<s.size(); j++){
                if(s[j] != '?' and s[j] != F2[j+i]){
                    truth = 0; break;
                }
            }
            if(truth){
                cout << i+1 << "\n"; return;
            }
        }

        __int128 ans = 0x3f3f3f3f3f3f3f3fll; ans = ans*ans;
        __int128 origin = ans;

        for(int d=4; d<=26; d++){ // len of first one
            if(ans != origin) break;
            for(int blank=0; blank<d; blank++){
                for(int cnt=1; cnt<=10; cnt++){
                    string G0 = string(blank, '?') + s;
                    if(cnt*d - d >= G0.size()) break;
                    while(G0.size() < cnt*d) G0.push_back('?');
                    int u = G0.size() - cnt*d;
                    u = (-u) % (d+1);
                    if(u < 0) u += d+1;
                    G0 = G0 + string(u, '?');
                    vector<string> G;
                    int valid = 1;
                    for(int i=0; i<cnt; i++) {
                        if(G0[i*d] == '0') valid = 0;
                        G.push_back(string(1, '0') + G0.substr(i*d, d));
                    }
                    char turn = '?';
                    for(int i=cnt*d; i<G0.size(); i+=d+1) {
                        turn = '1';
                        string s = G0.substr(i, d+1);
                        if(s[0] != '?' and s[0] != '1') valid = 0;
                        s[0] = '1';
                        G.push_back(s);
                    }

                    if(!valid) continue;
                    while(G.size() < 11){
                        G.push_back(string(d+1, '?'));
                    }
                    int Gsz = 11;
                    for(int turn=0; turn<Gsz-1; turn++){
                        for(int ch=0; ch<=d-1; ch++){ // 0..ch-1 no change, ch...d-1 one change, d all change
                            int truth = 1;
                            string start(d+1, '?');
                            for(int i=0; i<=ch-1; i++){
                                char c = '?';
                                for(int j=0; j<Gsz; j++){
                                    if(G[j][i] == '?') continue;
                                    if(c == '?') c = G[j][i];
                                    else{
                                        if(c != G[j][i]){
                                            truth = 0; goto getout;
                                        }
                                    }
                                }
                                if(c == '?') {
                                    if(i != 1) c = '0';
                                    else c = '1';
                                }
                                start[i] = c;
                            }

                            for(int i=ch; i<=ch; i++){ // c0 .. 0...8
                                char c0 = '?', c1 = '?';
                                for(int j=0; j<=turn; j++){
                                    if(G[j][i] == '?') continue;
                                    if(c0 == '?') c0 = G[j][i];
                                    else{
                                        if(c0 != G[j][i]){
                                            truth = 0; goto getout;
                                        }
                                    }
                                }
                                for(int j=turn+1; j<Gsz; j++){
                                    if(G[j][i] == '?') continue;
                                    if(c1 == '?') c1 = G[j][i];
                                    else{
                                        if(c1 != G[j][i]){
                                            truth = 0; goto getout;
                                        }
                                    }
                                }
                                if(c0 != '?' and c1 != '?'){
                                    if(((c0-'0') + 1) % 10 + '0' != c1){
                                        truth = 0; goto getout;
                                    }
                                }
                                if(c0 == '?'){
                                    if(c1 == '?'){
                                        if(i != 1) c0 = '0';
                                        else c0 = '1';
                                    }
                                    else c0 = '0' + (c1-'0'+9)%10;
                                }
                                if(c0 == '9'){
                                    truth = 0; goto getout;
                                }
                                start[i] = c0;
                            }

                            for(int i=ch+1; i<=d-1; i++){ // shoule be all 9
                                char c0 = '9', c1 = '0';
                                for(int j=0; j<=turn; j++){
                                    if(G[j][i] == '?') continue;
                                    if(c0 == '?') c0 = G[j][i];
                                    else{
                                        if(c0 != G[j][i]){
                                            truth = 0; goto getout;
                                        }
                                    }
                                }
                                for(int j=turn+1; j<Gsz; j++){
                                    if(G[j][i] == '?') continue;
                                    if(c1 == '?') c1 = G[j][i];
                                    else{
                                        if(c1 != G[j][i]){
                                            truth = 0; goto getout;
                                        }
                                    }
                                }
                                if(c0 != '?' and c1 != '?'){
                                    if(((c0-'0') + 1) % 10 + '0' != c1){
                                        truth = 0; goto getout;
                                    }
                                }
                                start[i] = c0;
                            }

                            for(int i=d; i<=d; i++){ // increase
                                char c0 = '0' + 9 - turn;
                                for(int j=0; j<Gsz; j++){
                                    if(G[j][i] == '?') continue;
                                    if((c0-'0'+j)%10 + '0' != G[j][i]){
                                        truth = 0; goto getout;
                                    }
                                }
                                start[i] = c0;
                            }

                            getout:
                            if(start[1] == '0') truth = 0;
                            if(truth){
                                __int128 A = 0;
                                for(char c:start){
                                    A *= 10;
                                    A += c-'0';
                                }
                                // if(A == 813097){
                                // cout << start << " st\n";
                                // cout << d << " " << turn << " " << ch << "\n";
                                // for(string s:G) cout << s << '\n';
                                // //return;
                                // }
                                ans = min(ans, convert(A-1) + blank + 1);
                            }
                        }
                    }
                }
            }
        }
        ans %= MOD;
        cout << (ll)ans << "\n";
    }
    __int128 convert(__int128 A){
        __int128 u = 1, d = 1;
        __int128 ans = 0;
        while(u*10 - 1 <= A){
            ans = (ans + u*9*d);
            u *= 10; d++;
        }
        ans = ans + (A-u+1)*d;
        return ans;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    for(int i=1; i<=1119; i++){
        string s;
        int i1 = i;
        while(i1){
            s.push_back('0' + i1%10);
            i1 /= 10;
        }
        reverse(all(s)); 
        F2 = F2 + s;
    }

    int tt; cin >> tt;
    while(tt--){
        solve S;
    }
    return 0;
}