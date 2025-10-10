#include<iostream>

using namespace std;

class Node
{
    public:
        friend class LinkQueue;
    private:
        int value;
        Node* nxt;
        Node* pre;
};

class LinkQueue
{
    private:
        Node* front;
        Node* rear;
        int size;
    public:
        LinkQueue():front(NULL),rear(NULL),size(0){} //初始化

        int push(int x)
        {
            if(isFull())
                return -1;
            size++;
            Node* nod=new Node;
            nod->value=x;
            nod->pre=rear;
            nod->nxt=nullptr;
            //更新front和rear指针
            if(front==nullptr)
            {
                front=nod;
                rear=nod;
            }
            else
            {
                rear->nxt=nod;
                rear=nod;
            }
            return 0;
        }

        int pop()
        {
            if(isEmpty())
                return -1;
            int value=front->value;
            Node* tmp=front;
            front=front->nxt;
            delete tmp;
            size--;
            if(isEmpty())
                rear=nullptr;
            return value;
        }
        bool isFull()
        {
            return false;
        }
        bool isEmpty()
        {
            return front==nullptr;
        }
        int length()
        {
            return size;
        }
        int getFront()
        {
            if(isEmpty())
                return -1;
            return front->value;
        }
        void clear()
        {
            while(front!=nullptr)
            {
                Node* tmp=front;
                front=front->nxt;
                delete tmp;
            }
            front=nullptr;
            rear=nullptr;
            size=0;
        }
        ~LinkQueue()
        {
            clear();
        }
};