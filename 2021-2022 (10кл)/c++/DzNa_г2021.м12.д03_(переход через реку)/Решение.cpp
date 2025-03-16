#include <iostream>
using namespace std;

int main()
{
    int reka[8][9] = {{0,0, 0, 0, 0, 0,  0,   0,  0},
                      {0,46,35,16,25,1,  13,  7,  0},
                      {0,16,14,13,15,2,  4,   0,  0},
                      {0,2, 1, 1, 18,1,  0,   2,  0},
                      {0,1, 8, 2, 3, 1,  123, 13, 0},
                      {0,2, 5, 10,12,15, 34,  57, 0},
                      {0,1, 1, 1, 1, 1,  1,   1,  1},
                      {0,1, 1, 1, 1, 1,  1,   1,  1}};
    int volna[8][9], vnapr[8][9];
    for (int i=0; i<8; i++)
        for (int j=0; j<9; j++)
            vnapr[i][j] = -1;
    for (int j=1; j<8; j++)
        vnapr[7][j] = 3;
    for (int i=0; i<8; i++)
        for (int j=0; j<9; j++)
            volna[i][j] = 99999;
    for (int j=1; j<8; j++)
        volna[7][j] = reka[7][j];
   
   
   // волна
    int flag = 0;
    while (flag==0)
    {
        flag = 1;
        for (int i=6; i>0; i--)
            for (int j=1; j<8; j++)
            {
                if (volna[i][j+1] <= volna[i-1][j] and volna[i][j+1] <= volna[i][j-1] and volna[i][j+1] <= volna[i+1][j]) // если идём справа
                    {   if (volna[i][j+1] + reka[i][j] < volna[i][j])
                        {   
                            volna[i][j] = volna[i][j+1] + reka[i][j];
                            vnapr[i][j] = 0;
                            flag = 0;
                        }
                    }
                else if (volna[i-1][j] <= volna[i][j+1] and volna[i-1][j] <= volna[i][j-1] and volna[i-1][j] <= volna[i+1][j]) // если идём сверху
                    {   if (volna[i-1][j] + reka[i][j] < volna[i][j])
                        {
                            volna[i][j] = volna[i-1][j] + reka[i][j];
                            vnapr[i][j] = 1;
                            flag = 0;
                        }
                    }
                else if (volna[i][j-1] <= volna[i][j+1] and volna[i][j-1] <= volna[i-1][j] and volna[i][j-1] <= volna[i+1][j]) // если идём слева
                    {   if (volna[i][j-1] + reka[i][j] < volna[i][j])
                        {
                            volna[i][j] = volna[i][j-1] + reka[i][j];
                            vnapr[i][j] = 2;
                            flag = 0;
                        }
                    }
                else if (volna[i+1][j] <= volna[i][j+1] and volna[i+1][j] <= volna[i-1][j] and volna[i+1][j] <= volna[i][j-1]) // если идём снизу
                    {   if (volna[i+1][j] + reka[i][j] < volna[i][j])
                        {
                            volna[i][j] = volna[i+1][j] + reka[i][j];
                            vnapr[i][j] = 3;
                            flag = 0;
                        }
                    }
            }
        
    }
    
    
    // вывод суммы и координат
    int minexit=1;
    for (int j=2; j<8; j++)
        if (volna[1][j] < volna[1][minexit]) minexit = j;
    int coord[25][2];
    for (int i=0; i<25; i++)
        {coord[i][0] = -1; coord[i][1] = -1;}
    
    int i=1,j=minexit,  ii=1;
    int xnapr[] = {1, 0, -1, 0};
    int ynapr[] = {0, -1, 0, 1};
    int nn=0;
    while (i<8)
    {
        coord[nn][0] = i; coord[nn][1] = j; nn++;
        ii += ynapr[vnapr[i][j]];
        j += xnapr[vnapr[i][j]];
        i = ii;
    }
    
    cout<<volna[1][minexit]<<endl;
    for (auto t: coord)
    {
        if (t[0] == -1) break;
        cout<<t[0]<<" "<<t[1]<<endl;
    }
    return 0;
}