#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define X first
#define Y second

bool isvalid(vector<int> &v){
    int n = v.size()-2;
    int cnt = 0;
    for(int i=1; i<=n-2; i++){
        if((v[i]<v[i+1]) != (v[i+1]<v[i+2])) cnt++;
        if(v[i] <= 0 or v[i] > n) return false;
    }
    if(v[n] <= 0 or v[n-1] <= 0 or v[n] > n or v[n-1] > n) return false;
    return cnt <= 1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<int> v(n+2), v_left(n+2), v_right(n+2), chk(n+2+n);
    for(int i=1; i<=n; i++) {
        cin >> v[i]; chk[v[i]] = 1;
    }
    int truth = 0;
    for(int i:v){
        if(i) truth = 1;
    }
    if(!truth){
        for(int i=1; i<=n; i++) cout << i << " "; cout << "\n";
        return 0;
    }

    for(int i=1; i<=n; i++){
        v_left[i] = v[i]; v_right[i] = v[i];
    }
    for(int i=1; i<=n; i++){
        if(v_left[i] == 0){
            v_left[i] = v_left[i-1];
        }
    }
    for(int i=n; i>=1; i--){
        if(v_right[i] == 0){
            v_right[i] = v_right[i+1];
        }
    }

    int il = 1, ir = n;
    while(v[il]) il++;
    while(v[ir]) ir--;
    int target = 1;
    while(il <= ir){
        while(chk[target]) target++;
        if(v_right[il] == v_left[ir] or v_right[il] == v_right[ir]) break;
        if(v_right[il] > v_left[ir]){
            if(v_left[ir] > target and target > v[ir+1]){
                v[ir] = target; chk[target] = 1;
                while(v[ir]) ir--;
            }
            else{
                v[il] = target; chk[target] = 1;
                while(v[il]) il++;
            }
        }
        else{
            if(v[il-1] < target and target < v_right[il]){
                v[il] = target; chk[target] = 1;
                while(v[il]) il++;
            }
            else{
                v[ir] = target; chk[target] = 1;
                while(v[ir]) ir--;
            }
        }
    }
    if(v_right[il] == v_right[ir]){
        if(v[il-1] < v[ir+1]){
            for(int i=il; i<=ir; i++){
                while(chk[target]) target++;
                v[i] = target; chk[target] = 1;
            }
        }
        else{
            for(int i=ir; i>=il; i--){
                while(chk[target]) target++;
                v[i] = target; chk[target] = 1;
            }
        }
        if(isvalid(v)){
            for(int i=1; i<=n; i++) cout << v[i] << " "; cout << "\n";
        }
        else cout << "*\n";
        
        return 0;
    }

    {
        int il_1 = il, ir_1 = ir, target1 = target;
        vector<int> v1 = v, chk1 = chk;
        target1 = v[il_1-1] + 1;
        for(int i=il_1; i<=ir_1; i++){
            if(v1[i]){
                int u = n; while(chk1[u]) u--;
                v1[i+1] = u; chk1[u] = 1; break;
            }
            while(chk1[target1]) target1++;
            v1[i] = target1; chk1[target1] = 1;
        }
        target1 = v[ir_1 + 1] + 1;
        for(int i=ir_1; i>=il_1; i--){
            if(v1[i]) break;
            while(chk1[target1]) target1++;
            v1[i] = target1; chk1[target1] = 1;
        }
        if(isvalid(v1)){
            for(int i=1; i<=n; i++) cout << v1[i] << " "; cout << "\n";
            return 0;
        }
    }

    {
        int il_1 = il, ir_1 = ir, target1 = target;
        vector<int> v1 = v, chk1 = chk;
        target1 = v[ir_1 + 1] + 1;
        for(int i=ir_1; i>=il_1; i--){
            if(v1[i]){
                int u = n; while(chk1[u]) u--;
                v1[i-1] = u; chk1[u] = 1; break;
            }
            while(chk1[target1]) target1++;
            v1[i] = target1; chk1[target1] = 1;
        }
        target1 = v[il_1-1] + 1;
        for(int i=il_1; i<=ir_1; i++){
            if(v1[i]) break;
            while(chk1[target1]) target1++;
            v1[i] = target1; chk1[target1] = 1;
        }
        if(isvalid(v1)){
            for(int i=1; i<=n; i++) cout << v1[i] << " "; cout << "\n";
            return 0;
        }
    }

    {
        int il_1 = il, ir_1 = ir, target1 = target;
        vector<int> v1 = v, chk1 = chk;
        for(int i=ir_1; i>=il_1; i--){
            if(v1[i]){
                continue;
            }
            while(chk1[target1]) target1++;
            v1[i] = target1; chk1[target1] = 1;
        }
        if(isvalid(v1)){
            for(int i=1; i<=n; i++) cout << v1[i] << " "; cout << "\n";
            return 0;
        }
    }

    {
        int il_1 = il, ir_1 = ir, target1 = target;
        vector<int> v1 = v, chk1 = chk;
        for(int i=il_1; i<=ir_1; i++){
            if(v1[i]){
                continue;
            }
            while(chk1[target1]) target1++;
            v1[i] = target1; chk1[target1] = 1;
        }
        if(isvalid(v1)){
            for(int i=1; i<=n; i++) cout << v1[i] << " "; cout << "\n";
            return 0;
        }
    }
    if(isvalid(v)){
        for(int i=1; i<=n; i++) cout << v[i] << " "; cout << "\n";
    }
    else cout << "*\n";

    return 0;
}