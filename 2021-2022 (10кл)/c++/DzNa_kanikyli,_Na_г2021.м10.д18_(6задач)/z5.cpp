#include <iostream>
using namespace std;

int main()
{
    int a[10][10];
    int max[10] = {0,0,0,0,0,0,0,0,0,0};
    int min[10] = {0,0,0,0,0,0,0,0,0,0};
    for(int i=0; i<10; i=i+1)
        for(int j=0; j<10; j=j+1)
            cin>>a[i][j];
            if(a[i][j]>max[i]) max[i]=a[i][j];
            if(a[i][j]<min[j]) min[j]=a[i][j];
    
    int s=0;
    for(int i=0; i<10; i=i+1)
        for(int j=0; j<10; j=j+1)
            if(a[i][j]==max[i]==min[j]) {cout<<i<<" "<<j; s=s+1;}
    cout<<s;
    
    return 0;
}
