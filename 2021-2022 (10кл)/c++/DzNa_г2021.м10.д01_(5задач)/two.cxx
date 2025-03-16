#include <iostream>

using namespace std;

int main()
{
    int a,b1,b2,b3,b4,b5;
    cin>>a;
    b1=0;
    b2=0;
    b3=0;
    b4=0;
    b5=0;
    while(a>0)
    {
        if(a>b5)
        {
            b5=a;
            if(a>b4)
            {
                b5=b4;
                b4=a;
                if(a>b3)
                {
                    b4=b3;
                    b3=a;
                    if(a>b2)
                    {
                        b3=b2;
                        b2=a;
                        if(a>b1)
                        {
                            b2=b1;
                            b1=a;
                        }
                    }
                }
            }
        }
        cin>>a;
    }
    cout<<b1<<', '<<b2<<', '<<b3<<', '<<b4<<', '<<b5;
    return 0;
}
