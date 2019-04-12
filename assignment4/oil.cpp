#include "oil.h"

#define MIN(x,y) x<y?x:y
#define MAX(x,y) x>y?x:y

int f,l;

bool Search(int it_f, int it_l){
    int mid=(it_f + it_l)/2,o1,o2=2,ret=1;
    if(it_l-it_f<3){
        --ret;
        o1 = observe(it_f,it_f+1);
        if(o1!=2){
            f = MIN((o1?it_f:it_l),f);
            l = MAX((o1?it_f+1:it_l),l);
        }
        else{
            o2 = observe(it_f+1, it_l);
            f = MIN(it_f+(o2>0),f);
            if(!o2)
                l = MAX(it_f,l);
            else
                l = MAX((o2%2?it_l:it_f+1),l);
        }
        return (o1+2)%3 == o2;
    }
    else
        o1 = observe(it_f, mid);
    if(o1/2)
        ret = Search(it_f, mid);
    if(o1*ret)
        o2 = observe(mid+1, it_l);
    if(ret*(o2/2))
        ret = Search(mid+1, it_l);
    if(o1%2|o2%2){
        f = MIN(((o1%2)?it_f:mid+1),f);
        l = MAX((o2%2)?it_l:mid,l);
    }
    return !((o1/2 + o1%2)*(!(o2%2)));
}

int main(void){
    initial();
    Search(l=0, f=oil_size()-1);
	oil_report(f,l);
    return 0;
}
