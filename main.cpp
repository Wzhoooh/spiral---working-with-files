#include <iostream>
#include "spiral_1st_sem/header.h"
#include "UI.h"

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    string lenHorisontal;
    string lenVertical;
    int statement = 1;
    int lastStatementToLoad = 1;
    bool state = false;

    for (;;)
    {
        try
        {
            if (state == false)
            {
                cout << "LENGTH OF GORISONTAL: ";
                cin >> lenHorisontal;
                InputData input1(lenHorisontal, "1", 1);
            }
            state = true;

            cout << "LENGTH OF VERTICAL: ";
            cin >> lenVertical;
            InputData input2("1", lenVertical, 1);

            break;
        }
        catch (exception* ex)
        {
            cout << ex->what() << endl;
            cout << endl << endl;
        }
    }

    system("cls");
    cout << "LENGTH OF GORISONTAL: " << lenHorisontal << endl;
    cout << "LENGTH OF VERTICAL: " << lenVertical << endl;
    cout << "-------------------" << endl << endl;

    try
    {
        for (;;)
        {
            InputData id(lenHorisontal, lenVertical, statement);
            Spiral spiral(id.getLenHorisontal(), id.getLenVertical());

            printMenu(statement);

            Transform* transformers[] = {new TransformNormal, new TransformInside, new TransformMirror, new TransformMirrorInside};
            for (int i = 0; i < 4; i++)
            {
                if (transformers[i]->isMine(id.getStatement()))
                {
                    Spiral newSpiral = transformers[i]->transform(spiral);
                    newSpiral.print();
                    break;
                }
            }

            if (statement == 5)
            {
                readFile(spiral);
                lenHorisontal = spiral.getLenHorisontal() + '0';
                lenVertical = spiral.getLenVertical() + '0';
                system("cls");
                cout << "LENGTH OF GORISONTAL: " << lenHorisontal << endl;
                cout << "LENGTH OF VERTICAL: " << lenVertical << endl;
                cout << "-------------------" << endl << endl;
                printMenu(statement);
            }
            if (statement == 6)
            {
                loadToFile(spiral);
                system("cls");
                cout << "LENGTH OF GORISONTAL: " << lenHorisontal << endl;
                cout << "LENGTH OF VERTICAL: " << lenVertical << endl;
                cout << "-------------------" << endl << endl;
                printMenu(statement);
            }

            unsigned char biteFirst  = 0;
            unsigned char biteSecond = 0;

            while(!isRightButton(biteFirst, biteSecond))
            {
                biteFirst = getch();
                if (biteFirst == 224)
                    biteSecond = getch();
                else
                    biteSecond = 0;
            }

            lastStatementToLoad = statement;
            statement = changeStatement(statement, biteFirst, biteSecond);

            if (statement == 0)
                return 0;

            system("cls");

            cout << "LENGTH OF GORISONTAL: " << lenHorisontal << endl;
            cout << "LENGTH OF VERTICAL: " << lenVertical << endl;
            cout << "-------------------" << endl << endl;
        }
    }
    catch(exception* ex)
    {
        cout << "EXCEPTIONNN  " << ex->what() << endl;
        cout << endl << endl;
    }
}
