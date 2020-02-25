#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

class Spiral;

void printMenu(int statement);
int changeStatement(int statement, unsigned char biteFirst, unsigned char biteSecond);
bool isRightButton(int biteFirst, int biteSecond);
void loadToFile(Spiral& source);
Spiral readFile();
char* numberToStr(int number);
#endif // UI_H_INCLUDED
