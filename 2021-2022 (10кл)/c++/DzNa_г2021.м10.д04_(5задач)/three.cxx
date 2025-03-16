#include <iostream>

using namespace std;

int main()
{
    int a,b,s,c,d;
    c=0;
    d=0;
    cin>>b;
    s=b;
    while(s%777>0 or s==0)
    {
        a=b;
        cin>>b;
        s=s+b;
        if(b>a) {d=d+1; c=max(c,d);}
        else d=0;
    }
    if(c==0) cout<<0;
    else cout<<c+1;
    return 0;
}
