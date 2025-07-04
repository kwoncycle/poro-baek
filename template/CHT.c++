#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define X first
#define Y second
#define ll long long

struct CHT{
    vector<pii> stk; // (a, b)
    void insert(pii p){
        while(stk.size() >= 1 and stk.back().X == p.X and stk.back().Y > p.Y) stk.pop_back();
        if(stk.size() >= 1 and stk.back().X == p.X and stk.back().Y < p.Y) return;
        while(stk.size() >= 2 and cx(stk[stk.size()-2], p) > cx(stk[stk.size()-1], p)) stk.pop_back();
        stk.push_back(p);
    }
    double cx(pii p1, pii p2){
        return (double)(p2.Y - p1.Y) / (double)(p1.X - p2.X);
    }
    ll query(ll x){
        if(stk.size() == 1) return stk[0].X * x + stk[0].Y;
        int st = 0, ed = stk.size() - 1;
        if(x < cx(stk[st], stk[st + 1])){
            return stk[0].X * x + stk[0].Y;
        }
        while(st + 1 < ed){
            int md = (st + ed) / 2;
            if(cx(stk[md], stk[md + 1]) < x) st = md;
            else ed = md;
        }
        return stk[st + 1].X * x + stk[st + 1].Y;
    }
};

int main(){
    return 0;
}