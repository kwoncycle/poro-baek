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

struct Cache{
    map<int, int> timeline;
    set<pii> st;
    int sz;
    Cache(int h){
        sz = h;
    }

    bool find(int o, int tm){
        if(timeline.find(o) != timeline.end()){
            int u = timeline[o];
            if(st.find({u,o}) != st.end()){
                st.erase({u,o});
                timeline[o] = tm;
                st.insert({tm, o});
                return true;
            }
            else{
                if((int)st.size() == sz){
                    st.erase(st.begin());
                }
                timeline[o] = tm;
                st.insert({tm, o});
                return false;
            }
        }

        timeline[o] = tm;
        if((int)st.size() == sz){
            st.erase(st.begin());
        }
        st.insert({tm, o});
        return false;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, h, q; cin >> n >> m >> h >> q;
    map<string, int> station;
    for(int i=0; i<n; i++){
        string s; cin >> s;
        station[s] = i;
    }

    map<int, int> node_id;
    vector<int> id2node(m);
    vector<char> node_type(m);
    vector<Cache> cache(m, Cache(h));
    int bucket;
    for(int i=0; i<m; i++){
        int o; cin >> o;
        node_id[o] = i;
        id2node[i] = o;
        cin >> node_type[i];
        if(node_type[i] == 'B') bucket = i;
    }

    int k; cin >> k;
    
    vector<vector<ll>> graph(m, vector<ll>(m, 0x3f3f3f3f33ffll));
    for(int i=0; i<k; i++){
        int a1, a2, a3;
        cin >> a1 >> a2 >> a3;
        graph[node_id[a1]][node_id[a2]] = a3;
        graph[node_id[a2]][node_id[a1]] = a3;
    }

    //vector<vector<ll>> dst(m, vector<ll>(m, 0x3f3f3f3f3f3fll));
    for(int i=0; i<m; i++) graph[i][i] = 0;

    for(int k=0; k<m; k++){
        for(int i=0; i<m; i++){
            for(int j=0; j<m; j++){
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }

    vector<int> nearest_cache(m, -1);
    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            if(i == j) continue;
            if(node_type[j] == 'C'){
                if(nearest_cache[i] == -1) nearest_cache[i] = j;
                if(graph[i][j] < graph[i][nearest_cache[i]]) nearest_cache[i] = j;
                else if(graph[i][j] == graph[i][nearest_cache[i]]){
                    if(id2node[j] < id2node[nearest_cache[i]]) nearest_cache[i] = j;
                }
            }
        }
    }

    //for(int i=0; i<m; i++) cout << id2node[nearest_cache[i]] << " " << id2node[i] << "X\n";
    for(int qi=0; qi<q; qi++){
        int nd; string s;
        cin >> nd >> s;
        int id = node_id[nd];
        int si = station[s];
        //cout << id << " " << si << "\n";
        int c = nearest_cache[id];
        //cout << "Cache " << c << ": ";
        //for(auto &[i,j]:cache[c].st) cout << i << " " << j << "-";
        //cout << "\n";
        //cout << "search " << si << "\n";
        bool b = cache[c].find(si, qi);
        //cout << "Cache " << c << ": ";
        //for(auto &[i,j]:cache[c].st) cout << i << " " << j << "-";
        //cout << "\n";
        if(b){
            cout << graph[id][c]*2 << "\n";
        }
        else{
            cout << graph[id][c]*2 + graph[c][bucket]*2 << "\n";
        }
    }

    return 0;
}