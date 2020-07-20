#include <bits/stdc++.h>

using namespace std;

vector<int> ans;
ifstream in("diet.inp");
ofstream out("diet.out");
int N, global_cost=10000;

void backtracking(vector<int> diet, vector<vector<int>> lst, int pcost, vector<int> alist){
    int i, idx=0, mx=0, sum=0;
    for(i=0; i<4; ++i){
        sum += (diet[i]>0);
        if(mx<diet[i]){
            idx = i;
            mx = diet[i];
        }
    }
    if(!sum){
        if(global_cost>pcost){
            global_cost = pcost;
            ans = alist;
        }
        return;
    }
    mx = -1;
    for(i=0; i<N; ++i)
        if(lst[i][5])
            mx = i;
    if(mx<0)
        return;
    lst[mx][5]=0;
    backtracking(diet, lst, pcost, alist);
    alist.push_back(mx);
    for(i=0; i<4; ++i)
        diet[i] -= lst[mx][i];
    backtracking(diet, lst, pcost + lst[mx][4], alist);
    return;
}

int main(void){
    int i,j, buf, idx;
    in>>N;
    vector<int> diet(4,0);
    vector<vector<int>> lst(N,vector<int>(6,1));
    for(i=0; i<4; ++i)
        in>>diet[i];
    for(i=0; i<N; ++i)
        for(j=0; j<5; ++j)
            in>>lst[i][j];
    backtracking(diet, lst, 0, vector<int>());
    sort(ans.begin(), ans.end());
    for(int i=0; i<ans.size(); ++i)
        out<<ans[i]+1<<' ';
    return 0;
}
