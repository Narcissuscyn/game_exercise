#include <iostream>
using namespace std;
// ���ܣ���ӡ�����
// ������
// location ����ߵ�λ�ã� 0 ��ͷ�ߣ�1 �����ߣ�2 ��β��
// colCount ��������
// colWidth �����п�
void PrintTableLine(int location, int colCount, int colWidth)
{
    //ע�⣺��Щ�����ķ��ţ�����Ҫ��3���ַ�װ(����/0)
    char lineHead[][3] = {"��", "��", "��"};
    char lineMid1[][3] = {"��", "��", "��"};
    char lineMid2[][3] = {"��", "��", "��"};
    char lineTail[][3] = {"��", "��", "��"};
    cout << lineHead[location]; //����
    for (int i = 0; i < colCount; i++)
    {
        for (int j = 0; j < colWidth/2; j++)
        {
            cout << lineMid1[location];
        }
        if (i < colCount - 1) cout << lineMid2[location];
    }
    cout << lineTail[location] << endl;//��β
}
// ���ܣ���ȡָ����ά�����е������ʾ���
// ������A ��ά��������rowCount ������colCount ����
int GetMaxWidth(int* A, int rowCount, int colCount)
{
    int width = 0;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            int c = 1;
            int temp = A[i*rowCount+j];
            while (temp)
            {
                temp /= 10;
                c++;
            }
            width = width < c ? c : width;
        }
    }
    return width;
}

// ���ܣ�����ά�����ӡ�ɱ����ʽ
// ������A ��ά��������rowCount ������colCount ����
void PrintArray(int* A, int rowCount, int colCount)
{
    int i, j, colWidth;

    colWidth = GetMaxWidth(A, rowCount, colCount); //��ȡ���������е������
    //��ӡ��ͷ��
    PrintTableLine(0, colCount, colWidth);
   //��ӡ�������
   for (i = 0; i < rowCount; i++)
    {
        if (i > 0) PrintTableLine(1, colCount, colWidth); //��ӡ������
       cout << "��";  //����
       for (j = 0; j < colCount; j++)
        {
          cout.width(colWidth);       //���ݰ�ָ��������
       cout << A[i*rowCount+j];
            if (j < colCount - 1 ) cout << "��"; // ��������
        }
        cout << "��" << endl;    //��β
    }
    PrintTableLine(2, colCount, colWidth); //��ӡ��β
}
int  main()
{
    //int A[][4] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9},{2,3,4}};
    //PrintArray(&A[0][0], 4, 4);
      char lineHead[][3] = {"��", "��", "��"};
      cout<<lineHead[2];
    return 0;
}
