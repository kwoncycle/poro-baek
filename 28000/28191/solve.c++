#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

map<array<short,3>, short> mp;

struct solve{
    solve(){
        int n; cin >> n;
        int q = query(1,2,3);
        vector<short> V;
        if(q == 1) V = {1,2,3};
        else V = {1,3,2};
        for(int i=4; i<=n; i++){
            merge(V, i);
        }
        cout << "! " << V.size() << " ";
        for(short i:V) cout << i << " "; cout << endl;
    }
    short query(short i, short j, short k){
        if(mp.find({i,j,k}) != mp.end()) return mp[{i,j,k}];
        short ans; 
        cout << "? " << i << " " << j << " " << k << endl;
        cin >> ans;
        mp[{i,j,k}] = ans;
        mp[{j,k,i}] = ans;
        mp[{k,i,j}] = ans;
        mp[{i,k,j}] = -ans;
        mp[{j,i,k}] = -ans;
        mp[{k,j,i}] = -ans;
        
        return ans;
    }

    void merge(vector<short> &ch, int id){
        int n = ch.size();
        vector<short> v1(n);
        for(int i=0; i<n; i++) v1[i] = i;
        while(v1.size() > 3){
            short i1 = v1[0], i2 = v1[v1.size()/2];
            short q = query(ch[i1], ch[i2], id);
            vector<short> v2;
            if(q == 1){
                v2.push_back(v1[0]);
                for(int i=v1.size()/2; i<(int)v1.size(); i++) v2.push_back(v1[i]);
                v1 = v2;
            }
            else{
                for(int i=0; i<=(int)v1.size()/2; i++) v2.push_back(v1[i]);
                v1 = v2;
            }
        }
        
        if(query(ch[v1[1]], ch[v1[2]], id) == -1){
            mergep(ch, id, v1[1], -1);
        }
        else if(v1[2]==n-1 and query(ch[v1[0]], ch[v1[2]], id) == 1){
            mergep(ch, id, n-1, v1[1]);
        }
        else if(v1[1]==1 and query(ch[v1[0]], ch[v1[1]], id) == -1){
            mergep(ch, id, 0, v1[1]);
        }
        return;
    }

    void mergep(vector<short> &ch, short id, short st, short no){ // we know query(ch[st], ch[st+1], id) = -1 , if no !+ -1, query(ch[no], ch[no+1], id) = 1
        if(no == -1){
            int n = ch.size();
            int s1 = st, s2 = st+1;
            while(query(id, ch[s2%n], ch[(s2+1)%n]) == -1) s2++;
            while(query(id, ch[(n+s1%n)%n], ch[(n+(s1-1)%n)%n]) == 1) s1--;
            vector<short> V;
            V.push_back(id);
            for(int i=s2; i%n != (n+s1%n)%n; i++){
                V.push_back(ch[i%n]);
            }
            V.push_back(ch[(n+s1%n)%n]);
            ch = V;
        }
        else{
            int n = ch.size();
            int s1, s2;
            {
                int start = st, end = no;
                while(start > end) end += n;
                while(start + 1 < end){
                    int md = (start + end) / 2;
                    int q = query(id, ch[md%n], ch[(md+1)%n]);
                    if(q == -1) start = md;
                    else end = md;
                }
                s2 = start+1;
            }
            {
                int start = no, end = st;
                while(start > end) end += n;
                while(start + 1 < end){
                    int md = (start + end) / 2;
                    int q = query(id, ch[md%n], ch[(md+1)%n]);
                    if(q == 1) start = md;
                    else end = md;
                }
                s1 = start+1;
            }
            vector<short> V;
            V.push_back(id);
            for(int i=s2; i%n != (n+s1%n)%n; i++){
                V.push_back(ch[i%n]);
            }
            V.push_back(ch[(n+s1%n)%n]);
            ch = V;
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve s;
    return 0;
}