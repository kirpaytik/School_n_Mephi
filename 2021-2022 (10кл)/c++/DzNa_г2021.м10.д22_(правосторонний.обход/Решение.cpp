#include <iostream>
using namespace std;

int main()
{
    int nx[4] = {1,0,-1,0};
    int ny[4] = {0,-1,0,1};
    int matr[10][10];
    int f=0;
    int ii,jj;
    cout<<"Заполнять матрицу следует только единицами и нулями\n";
    for(int i=0; i<10; i=i+1)
        for(int j=0; j<10; j=j+1)
        {
            cin>>matr[i][j];
            if(matr[i][j]==1 and f==0) {matr[i-1][j]=3; ii=i; jj=j; f=1;}
        }
    int i=ii-1; int j=jj+1;
    int n = 3;
    while(matr[i][j+nx[n]]!=3)
    {
        if(matr[i+ny[n]][j+nx[n]]==0) {matr[i][j]=2; i=i+ny[n]; j=j+nx[n]; n=(n+3)%4;}
        else n=(n+1)%4;
    }
    matr[i][j]=2; matr[ii-1][j]=2;
    for(int i=0; i<10; i=i+1)
    {
        for(int j=0; j<10; j=j+1)
	cout<<matr[i][j]<<" ";
        cout<<"\n";
    }
    return 0;
}