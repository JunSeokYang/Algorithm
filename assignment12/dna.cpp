#include <bits/stdc++.h>

using namespace std;

string A, B;
int alen, blen;
ofstream output;
string SearchStr(vector<vector<int > > &mat, int x, int y){
    if(x<2 || y<2 || !(mat[x][y]))
        return "";
    vector<string> lst;
    string s="";
    for(int i=1; i<3; ++i)
        for(int j=1; j<3; ++j)
            if(A[x-2]==B[y-2])
                if(mat[x][y] == (mat[x-i][y-j]+1))
                    lst.push_back(SearchStr(mat, x-i, y-j));
    if(!lst.empty())
        s = lst[0];
    for(int i=1; i<lst.size(); ++i)
        if(s>lst[i])
            s = lst[i];
    return s+A[x-2];
}

string LCS(){
    vector<vector<int > > mat(alen+2,vector<int >(blen+2,0));
    vector<string> lst;
    vector<int> x,y;
    string s;
    int mx=0;
    for(int i=2; i<alen+2; ++i)
        for(int j=2; j<blen+2; ++j){
            mat[i][j] = (A[i-2]==B[j-2])*(max(max(mat[i-1][j-1], mat[i-2][j-2]), max(mat[i-1][j-2], mat[i-2][j-1]))+1);
            if(mx<mat[i][j]){
                mx = mat[i][j];
                x.clear(); y.clear();
            }
            if(mat[i][j] == mx){
                x.push_back(i); y.push_back(j);
            }
        }

    for(int i=0; i<x.size(); ++i)
        lst.push_back(SearchStr(mat, x[i], y[i]));
    s = lst[0];
    for(int i=1; i<lst.size(); ++i)
        if(s>lst[i])
            s = lst[i];
    return s;
}

int main(void){
    ifstream  input("dna.inp");
    output.open("dna.out");
    string buf;
    input>>A>>B;
    alen = A.length();
    blen = B.length();
    buf = LCS();
    cout<<buf<<endl;
    output<<buf;
    return 0;
}
