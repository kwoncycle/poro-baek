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

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    if(m >= 2*n-3){
        cout << "0" << endl;
        for(int i=1; i<=(1<<n)-1; i++){
            string s;
            for(int j=0; j<n; j++){
                if((i>>j)&1) s.push_back('1');
                else s.push_back('0');
            }
            reverse(all(s));
            for(int j=0; j<n; j++){
                if(s[j] == '0'){
                    if(s[(j+1)%n] == '1') ;
                    else s[j] = '2';
                }
            }
            cout << s << endl;
        }
        return 0;
    }
    else{
        cout << "1" << endl;
        string v[30], ans[30];
        for(int i=0; i<n; i++){
            string s;
            for(int j=0; j<n; j++){
                if(((1<<i)>>j)&1) s.push_back('1');
                else s.push_back('0');
            }
            reverse(all(s));
            cout << "? " << s << endl;
            cin >> v[i];
            ans[i] = s;
        }
        for(int i=0; i<n; i++){
            vector<int> T;
            for(int j=0; j<n; j++){
                if(v[j][i] == '0') T.push_back(j);
            }
            if(T.size() >= 2){
                int i0 = T[0], i1 = T[1];
                string s0 = ans[i0], s1 = ans[i1], s2 = string(n, '0');
                for(int i=0; i<n; i++){
                    if(s0[i] != '1' and s1[i] != '1'){
                        s2[i] = '1';
                    }
                    else s2[i] = '0';
                }
                cout << "! " << s0 << " " << s1 << " " << s2 << endl;
                return 0;
            }
        }

        vector<pii> T;
        for(int i=0; i<n; i++){
            int cnt = 0;
            for(char c:v[i]){
                if(c == '0') cnt++;
            }
            T.push_back({cnt, i});
        }
        sort(all(T));
        if(T[0].X + T[1].X <= 1){
            int i0 = T[0].Y, i1 = T[1].Y;
            string s0 = ans[i0], s1 = ans[i1], s2 = string(n, '0');
            for(int i=0; i<n; i++){
                if(s0[i] != '1' and s1[i] != '1'){
                    s2[i] = '1';
                }
                else s2[i] = '0';
            }
            cout << "! " << s0 << " " << s1 << " " << s2 << endl;
            return 0;
        }
        else{
            // all 1
            int i0 = T[0].Y;
            int i1 = 0;
            while(true){
                int truth = 0;
                for(int i=0; i<n; i++){
                    if(v[i0][i] == '0' and v[i1][i] == '1'){
                        truth = 1; break;
                    }
                }
                if(truth) break;
                i1++;
            }
            string s0 = ans[i0], s1 = ans[i1], s2 = string(n, '0');
            for(int i=0; i<n; i++){
                if(s0[i] != '1' and s1[i] != '1'){
                    s2[i] = '1';
                }
                else s2[i] = '0';
            }
            cout << "! " << s0 << " " << s1 << " " << s2 << endl;
            return 0;
        }
    }
    return 0;
}