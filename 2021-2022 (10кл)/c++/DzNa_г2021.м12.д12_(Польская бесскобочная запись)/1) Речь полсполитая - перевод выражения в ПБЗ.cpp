#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str; cin>>str; // ВВОД БЕЗ ПРОБЕЛОВ: a+b*(c-d*e+f)^g/h
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
            polska += stroka[i];
        
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
    
    cout<<polska;

    return 0;
}
