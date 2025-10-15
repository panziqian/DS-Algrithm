#include<iostream>
#include<cstring>
#define MAX_SIZE 10005
using namespace std;

class String
{
    private:
        char* ch;
        int size;
    public:
        String()
        {
            size=0;
            ch=new char[size+1];
            ch[0]='\0';
        }
        String(const String& s)
        {
            size=s.size;
            ch=new char[size+1];
            strcpy(ch,s.ch);
        }
        String(const char* init)
        {
            size=strlen(init);
            ch=new char[size+1];
            strcpy(ch,init);
        }
        ~String()
        {
            delete[] ch;
        }
        int length()
        {
            return size;
        }
        String& operator=(const String& other)
        {
            if(this != &other)
            {
                size=other.size;
                delete[] ch;
                ch=new char[size+1];
                strcpy(ch,other.ch);
            }
            return *this;
        }
        String operator+(const String& other) const
        {
            String output;
            output.size=size+other.size;
            output.ch=new char[output.size+1];
            strcpy(output.ch,ch);
            strcat(output.ch,other.ch);
            return output;
        }
        String& operator+=(const String& other)
        {
            String output;
            output=*this+other;
            size=output.size;
            delete[] ch;
            ch=new char[size];
            strcpy(ch,output.ch);
            return *this;
        }
        String operator()(const int pos,const int len) const
        {
            if(len<0||len>size)
            {
                return String();
            }
            String output;
            output.size=len;
            output.ch=new char[len+1]; 
            int cnt=0,i=pos;
            for(;cnt<len;i++)
            {
                output.ch[cnt]=ch[i];
                cnt++;
            }
            output.ch[cnt]='\0';
            return output;
        }
        bool operator==(const String& other) const
        {
            if(size!=other.size)
                return 0;
            return strcmp(ch,other.ch)==0;
        }
        bool operator!=(const String& other) const
        {
            if(size!=other.size)
                return 1;
            return strcmp(ch,other.ch)!=0;
        }
        friend ostream& operator<<(ostream& os,const String& s)
        {
            os<<s.ch;
            return os;
        }
        int find(const String& pat)
        {
            return 1;
        }
        char& operator[](int i)
        {
            return ch[i];
        }
};

int main()
{
    String str("abcd");
    String str2("123");
    String str3;
    str+=str2;
    cout<<str<<endl;
    cout<<str(1,4)<<endl;
    String cmp("bcd1");
    cout<<cmp<<endl;
    cout<<(cmp==str);
    return 0;
}