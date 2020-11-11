#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>


using namespace std;

//struct wnum
//{
//	int NoD;
//	bitset<512>bwnum;
//	void set_num(char[], int);
//	void set_num(wnum&);
//	void wnum::set_num(int);
//};
//
//
//wnum addwc(wnum& wnumin1, wnum& wnumin2, bool& carry)
//{
//	wnum res;
//	carry = 0;
//	int sz = wnumin1.NoD > wnumin2.NoD ? wnumin1.NoD : wnumin2.NoD;
//	res.NoD = sz;
//	for (int i = 0; i < sz; i++)
//	{
//		res.bwnum[i] = wnumin1.bwnum[i] ^ wnumin2.bwnum[i] ^ carry;
//		carry = ((wnumin1.bwnum[i] | wnumin2.bwnum[i]) & carry) | (wnumin1.bwnum[i] & wnumin2.bwnum[i]) ? 1 : 0;	//!res.bwnum[i] & (wnumin1.bwnum[i] & wnumin2.bwnum[i]) | carry 
//	}
//	if (carry)
//	{
//		res.bwnum[sz] = wnumin1.bwnum[sz] ^ wnumin2.bwnum[sz] ^ carry;
//		carry = 0;
//		res.NoD = ++sz;
//	}
//	return res;
//}
//
//wnum sub(wnum& wnumin1, wnum& wnumin2)
//{
//	bool CF;
//	wnum res, tmp;
//	res.set_num(1);
//	tmp.set_num(wnumin2);
//	int sz = wnumin1.NoD > wnumin2.NoD ? wnumin1.NoD : wnumin2.NoD;
//	for(int i = 0; i<sz; i++) tmp.bwnum.flip(i);
//	tmp.NoD = sz;
//	tmp = addwc(tmp, res, CF);
//	res = addwc(wnumin1, tmp, CF);
//	res.bwnum[res.NoD - 1] = 0;
//	return res;
//}

bool zero(char in[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (in[i] == '-') continue;
		if (in[i] != '0')
		{
			return false;
		}
	}
	 return true;
}

int input(char input[])
{
	int exit;
	int n;
	do {
		exit = 1;
		n = -1;
		cout << "Input a number:" << endl;
		cin >> input;

		while (input[++n] != '\0') {
			if (input[n] == '-') continue;
			if (input[n] < '0' || '9'  < input[n]) {
				input[0] = '\0';
				exit = 0;
				cout << "Input numbers from 0 to 9 only." << endl;
				break;
			}
		};
	} while (!exit);
	return n;
}

//void wnum:: set_num(char num[], int n)
//{
//	string num_str;
//	div_t res;
//
//	do
//	{
//		num_str += (num[n - 1] - '0') % 2 + '0';
//		res.quot = res.rem = 0;
//
//		for (int i = 0; i < n; ++i)
//		{
//			int a = (num[i] - '0') + res.rem * 10;
//			res.quot = a / 2;
//			num[i] = res.quot + '0';
//			res.rem = a % 2;
//		}
//
//	}while(!zero(num, n));	//!zero(num, n)
//
//	for (int i = 0; i < (int)num_str.size() / 2; i++)
//	{
//		NoD = num_str.size() - 1;
//		char buf = num_str[i];
//		num_str[i] = num_str[NoD - i];
//		num_str[NoD - i] = buf;
//	}
//
//	++NoD;
//	bitset<512> bnum(num_str);
//	bwnum = bnum;
//}
//
//void wnum::set_num(wnum& wn)
//{
//	bwnum = wn.bwnum;
//	NoD = wn.NoD;
//}
//
//void wnum:: set_num(int num)
//{
//	bitset<512> zeros;
//	bitset<512> tmp(num);
//	NoD = 32;
//	zeros.flip();
//	zeros ^= tmp;
//	do { --NoD; } while (zeros[NoD] && NoD > 0);
//	++NoD;
//	bwnum = tmp;
//	
//}
