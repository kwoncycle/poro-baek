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
int truth = 1;

vector<int> graph[200005];
vector<int> val(200005, -1);

void DFS(int x){
    for(int i:graph[x]){
        if(val[i] == -1){
            val[i] = 1 - val[x];
            DFS(i);
        }
        else{
            if(val[i] + val[x] == 1) continue;
            else {truth = 0; break;}
        }
    }
}

// 1 3 2
// 4 5 6

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<pii> edge(m);
    for(int i=0; i<m; i++){
        int a,b; cin >> a >> b;
        edge[i] = {a,b};
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for(int i=1; i<=n; i++){
        if(val[i] == -1){
            val[i] = 0;
            DFS(i);
        }
    }

    int cnt0 = 0, cnt1 = 0;
    for(int i=1; i<=n; i++){
        if(val[i] == 0) cnt0++;
        else cnt1++;
    }
    if(cnt0%2 == 1 and cnt1%2 == 1){
        if(cnt0*cnt1 == m){
            cout << (cnt0+cnt1-2)/2 << "\n";
        }
        else cout << (cnt0+cnt1)/2 << "\n";
    }
    else{
        cout << (n - (n%2))/2 << "\n";
    }

    return 0;
}