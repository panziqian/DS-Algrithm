#include <iostream>
using namespace std;
int bd[10][10];
bool s_flag = false;
void res_print()
{
    // print the correct ans matrix
    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            cout << bd[i][j] << " ";
        }
        cout << endl;
    }
}
bool checkVaild(int row, int col)
{
    // return 0 if invaild or 1 if vaild
    // 检查列
    for (int i = 1; i < row; i++)
    {
        if (bd[i][col])
            return false;
    }
    // 检查左上到右下对角线
    int x = row - 1, y = col - 1;
    while ((x > 0) && (y > 0))
    {
        if (bd[x][y])
            return false;
        x--;
        y--;
    }
    // 检查右上到左下对角线
    x = row - 1;
    y = col + 1;
    while ((x > 0) && (y <= 8))
    {
        if (bd[x][y])
            return false;
        x--;
        y++;
    }
    return true;
}
bool fun(int row)
{
    if (row == 9)
    {
        res_print();
        cout << endl;
        return true;
    }
    for (int i = 1; i <= 8; i++)
    {
        if (checkVaild(row, i))
        {
            bd[row][i] = 1;
            fun(row + 1);
            bd[row][i] = 0;
        }
    }
    return false;
}
int main()
{
    fun(1);
    return 0;
}