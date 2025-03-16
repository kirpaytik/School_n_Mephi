#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int a,b,c,l;
    cin>>a>>b;
    c=0;
    l=0;
    while(a>0 or b>0)
    {
        c= max(a%10,b%10)*pow(10,l) + c;
        l=l+1;
        a=a/10;
        b=b/10;
    }
    cout<<c;
    return 0;
}
