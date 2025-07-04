#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef pair<int,int> pii;
typedef tree<int,null_type,less<int>,rb_tree_tag, tree_order_statistics_node_update> ordered_set;

struct SuffixArray{
 int n;
 vector<int> sa,rk,lcp; // note: sa[rk[i]] = i
 SuffixArray(string&s):n(s.size()),sa(n),rk(n+1,-1),lcp(n){
  for(int i=0;i<n;i++) sa[i]=i, rk[i]=s[i];
  for(int d=0;d<n;d=d?d<<1:1){
   vector<pii> g(n);
   vector<int> c(max(256,n));
   for(int i=0;i<n;i++){
    c[rk[i]]++, g[i]={rk[i],rk[min(n,i+d)]};
   }
   auto p=c, t=sa;
   for(int i=1;i<p.size();i++) p[i]+=p[i-1];
   auto upd=[&](int x){t[p[rk[x]]-(c[rk[x]]--)]=x;};
   for(int i=n-d;i<n;i++) upd(i);
   for(int i=0;i<n;i++)if(sa[i]>=d) upd(sa[i]-d);
   swap(sa,t); rk[sa[0]]=0;
   for(int i=1;i<n;i++){
    rk[sa[i]]=rk[sa[i-1]]+(g[sa[i]]!=g[sa[i-1]]);
   }
  }
  rk.pop_back();
  for(int i=0,h=0;i<n;i++,h=max(h-1,0))if(rk[i]){
   while(max(i,sa[rk[i]-1])+h<n && s[i+h]==s[sa[rk[i]-1]+h]) h++;
   lcp[rk[i]] = h;
  }
 }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    string s; cin >> s;

    int cnt0 = 0, cnt1 = 0, cnt01 = 0;
    for(char c:s){
        if(c == '0') cnt0++;
        else cnt1++;
    }

    for(int i=cnt0; i<cnt1+cnt0; i++){
        if(s[i] == '0') cnt01++;
    }

    if(cnt01 == 0){
        string ans = string(cnt0, '0') + string(cnt1, '1');
        cout << ans << "\n"; return 0;
    }

    vector<int> state0, state1, nxt0, nxt1;
    ordered_set st;
    
    int ttl = cnt01, cur = cnt01, turn = 1;
    for(int i=0; i<n; i++) st.insert(i);
    for(int i=cnt0-1; i>=0; i--){
        cur--;
        if(s[i] == '1'){
            state0.push_back(turn);
            auto o = st.find_by_order(cur);
            nxt0.push_back(*o); st.erase(o);
            ttl--;
        }
        if(cur == 0){
            cur = ttl; turn++;
        }
    }

    ttl = cnt01, cur = cnt01, turn = 1;
    for(int i=0; i<n; i++) st.insert(i);
    for(int i=cnt0; i<cnt1+cnt0; i++){
        cur--;
        if(s[i] == '0'){
            state1.push_back(turn);
            auto o = st.find_by_order(cur);
            nxt1.push_back(*o); st.erase(o);
            ttl--;
        }
        if(cur == 0){
            cur = ttl; turn++;
        }
    }

    cur = cnt01-1;
    string ans;
    for(int i=0; i<cnt01; i++){
        ans += string(state0[cur], '0');
        cur = nxt0[cur];
        ans += string(state1[cur], '1');
        cur = nxt1[cur];
    }

    string ans1 = ans + ans;
    SuffixArray SA(ans1);
    string u;
    for(int i:SA.sa){
        if(0 <= i and i < n){
            u.push_back(ans[(i + n - 1)%n]);
        }
    }

    if(ans.size() != n or u != s) cout << "-1\n";
    else {
        cout << ans << "\n";
    }
    return 0;
}