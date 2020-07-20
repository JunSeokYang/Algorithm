#include <bits/stdc++.h>

using namespace std;


ifstream input("ct.inp");
ofstream output("ct.out");
vector<vector<int>> lst;
vector<int> r,c,rd,ld;
int N, in, lbuf, rbuf;

struct cmp{
    bool operator()(vector<int> t, vector<int> u){
        return t[N] < u[N];
    }
};

void BFS(vector<vector<int> > &arr, int p, int q, int t){
    stack<int> bfsx, bfsy;
    int i,j,x[] = {-1,0,1,0}, y[] = {0,1,0,-1};
    bfsx.push(p);
    bfsy.push(q);
    while(!bfsx.empty()){
        i = bfsx.top();
        j = bfsy.top();
        bfsx.pop();
        bfsy.pop();
        if(arr[i][j]==t){
            arr[i][j] = !t;
            for(int k=0; k<4; k++)
                if( (i+x[k] >=0) && (i+x[k] < N) && (j+y[k] >=0) && (j+y[k] < N) )
                    if(arr[i+x[k]][j+y[k]]==t){
                        bfsx.push(i+x[k]);
                        bfsy.push(j+y[k]);
                    }
        }
    }
}

bool check(vector<vector<int>> chk){
    vector<vector<int>> bfst = chk, dfst = chk;
    int sum,p,q;
    for(int i=0; i<N; ++i){
        sum = 0;
        for(int j=0; j<N; ++j)
            sum += chk[j][i];
        if(sum != c[i])
            return 0;
    }
    for(int i=0; i<N; ++i){
        sum = 0;
        for(int j=0; j<N; ++j)
            sum += chk[i][j];
        if(sum != r[i])
            return 0;
    }
    for(int i=0; i<2*N-1; ++i){
        sum = 0;
        lbuf = i/N?N-i%N-1:i+1;
        rbuf = i/N?0:N-1-i;
        for(int j=0; j<lbuf; ++j)
            sum += chk[(i/N)*(i%N+1) + j][rbuf+j];
        if(sum != ld[i])
            return 0;
    }
    for(int i=0; i<2*N-1; ++i){
        sum = 0;
        lbuf = i/N?N-i%N-1:i+1;
        rbuf = i/N?i-1-(i%N):i;
        for(int j=0; j<lbuf; ++j)
            sum += chk[(i/N)*(i%N+1)+ j][rbuf-j];
        if(sum != rd[i])
            return 0;
    }

    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j){
            if(dfst[i][j]){
                BFS(dfst, i,j,1);
                i = j = N;
            }
        }

    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j)
            if(dfst[i][j])
                return 0;

    for(int i=0; i<N; ++i)
        BFS(bfst, 0, i ,0);
    for(int i=0; i<N; ++i)
        BFS(bfst, i, 0,0);
    for(int i=0; i<N; ++i)
        BFS(bfst, i, N-1,0);
    for(int i=0; i<N; ++i)
        BFS(bfst, N-1, i,0);
	
    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j)
            if(!bfst[i][j])
                return 0;


    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j)
            if(chk[i][j])
                output<<"B ";
            else
                output<<"- ";
        output<<endl;
    }
    return 1;

}

bool backtracking(vector<vector<int>> visit, vector<int> row, vector<int> left, vector<int> right, int index){
    vector<int> iter(N,0), myperm;
    if(check(visit))
        return 1;
    if(index == N)
        return 0;
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    int sum,cnt;
    for(int j=0; j<c[index]; ++j)
        iter[N-1-j] = 1;
    do{
        sum = cnt = 0;
        myperm = iter;
        for(int k=0; k<N; ++k){
            if(iter[k]*!(row[k] && left[N+k-index-1] && right[k+index]))
                continue;
            sum += iter[k]*lst[k][index];
            cnt += iter[k];
        }
        if(sum && (cnt == c[index])){
            myperm.push_back(sum);
            pq.push(myperm);
        }
    }while(next_permutation(iter.begin(), iter.end()));

    while(!pq.empty()){
        vector<int> rowb = row, leftb = left, rightb = right;
        myperm = pq.top();
        pq.pop();
        for(int k=0; k<N; ++k){
            rowb[k] -= myperm[k]; leftb[N+k-index-1] -= myperm[k]; rightb[k+index] -= myperm[k];
            visit[k][index] = myperm[k];
        }
        if(backtracking(visit, rowb, leftb, rightb, index+1))
            return 1;
    }
    if(!c[index])
        return backtracking(visit, row, left, right, index+1);
    return 0;
}

int main(){
    input>>N;
    lst = vector<vector<int>>(N,vector<int>(N,0));
    vector<vector<int>> pre(N, vector<int>(N,0));
    for(int i=0; i<N; ++i){
        input>>in;
        c.push_back(in);
        for(int j=0; j<N; ++j)
            lst[j][i] += c[i];
    }
    for(int i=0; i<N; ++i){
        input>>in;
        r.push_back(in);
        for(int j=0; j<N; ++j)
            lst[i][j] += r[i];
    }
    for(int i=0; i<2*N-1; ++i){
        input>>in;
        ld.push_back(in);
        lbuf = i/N?N-i%N-1:i+1;
        rbuf = i/N?0:N-1-i;
        for(int j=0; j<lbuf; ++j)
            lst[(i/N)*(i%N+1) + j][rbuf+j] += ld[i];
    }
    for(int i=0; i<2*N-1; ++i){
        input>>in;
        rd.push_back(in);
        lbuf = i/N?N-i%N-1:i+1;
        rbuf = i/N?i-1-(i%N):i;
        for(int j=0; j<lbuf; ++j)
            lst[(i/N)*(i%N+1)+ j][rbuf-j] += rd[i];
    }
    for(int i=0; i<N; i++)
        if(backtracking(pre, r,ld, rd, i))
            return 0;
    return 0;
}
