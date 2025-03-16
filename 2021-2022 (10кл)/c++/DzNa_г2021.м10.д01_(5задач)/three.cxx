#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int a,b,c,d,f;
    cin>>a;
    cin>>b;
    c=(a%10)*pow(10,(9-(a%10)));
    a=a/10;
    while (a>0)
    {
        f=0;
        d=c;
        while(d>0)
        {
            if(d%10==a%10)
               f=1;
            d=d/10;
        }
        if(f==0)
            c=c+ (a%10)*pow(10,(9-(a%10)));
        a=a/10;
    }
    while (b>0)
    {
        f=0;
        d=c;
        while(d>0)
        {
            if(d%10==b%10)
               f=1;
            d=d/10;
        }
        if(f==0)
            c=c+ (b%10)*pow(10,(9-(b%10)));
        b=b/10;
    }
    d=0;
    int l;
    l=0;
    while(c>0)
    {
        if(c%10==0)
            c=c/10;
        if(c%10>0)
        {
            d= (c%10)*pow(10,l) + d;
            l=l+1;
            c=c/10;
        }
    }
    cout<<d;
    return 0;
}
