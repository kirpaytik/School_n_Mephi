#include <iostream>
using namespace std;

// Заголовки функций
int sign (int x);
void read1 (); void read2 ();
void justMove (string a, string b, int color);
void moveP (string a, string b, int color); void moveL (string a, string b, int color, int figura); void moveH (string a, string b, int color);
void moveE (string a, string b, int color, int figura); void moveQ (string a, string b, int color); void moveK (string a, string b, int color);
void checkEndOfGame ();
void vivod ();


// массивы
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
string zapis1[100];       // запись осуществляется в соответствующей функции read()
string zapis2[100][2];    // 


// переменные
int turnNum = 0;
string eeerok="", NotEEE;
// флаги
int unrealMove=0;
int WhKFlag=0, WhLaFlag=0, WhLhFlag=0, BlKFlag=0, BlLaFlag=0, BlLhFlag=0;
int PPflag, PPnullFlag=0;
string HowTurnLoL;
int endGameFlag=0;


///////////////////                ОМЕН                ///////////////////
int main()
{
    cout << "Ход будет делать тот, на кого попадёт, или пусть по очереди?) (1 или 2)" << endl;
    cin >> HowTurnLoL;
    while (HowTurnLoL!="1"  and  HowTurnLoL!="2")
    {
        cout << "Пожалуйста, введите 1 или 2: ходит тот, на кого попадёт, или по очереди?" << endl;
        cin >> HowTurnLoL;
    }
    if (HowTurnLoL == "2")
    {
        zapis2[0][0] = "o";
        read2();
    }
    else
    {
        zapis1[0] = "o";
        read1();
    }
    
    vivod();
    
    return 0;
}



// функции


int sign(int x)
{
    return (x>0  ?  1  :  -1);
}

void read1()
{
    cout << "Вводите 2 клетки в каждой строке: начальную клетку фигуры и конечную" << endl;
    cout << "Если хотите вывести поле, введите 1 1" << endl << "Чтобы завершить ввод введите 0 0" << endl;
    string cell1, cell2;
    cin >> cell1 >> cell2;
    while (cell1 != "0"  or  cell2 != "0")
    {
        if (cell1 == "1"  and  cell2 == "1")
        {
            vivod();
            cin >> cell1 >> cell2;
        }
        else
        {
            if (cell1 == cell2)
                cout << "Невозможный ход" << endl;
            
            else
            {
                int k11 = (int)(cell1[0] - 97);
                int k12 = (int)(cell1[1]) - 48;
                int k21 = (int)(cell2[0] - 97);
                int k22 = (int)(cell2[1]) - 48;
                
                if (k11>7 or k12>8 or k12<1 or k21>7 or k22>8 or k22<1 or pole[8-k12][k11]==0)
                    cout << "Одна из клеток введена некорректно (не существует/нет на поле), или в начальной клетке нет фигуры" << endl;
                else
                {
                    justMove (cell1, cell2, pole[8-k12][k11]%10);
                    if (unrealMove == 1)
                    {
                        cout << "Невозможный ход" << endl;
                        turnNum--;
                        unrealMove = 0;
                    }
                    else
                    {
                        if (eeerok=="")
                            zapis1[turnNum-1] = cell1 + " " + cell2;
                        else
                            {zapis1[turnNum-1] = eeerok;  eeerok = "";}
                        if (turnNum < 100)
                            zapis1[turnNum] = "o";
                    }
                } // else (сell введена корректно)
            } // else (не-невозможный ход)
            
            checkEndOfGame();
            if (endGameFlag > 0)
                {cell1 = "0"; cell2 = "0";}
            else
                cin >> cell1 >> cell2;
        }
    } // конец while
    endGameFlag = (endGameFlag==0 ? -1 : endGameFlag);
}

