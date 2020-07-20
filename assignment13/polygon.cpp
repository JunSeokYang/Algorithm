#include <bits/stdc++.h>

using namespace std;

ifstream in("polygon.inp");
ofstream out("polygon.out");
vector<int> xv, yv;
int N, x[3], y[3], z;
int main(){
    in>>N;
    int i,j,cnt=0, x1, x2, x3, y1, y2, y3, flag1, flag2;
    bool None=false;
    in>>x[0]>>y[0];
    in>>x[1]>>y[1];
    xv.push_back(x[0]);
    yv.push_back(y[0]);
    xv.push_back(x[1]);
    yv.push_back(y[1]);
    for(i=0; i<N; ++i){
        if(i == N-2){
            x[2] = xv[0];
            y[2] = yv[0];
        }
        else if(i == N-1){
            x[2] = xv[1];
            y[2] = yv[1];
        }
        else{
            in>>x[2]>>y[2];
            xv.push_back(x[2]);
            yv.push_back(y[2]);
        }
        if((((x[0]*y[1]) + (x[1]*y[2]) + (x[2]*y[0])) - ((x[0]*y[2]) + (x[2]*y[1]) + (x[1]*y[0])))>0)
            ++cnt;
        x[0] = x[1];
        y[0] = y[1];
        x[1] = x[2];
        y[1] = y[2];
    }

    for(i=0; i<N-2; ++i){
        for(j=i+2; j<N; ++j){
            if(i==0 && j==N-1)
                continue;
            x1 = xv[i]; x2 = xv[i+1]; x3 = xv[j];
            y1 = yv[i]; y2 = yv[i+1]; y3 = yv[j];
            flag1 = (x1*y2 + x2*y3 + x3*y1 - x1*y3 - x3*y2 - x2*y1);
            x3 = xv[(j+1)%N]; y3 = yv[(j+1)%N];
            flag2 = (x1*y2 + x2*y3 + x3*y1 - x1*y3 - x3*y2 - x2*y1);
            if((flag1<0 && flag2<0) || (flag1>0 && flag2>0) || (flag1==0 && flag2==0)){
                continue;
            }
            x1 = xv[j]; x2 = xv[(j+1)%N]; x3 = xv[i];
            y1 = yv[j]; y2 = yv[(j+1)%N]; y3 = yv[i];
            flag1 = (x1*y2 + x2*y3 + x3*y1 - x1*y3 - x3*y2 - x2*y1);
            x3 = xv[i+1]; y3 = yv[i+1];
            flag2 = (x1*y2 + x2*y3 + x3*y1 - x1*y3 - x3*y2 - x2*y1);
            if((flag1<0 && flag2<0) || (flag1>0 && flag2>0) || (flag1==0 && flag2==0)){
                continue;
            }
            i = j = N;
            None = true;
        }
    }

    if(None)
        out<<"None\n";
    else if(cnt == 0)
        out<<"Convex\n";
    else
        out<<"Concave "<<cnt<<'\n';

}
