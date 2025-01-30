#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <stack>
#include <string.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define X first
#define Y second
#define GETVECTOR(n) for(int i=0; i< (n); i++) scanf("%d ",&inp[i]);
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n
typedef struct p3{
	int a; int b; int c;
}p3;

char a[1000005];
int main(){
    int tt; scanf("%d",&tt);
    while(tt--){
        scanf("%s",a);
        int n = strlen(a);
        stack<char> s, b;
        for(int i=0; i<n; i++){
            if(a[i] == '<'){
                if(s.empty()) continue;
                char c = s.top();
                s.pop(); b.push(c);
            }
            else if(a[i] == '>'){
                if(b.empty()) continue;
                char c = b.top();
                b.pop(); s.push(c);
            }
            else if(a[i] == '-'){
                if(s.empty()) continue;
                s.pop();
            }
            else{
                s.push(a[i]);
            }
        }
        int ns = s.size(), nb = b.size();
        a[ns + nb] = 0;
        for(int i=0; i<ns; i++){
            a[ns - i - 1] = s.top(); s.pop();
        }
        for(int i=0; i<nb; i++){
            a[ns + i] = b.top(); b.pop();
        }
        printf("%s\n",a);
    }
    return 0;
}