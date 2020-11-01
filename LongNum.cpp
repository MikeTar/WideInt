
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

int nun_base = 256;
int max_num_digits = 5;
bitset<8> dig;
vector<bitset<8>> slnum;

template <typename T>
vector<bitset<8>> set_num(vector<T>& num)
{
    vector<bitset<8>> slnum;

    for(int N = 0; N < num.size(); N++)
    {
        for(int B = 0; B < sizeof(T); B++)
        {
            T n = num[N] >> B*8;
            bitset<8> bnum(n);
            //if(bnum.to_ulong() != 0)
                slnum.push_back(bnum);
       }
    }
    return slnum;
}

int main()
{
    cout<<"Hello World"<<endl;
    vector<bitset<8>> some_num;
    vector<int> int_num;
    int_num.push_back(16781216);
    some_num = set_num(int_num);
    for(int i = some_num.size()-1; i >= 0; i--)
    {
        cout<<some_num[i]<<" ";
    }
    cout<<endl;
    
    for(int i = some_num.size()-1; i >= 0; i--)
    {
        cout<<some_num[i].to_ulong( )<<" ";
    }
    cout<<endl;
    return 0;
}

