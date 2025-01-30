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
    int n; char b;
    cin >> n >> b;
    string s; cin >> s;

    char def = b - 'A' + 'a';
    int cnt = 0;
    for(int i=0; i<n; i++){
        if(s[i] == def) cnt++;
    }
    if(cnt == 0){
        string s1, s2;
        for(int i=0; i<n; i++){
            if(s[i] == b) s1.push_back(s[i]);
            else s2.push_back(s[i]);
        }
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        string ans1 = s1+s2, ans2 = s2+s1;
        cout << min(ans1, ans2) << "\n";
        return 0;
    }
    if(cnt == 1){
        string s1, s2, s3;
        for(int i=0; i<n; i++){
            if(s[i] == b) s1.push_back(s[i]);
            else if(s[i] == def) s3.push_back(s[i]);
            else s2.push_back(s[i]);
        }
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        string ans1 = s1+s3+s2, ans2 = s2+s3+s1;
        cout << min(ans1, ans2) << "\n";
        return 0;
    }
    else{
        string s1, s2, s3;
        for(int i=0; i<n; i++){
            if(s[i] == b) s1.push_back(s[i]);
            else if(s[i] == def) s3.push_back(s[i]);
            else s2.push_back(s[i]);
        }
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        string s4 = s2 + string(cnt - 1, def);
        sort(s4.begin(), s4.end());
        string ans1 = s1+string(1, def) + s4, ans2 = s4 + string(1, def) + s1;
        
        string C1, C2, C3;
        for(int i=0; i<n; i++){
            if(s[i] != b and (s[i] >= 'A' and s[i] <= 'Z')){
                C1.push_back(s[i]);
            }
            else if(s[i] != b and s[i] != def) C2.push_back(s[i]);
            else if(s[i] == b) C3.push_back(s[i]);
        }
        C2 = C2 + string(cnt-2, def);
        sort(C1.begin(), C1.end());
        sort(C2.begin(), C2.end());
        string ans3 = C1 + string(1, def) + C3 + string(1, def) + C2;

        string D1, D2, D3, D4;
        for(int i=0; i<n; i++){
            if(s[i] != b and (s[i] >= 'A' and s[i] <= 'Z')){
                D1.push_back(s[i]);
            }
            else if(s[i] != b and s[i] < def) D2.push_back(s[i]);
            else if(s[i] != b and s[i] > def) D4.push_back(s[i]);
            else if(s[i] == b) D3.push_back(s[i]);
        }
        D4 = D4 + string(cnt-2, def);
        sort(D1.begin(), D1.end());
        sort(D2.begin(), D2.end());
        sort(D4.begin(), D4.end());
        string ans4 = D1 + D2 + string(1, def) + D3 + string(1, def) + D4;
        int cnt2 = 0;
        for(int i=0; i<n; i++){
            if(s[i] == b) cnt2++;
        }

        int cn1 = cnt, Cn2 = cnt2;
        string S4;
        S4.push_back(def); cn1--;
        // S2 S1 S3    bBBBBBBb

        //cout << ans1 << "\n";
        //cout << ans2 << "\n";
        //cout << ans3 << "\n";
        cout << min(min(ans3, ans4), min(ans1, ans2)) << "\n";
        return 0;
    }
    return 0;
}