void read2()
{
    cout << "Вводите 4 клетки в каждой строке: 2 клетки для хода белых и ещё две для хода чёрных" << endl;
    cout << "Если хотите вывести поле и сделанные ходы, введите 1 1" << endl << "Чтобы завершить ввод введите 0 0" << endl;
    string cell1, cell2;
    cin >> cell1 >> cell2;
    int colorTurn = 0;
    while (cell1 != "0"  or  cell2 != "0")
    {
        if (cell1 == "1"  and  cell2 == "1")
        {
            vivod();
            cin >> cell1 >> cell2;
        }
        else
        {
            if (cell1 == cell2)
                cout << "Невозможный ход" << endl;
            
            else
            {
                int k11 = (int)(cell1[0] - 97);
                int k12 = (int)(cell1[1]) - 48;
                int k21 = (int)(cell2[0] - 97);
                int k22 = (int)(cell2[1]) - 48;
                
                if (k11>7 or k12>8 or k12<1 or k21>7 or k22>8 or k22<1 or pole[8-k12][k11]==0)
                    cout << "Одна из клеток введена некорректно (не существует/нет на поле), или в начальной клетке нет фигуры" << endl;
                else if (pole[8-k12][k11]%10 != colorTurn)
                    cout << "Сейчас ход " << (colorTurn==0 ? "белых" : "чёрных") << endl;
                else
                {
                    justMove (cell1, cell2, colorTurn);
                    if (unrealMove == 1)
                    {
                        cout << "Невозможный ход" << endl;
                        turnNum--;
                        unrealMove = 0;
                    }
                    else
                    {
                        if (NotEEE == "")
                            zapis2[(turnNum-1)/2][colorTurn] = cell1 + " " + cell2;
                        else
                            {zapis2[(turnNum-1)/2][colorTurn] = NotEEE;  NotEEE = "";}
                        
                        if (colorTurn == 0)
                            zapis2[(turnNum-1)/2][colorTurn+1] = "o";
                        else if ((turnNum-1)/2 < 100)
                            zapis2[(turnNum-1)/2+1][colorTurn-1] = "o";
                        
                        colorTurn = 1-colorTurn;
                    }
                } // else (сell введено корректно)
            } // else (не-невозможный ход)
            
            checkEndOfGame();
            if (endGameFlag > 0)
                {cell1 = "0"; cell2 = "0";}
            else
                cin >> cell1 >> cell2;
        }
    } // конец while
    endGameFlag = (endGameFlag==0 ? -1 : endGameFlag);
}

void justMove (string a, string b, int color)
{
    int a0 = (int)(a[0] - 97);
    int a1 = (int)(a[1]) - 48;
    
    switch (pole[8-a1][a0] / 10)
    {
        case 1:
            moveP (a, b, color);
            break;
        case 2:
            moveL (a, b, color, 20);
            break;
        case 3:
            moveH (a, b, color);
            break;
        case 4:
            moveE (a, b, color, 40);
            break;
        case 5:
            moveQ (a, b, color);
            break;
        default:
            moveK (a, b, color);
    }
    
    if (PPnullFlag == 0)
        PPflag = 0;
    else
        PPnullFlag = 0;
}

void moveP (string a, string b, int color)
{
    turnNum++;
    int j1 = (int)(a[0] - 97);
    int i1 = (int)(a[1]) - 48;
    int j2 = (int)(b[0] - 97);
    int i2 = (int)(b[1]) - 48;

    if (pole[8-i2][j2] == 0  and  j1 == j2)
    {
        if (i2-i1 == (color==0 ? 1 : -1))
        {
            pole[8-i1][j1] = 0;
            pole[8-i2][j2] = 10 + color;
        }
        else if ((i2-i1 == (color==0 ? 2 : -2))  and  (i1 == (color==0 ? 2 : 7))  and  pole[8-(color==0 ? 3 : 6)][j2] == 0)
        {
            pole[8-i1][j1] = 0;
            pole[8-i2][j2] = 10 + color;
            PPflag = (j1+1)*10 + color;
            PPnullFlag = 1;
        }
        else
            // cout << "Невозможнен " << turnNum << "й ход" << endl;
            unrealMove = 1;
    }
    else if (abs(j2-j1) == 1  and  i2-i1 == (color==0 ? 1 : -1))
    {
        if (pole[8-i2][j2] > 0  and  pole[8-i2][j2]%10 != color)
        {
            pole[8-i1][j1] = 0;
            pole[8-i2][j2] = 10 + color;
        }
        else if (pole[8-i2][j2] == 0  and  j2==PPflag/10-1  and  i2 == (color==0 ? 6 : 3))
        {
            pole[8-i1][j1] = 0;
            pole[8-i1][j2] = 0;
            pole[8-i2][j2] = 10 + color;
            // PPflag = 0; PPnullFlag = 0;   не нужно, т.к. всё равно в justMove() станет 0
            //                            // но не удаляю строку, чтобы было не забывать о флаге
        }
    }
    else
        // cout << "Невозможнен " << turnNum << "й ход" << endl;
        unrealMove = 1;
    
    if (unrealMove == 0  and  i2 == (color==0 ? 8 : 1))
    {
        cout << "Пешка дошла до последней линии. В кого превратить? (L, H, E или Q)" << endl;
        string newPFig; cin >> newPFig;
        while ((newPFig!="L") and (newPFig!="H") and (newPFig!="E") and (newPFig!="Q"))
        {
            cout << "Пешку можно превратить только в одну из четырёх фигур: L, H, E или Q";
            cin >> newPFig;
        }
        switch ((int)newPFig[0])
        {
            case 76:
                pole[8-i2][j2] = 20 + color;
                break;
            case 72:
                pole[8-i2][j2] = 30 + color;
                break;
            case 69:
                pole[8-i2][j2] = 40 + color;
                break;
            case 81:
                pole[8-i2][j2] = 50 + color;
        }
    }
}

