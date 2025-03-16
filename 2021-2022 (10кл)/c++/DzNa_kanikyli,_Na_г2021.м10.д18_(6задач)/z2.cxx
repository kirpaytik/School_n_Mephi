#include <iostream>
using namespace std;

int main()
{
    short int n,c;
    cin>>n;
    int b[10][10] = {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                     {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};
	
    if(n%2==0)		// по часовой стрелке
    {
        if(n/2==0)			// начало с левого верхнего угла
        {
            b[0][0]=0;
            c=1;
            int i=0;
            int j=1;
            for(int g=0;g<5;g++)
            {
                while(b[i][j+1]==-1 and j!=9) {b[i][j]=c; c=c+1; j=j+1;}
                while(b[i+1][j]==-1 and i!=9) {b[i][j]=c; c=c+1; i=i+1;}
                while(b[i][j-1]==-1 and j!=0) {b[i][j]=c; c=c+1; j=j-1;}
                while(b[i-1][j]==-1 and i!=0) {b[i][j]=c; c=c+1; i=i-1;}
            }
            b[5][4]=99;
        }
        if(n/2==1)			// начало с правого верхнего угла
        {
            b[0][9]=0;
            c=1;
            int i=1;
            int j=9;
            for(int g=0;g<5;g++)
            {
                while(b[i+1][j]==-1 and i!=9) {b[i][j]=c; c=c+1; i=i+1;}
                while(b[i][j-1]==-1 and j!=0) {b[i][j]=c; c=c+1; j=j-1;}
                while(b[i-1][j]==-1 and i!=0) {b[i][j]=c; c=c+1; i=i-1;}
                while(b[i][j+1]==-1 and j!=9) {b[i][j]=c; c=c+1; j=j+1;}
            }
            b[4][4]=99;
        }
        if(n/2==3)			// начало с правого нижнего угла
        {
            b[9][9]=0;
            c=1;
            int i=9;
            int j=8;
            for(int g=0;g<5;g++)
            {
                while(b[i][j-1]==-1 and j!=0) {b[i][j]=c; c=c+1; j=j-1;}
                while(b[i-1][j]==-1 and i!=0) {b[i][j]=c; c=c+1; i=i-1;}
                while(b[i][j+1]==-1 and j!=9) {b[i][j]=c; c=c+1; j=j+1;}
                while(b[i+1][j]==-1 and i!=9) {b[i][j]=c; c=c+1; i=i+1;}
            }
            b[4][5]=99;
        }
        if(n/2==2)			// начало с левого нижнего угла
        {
            b[9][0]=0;
            c=1;
            int i=8;
            int j=0;
            for(int g=0;g<5;g++)
            {
                while(b[i-1][j]==-1 and i!=0) {b[i][j]=c; c=c+1; i=i-1;}
                while(b[i][j+1]==-1 and j!=9) {b[i][j]=c; c=c+1; j=j+1;}
                while(b[i+1][j]==-1 and i!=9) {b[i][j]=c; c=c+1; i=i+1;}
                while(b[i][j-1]==-1 and j!=0) {b[i][j]=c; c=c+1; j=j-1;}
            }
            b[5][5]=99;
        }
    }
    if(n%2==1)			// против часовой стрелки
    {
        if(n/2==0)			// начало с левого верхнего угла
        {
            b[0][0]=0;
            c=1;
            int i=1;
            int j=0;
            for(int g=0;g<5;g++)
            {
                while(b[i+1][j]==-1 and i!=9) {b[i][j]=c; c=c+1; i=i+1;}
                while(b[i][j+1]==-1 and j!=9) {b[i][j]=c; c=c+1; j=j+1;}
                while(b[i-1][j]==-1 and i!=0) {b[i][j]=c; c=c+1; i=i-1;}
                while(b[i][j-1]==-1 and j!=0) {b[i][j]=c; c=c+1; j=j-1;}
            }
            b[4][5]=99;
        }
        if(n/2==1)			// начало с правого верхнего угла
        {
            b[0][9]=0;
            c=1;
            int i=0;
            int j=8;
            for(int g=0;g<5;g++)
            {
                while(b[i][j-1]==-1 and j!=0) {b[i][j]=c; c=c+1; j=j-1;}
                while(b[i+1][j]==-1 and i!=9) {b[i][j]=c; c=c+1; i=i+1;}
                while(b[i][j+1]==-1 and j!=9) {b[i][j]=c; c=c+1; j=j+1;}
                while(b[i-1][j]==-1 and i!=0) {b[i][j]=c; c=c+1; i=i-1;}
            }
            b[5][5]=99;
        }
        if(n/2==3)			// начало с правого нижнего угла
        {
            b[9][9]=0;
            c=1;
            int i=8;
            int j=9;
            for(int g=0;g<5;g++)
            {
                while(b[i-1][j]==-1 and i!=0) {b[i][j]=c; c=c+1; i=i-1;}
                while(b[i][j-1]==-1 and j!=0) {b[i][j]=c; c=c+1; j=j-1;}
                while(b[i+1][j]==-1 and i!=9) {b[i][j]=c; c=c+1; i=i+1;}
                while(b[i][j+1]==-1 and j!=9) {b[i][j]=c; c=c+1; j=j+1;}
            }
            b[5][4]=99;
        }
        if(n/2==2)			// начало с левого нижнего угла
        {
            b[9][0]=0;
            c=1;
            int i=9;
            int j=1;
            for(int g=0;g<5;g++)
            {
                while(b[i][j+1]==-1 and j!=9) {b[i][j]=c; c=c+1; j=j+1;}
                while(b[i-1][j]==-1 and i!=0) {b[i][j]=c; c=c+1; i=i-1;}
                while(b[i][j-1]==-1 and j!=0) {b[i][j]=c; c=c+1; j=j-1;}
                while(b[i+1][j]==-1 and i!=9) {b[i][j]=c; c=c+1; i=i+1;}
            }
            b[4][4]=99;
        }
    }
    
    for (int t = 0; t < 10; t++)
    {
        for (int d = 0; d < 10; d++)
            cout<<b[t][d]<<" ";
        cout<<"\n";
    }
    return 0;
}
