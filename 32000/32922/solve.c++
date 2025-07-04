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

struct solve{
    int n;
    vector<pll> v;
    vector<char> C;
    ll B = 0, R = 0, lastb, lastr;
    solve(){
        cin >> n;
        v.resize(n); C.resize(n);
        for(int i=0; i<n; i++){
            cin >> v[i].X >> v[i].Y >> C[i];
            if(C[i] == 'R') {
                R += v[i].Y; lastr = v[i].X;
            }
            else {
                B += v[i].Y; lastb = v[i].X;
            }
        }
        if(R == B){
            DRAW();
            return;
        }
        vector<ll> smR(1, 0), smB(1, 0);
        for(int i=n-1; i>=0; i--){
            if(C[i] == 'R') smR.push_back(smR.back() + v[i].Y);
            if(C[i] == 'B') smB.push_back(smB.back() + v[i].Y);
        }
        for(ll i:smB) smR.push_back(i);
        sort(all(smR));
        smR.erase(unique(all(smR)), smR.end());
        vector<__int128> needB(smR.size()), needR(smR.size());
        {
            int id = n-1;
            ll cur = 0;
            for(int i=1; i<(int)needB.size(); i++){
                while(id>=0 and C[id] != 'B') id--;
                if(id == -1){
                    needB[i] = needB[i-1] + (__int128)(smR[i] - cur)*0x3f3f3f3f;
                    cur = smR[i];
                }
                else{
                    __int128 delta = 0;
                    while(id >= 0){
                        if(C[id] != 'B') id--;
                        else{
                            if(cur + v[id].Y <= smR[i]){
                                cur += v[id].Y;
                                delta += (__int128)v[id].Y * (0x3f3f3f - v[id].X);
                                v[id].Y = 0;
                                id--;
                            }
                            else{
                                delta += (__int128)(smR[i] - cur) * (0x3f3f3f - v[id].X);
                                v[id].Y -= smR[i] - cur;
                                cur = smR[i];
                                break;
                            }
                        }
                    }
                    needB[i] = needB[i-1] + delta;
                }
                //cout << smR[i] << " " << (ll)needB[i] << " -> ";
            }
        }
        
        {
            int id = n-1;
            ll cur = 0;
            for(int i=1; i<(int)needR.size(); i++){
                while(id>=0 and C[id] != 'R') id--;
                if(id == -1){
                    needR[i] = needR[i-1] + (__int128)(smR[i] - cur)*0x3f3f3f3f;
                    cur = smR[i];
                }
                else{
                    __int128 delta = 0;
                    while(id >= 0){
                        if(C[id] != 'R') id--;
                        else{
                            if(cur + v[id].Y <= smR[i]){
                                cur += v[id].Y;
                                delta += (__int128)v[id].Y * (0x3f3f3f - v[id].X);
                                v[id].Y = 0;
                                id--;
                            }
                            else{
                                delta += (__int128)(smR[i] - cur) * (0x3f3f3f - v[id].X);
                                v[id].Y -= smR[i] - cur;
                                cur = smR[i];
                                break;
                            }
                        }
                    }
                    needR[i] = needR[i-1] + delta;
                }
            }
        }

        if(R < B){
            int truth = 0;
            for(int i=0; i<(int)needR.size(); i++){
                if(needR[i] < needB[i]){
                    truth = 1; break;
                }
            }
            if(truth){
                DRAW();
            }
            else SECOND();
            return;
        }
        if(R > B){
            int truth = 0;
            for(int i=0; i<(int)needR.size(); i++){
                if(needR[i] > 1 + needB[i]){
                    truth = 1; break;
                }
            }
            if(truth){
                DRAW();
            }
            else FIRST();
            return;
        }
    }
    void DRAW(){
        cout << "Draw " << lastr << " +\n";
    }
    void FIRST(){
        cout << "First " << lastr << " +\n";
    }
    void SECOND(){
        cout << "Second\n";
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        solve S;
    }
    return 0;
}