void moveL (string a, string b, int color, int figura)
{
    turnNum++;
    int j1 = (int)(a[0] - 97);
    int i1 = (int)(a[1]) - 48;
    int j2 = (int)(b[0] - 97);
    int i2 = (int)(b[1]) - 48;
    
    if (color == 0  and  i1 == 1) // Проверка строки (i1) тоже нужна: а вдруг пешка пройдёт до конца и превратится в ладью?
    {
        if (j1 == 0)
            WhLaFlag = 1;
        else if (j1 == 7)
            WhLhFlag = 1;
    }
    else if (color == 1  and  i1 == 8)
    {
        if (j1 == 0)
            BlLaFlag = 1;
        else if (j1 == 7)
            BlLhFlag = 1;
    }

    if (j1 == j2)
    {
        int c = i1, flag = 0;
        int signForCi = sign(i2-i1);
        c += signForCi;
        while (c != i2)
        {
            if (pole[8-c][j1] > 0)
                flag++;
            c += signForCi;
        }
        if (pole[8-c][j1] > 0  and  pole[8-c][j1]%10 == color)
            flag++;
        
        if (flag == 0)
        {
            pole[8-i1][j1] = 0;
            pole[8-i2][j2] = figura + color;
        }
        else
            // cout << "Невозможнен " << turnNum << "й ход" << endl;
            unrealMove = 1;
    }
    else if (i1 == i2)
    {
        int c = j1, flag = 0;
        int signForCj = sign(j2-j1);
        c += signForCj;
        while (c != j2)
        {
            if (pole[8-i1][c] > 0)
                flag++;
            c += signForCj;
        }
        if (pole[8-i1][c] > 0  and  pole[8-i1][c]%10 == 0)
            flag ++;
        
        if (flag == 0)
        {
            pole[8-i1][j1] = 0;
            pole[8-i2][j2] = figura + color;
        }
        else
            // cout << "Невозможнен " << turnNum << "й ход" << endl;
            unrealMove = 1;
    }
    else
        // cout << "Невозможнен " << turnNum << "й ход" << endl;
        unrealMove = 1;
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
            // cout << "Невозможнен" << turnNum << "й ход" << endl;
            unrealMove = 1;
    }
    else
        // cout << "Невозможнен" << turnNum << "й ход" << endl;
        unrealMove = 1;
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
        int signForCi = sign(i2-i1);
        int signForCj = sign(j2-j1);
        ci += signForCi;
        cj += signForCj;
        while (ci != i2)
        {
            if (pole[8-ci][cj] > 0)
            flag++;
            ci += signForCi;
            cj += signForCj;
        }
        if (pole[8-ci][cj]>0 and color == pole[8-ci][cj]%10)
            flag++;
        
        if (flag == 0)
        {
            pole[8-i1][j1] = 0;
            pole[8-i2][j2] = figura + color;
        }
        else
            // cout << "Невозможнен " << turnNum << "й ход" << endl;
            unrealMove = 1;
    }
    else
        // cout << "Невозможнен " << turnNum << "й ход" << endl;
        unrealMove = 1;
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
    {
        turnNum++;
        // cout << "Невозможнен " << ++turnNum << "й ход" << endl;
        unrealMove = 1;
    }
}

