#include <iostream>

using namespace std;

int main()
{
    int n,i,a,s,c;
	cin>>n;
	c = 0;
	for(i=0;i<n;i++)
	{
		s = 0;
		cin>>a;
		while(a>0)
		{
			s = s + a%10;
			cout<<s;
			cout<<'\n';
			a = a/10;
		}
		if(s%2==0)
			c = c+1;
	}
	cout<<c;

    return 0;
}
