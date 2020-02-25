#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <exception>
#include <windows.h>
#include <conio.h>

using namespace std;

typedef vector < vector < int > > v_v_int;

// входные данные
class InputData;

// класс, строящий спираль
class Spiral;

// трансформеры
class Transform;
class TransformNormal;
class TransformMirror;
class TransformInside;
class TransformMirrorInside;

// исключение
class Wrong_Value;

int getLen(int number);
string getGaps(int lenMaxNumber, int nowNumber);


class Wrong_Value: public exception
{
    const char* what() const throw();
};


class InputData
{
private:
    int lenHorisontal;
    int lenVertical;
    int statement;

    bool isRight(string lenHorisontal, string lenVertical);
    void getValues(string lenHorisontal, string lenVertical, int statement);

public:
    InputData(string lenHorisontal, string lenVertical, int statement);

    int getLenHorisontal() const;
    int getLenVertical() const;
    int getStatement() const;
};


class Spiral
{
private:
    int lenHorisontal;
    int lenVertical;
    v_v_int spiral;

private:
    void setNumbers();

public:
    Spiral(int lenHorisontal, int lenVertical);
    Spiral(v_v_int inputSpiral);
    Spiral(const Spiral&) = default;
    Spiral operator = (Spiral&&);
    void print() const;
    int getMaxLen();

    int getNumberFromSpiral(int i, int j);

    int getLenHorisontal();
    int getLenVertical();
};


class Transform
{
public:
    virtual bool isMine(int statement);
    virtual Spiral transform(Spiral sp);
};

class TransformNormal: public Transform
{
public:
    virtual bool isMine(int statement);
    Spiral transform(Spiral sp);
};

class TransformMirror: public Transform
{
public:
    virtual bool isMine(int statement);
    Spiral transform(Spiral sp);
};

class TransformInside: public Transform
{
public:
    virtual bool isMine(int statement);
    Spiral transform(Spiral sp);
};

class TransformMirrorInside: public Transform
{
public:
    virtual bool isMine(int statement);
    Spiral transform(Spiral sp);
};

#endif // HEADER_H_INCLUDED
