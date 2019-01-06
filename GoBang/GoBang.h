#ifndef GOBANG_H
#define GOBANG_H
#define SIZE 15
#include<string>
#include<iostream>
using namespace std;
class  Checker
{
private:
    char* chess1,*chess2;
    string lineHead[3] = {"┌", "├", "└"};
    char *lineMid1[3] = {"─", "─", "─"};
    char *lineMid2[3] = {"┬", "┼", "┴"};
    char *lineTail[3] = {"┐", "┤", "┘"};
    char *shu="│";
    void Setm();
    void SetM();
    void SetUp();
    void SetDown();
    public:
    char* board[SIZE][SIZE];
    char* GetChess1(){return chess1;}
    char*GetChess2(){return chess2;}
    Checker();
    void Display();
    bool Setchess(int row,int col,int chess);
   bool JudgeWin(char*ch);
};
class ManGB:public Checker
{
public:

};
class ComputerGB:public Checker
{
    public:

        bool SetComputer();
};
#endif // GOBANG_H

