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

int n; 
vector<int> rt;
vector<vector<int>> under;
vector<string> s;

void JG(int x, int depth){
    for(int y:under[x]){
        for(int i=0; i<depth; i++) cout << '.';
        cout << s[y] << "\n";
        JG(y, depth + 1);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n;
    rt = vector<int>(n+1, -1);
    under = vector<vector<int>>(n+1);
    s = vector<string>(n+1);

    for(int i=1; i<=n; i++){
        int r; cin >> r;
        rt[i] = r;
        under[r].push_back(i);
        cin >> s[i];
    }
    
    JG(0, 0);
    return 0;
}