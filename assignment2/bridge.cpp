#include <bits/stdc++.h>

using namespace std;

typedef struct point{
    float x[3];
} Point;

inline float leng(Point A, Point B){
    float sum=0;
    for(int i=0; i<3; ++i)
        sum += (A.x[i]-B.x[i])*(A.x[i]-B.x[i]);
    return sqrt(sum);
}

class My_comp{
public:
    My_comp():result(0){};
    int operator()(Point *s);
private:
    float result;
};

int My_comp::operator()(Point *s){
    float a,b,c;
    Point k;
    for(int i=0; i<3; ++i)
        k.x[i] = s[0].x[i]*0.5 + s[1].x[i]*0.5;
    a=leng(s[0], s[2]);
    c=leng(s[1], s[2]);
    b=leng(k, s[2]);

    if(((int)a == (int)b) &&((int)b == (int)c)) return (int)b + (b-(int)b>0);
    else if(a<c) s[1] = k;
    else s[0] = k;
    result = b;
    return operator()(s);

}

int main(void){
    ifstream input("bridge.inp");
    ofstream output("bridge.out");
    My_comp Shortest;
    Point dots[3];

    for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
            input>>dots[i].x[j];

    output<<Shortest(dots);

    input.close();
    output.close();
    return 0;
}
