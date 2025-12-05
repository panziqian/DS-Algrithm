#include<iostream>
using namespace std;
int bd[10][10];
bool s_flag=false;
void res_print()
{
    //print the correct ans matrix
    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            cout<<bd[i][j]<<" ";
        }
        cout<<endl;
    }
}
bool checkVaild(int row,int col)
{
    // return 0 if invaild or 1 if vaild
    for(int i=1;i<=8;i++)
    {
        //check for the row
        if((i!=row)&&bd[i][col])
            return false;
        //chec for the col
        if((i!=col)&&bd[row][i])
            return false;
    }
    // 检查正对角线
    int x=row-1,y=col-1;
    while((x>0)&&(y>0))
    {
        if(bd[x][y])
            return false;
        x--;
        y--;
    }
    // 检查反对角线
    x=row-1,y=col+1;
    while((x>0)&&(y<=8))
    {
        if(bd[x][y])
            return false;
        x--;
        y++;
    }
    return true;
}
bool fun(int row,int col)
{
    if(row==9)
    {
        s_flag=1;
        return true;
    }
    if(!checkVaild(row,col))
    {
        return false;
    }
    for(int i=1;i<=8;i++)
    {
        bd[row+1][i]=1;
        fun(row+1,i);
        if(s_flag)
            return true;
        bd[row+1][i]=0;
    }
    return false;
}
int main()
{
    fun(0,0);
    res_print();
    return 0;
}