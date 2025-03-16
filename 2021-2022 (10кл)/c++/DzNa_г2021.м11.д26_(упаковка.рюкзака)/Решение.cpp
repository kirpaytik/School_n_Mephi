#include <iostream>
using namespace std;

int main()
{
    int v;
    cout<<"Введите объём рюкзака\n"; cin>>v;
    int ob, st;
    int mas1[v]={0}, mas2[v]={0};
    int n;
    cout<<"Введите количество предметов\n"; cin>>n;
    
    for (int nn=0; nn<n; nn++)
    {
        cout<<"Введите сначала объём предмета, а затем его стоимость\n"; cin>>ob>>st;
        for (int i=0; i<v; i++)
        {
            if (mas1[i]>0 and i+ob<v and mas1[i+ob]<mas1[i]+st)
                mas2[i+ob] = mas1[i] + st;
            else if (mas1[i]<st and i==ob-1) mas2[i] = st;
        }
        
        for (int j=0; j<v; j++)
            mas1[j] = mas2[j];
    }
    
    int max=0;
    for (int i=0; i<v; i++)
        if (mas1[i]>max)
            max = mas1[i];
    cout<<max;

    return 0;
}
