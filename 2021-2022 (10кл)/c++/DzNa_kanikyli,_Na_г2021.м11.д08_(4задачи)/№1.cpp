#include <iostream>
using namespace std;
#include <cmath>

int main()
{
	long long n;
	cin >> n;
	long long nn = n;
	int nnum1[19];
	for (int i = 18; i > -1; i--)
	{
		nnum1[i] = nn % 10;
		nn /= 10;
	}
	nn = n;
	int ii;
	for (int i = 0; i < 19; i++)
		if (nnum1[i] != 0){ii = i; break;}
	int x2=0, xmax=0;
	cout<<ii<<endl;
	for (int i=0; i<19-ii; i++)
	{
	    for(int j=ii+i; j<19; j++)
	    {
            x2 = x2*10 + nnum1[j];
            if(sqrt(x2)==(int)sqrt(x2))
                if(x2>xmax*xmax) xmax = sqrt(x2);
	    }
	    x2 = 0;
	}
	cout<<xmax;

	return 0;
}