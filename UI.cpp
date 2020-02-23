#include "UI.h"
#include <iostream>
#include <set>
#include <utility>
using std::cout;
using std::endl;
using std::set;
using std::pair;

void printMenu(int statement)
{
    if (statement == 1)
        cout << "1. INSIDE CLOCKWISE         <-" << endl;
    else
        cout << "1. INSIDE CLOCKWISE" << endl;

    if (statement == 2)
        cout << "2. INSIDE COUNTERCLOCKWISE  <-" << endl;
    else
        cout << "2. INSIDE COUNTERCLOCKWISE" << endl;

    if  (statement == 3)
        cout << "3. OUTSIDE CLOCKWISE        <-" << endl;
    else
        cout << "3. OUTSIDE CLOCKWISE" << endl;

    if (statement == 4)
        cout << "4. OUTSIDE COUNTERCLOCKWISE <-" << endl;
    else
        cout << "4. OUTSIDE COUNTERCLOCKWISE" << endl;
    cout << endl;
}


int changeStatement(int statement, unsigned char biteFirst, unsigned char biteSecond)
{
    int newStatement;

    if (biteFirst == 224)
    {
        if (biteSecond == 72) // стрелочка вверх
            newStatement = statement == 1 ? 4 : (statement - 1);
        else if (biteSecond == 80) // стрелочка вниз
            newStatement = statement == 4 ? 1 : (statement + 1);
        else newStatement = statement; // нажата неправильная кнопка, состояние не изменяется
    }
    else
    {
        if (biteFirst == '1')
            newStatement = 1;
        else if (biteFirst == '2')
            newStatement = 2;
        else if (biteFirst == '3')
            newStatement = 3;
        else if (biteFirst == '4')
            newStatement = 4;
        else newStatement = statement; // нажата неправильная кнопка, состояние не изменяется
    }

    if (biteFirst == 27) // escape
        newStatement = 0; // завершаем программу

    return newStatement;
}

bool isRightButton(int biteFirst, int biteSecond)
{
    set < pair <int, int> > allVariants{{'1', 0}, {'2', 0},  {'3', 0}, {'4', 0},
                                        {27, 0},  {224, 72}, {224, 80}};

    set < pair <int, int> >::iterator result = allVariants.find({biteFirst, biteSecond});
    return (result != allVariants.end());
}
