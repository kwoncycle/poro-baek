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
    int tt; cin >> tt;
    for(int tc=1; tc<=tt; tc++){
        vector<string> s(9);
        for(int i=0; i<9; i++) cin >> s[i];
        int t = 82;
        while(t--){
            for(int i=0; i<9; i++){
                vector<int> check(10, 1);
                int cnt = 9;
                for(int j=0; j<9; j++){
                    if(s[i][j] != '0') {
                        check[s[i][j]-'0'] = 0;
                        cnt--;
                    }
                }
                if(cnt == 1){
                    char want = '0';
                    for(int j=1; j<=9; j++)
                        if(check[j]) want = '0' + j;
                    for(int j=0; j<9; j++){
                        if(s[i][j] == '0'){
                            s[i][j] = want;
                        }
                    }
                }
            }
            for(int i=0; i<9; i++){
                vector<int> check(10, 1);
                int cnt = 9;
                for(int j=0; j<9; j++){
                    if(s[j][i] != '0') {
                        check[s[j][i]-'0'] = 0;
                        cnt--;
                    }
                }
                if(cnt == 1){
                    char want = '0';
                    for(int j=1; j<=9; j++)
                        if(check[j]) want = '0' + j;
                    for(int j=0; j<9; j++){
                        if(s[j][i] == '0'){
                            s[j][i] = want;
                        }
                    }
                }
            }
            for(int i0 = 0; i0<9; i0+=3){
                for(int j0=0; j0<9; j0+=3){
                    vector<int> check(10, 1);
                    int cnt = 9;
                    for(int i=i0; i<i0+3; i++){
                        for(int j=j0; j<j0+3; j++){
                            if(s[j][i] != '0') {
                                check[s[j][i]-'0'] = 0;
                                cnt--;
                            }
                        }
                    }
                    if(cnt == 1){
                        char want = '0';
                        for(int j=1; j<=9; j++)
                            if(check[j]) want = '0' + j;
                        for(int i=i0; i<i0+3; i++){
                            for(int j=j0; j<j0+3; j++){
                                if(s[j][i] == '0'){
                                    s[j][i] = want;
                                }
                            }
                        }
                    }
                }
            }
        }
        cout << "Scenario #" << tc << ":\n";
        for(int i=0; i<9; i++) cout << s[i] << "\n";
        cout << "\n";
    }
    return 0;
}