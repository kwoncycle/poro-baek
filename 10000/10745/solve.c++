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

namespace Aho {
 const int MAXN = 100010 + 4; // sum of the lengths
 const int MAXC = 26;
 int term[MAXN],len[MAXN],to[MAXN][MAXC],link[MAXN], sz = 1;
 void add(string s){
  int x = 0;
  for(auto&c: s){ c-='a';
   if(!to[x][c]){
    to[x][c] = sz++;
    len[to[x][c]] = len[x] + 1;
   }
   x = to[x][c];
  }
  term[x] = x;
 }
 void push_links(){
  queue<int>q; q.push(0);
  while(!q.empty()){
   int x = q.front(); q.pop();
   int y = link[x];
   if(!term[x]) term[x] = term[y];
   for(int c=0;c<MAXC;c++){
    if(to[x][c]){
     link[to[x][c]] = x ? to[y][c] : 0;
     q.push(to[x][c]);
    }
    else to[x][c] = to[y][c];
   }
  }
 }
 string get(string s){
    string ans;
    vector<int> st;
    int x = 0;
    st.push_back(x);
    for(auto&c: s){
        x = to[x][c-'a'];
        ans.push_back(c);
        st.push_back(x);
        if(term[x]){
            int l = len[x];
            for(int i=0; i<l; i++){
                st.pop_back(); ans.pop_back();
            }
            x = st.back();
        }
    }
    return ans;
 }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s; cin >> s;
    int n; cin >> n;
    while(n--){
        string s1; cin >> s1;
        Aho::add(s1);
    }
    Aho::push_links();
    cout << Aho::get(s) << "\n";

    return 0;
}