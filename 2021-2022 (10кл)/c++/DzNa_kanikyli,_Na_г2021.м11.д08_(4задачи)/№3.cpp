#include <iostream>
using namespace std;

int main()
{
    int n, sum=0;
    cin >> n;
    int x,y;
    for(int i=2; i<=n; i++)
    {
        --sum += i;
        for(int j=2; j<i; j++)
        {
            x = i; y = j;
            while(x%y != 0)
            {
                x = x%y;
                swap(x,y);
            }
            if(y > 1) sum--;
        }
    }
   
    int mass[sum][2], numstr = 0;
    for(int i=2; i<=n; i++)
    {
        for(int j=1; j<i; j++)
        {
            x = i; y = j;
            while(x%y != 0)
            {
                x = x%y;
                swap(x,y);
            }
            if(y > 1) continue;
            mass[numstr][0] = j;
            mass[numstr][1] = i;
            numstr++;
        }
    }
   
   
    int pyz;
    for(int j=0; j<sum-1; j++) //j in range(len(numtrue)-1):
    {
    pyz = 0;
    for(int i=j+1; i<sum-1-j; i++) //i in range(j+1, len(numtrue)-1-j):
    {
    if((float)mass[i][0]/mass[i][1] > (float)mass[i+1][0]/mass[i+1][1]) //if(numtrue[i] > numtrue[i+1]):
    {pyz = 1; swap(mass[i][0], mass[i+1][0]); swap(mass[i][1], mass[i+1][1]);} //numtrue[i], numtrue[i+1] = numtrue[i+1], numtrue[i]
    //pyz = 1
    if((float)mass[sum-i-1][0]/mass[sum-i-1][1] < (float)mass[sum-i-2][0]/mass[sum-i-2][1]) //if(numtrue[len(numtrue)-i-1] < numtrue[len(numtrue)-i-2]):
    {pyz=1; swap(mass[sum-i-1][0], mass[sum-i-2][0]); swap(mass[sum-i-1][1], mass[sum-i-2][1]);} //numtrue[len(numtrue)-i-1], numtrue[len(numtrue)-i-2] = numtrue[len(numtrue)-i-2], numtrue[len(numtrue)-i-1
    //pyz = 1
    //print(numtrue)
    }
    //print()
    if(pyz==0) break; //if(pyz==0):
    //print("pyz0")
    //break
    }
   
   
    // for(int i=sum-1; i>0; i--)
    // {
    //     pyz = 0;
    //     for(int j=0; j<i; j++)
    //         if((float)mass[j][0]/mass[j][1] > (float)mass[j+1][0]/mass[j+1][1])
    //             {pyz = 1; swap(mass[j][0], mass[j+1][0]); swap(mass[j][1], mass[j+1][1]);}
    //     if(pyz==0) break;
    // }
   
   
    for(int i=0; i<sum; i++)
        cout << mass[i][0] << " " << mass[i][1] << endl;

    return 0;
}
