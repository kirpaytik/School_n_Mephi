#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str; getline(cin, str);
    int dlina = str.size();
    string stroka[dlina];
    for (int i=0; i<dlina; i++)
        stroka[i] = str[i];
    
    string znaki = ")+-*/^(";
    string step = ")+-*/(";
    string muldev = ")+-(";
    string plumin = ")(";
    
    string stek[dlina]; int yk=0;
    string polska = "";
    
    for (int i=0; i<dlina; i++)
    {
        if (znaki.find(stroka[i]) > 1000)
            {polska += stroka[i];
            // cout<<"polska += '"<<stroka[i]<<"'"<<endl;
            }
        
        else
        {
            if (yk == 0)
            {   stek[yk] = stroka[i]; yk++; }
            
            else if (stroka[i] == "(")
            {   stek[yk] = "("; yk++;   }
            
            else if (stroka[i] == ")")
            {
                while(stek[yk-1] != "(")
                {
                    yk--;
                    polska += stek[yk];
                    // stek[yk] = "";
                }
                yk--; stek[yk] = "";
            }
            
            else if (stroka[i] == "+" or stroka[i] == "-")
            {
                while (yk>0 and plumin.find(stek[yk-1]) > 1000)
                {
                    yk--;
                    polska += stek[yk];
                    // stek[yk] = "";
                }
                stek[yk] = stroka[i]; yk++;
            }
            
            else if (stroka[i] == "*" or stroka[i] == "/")
            {
                while (yk>0 and muldev.find(stek[yk-1]) > 1000)
                {
                    yk--;
                    polska += stek[yk];
                    // stek[yk] = "";
                }
                stek[yk] = stroka[i]; yk++;
            }
            
            else
            if (stroka[i] == "^")
            {
                while (yk>0 and stek[yk-1] == "^")
                {
                    yk--;
                    polska += stek[yk];
                    // stek[yk] = "";
                }
                stek[yk] = stroka[i]; yk++;
            }
            
        }
    }
    
    while (yk>-1)
    {
        polska += stek[yk];
        yk--;
    }
    yk++;
    
    cout<<polska<<endl;
    
    string poli, poli2;
    int dl = polska.size();
    int stek2[dl] = {0}; yk=0;
    string znaki2 = "+-*/^";
    
    for (int i=0; i<dl; i++)
    {
        poli = polska[i];
        if (poli == " ")
        {
            poli2 = polska[i-1];
            if (poli2 != " ")
                yk++;
        }
        else
        {
            if (znaki2.find(polska[i]) > 1000000)
            {
                if (znaki2.find(polska[i]) < 10)
                    yk++;
                stek2[yk] = stek2[yk]*10 + stoi(poli);
            }
            
            else
            {
                yk++;
                if (znaki2.find(polska[i]) == 0)
                {
                    stek2[yk-2] = stek2[yk-2] + stek2[yk-1];
                    stek2[yk-1] = 0;
                    yk -= 2;
                }
                
                else if (znaki2.find(polska[i]) == 1)
                {
                    stek2[yk-2] = stek2[yk-2] - stek2[yk-1];
                    stek2[yk-1] = 0;
                    yk -= 2;
                }
                
                else if (znaki2.find(polska[i]) == 2)
                {
                    stek2[yk-2] = stek2[yk-2] * stek2[yk-1];
                    stek2[yk-1] = 0;
                    yk -= 2;
                }
                
                else if (znaki2.find(polska[i]) == 3)
                {
                    stek2[yk-2] = stek2[yk-2] / stek2[yk-1];
                    stek2[yk-1] = 0;
                    yk -= 2;
                }
                
                else if (znaki2.find(polska[i]) == 4)
                {
                    stek2[yk-2] = stek2[yk-2] ^ stek2[yk-1];
                    stek2[yk-1] = 0;
                    yk -= 2;
                }
            }
            
        }
        
    }
    
        
    cout<<stek2[0];

    return 0;
}
