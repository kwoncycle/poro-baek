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

ll Type[2][300005], A[2][300005];
set<pll> s1, s2, s12, used2;
ll ans;
void E1(int i, bool version){
    s1.erase({A[0][i], i});
    if(Type[1][i] == 2){
        if(s12.find({A[1][i] - A[0][i], i}) != s12.end()){
            s12.erase({A[1][i] - A[0][i], i});
            if(version) {
                used2.insert({A[1][i], i});
            }
            else s2.insert({A[1][i], i});
        }
    }
}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    ll n, k; cin >> n >> k;
    k--;
    for(int i=0; i<n; i++){
        cin >> Type[0][i];
    }
    for(int i=0; i<n; i++){
        cin >> Type[1][i];
    }
    ll sm = 0;
    for(int i=0; i<n; i++) cin >> A[0][i];
    for(int i=0; i<n+1; i++){
        ll s; cin >> s;
        sm += s;
    }
    for(int i=0; i<n; i++) cin >> A[1][i];

    for(int i=0; i<n; i++){
        if(Type[0][i] > Type[1][i]){
            swap(Type[0][i], Type[1][i]);
            swap(A[0][i], A[1][i]);
        }
    }

    for(int i=0; i<n; i++){
        if(Type[0][i] == 1 and Type[1][i] == 1){
            if(A[0][i] < A[1][i]) swap(A[0][i], A[1][i]);
            s1.insert({max(A[0][i], A[1][i]), i});
            while(s1.size() > k) s1.erase(s1.begin());
        }
        else if(Type[0][i] == 2 and Type[1][i] == 2){
            if(A[0][i] > A[1][i]) swap(A[0][i], A[1][i]);
            s2.insert({max(A[0][i], A[1][i]), i});
        }
        else{
            s1.insert({A[0][i], i});
            while(s1.size() > k) s1.erase(s1.begin());
        }
    }
    for(int i=0; i<n; i++){
        if(Type[0][i] == 1 and Type[1][i] == 2){
            if(s1.find({A[0][i], i}) == s1.end()) s2.insert({A[1][i], i});
            else s12.insert({A[1][i] - A[0][i], i});
        }
    }

    ll score = s1.size();
    ans = sm;
    for(auto &[i,_]:s1) ans += i;
    //cout << ans << "\n";
    while(true){
        // for(auto [_, i]:s2) cout << i << " "; cout << " s2\n";
        // for(auto [_, i]:s12) cout << i << " "; cout << " s12\n";
        // for(auto [_, i]:s1) cout << i << " "; cout << " s1\n";

        // for(auto [i, _]:s1) cout << i << " "; 
        // for(auto [i, _]:used2) cout << i << " ";
        // cout << " used " << ans << "\n";
        if(s2.empty() and s12.empty()) break;
        ll add2 = 0, add1 = 0, add0 = 0, who0 = 0, who1 = 0, who2 = 0;
        if(score + 2 <= k){
            if(!s2.empty()){
                if(add2 < (*s2.rbegin()).X) {
                    add2 = (*s2.rbegin()).X; who2 = 2;
                }
            }
        }
        
        if(score + 1 <= k){
            if(!s2.empty() and !s1.empty()){
                if(add1 < (*s2.rbegin()).X - (*s1.begin()).X){
                    add1 = (*s2.rbegin()).X - (*s1.begin()).X;
                    who1 = 2;
                }
            }
            if(!s12.empty()){
                if(add1 < (*s12.rbegin()).X){
                    add1 = (*s12.rbegin()).X; 
                    who1 = 12;
                }
            }
        }
        if(score + 0 <= k){
            if(!s12.empty() and s1.size() >= 2){
                auto t = s1.begin();
                auto j = s12.rbegin();
                if((*j).Y == (*t).Y) t++;
                if(add0 < (*j).X - (*t).X){
                    add0 = (*j).X - (*t).X;
                    who0 = 12;
                }
                if(t != s1.begin()){
                    if(s12.size() >= 2){
                        j++; t = s1.begin();
                        if(add0 < (*j).X - (*t).X){
                            add0 = (*j).X - (*t).X;
                            who0 = 12;
                        }
                    }
                }
            }
            if(!s2.empty() and s1.size() >= 2){
                auto t = s2.rbegin();
                auto j0 = s1.begin(), j1 = j0;
                j1++;
                if(add0 < (*t).X - (*j0).X - (*j1).X){
                    add0 = (*t).X - (*j0).X - (*j1).X;
                    who0 = 2;
                }
            }
            if(used2.size() >= 1 and s12.size() >= 2){
                auto j0 = s12.rbegin(), j1 = j0; j1++;
                auto t = used2.begin();
                if(add0 < (*j0).X + (*j1).X - (*t).X){
                    add0 = (*j0).X + (*j1).X - (*t).X;
                    who0 = 21122;
                }
            }

        }
        //cout << add2 << " " << add1 << " " << add0 << " " << who0 << " add\n";
        if(max({add2, add1, add0}) == 0) break;
        if(add2 > add1 and add2 > add0){
            score += 2;
            ans += add2; 
            used2.insert(*s2.rbegin());
            s2.erase(*s2.rbegin());
        }
        else if(add1 > add0){
            score += 1;
            if(who1 == 2){
                ans += add1;
                used2.insert(*s2.rbegin());
                s2.erase(*s2.rbegin());
                int i = (*s1.begin()).Y;
                E1(i, false);
            }
            else if(who1 == 12){
                ans += add1;
                int i = (*s12.rbegin()).Y;
                
                E1(i, true);
            }
        }
        else{
            if(who0 == 12){
                ans += add0;
                auto t = s1.begin();
                auto j = s12.rbegin();
                if((*j).Y == (*t).Y) t++;
                if(add0 == (*j).X - (*t).X){
                    int i0 = (*t).Y, i1 = (*j).Y;
                    E1(i1, true); E1(i0, false);
                    continue;
                }
                if(t != s1.begin()){
                    j++; t = s1.begin();
                    if(add0 == (*j).X - (*t).X){
                        int i0 = (*t).Y, i1 = (*j).Y;
                        E1(i1, true); E1(i0, false);
                    }
                    else assert(false);
                }
            }
            else if(who0 == 2){
                ans += add0;
                auto t = s2.rbegin();
                auto j0 = s1.begin(), j1 = j0; j1++;
                int i0 = (*j0).Y, i1 = (*j1).Y;
                used2.insert(*t);
                s2.erase(*t);
                E1(i0, false); E1(i1, false);
            }
            else if(who0 == 21122){
                ans += add0;
                auto j0 = s12.rbegin(), j1 = j0; j1++;
                int i0 = (*j0).Y, i1 = (*j1).Y;
                auto t = used2.begin();
                s2.insert(*t); used2.erase(t);
                E1(i0, true); ;E1(i1, true);
            }
        }
    }

    cout << ans << "\n";


    return 0;
}