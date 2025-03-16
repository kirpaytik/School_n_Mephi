#include <iostream>
using namespace std;

int gr[7][7] = {{0,1,0,0,0,0,1},
                {1,0,1,1,1,0,0},
                {0,1,0,0,1,1,1},
                {0,1,0,0,1,0,0},
                {0,1,1,1,0,1,0},
                {0,0,1,0,1,0,0},
                {1,0,1,0,0,0,0}};

void rec(int r)
{
    for (int j=0; j<7; j++)
        if (gr[r][j] == 1)
           {gr[r][j] = 0; gr[j][r] = 0; rec(j);}
    cout << r+1 << "-";
}

int main()
{
    int chetver, flag=0;
    for (int i=0; i<7; i++)
    {
        chetver = 0;
        for (int j=0; j<7; j++)
            if (gr[i][j] == 1) chetver++;
        flag += chetver % 2;
    }
           
    if (flag > 0)
        cout << "Нету цикла Эйлера";
    else
    {
        cout << "-";
        rec(0);
    }
   
    return 0;
}
