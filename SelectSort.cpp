#include<iostream>
#define MAX_SIZE 1005
using namespace std;

void swap(int &x,int &y)
{
    int tmp=x;
    x=y;
    y=tmp;
}

void SelectSort(int *arr, int size)
{
    for(int i=0;i<size;i++)
    {
        int tmp=i;
        for(int j=i+1;j<size;j++)
        {
            if(arr[tmp]<arr[j])
            {
                tmp=j;
            }
        }
        if(tmp!=i)
            swap(arr[tmp],arr[i]);
    }
}

int main()
{
    int n;
    int arr[MAX_SIZE];
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>arr[i];
    SelectSort(arr,n);
    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";
    return 0;
}