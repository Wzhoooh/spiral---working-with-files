#include "UI.h"
#include "spiral_1st_sem/header.h"
#include <iostream>
#include <cstdio>
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

    if (statement == 5)
        cout << "5. READ FROM FILE           <-" << endl;
    else
        cout << "5. READ FROM FILE" << endl;

    if (statement == 6)
        cout << "6. LOAD TO FILE             <-" << endl;
    else
        cout << "6. LOAD TO FILE" << endl;
    cout << endl;
}


int changeStatement(int statement, unsigned char biteFirst, unsigned char biteSecond)
{
    int newStatement;

    if (biteFirst == 224)
    {
        if (biteSecond == 72) // стрелочка вверх
            newStatement = statement == 1 ? 6 : (statement - 1);
        else if (biteSecond == 80) // стрелочка вниз
            newStatement = statement == 6 ? 1 : (statement + 1);
        else newStatement = statement; // нажата неправильна€ кнопка, состо€ние не измен€етс€
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
        else if (biteFirst == '5')
            newStatement = 5;
        else if (biteFirst == '6')
            newStatement = 6;
        else newStatement = statement; // нажата неправильна€ кнопка, состо€ние не измен€етс€
    }

    if (biteFirst == 27) // escape
        newStatement = 0; // завершаем программу

    return newStatement;
}

bool isRightButton(int biteFirst, int biteSecond)
{
    set<pair<int, int>>allVariants{{'1', 0}, {'2', 0},  {'3', 0}, {'4', 0}, {'5', 0}, {'6', 0},
                                        {27, 0},  {224, 72}, {224, 80}};

    set<pair<int, int>>::iterator result = allVariants.find({biteFirst, biteSecond});
    return (result != allVariants.end());
}

char* numberToStr(int number)
{
    int sizeStr = 20;
    char* str = (char*)malloc(sizeStr);
    for (int i = 0; i < sizeStr; i++)
        str[i] = '\0';

    int i = 0;
    while (number)
    {
        for (int i = sizeStr-1; i > 0; i--)
            str[i] = str[i-1];

        str[0] = number % 10 + '0';
        number /= 10;
    }
    return str;
}

void loadToFile(Spiral& source)
{
    system("cls");
    char nameOfFile[100] = { 'd', 'a', 't', 'a', '\\' };
    FILE* f = NULL;

    for (;;)
    {
        printf("Enter name to file: ");
        scanf("%s", nameOfFile+5);

        f = fopen(nameOfFile, "wt");
        if (f == NULL)
        {
            system("cls");
            printf("INVALID NAME");
            Sleep(500);
            system("cls");
            continue;
        }
        else
        {
            char dataBuff[4]= { '0', '0', '\n', '\0' };
            dataBuff[0] = source.getLenHorisontal() + '0';
            dataBuff[1] = source.getLenVertical() + '0';
            fwrite(dataBuff, 1, 3, f);

            int lenOfStr = source.getMaxLen() * source.getLenHorisontal() + source.getLenHorisontal();
            char loadedData[source.getLenVertical()][lenOfStr] = {};
            for (int j = 0; j < source.getLenVertical(); j++)
            {
                int t = 0;
                for (int i = 0; i < source.getLenHorisontal(); i++)
                {
                    char* s = numberToStr(source.getNumberFromSpiral(i, j)); /// возможно перепутано
                    for (int k = 0; s[k] != 0; k++)
                    {
                        loadedData[j][t] = s[k];
                        t++;
                    }
                    int numGaps = getGaps(source.getMaxLen(), source.getNumberFromSpiral(i, j)).size()+1;
                    for (int f = 0; f < numGaps; f++, t++)
                    {
                        loadedData[j][t] = ' ';
                    }
                }
            }

            for (int j = 0; j < source.getLenVertical(); j++)
            {
                fwrite(loadedData[j], 1, lenOfStr, f);
                fwrite("\n", 1, 1, f);
            }
            break;
        }
    }
    fclose(f);
    system("cls");
}

Spiral readFile()
{
    system("cls");
    char nameOfFile[100] = { 'd', 'a', 't', 'a', '\\' };
    FILE* f = NULL;

    for (;;)
    {
        printf("Enter name to file: ");
        scanf("%s", nameOfFile+5);

        f = fopen(nameOfFile, "rt");
        if (f == NULL)
        {
            system("cls");
            printf("INVALID NAME");
            Sleep(500);
            system("cls");
            continue;
        }
        else
        {
            char buffer[2]= {};
            std::cout << "fread: " << fread(buffer, 1, 2, f) << std::endl;
            Spiral newSpiral(buffer[0], buffer[1]);
            fclose(f);
            return newSpiral;
        }
    }
}
