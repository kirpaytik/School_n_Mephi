#include <iostream>
using namespace std;

int pyti[8][8] = {0, 0, 0, 0, 0, 0, 1, 0,
                  0, 0, 0, 1, 1, 1, 0, 0,
                  1, 0, 0, 0, 0, 1, 0, 0,
                  0, 1, 0, 0, 1, 1, 0, 0,
                  0, 1, 1, 1, 0, 0, 0, 0,
                  1, 1, 0, 1, 1, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 1,
                  0, 1, 0, 0, 0, 0, 1, 0 };
int a[8];
int mask[8] = {0, 0, 0, 0, 0, 0, 0, 0,};
int n,b;

void rec(int k)
{
    if (a[k-1] == b)
    {
        for (int i=0; i<k; i++)
            cout << a[i]+1 << "-";
        cout << endl;
    }
    else
    {
        int i;
        for (i=0; i<8; i++)
            if (pyti[a[k-1]][i] == 1  and  mask[i] == 0)
            {
                mask[i] = 1;
                a[k] = i;
                rec(k+1);
                mask[i] = 0;
            }
    }
}

int main()
{
    cin >> n >> b;
    n--; b--;
    a[0] = n;
    mask[n] = 1;

    rec(1);
   
    return 0;
}