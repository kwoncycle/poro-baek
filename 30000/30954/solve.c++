#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()

vector<int> state[104], want[104];
int sz[104];
int n, k;

void Q(int l, int r){
    if(state[l].empty()) return;

    state[r].push_back(state[l].back());
    state[l].pop_back();
    
    assert(state[r].size() <= sz[r]);
    cout << l << " " << r << "\n";
}

void check(){
    for(int i=1; i<=k; i++){
        cout << i << ": ";
        for(int j:state[i]) cout << j << " ";
        cout << "\n";
    }
}

void checkw(){
    for(int i=1; i<=k; i++){
        cout << i << ": ";
        for(int j:want[i]) cout << j << " ";
        cout << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> k;
    for(int i=1; i<=k; i++){
        int r; cin >> r;
        sz[i] = r;
        while(r--){
            int x; cin >> x;
            if(x){
                state[i].push_back(x);
            }
        }
    }

    int cur = 1, mx = 0, id;
    for(int i=1; i<=k; i++){
        if(sz[i] > mx){
            mx = sz[i]; id = i;
        }
    }

    for(int i=1; i<=n; i++){
        while(want[cur].size() == sz[cur]) cur++;
        want[cur].push_back(i);
    }

    for(int i=k-1; i>=id; i--){
        while(!want[i].empty()){
            int j = want[i].back(); want[i].pop_back();
            int o = k;
            while(want[o].size() == sz[o]) o--;
            want[o].push_back(j);
        }
    }

    for(int i=1; i<=k; i++){
        if(i == id) continue;
        while(!state[id].empty() and state[i].size() < sz[i]){
            Q(id, i);
        }
    }

    vector<int> order;
    for(int i=1; i<=k; i++){
        for(int j:want[i]) order.push_back(j);
    }
    for(int i:order){
        int locw0, locw1;
        for(int j=1; j<=k; j++){
            for(int x=0; x<want[j].size(); x++){
                if(want[j][x] == i){
                    locw0 = j, locw1 = x;
                    goto escape;
                }
            }
        }
        escape:

        int locs0, locs1;
        for(int j=1; j<=k; j++){
            for(int x=0; x<state[j].size(); x++){
                if(state[j][x] == i){
                    locs0 = j, locs1 = x;
                    goto escape1;
                }
            }
        }
        escape1:
        if(locw0 == locs0 and locw1 == locs1) continue;
        if(locw0 == locs0){
            int zmt = 1, emp = 1;
            while(zmt == locw0 or zmt == locs0 or zmt == id) zmt++;
            if(!state[zmt].empty()){
                emp = 0;
                Q(zmt, id);
            }
            while(state[locw0].size() > locs1 + 1){
                Q(locw0, id);
            }
            Q(locw0, zmt);
            while(state[locw0].size() >= locw1 + 1){
                Q(locw0, id);
            }
            Q(zmt, locw0);
            Q(id, zmt);
            while(!state[id].empty()) Q(id, locw0);
            if(!emp){
                Q(id, zmt);
            }
        }
        else{
            int zmt = 1, emp = 1;
            while(zmt == locs0 or zmt == id) zmt++;
            if(!state[zmt].empty()){
                emp = 0;
                Q(zmt, id);
            }
            while(state[locs0].size() > locs1 + 1){
                Q(locs0, id);
            }
            Q(locs0, zmt);
            while(!state[id].empty()) Q(id, locs0);
            Q(locs0, id);
            Q(zmt, locs0);
            Q(id, zmt);
            if(!emp){
                Q(id, zmt);
            }
            

            while(state[locw0].size() >= locw1 + 1){
                Q(locw0, id);
            }
            Q(locs0, locw0);
            Q(id, locs0);
            while(!state[id].empty()) Q(id, locw0);
        }
        //check();
    }

    for(int i=id+1; i<=k; i++){
        while(!state[i].empty()){
            int truth = 0;
            for(int j=id; j<i; j++){
                if(state[j].size() < sz[j]){
                    Q(i, j);
                    truth = 1; break;
                }
            }
            if(!truth) break;
        }
    }
    cout << "0 1\n";



    return 0;
}