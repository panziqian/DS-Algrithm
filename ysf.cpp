#include <iostream>
#define MAX_NUM 10005
using namespace std;
int debug = 1;
int n, m = 20;
int arr[MAX_NUM];
class Node
{
  public:
    int val;
    int num;
    Node *nxt;
    Node() : val(0), num(0), nxt(nullptr) {};
    Node(int value, int number)
    {
        num = number;
        val = value;
        nxt = nullptr;
    }
};
class LinkList
{
  public:
    int size;
    Node *head;
    Node *rear;
    LinkList() : size(0), head(nullptr), rear(nullptr) {};
    LinkList(int *arr, int n)
    {
        size = 1;
        head = new Node(arr[1], 1);
        rear = head;
        for (int i = 2; i <= n; i++)
            push(arr[i], i);
        rear->nxt = head;
    }
    void push(int x, int number)
    {
        size++;
        Node *tmp = new Node(x, number);
        rear->nxt = tmp;
        rear = rear->nxt;
    }
    bool empty()
    {
        if (size == 0)
            return 1;
        return 0;
    }
    int delet(Node *x)
    {
        int res = x->num;
        if (size == 1)
        {
            size = 0;
            delete x;
            head = rear = nullptr;
            return res;
        }
        size--;
        if (x->num == head->num)
        {
            rear->nxt = head->nxt;
            head = rear->nxt;
            delete x;
            return res;
        }
        Node *it = head;
        while (it->nxt->num != res)
            it = it->nxt;
        if (x == rear)
            rear = it;
        it->nxt = x->nxt;
        delete x;
        return res;
    }
};
void process(int *arr, int n)
{
    LinkList *l = new LinkList(arr, n);
    Node *iter = l->head;
    while (iter->num != l->head->num)
    {
        cout << iter->num << "->" << iter->val << endl;
        iter = iter->nxt;
    }
    cout << endl;
    int cnt = 1;
    Node *it = l->head;
    while (!l->empty())
    {
        if (cnt == m)
        {
            Node *to_del = it;
            m = it->val;
            it = it->nxt;
            int res = l->delet(to_del);
            cout << res << " ";
            cnt = 1;
        }
        else
        {
            it = it->nxt;
            cnt++;
        }
    }
}
int main()
{
    freopen("ysf.in", "r", stdin);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    LinkList *ls = new LinkList(arr, n);
    Node *it = ls->head;
    process(arr, n);
    return 0;
}
