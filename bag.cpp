#include<iostream>
#include<algorithm>
#include<stack>
#define MAX_SIZE 10005
using namespace std;
int arr[MAX_SIZE];
bool selected[MAX_SIZE];
int n,weight;
stack<int> st,buf;
bool comp(const int a,const int b)
{
    if(a>b)
        return 1;
    return 0;
}
void find_solution(int itemNum,int total_weight)
{
    if(total_weight==weight)
    {
        while(!st.empty())
        {
            int temp=st.top();
            buf.push(temp);
            cout<<temp<<" ";
            st.pop();
        }
        cout<<endl;
        while(!buf.empty())
        {
            st.push(buf.top());
            buf.pop();
        }
        return;
    }
    for(int i=itemNum;i<n;i++)
    {
        if((total_weight+arr[i]<=weight)&&(!selected[i]))
        {
            st.push(arr[i]);
            selected[i]=1;
            find_solution(i,total_weight+arr[i]);
            selected[i]=0;
            st.pop();
        }
    }
}
int main()
{
    //freopen("bag.in","r",stdin);
    cin>>weight>>n;
    for(int i=0;i<n;i++)
        cin>>arr[i];
    sort(arr,arr+n,comp);
    memset(selected,0,sizeof(selected));
    find_solution(0,0);
    return 0;
}