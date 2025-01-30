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

struct sticker{
    char s; int d, a;
    sticker(char si, int di, int ai){
        s = si; d = di; a = ai;
    }
    sticker(){
        sticker(1, -1, -1);
    }
};

vector<sticker> v;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    v.resize(m+1);
    // input
    for(int i=1; i<=m; i++){
        char c;
        int d, a;
        cin >> c >> d >> a;
        v[i] = sticker(c, d, a);
    }
    
    vector<int> state(n);
    for(int i=0; i<n; i++) cin >> state[i];
    string s; cin >> s;

    vector<int> cheap(26, 999999);
    for(int i=1; i<=m; i++){
        int o = v[i].s - 'a';
        cheap[o] = min(cheap[o], v[i].a);
    }

    //for(int i:cheap) cout << i << " "; cout << "\n";

    ll cost_min = 999999999999999ll;
    for(int i=0; i+k-1<n; i++){
        // i~i+k-1
        vector<int> need(26, 0), got(26, 0);
        vector<priority_queue<int, vector<int>, greater<int>>> vpq(26);
        ll ttl_cost = 0;
        for(int j=i; j<i+k; j++){
            if(v[state[j]].s == s[j-i]) continue;
            need[s[j-i]-'a']++;
            ttl_cost += v[state[j]].d;
            got[v[state[j]].s-'a']++;
        }
        //for(int ii:got) cout << ii << " "; cout << "\n";
        for(int j=0; j<n; j++){
            if(i <= j and j < i+k) continue;
            int o = v[state[j]].s - 'a';
            vpq[o].push(v[state[j]].d);
        }
        for(int j=0; j<26; j++){
            need[j] -= got[j];
            if(need[j] <= 0) continue;
            while(need[j]--){
                if(vpq[j].empty()){
                    if(cheap[j] >= 99999){
                        cout << "-1\n"; return 0;
                    }
                    ttl_cost += cheap[j];
                }
                else{
                    int o = vpq[j].top();
                    if(o < cheap[j]){
                        vpq[j].pop(); ttl_cost += o;
                    }
                    else ttl_cost += cheap[j];
                }
            }
        }
        //cout << i << " " << ttl_cost << "\n";
        cost_min = min(cost_min, (ll)ttl_cost);
    }
    cout << cost_min << "\n";

    return 0;
}