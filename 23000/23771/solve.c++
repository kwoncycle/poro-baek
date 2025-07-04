#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define ordered_set tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define X first
#define Y second
#define all(x) (x).begin(), (x).end()

const int SZ = 300005;
int n;
int G[SZ], H[SZ], Gi[SZ], Hi[SZ];

vector<pii> ans;
void swapG(int l, int r){
    Gi[G[l]] = r;
    Gi[G[r]] = l;
    swap(G[l], G[r]);
    ans.push_back({l+1, r+1});
}


ordered_set os, os1;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n;
    vector<pii> vG, vH;
    for(int i=0; i<n; i++){
        cin >> G[i];
        vG.push_back({G[i], i});
    }
    for(int i=0; i<n; i++){
        cin >> H[i];
        vH.push_back({H[i], i});
    }
    sort(all(vG));
    sort(all(vH));
    vector<vector<int>> L;
    for(int i=0; i<n; i++){
        G[vG[i].Y] = i;
        H[vH[i].Y] = i;
        if(i == 0 or vG[i-1].X != vG[i].X){
            L.push_back(vector<int>(0));
        }
        L.back().push_back(i);
    }
    for(int i=0; i<n; i++){
        Gi[G[i]] = i;
        Hi[H[i]] = i;
        os.insert(i); os1.insert(i);
    }

    ll anssz = 0;
    for(int i=0; i<n; i++){
        anssz += abs((ll)os.order_of_key(Gi[i]) - (ll)os1.order_of_key(Hi[i]));
        os.erase(Gi[i]); os1.erase(Hi[i]);
    }
    for(int i=0; i<n; i++) os.insert(i);

    
    for(int l=0; l<(L.size()); l++){
        int sz = L[l].size();
        vector<int> idG, idH;
        for(int i:L[l]){
            idG.push_back(os.order_of_key(Gi[i]));
            idH.push_back(os.order_of_key(Hi[i]));
        }
        while(!idG.empty()){
            int id = idG.size() - 1;
            if(idG[id] == idH[id]){
                os.erase(os.find_by_order(idH[id]));
                idG.pop_back(); idH.pop_back();
                continue;
            }
            else if(idG[id] < idH[id]){
                for(int i=idG[id]; i<idH[id]; i++){
                    int l = *os.find_by_order(i), r = *os.find_by_order(i+1);
                    swapG(l, r); if(ans.size() >= 200050) goto outt;
                }
                os.erase(os.find_by_order(idH[id]));
                idG.pop_back(); idH.pop_back();
                continue;
            }
            else{
                int cur = id;
                while(id>=0 and idG[id] > idH[id]) id--;
                for(int t=id+1; t<=cur; t++){
                    for(int i=idG[t]; i>idH[t]; i--){
                        int l = *os.find_by_order(i), r = *os.find_by_order(i-1);
                        swapG(l, r); if(ans.size() >= 200050) goto outt;
                    }
                }
                for(int t=cur; t>=id+1; t--){
                    os.erase(os.find_by_order(idH[t]));
                    idG.pop_back(); idH.pop_back();
                }
            }
        }
    }

    outt:
    cout << anssz << "\n";
    // assert(anssz >= ans.size());
    // for(int i=0; i<n; i++){
    //     assert(anssz != ans.size() or H[i] == G[i]);
    // }
    for(int i=0; i<min(200000, (int)ans.size()); i++){
        cout << ans[i].X << " " << ans[i].Y << "\n";
    }
    
    return 0;
}