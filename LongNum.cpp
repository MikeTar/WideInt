
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

int nun_base = 256;
int max_num_digits = 5;

template <typename T>
vector<unsigned long> set_num(vector<T>& num)
{
    vector<unsigned long> slnum;

    for(int N = 0; N < num.size(); N++)
    {
        for(int B = 0; B < sizeof(T); B++)
        {
            T n = num[N] >> B*8*sizeof(unsigned long);
            bitset<32> bnum(n);
            slnum.push_back(bnum.to_ulong());
       }
    }
    return slnum;
}

int main()
{
    cout<<"Hello World"<<endl;
    vector<unsigned long> some_num;
    vector<int> int_num;
    int_num.push_back(16781216);
    some_num = set_num(int_num);
    for(int i = some_num.size()-1; i >= 0; i--)
    {
        cout<<some_num[i]<<" ";
    }
    cout<<endl;
    
    return 0;
}

