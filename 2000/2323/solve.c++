#include <bits/stdc++.h>
using namespace std;

set<int> graph[1005];

int ban[1004], initial[1004][1004];

int n, m; 

vector<int> JG(int iq){
    if(iq == 3){
        vector<int> t1;
        for(int i=1; i<=n; i++) {
            if(!ban[i]) t1.push_back(i);
        }
        //assert(t1.size() == 3);
        return t1;
    }
    int id = 0;
    for(int j=1; j<=n; j++){
        if(!ban[j]){
            if(!id) id = j;
            else{
                if(graph[id].size() > graph[j].size()) id = j;
            }
        }
    }
    int id1 = *graph[id].begin();
    assert(ban[id1] == 0);
    ban[id1] = 1;
    for(int j=1; j<=n; j++){
        if(!ban[j] and graph[j].find(id1) != graph[j].end()) graph[j].erase(id1);
    }
    for(int j:graph[id1]){
        if(j != id and j != id1) graph[id].insert(j);
    }
    vector<int> t1 = JG(iq-1);
    int id2;
    for(int i=0; i<(int)t1.size(); i++){
        if(t1[i] == id) {
            id2 = i; break;
        }
    }
    int id2b = (id2 + 1) % (int)t1.size();
    if(graph[id1].find(t1[id2b]) != graph[id1].end()) {
        vector<int> t2;
        for(int i=t1.size()-1; i>=id2 + 1; i--){
            t2.push_back(t1[i]);
            t1.pop_back();
        }
        t2.push_back(id1);
        while(!t2.empty()){
            t1.push_back(t2.back()); t2.pop_back();
        }
    }
    else{
        vector<int> t2;
        for(int i=t1.size()-1; i>=id2; i--){
            t2.push_back(t1[i]);
            t1.pop_back();
        }
        t2.push_back(id1);
        while(!t2.empty()){
            t1.push_back(t2.back()); t2.pop_back();
        }
    }
    return t1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    for(int i=0; i<m; i++){
        int a, b; cin >> a >> b;
        initial[a][b] = 1; initial[b][a] = 1;
        graph[a].insert(b); graph[b].insert(a);
    }
    for(int i=1; i<=n; i++) assert(ban[i] == 0);
    vector<int> ans = JG(n);
    
    set<int>st;
    for(int i:ans) {
        st.insert(i);
        assert(1 <= i and i <= n);
    }
    assert(st.size() == n);
    assert(ans.size() == n);
    for(int i=0; i<n-1; i++) assert(initial[ans[i]][ans[i+1]]);
    assert(initial[ans[n-1]][ans[0]]);
    cout << "0\n";
    for(int i:ans) {
        cout << i << " ";
    }
}