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

bool isalpha(char c){
    if('a'<=c and c<='z') return true;
    if('A'<=c and c<='Z') return true;
    return false; 
}

bool isCap(char c){
    if('A'<=c and c<='Z') return true;
    return false; 
}

char toCap(char c){
    if(isCap(c)) return c;
    return c + 'A' - 'a';
}

char toNoCap(char c){
    if(!isCap(c)) return c;
    return c + 'a' - 'A';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    while(true){
        string s;
        getline(cin, s);
        if(s.size() == 1 and s[0] == '#') break;
        int n = s.size();
        string ans;
        for(int i=0; i<n; i++){
            if(s[i] == ' '){
                ans.push_back(' '); continue;
            }
            int j = i;
            while(j<n and s[j] != ' ') j++;
            vector<char> vc;
            for(int i1=j-1; i1>=i; i1--){
                if(isalpha(s[i1])) vc.push_back(s[i1]);
            }
            int idx = 0;
            for(int i1=i; i1<j; i1++){
                if(!isalpha(s[i1])) ans.push_back(s[i1]);
                else{
                    if(isCap(s[i1])){
                        ans.push_back(toCap(vc[idx]));
                    }
                    else{
                        ans.push_back(toNoCap(vc[idx]));
                    }
                    idx++;
                }
            }
            i = j-1;
        }
        cout << ans << "\n";
    }
    return 0;
}