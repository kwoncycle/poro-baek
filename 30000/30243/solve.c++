#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

int n;
int arr[31], val[31];
vector<int> missing, need;

void mixneed(){
    for(int i=1; i<=n; i++){
        val[i] = rand() & 0xffff;
    }
    int sz = need.size();
    if(sz <= 10){
        sort(all(need), [&](int l, int r){
            return val[l] < val[r];
        });
    }
    else{
        int i1 = rand() % (sz-10), i2 = rand() % 10;
        sort(need.begin() + i1, need.begin() + i1 + i2, [&](int l, int r){
            return val[l] < val[r];
        });
    }
}


int collide(){
    for(int i=1; i<=n; i++){
        for(int j=i+1; j<=n; j++){
            if(j-i == abs(arr[j] - arr[i])) return 1;

        }
    }
    return 0;
}

int main(){
    srand(time(0));
    cin >> n;
    for(int i=1; i<=n; i++) cin >> arr[i];
    for(int i=1; i<=n; i++){
        if(arr[i] == 0) missing.push_back(i);
    }
    for(int i=1; i<=n; i++){
        int truth = 1;
        for(int j=1; j<=n; j++){
            if(arr[j] == i) truth = 0;
        }
        if(truth) need.push_back(i);
    }
    int sz = missing.size();
    if(sz >= 11){
        for(int cnt=0; cnt<=100000; cnt++){
            mixneed();
            for(int i=0; i<sz; i++){
                arr[missing[i]] = need[i];
            }
            while(true){
                int truth = 0;
                for(int i=0; i<sz; i++){
                    for(int j=i+1; j<sz; j++){
                        int before = 0;
                        for(int id=1; id<=n; id++){
                            if(abs(missing[i] - id) == abs(arr[missing[i]] - arr[id])) before++;
                            if(abs(missing[j] - id) == abs(arr[missing[j]] - arr[id])) before++;
                        }
                        swap(arr[missing[i]], arr[missing[j]]);
                        int after = 0;
                        for(int id=1; id<=n; id++){
                            if(abs(missing[i] - id) == abs(arr[missing[i]] - arr[id])) after++;
                            if(abs(missing[j] - id) == abs(arr[missing[j]] - arr[id])) after++;
                        }
                        if(before > after){
                            truth = 1;
                        }
                        else swap(arr[missing[i]], arr[missing[j]]);
                    }
                }
                if(!truth) break;
            }
            int cur = collide();
            if(cur == 0){
                for(int i=1; i<=n; i++) cout << arr[i] << " ";
                cout << "\n";
                return 0;
            }
        }
        cout << "-1\n";
    }
    else{
        do{
            for(int i=0; i<sz; i++){
                arr[missing[i]] = need[i];
            }
            if(!collide()){
                for(int i=1; i<=n; i++) cout << arr[i] << " ";
                cout << "\n";
                return 0;
            }
        }while(next_permutation(all(need)));

        cout << "-1\n";
    }


    return 0;
}