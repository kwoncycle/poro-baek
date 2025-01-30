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

map<string, vector<string>> mp;
map<string, set<string>> mp_st;
set<string> scholar;

void search(string &s){
    if(!mp_st[s].empty()){
        return;
    }

    mp_st[s].insert("poro1557");
    for(auto name:mp[s]){
        if(scholar.find(name) == scholar.end()){
            mp_st[s].insert(name);
        }
        else{
            if(mp_st[name].empty()) search(name);
            for(auto i:mp_st[name]) mp_st[s].insert(i);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    while(true){
        int n; cin >> n;
        if(n == 0) break;
        mp.clear(); mp_st.clear(); scholar.clear();

        string target;
        for(int i=0; i<n; i++){

            string s; cin >> s;
            int id = 0;
            while(s[id] != ':') id++;
            string group = s.substr(0, id);
            if(i == 0) target = group;
            mp[group] = vector<string>(0);
            scholar.insert(group);
            while(true){
                id++;
                int id1 = id;
                while(s[id] != ',' and s[id] != '.') id++;
                string name = s.substr(id1, id-id1);
                mp[group].push_back(name);
                if(s[id] == '.') break;
            }
        }

        search(target);
        cout << (int)mp_st[target].size() - 1 << "\n";

        
    }
    return 0;
}