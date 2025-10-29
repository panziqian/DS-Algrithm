#include <iostream>
using namespace std;

class TreeNode
{
public:
    int key;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : key(x), left(nullptr), right(nullptr) {};
};

void iteration(TreeNode *root)
{
    if (root == nullptr)
        return;
    iteration(root->left);
    cout << root->key << " ";
    iteration(root->right);
}
TreeNode *findMax(TreeNode *root)
{
    if (root == nullptr)
        return nullptr;
    while (root->right != nullptr)
        root = root->right;
    return root;
}
TreeNode *findMin(TreeNode *root)
{
    if (root == nullptr)
        return nullptr;
    while (root->left != nullptr)
        root = root->left;
    return root;
}
void insert(TreeNode *&root, int x)
{
    if (root == nullptr)
    {
        TreeNode *tn = new TreeNode(x);
        root = tn;
        return;
    }
    if (x == root->key)
        return;
    else if (x < root->key)
        insert(root->left, x);
    else
        insert(root->right, x);
    return;
}
void find(TreeNode *root, int x)
{
    while (1)
    {
        if (x < root->key)
        {
        }
    }
}
TreeNode *build(int *arr)
{
    if (*arr == -1)
        return nullptr;
    TreeNode *root = new TreeNode(*arr);
    arr++;
    while (*arr != -1)
    {
        insert(root, *arr);
        arr++;
    }
    return root;
}

int arr[10005]={1,3,2,90,66,23,12,875,-1};
int main()
{
    TreeNode *root = build(arr);
    iteration(root);
    cout << endl;
    TreeNode *maxNode = findMax(root);
    TreeNode *minNode = findMin(root);
    cout<<"Max:"<<maxNode->key<<" "<<"Min:"<<minNode->key<<endl;
    return 0;
}