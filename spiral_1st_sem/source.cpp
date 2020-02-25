#include "header.h"
#include <iostream>

InputData::InputData(string lenHorisontal, string lenVertical, int statement)
{
    if (this->isRight(lenHorisontal, lenVertical))
        this->getValues(lenHorisontal, lenVertical, statement);
    else
        throw new Wrong_Value;
}

bool InputData::isRight(string lenHorisontal, string lenVertical)
{
    for (int i = 0; i < lenHorisontal.size(); i++)
        if (!(lenHorisontal[i] >= '0' && lenHorisontal[i] <= '9'))
            throw new Wrong_Value;

    for (int i = 0; i < lenVertical.size(); i++)
        if (!(lenVertical[i] >= '0' && lenVertical[i] <= '9'))
            throw new Wrong_Value;

    return true;
}

void InputData::getValues(string lenHorisontal, string lenVertical, int statement)
{
    stringstream ss;
    ss << lenHorisontal;
    ss >> this->lenHorisontal;
    ss.clear();

    ss << lenVertical;
    ss >> this->lenVertical;
    ss.clear();

    this->statement = statement;

    if (this->lenHorisontal > 9 || this->lenVertical > 9 ||
        this->lenHorisontal <= 0 || this->lenVertical <= 0)
        throw new Wrong_Value;
}

int InputData::getLenHorisontal() const
{
    return this->lenHorisontal;
}
int InputData::getLenVertical() const
{
    return this->lenVertical;
}
int InputData::getStatement() const
{
    return this->statement;
}


const char* Wrong_Value::what() const throw()
{
    return "ERROR: there is some wrong value";
}


Spiral::Spiral(int lenHorisontal, int lenVertical)
{
    this->lenHorisontal = lenHorisontal;
    this->lenVertical = lenVertical;

    if (this->lenHorisontal <= 0 || this->lenVertical <= 0)
        throw new Wrong_Value;

    // задаем начальные размеры для вектора
    spiral.resize(this->lenHorisontal);
    for (int i = 0; i < spiral.size(); i++)
        spiral[i].resize(this->lenVertical);

    setNumbers();
}

Spiral::Spiral(v_v_int inputSpiral)
{
    this->spiral = inputSpiral;
}


Spiral& Spiral::operator = (Spiral&& source)
{
std::cout << "&&" << std::endl;
    lenHorisontal = source.lenHorisontal;
    lenVertical = source.lenVertical;
    spiral = std::move(source.spiral);
    return *this;
}

void Spiral::print() const
{
    int maxLen = getLen(spiral[0].size() * spiral.size());

    for (int j = 0; j < spiral[0].size(); j++)
    {
        for (int i = 0; i < spiral.size(); i++)
        {
            cout << spiral[i][j] << " ";
            cout << getGaps(maxLen, spiral[i][j]);
        }
        cout << endl;
    }
}

int Spiral::getMaxLen()
{
    return getLen(spiral[0].size() * spiral.size());
}

int getLen(int number)
{
    int len = 0;
    for (; number > 0; number /= 10)
    {
        len++;
    }
    return len;
}

string getGaps(int lenMaxNumber, int nowNumber)
{
    string returnedStr;
    int differnce = lenMaxNumber - getLen(nowNumber);
    for (int i = 0; i < differnce; i++)
        returnedStr += ' ';

    return returnedStr;
}

void Spiral::setNumbers()
{
    int number = 1;
    int horisontal = spiral.size();
    int vertical = spiral[0].size();

    int i = 0; // horisontal
    int j = 0; // vertical

    for (;;)
    {
        /// движемся направо
        for (; i < horisontal; i++)
        {
            if (spiral[i][j] == 0)
            {
                spiral[i][j] = number;
                number++;
            }

            if (i < horisontal - 1 && spiral[i+1][j] != 0)
                goto p1;
        }
        i--;
        p1:;

        /// движемся вниз
        for (; j < vertical; j++)
        {
            if (spiral[i][j] == 0)
            {
                spiral[i][j] = number;
                number++;
            }

            if (j < vertical - 1 && spiral[i][j+1] != 0)
                goto p2;
        }
        j--;
        p2:;

        /// движемся налево
        for (; i >= 0; i--)
        {
            if (spiral[i][j] == 0)
            {
                spiral[i][j] = number;
                number++;
            }

            if (i > 0 && spiral[i-1][j] != 0)
                goto p3;
        }
        i++;
        p3:;

        /// движемся вверх
        for (; j >= 0; j--)
        {
            if (spiral[i][j] == 0)
            {
                spiral[i][j] = number;
                number++;
            }

            if (j > 0 && spiral[i][j-1] != 0)
                goto p4;
        }
        j++;
        p4:;

        bool flag = 0;
        for (int i = 0; i < spiral.size(); i++)
            for (int j = 0; j < spiral[0].size(); j++)
                if (spiral[i][j] == 0)
                    flag = true;

        if (flag == false)
            return;
    }
}

