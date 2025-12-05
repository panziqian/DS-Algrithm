#include <cstdio>
#include <iostream>
using namespace std;

class AVLNode
{
  public:
    int val;
    int height;
    AVLNode *left;
    AVLNode *right;
    AVLNode() : val(0), height(1), left(nullptr), right(nullptr) {};
    AVLNode(int value)
    {
        val = value;
        height = 1;
    }
};

int height(AVLNode *node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

void updateHeight(AVLNode *node)
{
    node->height = 1 + max(height(node->left), height(node->right));
}

int bf(AVLNode *node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

AVLNode *RotateRight(AVLNode *root)
{
    AVLNode *lchild = root->left;
    AVLNode *lrchild = lchild->right;
    root->left = lrchild;
    lchild->right = root;
    updateHeight(root);
    updateHeight(lchild);
    return lchild;
}

AVLNode *RotateLeft(AVLNode *root)
{
    AVLNode *rchild = root->right;
    AVLNode *rlchild = rchild->left;
    root->right = rlchild;
    rchild->left = root;
    updateHeight(root);
    updateHeight(rchild);
    return rchild;
}

AVLNode *Insert(AVLNode *&root, int x)
{
    if (root == nullptr)
    {
        AVLNode *node = new AVLNode(x);
        return node;
    }
    else if (root->val > x)
        root->left = Insert(root->left, x);
    else if (root->val < x)
        root->right = Insert(root->right, x);

    updateHeight(root);
    int balance = bf(root);

    // Right Right
    if (balance < -1 && bf(root->right) == -1)
        RotateLeft(root);

    // Right Left
    if (balance < -1 && bf(root->right) == 1)
    {
        root->right = RotateRight(root->right);
        return RotateLeft(root);
    }

    // Left Right
    if (balance > 1 && bf(root->left) == -1)
    {
        root->left = RotateLeft(root->left);
        return RotateRight(root);
    }

    // Left Left
    if (balance > 1 && bf(root->left) == 1)
        RotateLeft(root);

    return root;
}

void inorder(AVLNode *root)
{
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

// Print tree sideways for quick visualization
void printSideways(AVLNode *root, int depth = 0)
{
    if (!root)
        return;
    printSideways(root->right, depth + 1);
    for (int i = 0; i < depth; ++i)
        cout << "    ";
    cout << root->val << "\n";
    printSideways(root->left, depth + 1);
}

int getNodeSum(AVLNode *root)
{
    if(root==nullptr)
        return 0;
    return 1+ getNodeSum(root->left)+ getNodeSum(root->right);
}

int getDepthSum(AVLNode *root,int depth)
{
    if(root==nullptr)
        return 0;
    return depth+getDepthSum(root->left,depth+1)+getDepthSum(root->right,depth+1);
}
float calASL(AVLNode *root)
{
    int nodeSum = getNodeSum(root);
    int depthSum = getDepthSum(root,1);
    return (float)depthSum / (float)nodeSum;
}

void input(AVLNode *&root)
{
    char c;
    int num = 0;
    while ((c = getchar()) != EOF)
    {
        if (isdigit(c))
        {
            num = num * 10 + c - '0';
        }
        else
        {
            printf("%d ", num);
            root = Insert(root, num);
            num = 0;
        }
    }
}
int main()
{
    freopen("avl.in", "r", stdin);
    AVLNode *root = nullptr;
    input(root);
    printf("\n");
    inorder(root);
    printf("\n");
    float ASL=calASL(root);
    cout<<"ASL of AVL is "<<ASL<<endl;
    printf("\n----------------\n");
    printSideways(root);
    fclose(stdin);
    return 0;
}