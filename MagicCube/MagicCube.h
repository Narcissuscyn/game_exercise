#ifndef MY_H
#define MY_H

#include <iostream>
using namespace std;
#define RED    1
#define ORANGE 2
#define BLUE   3
#define GREEN  4
#define WHITE  5
#define YELLOW 6

#define UP    0
#define DOWN  1
#define FRONT 2
#define BACK  3
#define LEFT  4
#define RIGHT 5
class MagicCube;
class Face
{
friend class MagicCube;
friend void Display(MagicCube &);
private:
   int CenterColor;
   int Color[8];
public:
   Face(int color);
   void Spin_S();
   void Spin_N();
};
Face::Face(int color):CenterColor(color)
{for(int i=0;i<8;i++)Color[i]=color;}
void Face::Spin_S()
{
    int temp1=Color[0],temp2=Color[1];
    for(int i=7;i>=2;i--)Color[(i+2)%8]=Color[i];
    Color[2]=temp1;Color[3]=temp2;
}
void Face::Spin_N()
{for(int i=0;i<3;i++)Spin_S();}


class MagicCube
{
friend void Display(MagicCube &);
private:
    Face *face[6];
    void X_S(); //
    void Y_S(); //
    void Z_S(){X_N();Y_S();X_S();}
    void X_N(){for(int i=0;i<3;i++)X_S();}
    void Y_N(){for(int i=0;i<3;i++)Y_S();}
    void Z_N(){for(int i=0;i<3;i++)Z_S();}
public:
    MagicCube();
    ~MagicCube(){for(int i=0;i<6;i++)delete face[i];}
    void U();//
    void D(){X_S();X_S();U();X_N();X_N();}
    void F(){X_S();U();X_N();}
    void B(){X_N();U();X_S();}
    void L(){Y_S();U();Y_N();}
    void R(){Y_N();U();Y_S();}
//逆时针算法
    void Un(){for(int i=0;i<3;i++)U();}
    void Dn(){for(int i=0;i<3;i++)D();}
    void Fn(){for(int i=0;i<3;i++)F();}
    void Bn(){for(int i=0;i<3;i++)B();}
    void Ln(){for(int i=0;i<3;i++)L();}
    void Rn(){for(int i=0;i<3;i++)R();}
};
MagicCube::MagicCube()
{
    face[FRONT]=new Face(WHITE);
    face[BACK]=new Face(GREEN);
    face[LEFT]=new Face(YELLOW);
    face[RIGHT]=new Face(RED);
    face[UP]=new Face(BLUE);
    face[DOWN]=new Face(ORANGE);
}
void MagicCube::X_S()
{
    Face temp(*face[DOWN]);
    *face[DOWN]=*face[BACK];
    face[BACK]->Spin_S();
    face[BACK]->Spin_S();
    *face[BACK]=*face[UP];
    *face[UP]=*face[FRONT];
    *face[FRONT]=temp;
    face[FRONT]->Spin_S();
    face[FRONT]->Spin_S();
}
void MagicCube::Y_S()
{
    face[FRONT]->Spin_S();
    face[BACK]->Spin_N();
    Face temp(*face[UP]);

    *face[UP]=*face[LEFT];
    *face[LEFT]=*face[DOWN];
    *face[DOWN]=*face[RIGHT];
    *face[RIGHT]=temp;
}
void MagicCube::U()
{
    face[UP]->Spin_S();
    int temp1=face[FRONT]->Color[0],
        temp2=face[FRONT]->Color[1],
        temp3=face[FRONT]->Color[2];

    face[FRONT]->Color[0]=face[RIGHT]->Color[6];
    face[FRONT]->Color[1]=face[RIGHT]->Color[7];
    face[FRONT]->Color[2]=face[RIGHT]->Color[0];

    face[RIGHT]->Color[6]=face[BACK]->Color[4];
    face[RIGHT]->Color[7]=face[BACK]->Color[5];
    face[RIGHT]->Color[0]=face[BACK]->Color[6];

    face[BACK]->Color[4]=face[LEFT]->Color[2];
    face[BACK]->Color[5]=face[LEFT]->Color[3];
    face[BACK]->Color[6]=face[LEFT]->Color[4];

    face[LEFT]->Color[2]=face[FRONT]->Color[4];
    face[LEFT]->Color[3]=face[FRONT]->Color[5];
    face[LEFT]->Color[4]=face[FRONT]->Color[6];

    face[LEFT]->Color[2]=temp1;
    face[LEFT]->Color[3]=temp2;
    face[LEFT]->Color[4]=temp3;
}
void Display(MagicCube &m)
{
    char temp[7][20]={"0","RED   ","ORANGE","BLUE  ","GREEN ","WHITE ","YELLOW"};
    cout<<"FRONT"<<endl;
    for(int i=0;i<3;i++)
        cout<<temp[m.face[FRONT]->Color[i]]<<" ";
    cout<<endl;
    cout<<temp[m.face[FRONT]->Color[7]]<<" "<<temp[m.face[FRONT]->CenterColor]<<" "<<temp[m.face[FRONT]->Color[3]]<<endl;
    for(int i=6;i>=4;i--)
        cout<<temp[m.face[FRONT]->Color[i]]<<" ";
    cout<<endl;

     cout<<"UP"<<endl;
    for(int i=0;i<3;i++)
        cout<<temp[m.face[UP]->Color[i]]<<" ";
    cout<<endl;
    cout<<temp[m.face[UP]->Color[7]]<<" "<<temp[m.face[UP]->CenterColor]<<" "<<temp[m.face[UP]->Color[3]]<<endl;
    for(int i=6;i>=4;i--)
        cout<<temp[m.face[UP]->Color[i]]<<" ";
    cout<<endl;

    cout<<"DOWN"<<endl;
    for(int i=2;i>=0;i--)
        cout<<temp[m.face[DOWN]->Color[i]]<<" ";
    cout<<endl;
    cout<<temp[m.face[DOWN]->Color[3]]<<" "<<temp[m.face[DOWN]->CenterColor]<<" "<<temp[m.face[DOWN]->Color[7]]<<endl;
    for(int i=4;i<=6;i++)
        cout<<temp[m.face[DOWN]->Color[i]]<<" ";
    cout<<endl;

    cout<<"LEFT"<<endl;
    for(int i=4;i>=2;i--)
        cout<<temp[m.face[LEFT]->Color[i]]<<" ";
    cout<<endl;
    cout<<temp[m.face[LEFT]->Color[5]]<<" "<<temp[m.face[LEFT]->CenterColor]<<" "<<temp[m.face[LEFT]->Color[1]]<<endl;
    for(int i=6;i<=7;i++)
        cout<<temp[m.face[LEFT]->Color[i]]<<" ";
    cout<<temp[m.face[LEFT]->Color[0]]<<" ";
    cout<<endl;
}
#endif
