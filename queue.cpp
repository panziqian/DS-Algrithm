#include<iostream>
#define MAX_SIZE 5
using namespace std;

class pzqueue
{
    private:
    int front;
    int rear;
    public:
        int arr[MAX_SIZE];
        pzqueue()
        {
            front=0;
            rear=0;
            memset(arr,0,sizeof(arr));
        }

        void push(int num)
        {
            if(isFull())
                return;
            arr[rear]=num;
            rear=(rear+1)%MAX_SIZE;
        }
        
        //delete the front node and return the value of it.
        int pop()
        {
            if(isEmpty())
                return -1;
            int num=arr[front];
            front=(front+1)%MAX_SIZE;
            return num;
        }

        int isFull()
        {
            return (rear+1)%MAX_SIZE==front;
        }

        int isEmpty()
        {
            return front==rear;
        }

        int getFirst()
        {
            return arr[front];
        }

        int length()
        {
            return (rear-front+MAX_SIZE)%MAX_SIZE;
        }
};

