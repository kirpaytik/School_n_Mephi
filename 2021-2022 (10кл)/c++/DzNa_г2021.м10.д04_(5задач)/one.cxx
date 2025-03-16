#include <iostream>

using namespace std;

int main()
{
    int n,a,b,s;
    cin>>n;
    s=0;
    cin>>b;
    n=n-1;
    while(n>0)
    {
        a=b;
        cin>>b;
        if((a+b)%2==0) s=s+1;
        n=n-1;
    }
    cout<<s;
    return 0;
}
