#include <iostream>
using namespace std;
int a,b, mink=0;
int mass[1024] = {0};

int pow2[11] = {1,2,4,8,16,32,64,128,256,512,1024};
void rec(int c, int k)
{
    if (c == b and (k<mink or mink==0))
        mink = k;
    else
    {
        cout << c << endl;
        int i, cCopy=c;
        for (i=0; i<10; i++)
        {
            c = ((c&pow2[i]) == 0  ?  c+pow2[i]  :  c-pow2[i]);
            c = ((c&pow2[i+1]) == 0  ?  c+pow2[i+1]  :  c-pow2[i+1]);
            if (mass[c] == 0)
            {
                mass[c] = 1;
                rec(c, k+1);
                mass[c] = 0;
            }
            c = cCopy;
        }
    }
}

int main()
{
    cin >> a >> b;
    int n; cin >> n;
    int i,strin;
    for (i=0; i<n; i++)
    {
        cin >> strin; mass[strin] = 1;
    }
    
    rec(a,0);
    cout << mink;
    
    return 0;
}
