#include <iostream>

using namespace std;

int main()
{
    int n,a,b1,b3,b7,b21;
    cin>>n;
    b1=0;
    b3=0;
    b7=0;
    b21=0;
    while(n>0)
    {
      cin>>a;
      if(a==1) b1=b1+1;
      if(a==3) b3=b3+1;
      if(a==7) b7=b7+1;
      if(a==21) b21=b21+1;
      n=n-1;
    }
    cout<<min(b1,b21)+min(b3,b7);
    return 0;
}
