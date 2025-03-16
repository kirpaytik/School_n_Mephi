#include <iostream>
using namespace std;

int pole[8][8] = {21, 31, 41, 51, 61, 41, 31, 21,
                  11, 11, 11, 11, 11, 11, 11, 11,
                  0,  0,  0,  0,  0,  0,  0,  0,
                  0,  0,  0,  0,  0,  0,  0,  0,
                  0,  0,  0,  0,  0,  0,  0,  0,
                  0,  0,  0,  0,  0,  0,  0,  0,
                  10, 10, 10, 10, 10, 10, 10, 10,
                  20, 30, 40, 50, 60, 40, 30, 20};

string poleFigur[8][8] = {"","","","","","","","",
                          "","","","","","","","",
                          "","","","","","","","",
                          "","","","","","","","",
                          "","","","","","","","",
                          "","","","","","","","",
                          "","","","","","","","",
                          "","","","","","","",""};

int turnNum = 0;

int sign(int x)
{
    return (x>0  ?  1  :  -1);
}

void moveP (string a, string b, int color)
{
    turnNum++;
    int j1 = (int)(a[0] - 97);
    int i1 = (int)(a[1]) - 48;
    int j2 = (int)(b[0] - 97);
    int i2 = (int)(b[1]) - 48;

    if ((pole[8-i2][j2] == 0  or  pole[8-i2][j2]%10 != color)  and  j1 == j2)
    {
        if (i2-i1 == (color==0 ? 1 : -1))
        {
            pole[8-i1][j1] = 0;
            pole[8-i2][j2] = 10 + color;
        }
        else if ((i2 == (color==0 ? 4 : 5))  and  pole[8-(color==0 ? 3 : 4)][j2] == 0)
        {
            pole[8-i1][j1] = 0;
            pole[8-i2][j2] = 10 + color;
        }
        else
            cout << "Невозможнен " << turnNum << "й ход" << endl;
    }
    else if (abs(j2-j1) == 1  and  abs(i2-i1) == 1  and  pole[8-i2][j2] > 0  and pole[8-i2][j2]%10 != color)
    {
        pole[8-i1][j1] = 0;
        pole[8-i2][j2] = 10 + color;
    }
    else
        cout << "Невозможнен " << turnNum << "й ход" << endl;
}

void moveL (string a, string b, int color, int figura)
{
    turnNum++;
    int j1 = (int)(a[0] - 97);
    int i1 = (int)(a[1]) - 48;
    int j2 = (int)(b[0] - 97);
    int i2 = (int)(b[1]) - 48;

    if (j1 == j2)
    {
        int c = i1, flag = 0;
        c += sign(i2-i1);
        while (c != i2)
        {
            flag += pole[8-c][j1];
            c += sign(i2-i1);
        }
        if (pole[8-c][j1] > 0  and  pole[8-c][j1]%10 == color)
            flag++;
        
        if (flag == 0)
        {
            pole[8-i1][j1] = 0;
            pole[8-i2][j2] = figura + color;
        }
        else
            cout << "Невозможнен " << turnNum << "й ход" << endl;
    }
    else if (i1 == i2)
    {
        int c = j1, flag = 0;
        c += sign(j2-j1);
        while (c != j2)
        {
            flag += pole[8-i1][c];
            c += sign(j2-j1);
        }
        if (pole[8-i1][c] > 0  and  pole[8-i1][c]%10 == 0)
            flag ++;
        
        if (flag == 0)
        {
            pole[8-i1][j1] = 0;
            pole[8-i2][j2] = figura + color;
        }
        else
            cout << "Невозможнен " << turnNum << "й ход" << endl;
    }
    else
        cout << "Невозможнен " << turnNum << "й ход" << endl;
}

void moveH (string a, string b, int color)
{
    turnNum++;
    int j1 = (int)(a[0] - 97);
    int i1 = (int)(a[1]) - 48;
    int j2 = (int)(b[0] - 97);
    int i2 = (int)(b[1]) - 48;
    
    if ((i2-i1)*(i2-i1) + (j2-j1)*(j2-j1) == 5)
    {
        if (pole[8-i2][j2] == 0   or   pole[8-i2][j2] != color)
        {
            pole[8-i1][j1] = 0;
            pole[8-i2][j2] = 30 + color;
        }
        else
            cout << "Невозможнен" << turnNum << "й ход" << endl;
    }
    else
        cout << "Невозможнен" << turnNum << "й ход" << endl;
}

void moveE (string a, string b, int color, int figura)
{
    turnNum++;
    int j1 = (int)(a[0] - 97);
    int i1 = (int)(a[1]) - 48;
    int j2 = (int)(b[0] - 97);
    int i2 = (int)(b[1]) - 48;
    
    if (abs(i2-i1) == abs (j2-j1))
    {
        int ci = i1, cj = j1, flag = 0;
        ci += sign(i2-i1);
        cj += sign(j2-j1);
        while (ci != i2)
        {
            flag += pole[8-ci][cj];
            ci += sign(i2-i1);
            cj += sign(j2-j1);
        }
        if (pole[8-ci][cj]>0 and color == pole[8-ci][cj]%10)
            flag++;
        
        if (flag == 0)
        {
            pole[8-i1][j1] = 0;
            pole[8-i2][j2] = figura + color;
        }
        else
            cout << "Невозможнен " << turnNum << "й ход" << endl;
    }
    else
        cout << "Невозможнен " << turnNum << "й ход" << endl;
}

