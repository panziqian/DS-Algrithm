#include <cstddef>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class HuffmanNode
{
  public:
    int byte;
    uint64_t weight;
    HuffmanNode *left;
    HuffmanNode *right;
    HuffmanNode() : byte(-1), weight(0), left(nullptr), right(nullptr)
    {
    }
    HuffmanNode(int b, uint64_t w)
    {
        byte = b;
        weight = w;
    }
};

struct compareNode
{
    bool operator()(HuffmanNode *n1, HuffmanNode *n2)
    {
        return n1->weight > n2->weight;
    }
};

class BitWriter
{
  public:
    ofstream &os;
    uint8_t buf;
    int nbits;
    BitWriter(ofstream &o) : os(o), buf(0), nbits(0)
    {
    }
    void write_bit(bool b)
    {
        buf = (buf << 1) | (b ? 1 : 0);
        nbits++;
        if (nbits == 8)
        {
            os.put((char)buf);
            nbits = 0;
            buf = 0;
        }
    }
    void write_bits_from_string(const string &bits)
    {
        for (char c : bits)
            write_bit(c=='1');
    }
    int flush()
    {
        if (nbits == 0)
            return 0;
        int pad = 8 - nbits;
        buf <<= pad;
        os.put((char)buf);
        nbits = 0;
        buf = 0;
        return pad % 8;
    }
};

class BitReader
{
  public:
    istream &is;
    uint8_t buf;
    int nbits;
    BitReader(istream &i) : is(i), buf(0), nbits(0)
    {
    }
    int read_bit()
    {
        if (nbits == 0)
        {
            int c = is.get();
            if (c == EOF)
                return -1;
            buf = (uint8_t)c;
            nbits = 8;
        }
        int bit = (buf >> 7) & 1;
        buf <<= 1;
        nbits--;
        return bit;
    }
};

void getHuffmanCode(HuffmanNode *root, const string &prefix,
                    vector<string> &codes)
{
    if (root == nullptr)
        return;
    if (root->byte != -1)
    {
        codes[root->byte] = prefix.empty() ? "0" : prefix;
        return;
    }
    getHuffmanCode(root->left, prefix + "0", codes);
    getHuffmanCode(root->right, prefix + "1", codes);
}

void delete_tree(HuffmanNode *root)
{
    if (root == nullptr)
        return;
    delete_tree(root->left);
    delete_tree(root->right);
    free(root);
}

bool huffman_encode(string &infile, string &outfile)
{
    vector<uint64_t> freq(256,0);
    ifstream fin(infile, ios::binary);
    uint64_t orignal_size = 0;
    char buf[4096];
    while (fin.read(buf, sizeof(buf)) || fin.gcount())
    {
        streamsize s = fin.gcount();
        orignal_size += s;
        for (streamsize i = 0; i < s; i++)
        {
            freq[(uint8_t)buf[i]]++;
        }
    }
    priority_queue<HuffmanNode *, vector<HuffmanNode *>, compareNode> pq;
    for (int i = 0; i < 256; i++)
    {
        HuffmanNode *Node = new HuffmanNode(i,freq[i]);
        pq.push(Node);
    }
    HuffmanNode *root = nullptr;
    while(pq.size()>1)
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
    }
    root=pq.top();
    vector<string> codes(256);
    getHuffmanCode(root, "", codes);

    uint64_t total_bits = 0;
    for (int i = 0; i < 256; i++)
    {
        if (freq[i] > 0)
            total_bits += freq[i] * codes[i].size();
    }
    int padding = (int)((8 - (total_bits % 8)) % 8);

    ofstream fout(outfile, ios::binary);
    fout.write("HUF1", 4);
    fout.write((const char *)&orignal_size, sizeof(orignal_size));

    uint8_t pad8 = (uint8_t)padding;
    fout.write((char *)&pad8, sizeof(pad8));
    // 写入频率表
    for (int i = 0; i < 256; i++)
    {
        fout.write((const char *)&freq[i], sizeof(freq[i]));
    }

    ifstream fin2(infile, ios::binary);
    BitWriter bw = BitWriter(fout);
    char rbuf[4096];
    while (fin2.read(rbuf, sizeof(rbuf)) || fin2.gcount())
    {
        streamsize s = fin2.gcount();
        for (streamsize i = 0; i < s; i++)
        {
            uint8_t byte = (uint8_t)rbuf[i];
            bw.write_bits_from_string(codes[byte]);
        }
    }
    bw.flush();
    fout.close();
    delete_tree(root);
    return true;
}

bool huffman_decode(string &infile, string &outfile)
{
    ifstream fin(infile, ios::binary);

    char magic[4];
    fin.read(magic, 4);
    uint64_t orignal_size = 0;
    fin.read((char *)&orignal_size, sizeof(orignal_size));
    uint8_t padding = 0;
    fin.read((char *)&padding, sizeof(padding));
    vector<uint64_t> freq(256,0);
    for (int i = 0; i < 256; i++)
        fin.read((char *)&freq[i], sizeof(freq[i]));
    priority_queue<HuffmanNode *, vector<HuffmanNode *>, compareNode> pq;
    for (int i = 0; i < 256; i++)
    {
        if (freq[i] > 0)
            pq.push(new HuffmanNode(i, freq[i]));
    }
    while (pq.size() > 1)
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
    }
    HuffmanNode *root = pq.top();

    ofstream fout(outfile, ios::binary);
    BitReader br(fin);
    HuffmanNode *cur = root;
    uint64_t written = 0;
    while (written < orignal_size)
    {
        int bit = br.read_bit();
        if (bit == 0)
            cur = cur->left;
        else if (bit == 1)
            cur = cur->right;
        else if(bit==-1)
        {
            cerr<<"read bit: EOF reached unexpectedly\n";
            delete_tree(root);
            return false;
        }
        if (cur->byte != -1)
        {
            fout.put((char)cur->byte);
            written++;
            cur = root;
        }
    }
    fout.close();
    delete_tree(root);
    return true;
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        cerr << "Too few arguments!\n";
        return -1;
    }
    string mode = argv[1];
    string infile = argv[2];
    string outfile = argv[3];
    if (mode == "-e")
    {
        if (huffman_encode(infile, outfile) == false)
        {
            cerr << "Encode failed!\n";
            return -1;
        }
        cout << "finished encode from " << infile << " to " << outfile << endl;
    }
    else
    {
        if (huffman_decode(infile, outfile) == false)
        {
            cerr << "Encode failed!\n";
            return -1;
        }
        cout << "finished decode from " << infile << " to " << outfile << endl;
    }
}