void moveK (string a, string b, int color)
{
    int funKingFlag;
    if (color == 0)
    {
        funKingFlag = WhKFlag;
        WhKFlag = 1;
    }
    else
    {
        funKingFlag = BlKFlag;
        BlKFlag = 1;
    }
    
    turnNum++;
    int j1 = (int)(a[0] - 97);
    int i1 = (int)(a[1]) - 48;
    int j2 = (int)(b[0] - 97);
    int i2 = (int)(b[1]) - 48;
    
    if (abs(i2-i1)<2  and  abs(j2-j1)<2)
    {
        if (pole[8-i2][j2] == 0  or  pole[8-i2][j2] % 10 != color)
        {
            pole[8-i1][j1] = 0;
            pole[8-i2][j2] = 60+color;
        }
        else
            unrealMove = 1;
    }
    else if (i1 == i2  and  funKingFlag == 0)
    {
        if (color == 0)
        {
            if (j2-j1 == 2  and  WhLhFlag == 0  and  pole[7][5] == 0  and  pole[7][6] == 0)
            {
                pole[8-i1][j1] = 0;
                pole[8-i1][j2] = 60;
                pole[8-i1][j2+1] = 0;
                pole[8-i1][j2-1] = 20;
                
                eeerok = "Белые: 0-0"; NotEEE = "0-0";
            }
            else if (j2-j1 == -2  and  WhLaFlag == 0  and  pole[7][1] == 0  and  pole[7][2] == 0  and  pole[7][3] == 0)
            {
                pole[8-i1][j1] = 0;
                pole[8-i1][j2] = 60;
                pole[8-i1][j2-2] = 0;
                pole[8-i1][j2+1] = 20;
                
                eeerok = "Белые: 0-0-0"; NotEEE = "0-0-0";
            }
            else
                unrealMove = 1;
        }
        else
        {
            if (j2-j1 == 2  and  BlLhFlag == 0  and  pole[0][5] == 0  and  pole[0][6] == 0)
            {
                pole[8-i1][j1] = 0;
                pole[8-i1][j2] = 60;
                pole[8-i1][j2+1] = 0;
                pole[8-i1][j2-1] = 20;
                
                eeerok = "Чёрные: 0-0"; NotEEE = "0-0";
            }
            else if (j2-j1 == -2  and  BlLaFlag == 0  and  pole[0][1] == 0  and  pole[0][2] == 0  and  pole[0][3] == 0)
            {
                pole[8-i1][j1] = 0;
                pole[8-i1][j2] = 60;
                pole[8-i1][j2-2] = 0;
                pole[8-i1][j2+1] = 20;
                
                eeerok = "Чёрные: 0-0-0"; NotEEE = "0-0-0";
            }
            else
                unrealMove = 1;
        }
    }
    else
        // cout << "Невозможнен " << turnNum << "й ход" << endl;
        unrealMove = 1;
}

void checkEndOfGame()
{
    int i,j, WhKing, BlKing;
    for (i=0; i<8; i++)
        for (j=0; j<8; j++)
        {
            if (pole[i][j] == 60)
                WhKing = 1;
            else if (pole[i][j] == 61)
                BlKing = 1;
        }
    
    if (BlKing == 0)
        endGameFlag = 1;
    else if (WhKing == 0)
        endGameFlag = 2;
}

void vivod()
{
    int i,j;
    string nameFigura;
    for (i=0; i<8; i++)
        for (j=0; j<8; j++)
        {
            if (pole[i][j] > 0)
            {
                switch (pole[i][j]/10)
                {
                    case 1:
                        nameFigura = "P";
                        break;
                    case 2:
                        nameFigura = "L";
                        break;
                    case 3:
                        nameFigura = "H";
                        break;
                    case 4:
                        nameFigura = "E";
                        break;
                    case 5:
                        nameFigura = "Q";
                        break;
                    default:
                        nameFigura = "K";
                }
                
                nameFigura += (pole[i][j]%10 == 0  ?  "1"  :  "2");
                poleFigur[i][j] = nameFigura;
            }
            
            else
                poleFigur[i][j] = ((i+j)%2 == 0  ?  "  "  :  "//");
        }
    
    cout << "      a    b    c    d    e    f    g    h  " << endl;
    cout << "   +----+----+----+----+----+----+----+----+" << endl;
    for (i=0; i<15; i++)
    {
        cout << " ";
        if (i%2 == 0)
        {
            cout << 8-(i/2) << " | ";
            
            for (j=0; j<15; j++)
            {
                if (j%2 == 0)
                    cout << poleFigur[i/2][j/2] << " ";
                else
                    cout << "| ";
            }
            cout << "| " << 8-(i/2) <<  endl;
        }
        else
            cout << "  +----+----+----+----+----+----+----+----+" << endl;
    }
    cout << "   +----+----+----+----+----+----+----+----+" << endl;
    cout << "      a    b    c    d    e    f    g    h  " << endl;
    
    
    if (HowTurnLoL == "2")
    {
        if (zapis2[0][0] != "o")
        {
            cout << "Все ходы:" << endl;
            for (i=0; i<100; i++)
            {
                if (zapis2[i][0] == "o")
                    break;
                cout << i+1 << ") " << zapis2[i][0];
                if (zapis2[i][1] == "o")
                    break;
                cout << "   -   " << zapis2[i][1] << endl;
            }
        }
    }
    else
    {
        if (zapis1[0] != "o")
        {
            cout << "Все ходы:" << endl;
            for (i=0; i<100; i++)
            {
                if (zapis1[i] == "o")
                    break;
                cout << i+1 << ") " << zapis1[i] << endl;
            }
        }
    }
    cout << endl << " " << endl;
    
    if (endGameFlag == -1)
        cout << "Игра была остановлена";
    else if (endGameFlag == 1)
        cout << "Игра окончена! Белые победили";
    else if (endGameFlag == 2)
        cout << "Игра окончена! Чёрные победили";
}
