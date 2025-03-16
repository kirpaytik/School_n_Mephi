#include <iostream>

using namespace std;

int main()
{
    int n,i,a,s,c;
    cin>>n;
    c=0;
    while(n>0)
    {
        cin>>a;
        s=0;
        while(a>0)
        {
            s=s+a%5;
            a=a/5;
        }
        if(s%5==0)
            c=c+1;
        n=n-1;
    }
    cout<<c;
    return 0;
}
