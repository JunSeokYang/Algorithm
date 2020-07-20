#include <bits/stdc++.h>

using namespace std;

ifstream in("audio.inp");
ofstream out("audio.out");
vector<vector<int>> G;
long long ans, bitmask=0xF;
int N, buf, global_min=99999999999999;

void backtracking(short left_node, long long arrange, long long index, int weight){
    if(index==N){
        ans = arrange;
        global_min = weight;
        return;
    }
    long long gain;
    for(long long i=0; i<N; ++i){
        if(left_node & (1<<i)){
            gain = 0;
            for(long long j=0; j<index; ++j){
                for(int k=0; k<G[i].size(); ++k)
                    if(G[i][k] == (bitmask&((arrange & (bitmask<<(j*4)))>>(j*4)))){
                        gain += (index-j);
                        break;
                    }
            }
            if(gain+weight>=global_min)
                continue;
            arrange |= (i<<(index*4));
            left_node &= ~(1<<i);
            backtracking(left_node, arrange, index+1, weight+gain);
            left_node |= (1<<i);
            arrange &= ~(bitmask<<(index*4));
        }
    }
    return;
}

int main(){
    short left_node = 0x3FF;
    long long arrange=0;
    in>>N;
    G = vector<vector<int>>(N,vector<int>());
    for(int i=0; i<N; ++i){
        in>>buf;
        while(in>>buf){
            if(!buf)
                break;
            G[i].push_back(buf-1);
        }
    }
    backtracking(left_node, arrange, 0, 0);
    out<<global_min<<endl;
    for(long long i=0; i<N; ++i)
        out<<1+(bitmask&((ans & (bitmask<<(i*4)))>>(i*4)))<<' ';
    out<<endl;
    return 0;
}
