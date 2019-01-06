
#ifndef VIEW_H
#define VIEW_H

enum TypeOfRoad{VOID=0,UP,DOWN,LEFT,RIGHT,PLUS,
NAME_1,NAME_2,NAME_3,NAME_4,NAME_5,NAME_6,NAME_7,NAME_8,NAME_9,
NAME_10,NAME_11,NAME_12,NAME_13,NAME_14,NAME_15,NAME_16,NAME_17};
#include "string"
using namespace std;
class View
{
private:
    const char * StyleOfRoad[100]={"¡¤","¡ü","¡ý","¡û","¡ú","Ê®","¡ñ","¡ò","¡ð","¡ó","¡î","¡ï","¡ô","¡ù","¡ç","¡÷","¡ø","¡ó","¤"};
    int nPoint;
    int *X;
    int *Y;
    int *style;
    string *Name;
    int **Jlu;
    int row;
    int colm;
public:
    View(int r,int c,int x[],int y[],int style[],string [],int np);
   ~View();
    void Display()const;
    void ClearRoad();
    void GetRoad(int v1,int v2);
    void GetRoad(int x1,int y1,int x2,int y2);
    void SetRoad(int x,int y,int style);
    void SetPoint(int v);
};

#endif // VIEW_H
