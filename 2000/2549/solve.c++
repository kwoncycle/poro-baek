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

#define ull unsigned long long


ull target = 0;

int cnt(ull n1, ull n2){
    int ans = 0;
    for(ull i=0; i<16; i++){
        if(n1%16ull != n2%16ull) ans++;
        n1 /= 16ull;
        n2 /= 16ull;
    }
    return ans;
}

ull U[16];

set<ull> st;
map<ull, ull> mp;
queue<pair<ull, int>> q;

ull Utoull(){
    ull ans = 0;
    for(int i=15; i>=0; i--){
        ans <<= 4;
        ans ^= U[i];
    }
    return ans;
}

void mv(ull x, int ct){
    ull x1 = x;
    for(ull i=0; i<16; i++){
        U[i] = x&15ull;
        x >>= 4;
    }
    for(int i=0; i<4; i++){
        for(int t=0; t<4; t++){
            ull o = U[i*4];
            for(int j=0; j<3; j++){
                U[i*4+j] = U[i*4+j+1];
            }
            U[i*4+3] = o;
            if(t < 3){
                ull o1 = Utoull();
                if(cnt(o1, target) <= (6-ct)*4 and st.find(o1) == st.end()){
                        q.push({o1, ct+1});
                        st.insert(o1);
                        mp[o1] = x1;
                    
                }
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int t=0; t<4; t++){
            ull o = U[i];
            for(int j=0; j<3; j++){
                U[i+j*4] = U[i+j*4+4];
            }
            U[i+3*4] = o;
            if(t < 3){
                ull o1 = Utoull();
                if(cnt(o1, target) <= (6-ct)*4 and st.find(o1) == st.end()){
                        q.push({o1, ct+1});
                        st.insert(o1);
                        mp[o1] = x1;
                }
            }
        }
    }
}

array<int, 3> findmv(ull bf, ull aft){
    for(ull i=0; i<16; i++){
        U[i] = bf&15ull;
        bf >>= 4;
    }
    for(int i=0; i<4; i++){
        for(int t=0; t<4; t++){
            ull o = U[i*4];
            for(int j=0; j<3; j++){
                U[i*4+j] = U[i*4+j+1];
            }
            U[i*4+3] = o;
            if(t < 3){
                ull o1 = Utoull();
                if(o1 == aft){
                    return {1, i+1, t+1};
                }
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int t=0; t<4; t++){
            ull o = U[i];
            for(int j=0; j<3; j++){
                U[i+j*4] = U[i+j*4+4];
            }
            U[i+3*4] = o;
            if(t < 3){
                ull o1 = Utoull();
                if(o1 == aft){
                    return {2, i+1, t+1};
                }
            }
        }
    }
    assert(false);
    return {0,0,0};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    for(int i=0; i<16; i++) U[i] = i;
    target = Utoull();
    for(int i=0; i<16; i++) {
        cin >> U[i];
        U[i]--;
    }
    ull start = Utoull();
    q.push({Utoull(), 0});
    st.insert(start);
    int ct = 0;
    while(!q.empty()){
        auto [i, j] = q.front(); q.pop();
        ull i1 = i;
        for(int t=0; t<16; t++){
            //cout << i1%16ull << " ";
            i1 >>= 4;
        }
        //cout << "\n";
        if(i == target){
            cout << j << "\n";
            vector<array<int, 3>> ans;
            while(j--){
                ull i1 = mp[i];
                auto [x,y,z] = findmv(i, i1);
                ans.push_back({x,y,z});
                i = i1;
                //cout << x << " " << y << " " << z << "\n";
            }
            reverse(ans.begin(), ans.end());
            for(auto [x,y,z]:ans) cout << x << " " << y << " " << z << "\n";
            
            return 0;
        }
        mv(i, j);
        //break;
        //ct++;
        //if(ct > 25) break;
    }
    return 0;
}