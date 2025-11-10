#include <cstddef>
#include <cstdio>
#include <iostream>
#include <map>
#include <ostream>
#include <queue>
#include <string>
#include <unistd.h>
using namespace std;

class HuffmanNode
{
  public:
    char ch;
    int weight;
    HuffmanNode *left;
    HuffmanNode *right;
    HuffmanNode() : ch('\0'), weight(0), left(nullptr), right(nullptr) {};
    HuffmanNode(int c, int w)
    {
        ch = c;
        weight = w;
        left = nullptr;
        right = nullptr;
    }
};
struct compareNode
{
    bool operator()(HuffmanNode *n1, HuffmanNode *n2)
    {
        return n1->weight > n2->weight;
    }
};

void printSideways(HuffmanNode *root, int depth = 0)
{
    if (!root)
        return;
    printSideways(root->right, depth + 1);
    for (int i = 0; i < depth; ++i)
        cout << "    ";
    cout << root->ch << "\n";
    printSideways(root->left, depth + 1);
}

class HuffmanTree
{
  public:
    HuffmanNode *head;
    map<char, string> HuffmanCode;
    priority_queue<HuffmanNode *, vector<HuffmanNode *>, compareNode> pq;
    map<char, int> weight_map;
    HuffmanTree()
    {
        head = nullptr;
    }
    void build(string raw_st)
    {
        for (char ch : raw_st)
        {
            weight_map[ch]++;
        }
        for (const auto &kv : weight_map)
        {
            HuffmanNode *Node = new HuffmanNode(kv.first, kv.second);
            pq.push(Node);
        }
        int size = pq.size();
        for (int i = 1; i < size; i++)
        {
            HuffmanNode *Node1 = pq.top();
            pq.pop();
            HuffmanNode *Node2 = pq.top();
            pq.pop();
            HuffmanNode *pNode = new HuffmanNode();
            pNode->weight = Node1->weight + Node2->weight;
            pNode->left = Node1;
            pNode->right = Node2;
            pq.push(pNode);
            if (i == size - 1)
                head = pNode;
        }
        getHuffmanCode(head, "");
        return;
    }
    void getHuffmanCode(HuffmanNode *root, string code)
    {
        if (root->ch != '\0')
        {
            HuffmanCode[root->ch] = code;
            return;
        }
        getHuffmanCode(root->left, code + "0");
        getHuffmanCode(root->right, code + "1");
    }
    void displayHuffmanCode()
    {
        for (const auto &kv : HuffmanCode)
        {
            cout << kv.first << " => " << kv.second << endl;
        }
        return;
    }
    string encode(string raw_st)
    {
        string encoded_st = "";
        for (char ch : raw_st)
        {
            encoded_st += HuffmanCode[ch];
        }
        encoded_st += '\0';
        return encoded_st;
    }
    string decode(string encoded_st)
    {
        string decode_st = "";
        int spos = 0, n = 1, st_size = encoded_st.size();
        while (spos < st_size - 1)
        {
            string tmp = encoded_st.substr(spos, n);
            for (const auto &kv : HuffmanCode)
            {
                if (kv.second == tmp)
                {
                    decode_st += kv.first;
                    spos += n;
                    n = 0;
                    break;
                }
            }
            n++;
        }
        return decode_st;
    }
};
string Huffman_encode(string raw_st)
{
    HuffmanTree *tree = new HuffmanTree();
    tree->build(raw_st);
    string encoded_st = tree->encode(raw_st);
    return encoded_st;
}

string Huffman_decode(HuffmanTree *tree, string encoded_st)
{
    string decoded_st = tree->decode(encoded_st);
    return decoded_st;
}

int main(int argc, char *argv[])
{

    //freopen("input", "r", stdin);
    freopen("output", "w", stdout);
    string input = "";
    getline(cin, input);
    cout << "input string is: " << endl << input << endl;
    HuffmanTree *tree = new HuffmanTree();
    tree->build(input);
    tree->displayHuffmanCode();

    string encode_s = Huffman_encode(input);
    cout << encode_s << endl;
    string decode_s = Huffman_decode(tree, encode_s);
    cout << decode_s << endl;
    return 0;
}