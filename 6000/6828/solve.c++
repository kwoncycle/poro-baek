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

bool isint(char c){
    if(c >= '0' and c <= '9') return true;
    if(c == 5) return true;
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    while(true){
        string s; getline(cin, s);
        if(s[0] == '0' and s.size() == 1){
            break;
        }
        if(s.size() == 1) {
            cout << s << "\n";
            continue;
        }

        int n = (int)s.size()/2 + 1;
        vector<int> v1, v2;
        for(int i=0; i<n; i++){
            v1.push_back(s[i*2]);
            if(v1.size() >= 2){
                int i1 = v1.size() - 1;
                if(!isint(v1[i1-1]) and isint(v1[i1])) v2.push_back(v1[i1]);
            }
            while(true){
                if(v1.size() >= 3){
                    int i1 = v1.size() - 1;
                    if(!isint(v1[i1-2]) and isint(v1[i1-1]) and isint(v1[i1])){
                        if(v1[i1] != 5)
                        v2.push_back(v1[i1]);
                        v2.push_back(v1[i1-2]);
                        v1.pop_back(); v1.pop_back(); v1.pop_back();
                        v1.push_back(5);
                    }
                    else break;
                }
                else break;
            }
        }
        for(int i:v2) cout << (char)i << " ";
        cout << "\n";
    }
    return 0;
}