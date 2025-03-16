// проверял только на маленьком количестве букв. На большом нет возможности (не удаётся попробовать)
// на 24 строке в цикле for (i=0; i<34010; i++) (после строки int flag;) i меняется до 34010. Это потому что в файле, который прислал учитель, всего столько слов (строк). Для другого количества слов меняйте это число в параметрах цикла

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream Fin;
    Fin.open("word_rus.txt");
    
    int n;
    cin >> n;
    string slovo;
    cin >> slovo;
    
    string otvet[30];
    int otv=0;
    
    int i,j;
    string newWord;
    int flag;
    for (i=0; i<34010; i++)
    {
        Fin >> newWord;
        if (n*2 == newWord.length())
        {
            flag = 0;
            for (j=0; j<n*2; j+=2)
            {
                if (slovo.substr(j,2) != newWord.substr(j,2))
                    flag++;
            }
            if (flag == 1)
            {
                otvet[otv++] = newWord;
            }
        }
    }
    
    for (i=0; i<n; i++)
        cout << i << otvet[i] << endl;
}
