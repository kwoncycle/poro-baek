#include <bits/stdc++.h>
using namespace std;

namespace Aho
{
    const int MAXN = 100 + 4; // sum of the lengths
    const int MAXC = 26;
    int term[MAXN], len[MAXN], to[MAXN][MAXC], link[MAXN], sz = 1;
    void add(string s){
        int x = 0;
        for (auto &c : s){
            c -= 'a';
            if (!to[x][c]){
                to[x][c] = sz++;
                len[to[x][c]] = len[x] + 1;
            }
            x = to[x][c];
        }
        term[x] = x;
    }
    void push_links(){
        queue<int> q;
        q.push(0);
        while (!q.empty()){
            int x = q.front();
            q.pop();
            int y = link[x];
            if (!term[x]) term[x] = term[y];
            for (int c = 0; c < MAXC; c++){
                if (to[x][c]){
                    link[to[x][c]] = x ? to[y][c] : 0;
                    q.push(to[x][c]);
                }
                else to[x][c] = to[y][c];
            }
        }
    }
    bool get(string s){
        int x = 0;
        for (auto &c : s){
            x = to[x][c - 'a'];
            if (term[x]) return 1;
        }
        return 0;
    }
};