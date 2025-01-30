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
    while(true){
        string s; cin >> s;
        string stmp = s;
        if(s[0] == '#') break;
        string s1; cin >> s1;
        stmp = s1;
        int n = s.size();
        int blck = 0, grey = 0, white = 0;
        for(int i=0; i<n; i++){
            if(s1[i] == s[i]){
                s[i] = 1;
                s1[i] = 255;
                blck++;
            }
        }
        vector<int> cnt(26, 0), cnt1(26, 0);
        for(int i=0; i<n; i++){
            if(s[i] >= 'A' and s[i] <= 'Z')
                cnt[s[i]-'A']++;
            if(s1[i] >= 'A' and s1[i] <= 'Z')
                cnt1[s1[i] - 'A']++;
        }
        for(int i=0; i<n; i++){
            if((i > 0 and s1[i] == s[i-1])){
                grey++;
                cnt1[s1[i]-'A']--;
                cnt[s[i-1]-'A']--;
                s1[i] = 2;
                s[i-1] = 254;
            }
            if((i+1 < n and s1[i] == s[i+1])){
                grey++;
                cnt1[s1[i]-'A']--;
                cnt[s[i+1]-'A']--;
                s1[i] = 2;
                s[i+1] = 254;
            }
        }

        for(int i=0; i<26; i++){
            white += min(cnt[i], cnt1[i]);
        }
        cout << stmp << ": " << blck << " black, " << grey << " grey, " << white << " white\n"; 
    }
    return 0;
}