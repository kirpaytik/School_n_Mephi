#include <iostream>
using namespace std;

int main()
{
    int matr[7][7] = {{0,1,0,0,0,0,1},
                      {1,0,1,1,1,0,0},
                      {0,1,0,0,1,1,1},
                      {0,1,0,0,1,0,0},
                      {0,1,1,1,0,1,0},
                      {0,0,1,0,1,0,0},
                      {1,0,1,0,0,0,0}};
    int kolrebr = 0;
    for (int i=0; i<7; i++)
        for (int j=0; j<7; j++)
            if (matr[i][j] == 1) kolrebr++;
    kolrebr /= 2;
    int stek[++kolrebr] = {0};
    stek[0] = 1;
    //for (int i=0; i<kolrebr; i++)
        //cout<<stek[i];
    //cout<<endl<<endl;
    int ykaz = 0;
   
    int flagfori0 = 0;
    int i,j;
    for (i=1; i<8; i++)
    {//cout<<i<<" ";
        if (flagfori0 == 1) {i=0; flagfori0 = 0;}
        for (j=1; j<8; j++)
        {//cout<<j<<" m"<<matr[i-1][j-1];
            if (matr[i-1][j-1]==1) {stek[++ykaz] = j; matr[i-1][j-1]=0;matr[j-1][i-1]=0;  i=j-1; break;}
            if (j==7) {cout<<stek[ykaz]<<" ";  stek[ykaz--] = 0;  i=stek[ykaz]; j=1;}
           
        }
        //cout<<endl<<"STEK";
        //for (int t=0; t<kolrebr; t++)
            //cout<<stek[t];
        //cout<<endl;
        if (i==0) {cout<<"DA"; flagfori0=1; i=5;}
        //cout<<i;
        //cout<<endl;
       
        if (stek[0]==0) break;
       
    }
    //cout<<"H";
    return 0;
}