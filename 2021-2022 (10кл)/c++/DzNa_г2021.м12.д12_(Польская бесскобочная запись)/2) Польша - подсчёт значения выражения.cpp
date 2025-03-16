#include <iostream>
#include <string>
using namespace std;

int main()
{
    string polska; getline(cin, polska); string poli;   // ВВОД С ПРОБЕЛАМИ: 1 2 + 345 * 12 4 2 / ^ -
    int dlina = polska.size();
    int stek[dlina] = {0}; int yk=0;   // Может, нужен float stek? Иначе 5/2=2
    string znaki = "+-*/^";
    
    for (int i=0; i<dlina; i++)
    {
        poli = polska[i];
        if (poli == " ")
            yk++;
        else
        {
            if (znaki.find(polska[i]) > 1000000)
                stek[yk] = stek[yk]*10 + stoi(poli);
            
            else
            {
                if (znaki.find(polska[i]) == 0)
                {
                    stek[yk-2] = stek[yk-2] + stek[yk-1];
                    stek[yk-1] = 0;
                    yk -= 2;
                }
                
                else if (znaki.find(polska[i]) == 1)
                {
                    stek[yk-2] = stek[yk-2] - stek[yk-1];
                    stek[yk-1] = 0;
                    yk -= 2;
                }
                
                else if (znaki.find(polska[i]) == 2)
                {
                    stek[yk-2] = stek[yk-2] * stek[yk-1];
                    stek[yk-1] = 0;
                    yk -= 2;
                }
                
                else if (znaki.find(polska[i]) == 3)
                {
                    stek[yk-2] = stek[yk-2] / stek[yk-1];
                    stek[yk-1] = 0;
                    yk -= 2;
                }
                
                else if (znaki.find(polska[i]) == 4)
                {
                    stek[yk-2] = stek[yk-2] ^ stek[yk-1];
                    stek[yk-1] = 0;
                    yk -= 2;
                }
            }
            
        }
        
    }
    
        
    cout<<stek[0];
    
    return 0;
}
