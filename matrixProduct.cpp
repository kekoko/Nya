#include <iostream>
using namespace std;

string* fenge(string x){
	string *a;
	a = new string[2];
	int lg,cc;
	lg = x.length();
	cc = x.find("x");
	a[0] = x.substr(0,cc);
	a[1] = x.substr(cc+1,lg-cc-1);
	
	return a;
}
int main()
{
	string n,m;
	string *nn,*mm;
	cin>>n;
	cin>>m;
	nn = fenge(n);
	mm = fenge(m);
	
	if(nn[1] == mm[0]){
		cout<<nn[0]<<"x"<<mm[1];
	}
	else{
		cout<<"N";
	}
	delete nn;
	delete mm;
	return 0;
}

