#include <iostream>
using namespace std;

int main()
{
    int gr[7][7] = {{0,1,0,0,0,0,1},
                    {1,0,1,1,1,0,0},
                    {0,1,0,0,1,1,1},
                    {0,1,0,0,1,0,0},
                    {0,1,1,1,0,1,0},
                    {0,0,1,0,1,0,0},
                    {1,0,1,0,0,0,0}};
    
    int i,j;
    int chetver, flag=0;
    for (i=0; i<7; i++)
    {
        chetver = 0;
        for (j=0; j<7; j++)
            if (gr[i][j] == 1) chetver++;
        flag += chetver % 2;
    }
           
    if (flag > 0)
        cout << "Нету цикла Эйлера";
    else
    {
        int r=0;
        for (j=0; j<7; j++)
        {
            if (gr[r][j] == 1)
               {
                    cout << r+1 << " ";
                   gr[r][j] = 0; gr[j][r] = 0; r=j; j=-1;
               }
        }
        cout << r+1 << " ";
    }
   
    return 0;
}