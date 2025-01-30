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


vector<int> v(1000005);
vector<int> pre(1000005);
int get_sm(int i, int j){
    return pre[j] - (i-1>=0 ? pre[i-1] : 0);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n; cin >> n;
    
    for(int i=0; i<n; i++) cin >> v[i]; v[n] = 1;
    pre[0] = v[0];
    for(int i=1; i<=n; i++) pre[i] = pre[i-1] + v[i];

    if(v[0] == 0){
        for(int i=0; i<n; i++){
            if(v[i]){
                if(v[i] == -1){
                    cout << "BRAK\n"; return 0;
                }
                else break;
            }
        }

        int i1 = 0;
        while(i1 < n and v[i1] == 0) i1++;
        if(i1 == n){
            cout << "0\n"; return 0;
        }
        else{
            cout << (n-i1 - get_sm(i1, n-1)) << "\n"; return 0;
        }
    }

    if(v[0] == 1){
        cout << n - get_sm(0, n-1) << "\n"; return 0;
    }

    vector<int> idx1;
    for(int i=0; i<n; i++) if(v[i] == 1) idx1.push_back(i);
    if(idx1.empty()){
        int i1 = n-1;
        while(v[i1] == 0) i1--;
        cout << get_sm(0, i1) + i1+1 << "\n"; return 0;
    }


    ll ans = get_sm(0, n-1) + n;

    for(int i=0; i<(int)idx1.size()-1; i++){
        int u1 = idx1[i], u2 = idx1[i+1];
        if(u1 + 1 == u2){
            ans = min(ans, get_sm(0, u1-1) - u1 + n-u1 - get_sm(u1, n-1));
            continue;
        }
        int cur = -1;
        for(int j=u1; j<u2; j++){ // 0~j is -1 // j+1~u2-1 is 0 // u2~n-1 is 1
            if(v[j] == -1) cur = j;
        }

        if(cur == -1){
            ans = min(ans, get_sm(0, u1-1) + u1 + 1 + n-u1-1 - get_sm(u1+1, n-1))
        }
    }

    //ll ans 

    return 0;
}