#include <cctype>
#include <cstdio>
#include <iostream>
#define MAX_SIZE 10005
using namespace std;
class BST
{
  public:
    int arr[MAX_SIZE];
    int size;
    int last_pos;

    BST()
    {
        memset(arr, 0, sizeof(arr));
        size = 0;
        last_pos = 1;
    }
    ~BST()
    {
        destroy();
    }
    void destroy()
    {
        memset(arr, 0, sizeof(arr));
        size = 0;
        last_pos = 1;
    }
    int insert(int x, int root = 1)
    {
        int final_pos = 0;
        if (arr[root] == 0)
        {
            arr[root] = x;
            if (root > last_pos)
                last_pos = root;
            size++;
            return root;
        }
        if (arr[root] > x)
            final_pos = insert(x, 2 * root);
        else if (arr[root] < x)
            final_pos = insert(x, 2 * root + 1);
        return final_pos;
    }
    int find(int x, int pos = 1)
    {
        // return -1 if not found; return pos of the arr if found
        int ans = -1;
        if (!arr[pos])
            return ans;
        if (arr[pos] == x)
            return pos;
        int left = 2 * pos;
        int right = 2 * pos + 1;
        if (arr[pos] > x)
            ans = find(x, left);
        else if (arr[pos] < x)
            ans = find(x, right);
        return ans;
    }
    void inorder_iteration(int pos = 1)
    {
        if (pos > last_pos || arr[pos] == 0)
            return;
        inorder_iteration(2 * pos);
        cout << arr[pos] << " ";
        inorder_iteration(2 * pos + 1);
    }
    int findMax(int root_pos)
    {
        int ans = root_pos;
        int right = root_pos * 2 + 1;
        if (!arr[right])
            return ans;
        ans = findMax(right);
        return ans;
    }
    int findMin(int root_pos)
    {
        int ans = root_pos;
        int left = root_pos * 2;
        if (!arr[left])
            return ans;
        ans = findMin(left);
        return ans;
    }
    void Delete(int x)
    {
        int pos = find(x);
        int left = 2 * pos;
        int right = 2 * pos + 1;
        if (pos < 0 || !arr[pos])
            return;
        if (!arr[left] && !arr[right])
        {
            arr[pos] = 0;
            updateLastPos();
            return;
        }
        else if (arr[left])
        {
            int replace_pos = findMax(left);
            int to_replace = arr[replace_pos];
            Delete(arr[replace_pos]);
            arr[pos] = to_replace;
        }
        else
        {
            int replace_pos = findMin(right);
            int to_replace = arr[replace_pos];
            Delete(arr[replace_pos]);
            arr[pos] = to_replace;
        }
    }
    void updateLastPos(int pos = 1)
    {
        if (!arr[pos])
            return;
        if (pos > last_pos)
            last_pos = pos;
        int left = 2 * pos;
        int right = 2 * pos + 1;
        if (arr[left])
            updateLastPos(left);
        if (arr[right])
            updateLastPos(right);
        return;
    }
    int getDepthSum(int pos=1,int depth=1)
    {
        if(arr[pos]==0 || pos>last_pos)
            return 0;
        return depth+getDepthSum(2*pos,depth+1)+ getDepthSum(2*pos+1,depth+1);
    }
    float getASL()
    {
        int depthSum=getDepthSum();
        return (float)depthSum/(float)size;
    }
};

void input(BST *tree)
{
    int num = 0;
    char c;
    while ((c = getchar()) != '\n')
    {
        if (isdigit(c))
        {
            num = num * 10 + c - '0';
        }
        else if (num != 0)
        {
            printf("%d ", num);
            tree->insert(num);
            num = 0;
        }
    }
    return;
}

void check(BST *tree, int x)
{
    int find_res = tree->find(x);
    if (!find_res)
    {
        printf("No %d exist in the BST!\n", x);
        return;
    }
    else
    {
        tree->Delete(x);
        tree->inorder_iteration();
    }
}

int main()
{
    freopen("arrbst.in", "r", stdin);
    // input data is as follows:
    // 1 3 2 90 66 23 12 875\n
    // 3
    BST *tree = new BST();
    cout << "The input data: ";
    input(tree);

    // tests
    printf("\n");
    tree->inorder_iteration();
    printf("\n");
    float ASL=tree->getASL();
    cout<<"The ASL of the BST is "<<ASL<<endl;
    int x;
    cin >> x;
    printf("The pos of value %d is ", x);
    cout << tree->find(x) << endl;
    check(tree, x);
    fclose(stdin);
    return 0;
}