#include <iostream>
#define MAX_SIZE 1005
using namespace std;

void swap(int &x,int &y)
{
    int tmp=x;
    x=y;
    y=tmp;
}

void BubbleSort(int *arr,int size)
{
    bool flag=true;
    while(flag)
    {
        flag=false;
        for(int i=1;i<size;i++)
        {
            if(arr[i-1]>arr[i])
            {
                swap(arr[i-1],arr[i]);
                flag=true;
            }
        }
    }
}
int main()
{
    int n;
    int arr[MAX_SIZE];
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    BubbleSort(arr, n);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}