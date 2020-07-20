#include <bits/stdc++.h>
int main(){
	std::ifstream i("hamburg.inp");
	std::ofstream o("hamburg.out");
	int k,n,a[20],m=0,j,c=0;
	char b;
	i>>k>>n;
	for(;i>>b;++m)
		for(j=k;j>0;--j){
			a[m]=n=b=='P';
			if(m-j>=0&&(a[m-j]+n)==1){
				a[m-j]=a[m]=2;
				c++;
				j=0;
			}
		}
	o<<c;
}