void moveQ (string a, string b, int color)
{
    int j1 = (int)(a[0] - 97);
    int i1 = (int)(a[1]) - 48;
    int j2 = (int)(b[0] - 97);
    int i2 = (int)(b[1]) - 48;
    
    if (i1 == i2  or  j1 == j2)
        moveL(a, b, color, 50);
    else if (abs(i2-i1) == abs(j2-j1))
        moveE(a, b, color, 50);
    else
        cout << "Невозможнен " << ++turnNum << "й ход" << endl;
}

void moveK (string a, string b, int color)
{
    turnNum++;
    int j1 = (int)(a[0] - 97);
    int i1 = (int)(a[1]) - 48;
    int j2 = (int)(b[0] - 97);
    int i2 = (int)(b[1]) - 48;
    
    if (abs(i2-i1)<2  and  abs(j2-j1)<2  and  (pole[8-i2][j2] == 0  or  pole[8-i2][j2] % 10 != color))
       {pole[8-i1][j1] = 0; pole[8-i2][j2] = 60+color;}
    else
        cout << "Невозможнен " << turnNum << "й ход" << endl;
}

void justMove (string a, string b)
{
    int a0 = (int)(a[0] - 97);
    int a1 = (int)(a[1]) - 48;
    
    if (pole[8-a1][a0] / 10 == 1)
        moveP (a, b, pole[8-a1][a0]%10);
    else if (pole[8-a1][a0] / 10 == 2)
        moveL (a, b, pole[8-a1][a0]%10, 2);
    else if (pole[8-a1][a0] / 10 == 3)
        moveH (a, b, pole[8-a1][a0]%10);
    else if (pole[8-a1][a0] / 10 == 4)
        moveE (a, b, pole[8-a1][a0]%10, 4);
    else if (pole[8-a1][a0] / 10 == 5)
        moveQ (a, b, pole[8-a1][a0]%10);
    else
        moveK (a, b, pole[8-a1][a0]%10);
}

void read()
{
    cout << "Вводите 4 клетки в каждой строке: 2 клетки для хода белых и ещё две для хода чёрных. В конце ввода введите - 0 0" << endl;
    string cell1, cell2;
    string nulstr = "0";
    int k11, k12;
    cin >> cell1 >> cell2;
    int colorTurn = 0;
    while (cell1 != nulstr)
    {
        if (cell1 == cell2)
            cout << "Невозможнен " << ++turnNum << "й ход" << endl;
        else
        {
            k11 = (int)(cell1[0] - 97);
            k12 = (int)(cell1[1]) - 48;
            
            if (pole[8-k12][k11] == 0)
                cout << "Невозможнен" << ++turnNum << "й ход" << endl;
            else if (pole[8-k12][k11]%10 != colorTurn)
                cout << "Сейчас ход " << (colorTurn==0 ? "белых" : "чёрных") << endl;
            else
            {
                justMove (cell1, cell2);
                colorTurn = 1-colorTurn;
            }
        }
        
        cin >> cell1 >> cell2;
    }
}

void vivod()
{
    int i,j;
    string nameFigura;
    for (i=0; i<8; i++)
    {
        for (j=0; j<8; j++)
        {
            if (pole[i][j] > 0)
            {
                if (pole[i][j]/10 == 1)
                    nameFigura = "P";
                else if (pole[i][j]/10 == 2)
                    nameFigura = "L";
                else if (pole[i][j]/10 == 3)
                    nameFigura = "H";
                else if (pole[i][j]/10 == 4)
                    nameFigura = "E";
                else if (pole[i][j]/10 == 5)
                    nameFigura = "Q";
                else
                    nameFigura = "K";
                
                nameFigura += (pole[i][j]%10 == 0  ?  "1"  :  "2");
                poleFigur[i][j] = nameFigura;
            }
            
            else
                poleFigur[i][j] = ((i+j)%2 == 0  ?  "  "  :  "//");
        }
    }
    
    cout << "+----+----+----+----+----+----+----+----+" << endl;
    for (i=0; i<15; i++)
    {
        if (i%2 == 0)
        {
            cout << "| ";
            
            for (j=0; j<15; j++)
            {
                if (j%2 == 0)
                    cout << poleFigur[i/2][j/2] << " ";
                else
                    cout << "| ";
            }
            cout << "|" << endl;
        }
        else
            cout << "+----+----+----+----+----+----+----+----+" << endl;
    }
    cout << "+----+----+----+----+----+----+----+----+";
}

int main()
{
    read();
    vivod();
    
    return 0;
}