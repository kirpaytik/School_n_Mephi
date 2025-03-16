#include <iostream>
#include <string>
using namespace std;


struct chel
{
    string fio;
    int rost;
    float ves;
    chel *pred;
    chel *sled;
};
chel *p, *k;
int amm = 0;


void addCellToArrayBegin (string addFio, int addRost, float addVes)
{
    if (amm == 0)
    {
        chel *p = new chel;
        k = p;
        amm = 1;
        (*p).fio = addFio;
        (*p).rost = addRost;
        (*p).ves = addVes;
    }
    else
    {
        chel *newCell = new chel;
        amm++;
        (*newCell).fio = addFio;
        (*newCell).rost = addRost;
        (*newCell).ves = addVes;
        (*newCell).sled = p;
        (*p).pred = newCell;
        p = newCell;
    }
}


void addCellToArrayEnd (string addFio, int addRost, float addVes)
{
    if (amm == 0)
    {
        chel *p = new chel;
        k = p;
        amm = 1;
        (*p).fio = addFio;
        (*p).rost = addRost;
        (*p).ves = addVes;
    }
    else
    {
        chel *newCell = new chel;
        amm++;
        (*newCell).fio = addFio;
        (*newCell).rost = addRost;
        (*newCell).ves = addVes;
        (*newCell).pred = k;
        (*k).sled = newCell;
        k = newCell;
    }
}


void insertCellIntoArray (string addFio, int addRost, float addVes, string insertAfterCellFio)
{
    if (amm == 0)
        cout << "Фамилия " << insertAfterCellFio << "отсутствует в списке";
    else
    {
        chel *ykz = p;
        while((*ykz).fio != insertAfterCellFio and ykz != k)
            ykz = (*ykz).sled;
       
        if(ykz == k)
        {
            if ((*ykz).fio == insertAfterCellFio)
            {
                chel *ykz = new chel;
                amm++;
                (*ykz).fio = addFio;
                (*ykz).rost = addRost;
                (*ykz).ves = addVes;
                (*ykz).pred = k;
                (*k).sled = ykz;
                k = ykz;
            }
            else
                cout << "Фамилия " << insertAfterCellFio << "отсутствует в списке";
        }
        else
        {
            chel *ykz1 = ykz;
            chel *ykz = new chel;
            amm++;
            (*ykz).fio = addFio;
            (*ykz).rost = addRost;
            (*ykz).ves = addVes;
            (*ykz).sled = (*ykz1).sled;
            (*(*ykz1).sled).pred = ykz;
            (*ykz).pred = ykz1;
            (*ykz1).sled = ykz;
        }
    }
}


void deleteCellFromArray (string deleteCellFio)
{
    if (amm == 0)
        cout << "Фамилия " << deleteCellFio << "отсутствует в списке";
    else
    {
        chel *ykz = p;
        while((*ykz).fio != deleteCellFio and ykz != k)
            ykz = (*ykz).sled;
       
        if (ykz == k)
        {
            if ((*ykz).fio == deleteCellFio)
            {
                (*(*ykz).pred).sled = NULL;
                k = (*ykz).pred;
            }
            else
                cout << "Фамилия " << deleteCellFio << "отсутствует в списке";
        }
        else
        {
            (*(*ykz).pred).sled = (*ykz).sled;
            (*(*ykz).sled).pred = (*ykz).pred;
        }
    }
}

void readArray ()
{
    chel *ykz = p;
    int numstr = 1;
    while (ykz != k)
    {
        cout << numstr << ") " << (*ykz).fio << ", " << (*ykz).rost << " см., " << (*ykz).ves << " кг.";
        cout << endl;
        numstr++;
        ykz = (*ykz).sled;
    }
    cout << numstr << ") " << (*ykz).fio << ", " << (*ykz).rost << " см., " << (*ykz).ves << " кг.";
    numstr++;
}

int main()
{
    addCellToArrayBegin ("Иванов Иван Иванович", 175, 67.26);
    cout << (*p).fio << endl;
    cout << "l1a" << endl;
    addCellToArrayEnd ("Петров Петр Петрович", 195, 96.18);
    cout << (*k).fio << endl;
    cout << "l2a" << endl;
    insertCellIntoArray ("Романов Роман Романович", 185, 73.5, "Иванов Иван Иванович");
    cout << (*(*p).sled).fio << endl;
    cout << "l3a" << endl;
    deleteCellFromArray ("Иванов Иван Иванович");
    cout << (*p).fio << endl;
    cout << "l4a" << endl;
    readArray();
    cout << "l5a" << endl;
    return 0;
}