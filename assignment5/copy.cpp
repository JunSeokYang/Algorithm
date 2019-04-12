#include <bits/stdc++.h>

using namespace std;

wstring Q;
int len, blen;
int LCS(wstring buf){
    vector<vector<int > > mat(len+1,vector<int >(blen+1,0));
    for(int i=1; i<=len; ++i)
        for(int j=1; j<=blen; ++j)
            mat[i][j] = max(max(mat[i-1][j], mat[i][j-1]), mat[i-1][j-1] + (Q[i-1]==buf[j-1]));
    return mat[len][blen];
}

wstring mystr(wfstream &input){
    wstring ret;
    wchar_t buf, pre='\0';
    while((buf = input.get()) != L'$'){
        if(buf == L'는')
            buf = L'은';
        else if(buf == L'를')
            buf = L'을';
        else if(buf == L' ')
            if(pre == L' ')
                continue;
        ret = ret + buf;
        pre = buf;
    }
    return ret;
}

int main(void){
    locale loc("en_US.UTF-8");
    ios::sync_with_stdio(false);
    wfstream input("copy.inp");
    wofstream output("copy.out");
    input.imbue(loc);
    wcout.imbue(loc);
    wstring buf;
    float mx=0,sim;
    int N, index=1, lbuf;
    input>>N;
    Q = mystr(input);
    len = Q.length();
    for(int i=0; i<N-1; ++i){
        buf = mystr(input);
        blen = buf.length();
        lbuf = LCS(buf);
        sim = (float)lbuf*2/(blen + len);
        wcout<<Q<<endl<<buf<<endl;
        cout<<len<<' '<<blen<<' '<<sim<<' '<<lbuf<<endl;
        if(sim>mx){
            mx = sim;
            index = i+2;
        }
    }
    output<<index;
    return 0;
}
