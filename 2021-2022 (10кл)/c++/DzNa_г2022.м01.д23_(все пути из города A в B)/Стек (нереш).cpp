#include <iostream>
using namespace std;

int main()
{
    int pyti[8][8] = {0, 0, 0, 0, 0, 0, 1, 0,
                      0, 0, 0, 1, 1, 1, 0, 0,
                      1, 0, 0, 0, 0, 1, 0, 0,
                      0, 1, 0, 0, 1, 1, 0, 0,
                      0, 1, 1, 1, 0, 0, 0, 0,
                      1, 1, 0, 1, 1, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 1,
                      0, 1, 0, 0, 0, 0, 1, 0 };
    int n,b;
    cin >> n >> b;
    n--; b--;
    int stek[8];
    stek[0] = n;
    int mask[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    mask[n] = 1;
    int imass[8] = {0};
    
    int k=1;
    int i;
    while (k > 0)
    {
        if (stek[k-1] == b)
        {
            for (i=0; i<k; i++)
                cout << stek[i]+1 << "-";
            cout << endl;
            k--;
            mask[k] = 0;
        }
        else
        {
            if (imass[k] == 8)
            {
                imass[k] = 0;
                k--;
                mask[k] = 0;
            }
            else
                for (i=imass[k]; i<8; i++)
                {
                    imass[k]++;
                    if (pyti[stek[k-1]][i] == 1  and  mask[i] == 0)
                    {
                        mask[i] = 1;
                        stek[k] = i;
                        k++;
                        break;
                    }
                }
        }
    }
    
    return 0;
}
