#include <iostream>
#include "MagicCube.h"
using namespace std;

int main()
{
     MagicCube m;
     m.R();
     m.U();
     m.R();
     m.U();
     m.R();
     m.Un();
     m.Rn();
     m.Un();
     m.Rn();
     
     Display(m);

    return 0;
}
