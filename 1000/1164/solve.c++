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

array<int,2> nxt[51][51];
vector<string> v;
vector<vector<int>> hz;
int found = 0;
void BT(int i, int j, int n, int m){
    if(found) return;
    //auto [nexti, nextj] = nxt[i][j];
    int nexti = i, nextj = j+1;
    if(nextj >= m){
        nextj-=m; nexti++;
    }
    if(i >= n and j == 0){
        found = 1;
        return;
    }

    if(v[i][j] == 'B'){
        if(j+1<m and (v[i][j+1] == 'B' or v[i][j+1] == 'X')){
            v[i][j+1] = 'B';
            nextj = nextj+1;
            if(nextj >= m){
                nextj-=m; nexti++;
            }
            BT(nexti, nextj, n, m);
        }
        else{
            found = 1;
            return;
        }
        return;
    }

    if(v[i][j] == '.' or v[i][j] == 'A'){
        if(found) return;
        BT(nexti, nextj, n, m);
        return;
    }

    if(i+1 < n and j+3 < m){
        bool b1 = (v[i][j+1] == 'X'), b2 = (v[i][j+2] == 'X');
        if(v[i][j] == 'X' 
        and v[i+1][j] == 'X'
        and v[i+1][j+1] == 'X'
        and v[i+1][j+2] == 'X'
        and v[i+1][j+3] == 'X'
        and v[i][j+3] == 'X'
        and b1 == b2
        and hz[i][j] == 1
        and hz[i][j+3] == 0
        and hz[i+1][j] == 1
        and hz[i+1][j+1] == 0
        and hz[i+1][j+2] == 1
        and hz[i+1][j+3] == 0
        ){
            v[i][j] = 'A';
            v[i+1][j] = 'A';
            v[i+1][j+1] = 'A';
            v[i+1][j+2] = 'A';
            v[i+1][j+3] = 'A';
            v[i][j+3] = 'A';
            if(b1){
                v[i][j+1] = 'B';
                v[i][j+2] = 'B';
            }
            if(found) return;
            nextj += 3;
            if(nextj >= m){
                nextj -= m; nexti++;
            }
            BT(nexti, nextj, n, m);
            if(found) return;
            if(b1){
                v[i][j+1] = 'X';
                v[i][j+2] = 'X';
            }
            v[i][j] = 'X';
            v[i+1][j] = 'X';
            v[i+1][j+1] = 'X';
            v[i+1][j+2] = 'X';
            v[i+1][j+3] = 'X';
            v[i][j+3] = 'X';
        }
    }

    if(j+1 < m){
        if(v[i][j] == 'X' and v[i][j+1] == 'X'){
            v[i][j] = 'B'; v[i][j+1] = 'B';
            if(found) return;
            nextj = nextj+1;
            if(nextj >= m){
                nextj-=m; nexti++;
            }
            BT(nexti, nextj, n, m);
            if(found) return;
            v[i][j] = 'X'; v[i][j+1] = 'X';
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    v.resize(n);
    for(int i=0; i<n; i++){
        cin >> v[i];
    }
    hz = vector<vector<int>>(n, vector<int>(m, 0));
    for(int i=0; i<n; i++){
        int cntx = 0;
        for(int j=0; j<m; j++){
            if(v[i][j] == 'X'){
                cntx++;
                hz[i][j] = cntx % 2;
            }
        }
    }

    for(int i=0; i<n-1; i++){
        for(int j=0; j<m-3; j++){
            int ct = 0;
            if(j+1<m and v[i][j+1] == 'X') ct++;
            bool b1 = (v[i][j+1] == 'X'), b2 = (v[i][j+2] == 'X');
            if(v[i][j] == 'X' 
            and v[i+1][j] == 'X'
            and v[i+1][j+1] == 'X'
            and v[i+1][j+2] == 'X'
            and v[i+1][j+3] == 'X'
            and v[i][j+3] == 'X'
            and b1 == b2
            and hz[i][j] == 1
            and ct == 0
            ){
                v[i][j] = 'A';
                v[i+1][j] = 'A';
                v[i+1][j+1] = 'A';
                v[i+1][j+2] = 'A';
                v[i+1][j+3] = 'A';
                v[i][j+3] = 'A';
                j += 3;
            }
        }
    }
    //cout << "========================================================\n\n\n";
    //for(int i=0; i<n; i++) cout << v[i] << "\n";

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == 'X') v[i][j] = 'B';
        }
    }

    for(int i=0; i<n-1; i++){
        for(int j=0; j<m-3; j++){
            bool b1 = (v[i][j+1] == 'B'), b2 = (v[i][j+2] == 'B');
            if(v[i][j] == 'B' 
            and v[i+1][j] == 'B'
            and v[i+1][j+1] == 'B'
            and v[i+1][j+2] == 'B'
            and v[i+1][j+3] == 'B'
            and v[i][j+3] == 'B'
            and b1
            and b2
            and hz[i][j] == 1
            and hz[i][j+3] == 0
            and hz[i+1][j] == 1
            and hz[i+1][j+1] == 0
            and hz[i+1][j+2] == 1
            and hz[i+1][j+3] == 0
            ){
                v[i][j] = 'A';
                v[i+1][j] = 'A';
                v[i+1][j+1] = 'A';
                v[i+1][j+2] = 'A';
                v[i+1][j+3] = 'A';
                v[i][j+3] = 'A';
            }
        }
    }
    found = 1;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == 'B'){
                if(j+1<m and v[i][j+1] == 'B'){
                    j++; continue;
                }
                else{
                    found = 0;
                }
            }
        }
    }

    if(found){
        for(int i=0; i<n; i++) cout << v[i] << "\n";
    }
    else{
        cout << "-1\n";
    }
    return 0;

    array<int, 2> prev = {-1, -1};
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == 'X'){
                if(prev[0] >= 0){
                    nxt[prev[0]][prev[1]] = {i, j};
                }
                prev = {i, j};
            }
        }
    }

    nxt[prev[0]][prev[1]] = {n, 0};

    prev[0] = -1;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == 'X'){
                prev = {i, j};
                goto out;
            }
        }
    }
    out:

    if(prev[0] != -1)
        BT(prev[0], prev[1], n, m);
    else found = 1;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == 'X') v[i][j] = 'B';
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == 'B'){
                if(j+1<m and v[i][j+1] == 'B'){
                    j++; continue;
                }
                else{
                    found = 0;
                }
            }
        }
    }

    if(found){
        for(int i=0; i<n; i++) cout << v[i] << "\n";
    }
    else{
        cout << "-1\n";
    }
    return 0;
}