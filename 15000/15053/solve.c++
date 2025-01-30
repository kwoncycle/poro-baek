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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s; cin >> s;
    int truth = 0;
    vector<int> v;
    for(int i=0; i<(int)s.size(); i++){
        if(s[i] == 'a' or s[i] == 'e' or s[i] == 'i' or s[i] == 'o' or s[i] == 'u'){
            truth = 1; v.push_back(i);
        }
    }

    if(!truth){
        cout << "1\n"; return 0;
    }

    if(v[0] != 0){
        cout << "0\n"; return 0;
    }

    int o = v.size();
    int i1 = (o-1)/2, i2 = i1+1;
    if(o == 1){
        cout << s.size() << "\n"; return 0;
    }

    cout << v[i2] - v[i1] << "\n";
    
    return 0;
}