Spiral::getNumberFromSpiral(int i, int j)
{
    return spiral[i][j];
}

int Spiral::getLenHorisontal()
{
    return this->lenHorisontal;
}
int Spiral::getLenVertical()
{
    return this->lenVertical;
}

///--------------Transform Classes----------------------

bool Transform::isMine(int statement)
{
    throw new Wrong_Value;
}
Spiral Transform::transform(Spiral sp)
{
    throw new Wrong_Value;
}

bool TransformNormal::isMine(int statement)
{
    return (statement == 1);
}
Spiral TransformNormal::transform(Spiral sp)
{
    Spiral newSpiral = sp;
    return newSpiral;
}


bool TransformMirror::isMine(int statement)
{
    return (statement == 2);
}
Spiral TransformMirror::transform(Spiral sp)
{
    v_v_int newSpiralTable;
    // задаем начальный размер
    newSpiralTable.resize(sp.getLenHorisontal());
    for (int i = 0; i < newSpiralTable.size(); i++)
        newSpiralTable[i].resize(sp.getLenVertical());


    int maxNumber = newSpiralTable.size() * newSpiralTable[0].size() + 1;

    // заполняем
    for (int i = 0; i < newSpiralTable.size(); i++)
        for (int j = 0; j < newSpiralTable[0].size(); j++)
        {
            int newNumber = sp.getNumberFromSpiral(newSpiralTable.size() - i - 1, j);
            newSpiralTable[i][j] = newNumber;
        }

    // создаем новую спираль
    Spiral newSpiral(newSpiralTable);
    return newSpiral;
}


bool TransformInside::isMine(int statement)
{
    return (statement == 3);
}
Spiral TransformInside::transform(Spiral sp)
{
    v_v_int newSpiralTable;
    // задаем начальный размер
    newSpiralTable.resize(sp.getLenHorisontal());
    for (int i = 0; i < newSpiralTable.size(); i++)
        newSpiralTable[i].resize(sp.getLenVertical());


    int maxNumber = newSpiralTable.size() * newSpiralTable[0].size() + 1;

    // заполняем
    for (int i = 0; i < newSpiralTable.size(); i++)
        for (int j = 0; j < newSpiralTable[0].size(); j++)
        {
            int newNumber = maxNumber - sp.getNumberFromSpiral(i, j);
            newSpiralTable[i][j] = newNumber;
        }

    // создаем новую спираль
    Spiral newSpiral(newSpiralTable);
    return newSpiral;
}


bool TransformMirrorInside::isMine(int statement)
{
    return (statement == 4);
}
Spiral TransformMirrorInside::transform(Spiral sp)
{
    v_v_int newSpiralTable;
    // задаем начальный размер
    newSpiralTable.resize(sp.getLenHorisontal());
    for (int i = 0; i < newSpiralTable.size(); i++)
        newSpiralTable[i].resize(sp.getLenVertical());


    int maxNumber = newSpiralTable.size() * newSpiralTable[0].size() + 1;

    // заполняем
    for (int i = 0; i < newSpiralTable.size(); i++)
        for (int j = 0; j < newSpiralTable[0].size(); j++)
        {
            int newNumber = maxNumber - sp.getNumberFromSpiral(newSpiralTable.size() - i - 1, j);
            newSpiralTable[i][j] = newNumber;
        }

    // создаем новую спираль
    Spiral newSpiral(newSpiralTable);
    return newSpiral;



}


