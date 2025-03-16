#include <iostream>
using namespace std;

int main()
{
    int a,b; cin >> a >> b;
    if (a > b) {int c=a; a=b; b=c;}
    
    int sum=0;
    while (a <= b)
    {
        if (a/100000 + (a/10000)%10 + (a/1000)%10 == (a/100)%10 + (a/10)%10 + a%10)
            if (a/100000 * (a/10000)%10 * (a/1000)%10 == (a/100)%10 * (a/10)%10 * a%10)
                sum++;
        a++;
    }
    cout << sum;
    
    return 0;
}
