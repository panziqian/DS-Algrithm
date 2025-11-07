#include <cstdio>
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

int getNodeSum(TreeNode *root)
{
    // get the total number of nodes of the BST
    if (root == nullptr)
        return 0;
    return 1 + getNodeSum(root->left) + getNodeSum(root->right);
}
int getDepthSum(TreeNode *root, int depth)
{
    // get the total depth of all nodes
    if (root == nullptr)
        return 0;
    return depth + getDepthSum(root->left, depth + 1) +
           getDepthSum(root->right, depth + 1);
}

float calASL(int NodeSum, int DepthSum)
{
    // calcualte the ASL of the BST
    return (float)DepthSum / (float)NodeSum;
}
void iteration(TreeNode *root)
{
    // 对BST进行中序遍历
    if (root == nullptr)
        return;
    iteration(root->left);
    cout << root->key << " ";
    iteration(root->right);
}
TreeNode *findMax(TreeNode *root)
{
    // 查找BST中的值最大的节点
    if (root == nullptr)
        return nullptr;
    while (root->right != nullptr)
        root = root->right;
    return root;
}
TreeNode *findMin(TreeNode *root)
{
    // 查找BST中的值最小的节点
    if (root == nullptr)
        return nullptr;
    while (root->left != nullptr)
        root = root->left;
    return root;
}
TreeNode *insert(TreeNode *&root, int x)
{
    // 往BST中插入节点
    if (root == nullptr)
    {
        TreeNode *tn = new TreeNode(x);
        root = tn;
        return root;
    }
    if (x == root->key)
        return root;
    else if (x < root->key)
        insert(root->left, x);
    else
        insert(root->right, x);
    return nullptr;
}
TreeNode *find(TreeNode *root, int x)
{
    // 递归地查找指定值的节点
    if (root == nullptr)
        return nullptr;
    if (x == root->key)
        return root;
    else if (x < root->key)
        return find(root->left, x);
    else
        return find(root->right, x);
}
TreeNode *nonrecur_find(TreeNode *root, int x)
{
    // 非递归地查找指定值的节点
    if (root == nullptr)
        return nullptr;
    while (root != nullptr)
    {
        if (root->key == x)
            return root;
        else if (root->key > x)
            root = root->right;
        else
            root = root->left;
    }
    return nullptr;
}
TreeNode *getPNode(TreeNode *root, TreeNode *node)
{
    // 获取节点的父节点
    if (root == node)
        return nullptr;
    while (root->left != node && root->right != node)
    {
        if (node->key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}
void Delete(TreeNode *&root, TreeNode *node)
{
    // 删除节点
    TreeNode *parent = getPNode(root, node);
    if (node->left == nullptr && node->right == nullptr)
    {
        if (parent == nullptr)
        {
            free(node);
            root = nullptr;
            return;
        }
        if (parent->key > node->key)
            parent->left = nullptr;
        else
            parent->right = nullptr;
        free(node);
    }
    else if (node->left != nullptr && node->right != nullptr)
    {
        TreeNode *to_replace = findMax(node->left);
        int val_to_replace = to_replace->key;
        Delete(root, to_replace);
        node->key = val_to_replace;
    }
    else
    {
        if (parent == nullptr)
        {
            TreeNode *to_delete = root;
            if (node->left != nullptr)
                root = root->left;
            else
                root = root->right;
            free(to_delete);
            return;
        }
        if (node->left != nullptr)
            parent->left = node->left;
        else
            parent->right = node->right;
        free(node);
    }
    return;
}
void input(TreeNode *&root)
{
    // 处理输入
    char c;
    int num = 0;
    while ((c = getchar()) != '\n')
    {
        if (isdigit(c))
        {
            num = num * 10 + (c - '0');
        }
        else if (num != 0)
        {
            insert(root, num);
            num = 0;
        }
    }
    insert(root, num);
}

void check(TreeNode *root, int x)
{
    // find element x and if it exist, delete it and re-iterate the BST; if not,
    // output the message
    TreeNode *x_node = find(root, x);
    if (x_node == nullptr)
    {
        printf("%d does not exist in the BST\n", x);
        return;
    }
    else
    {
        Delete(root, x_node);
        iteration(root);
    }
    return;
}

int main()
{
    freopen("text.in", "r", stdin);
    TreeNode *root = nullptr;
    input(root);
    // test the output
    iteration(root); // 对BST进行中序遍历
    cout << endl;
    // output the ASL of the BST
    int node_sum = getNodeSum(root);
    int depth_sum = getDepthSum(root, 1);
    cout << "The ASL of the BST is  " << calASL(node_sum, depth_sum) << endl;
    // 输出BST中的最大节点和最小节点
    TreeNode *maxNode = findMax(root);
    TreeNode *minNode = findMin(root);
    cout << "Max:" << maxNode->key << " " << "Min:" << minNode->key << endl;
    int x = 1;
    cin >> x;
    printf("searching %d ...\n",x);
    check(root, x);
    fclose(stdin);
    return 0;
}