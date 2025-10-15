#include<iostream>
#include<cstring>
#define MAX_SIZE 10005
using namespace std;

class Stack
{
    private:
        int arr[MAX_SIZE];
        int len;
    public:
        Stack()
        {
            memset(arr,0,sizeof(arr));
            len=0;
        }
        bool push(int num)
        {
            if(len==MAX_SIZE)
                return false;
            arr[len++]=num;
            return true;
        }
        int pop()
        {
            if(!len)
                return -1;
            int output=arr[len-1];
            len--;
            return output;
        }
        int size()
        {
            return len;
        }
        int top()
        {
            if(!len)
                return -1;
            return arr[len-1];
        }
        bool isEmpty()
        {
            if(!len)
                return true;
            return false;
        }
        bool isFull()
        {
            if(len==MAX_SIZE)
                return true;
            return false;
        }
};