#include <iostream>
using namespace std;

int a[10][10]=
    {{1,0,0,0,0,0,0,0,0,1},
     {0,1,0,0,0,0,0,0,1,0},
     {0,0,1,0,0,0,0,1,0,0},
     {0,0,0,1,0,0,1,0,0,0},
     {0,0,0,0,1,1,0,0,0,0},
     {0,0,0,0,1,1,0,0,0,0},
     {0,0,0,1,0,0,1,0,0,0},
     {0,0,1,0,0,0,0,1,0,0},
     {0,1,0,0,0,0,0,0,1,0},
     {1,0,0,0,0,0,0,0,0,1}};
    
void fill(int m)
{
    for(int i=0; i<10; i=i+1)
    {
        for(int j=0; j<10; j=j+1)
        {
            if(m==1)
                if(i<j and (i+j)>9 and a[i][j]==0) a[i][j]=2;
            if(m==2)
                if(i<j and (i+j)<9 and a[i][j]==0) a[i][j]=2;
            if(m==4)
                if(i>j and (i+j)<9 and a[i][j]==0) a[i][j]=2;
            if(m==8)
                if(i>j and (i+j)>9 and a[i][j]==0) a[i][j]=2;
        }
    }
}

int main()
{
    short int n;
    cin>>n;
    
    
    for(int i=1; i<9; i=i<<1) fill(n&i);
    
    for(int g=0; g<10; g=g+1)
    {
        for(int k=0; k<10; k=k+1)
            cout<<a[g][k]<<" ";
        cout<<"\n";
    }
    
    return 0;
}
