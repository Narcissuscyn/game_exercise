#include <iostream>
#include<fstream>
#include<iomanip>
using namespace std;

int main()
{
    int n=0;
    ifstream infile;
    ofstream outfile;
    infile.open("infile.txt",ios::in);
    outfile.open("outfile.txt",ios::app);
    n=280;
    double number[n];
    if((!infile)||(!outfile)){
        cout<<"open error!"<<endl;
        return 0;
    }

    for(int i=0;i<n;i++){
        infile>>number[i];
        //cout<<number[i]<<endl;
    }
for(int m=0;m<8;m++){
    int k=m;
    double  sum=0;
   while(k<=280){
    sum=sum+number[k];
    k=k+8;
   }
   cout<<sum<<"  ";
   outfile<<sum<<"  ";
}

  outfile<<endl;
  outfile.close();

    return 0;

}
