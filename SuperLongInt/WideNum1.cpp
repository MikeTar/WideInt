#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>


using namespace std;

bool zero(char[], int);

struct wnum1
{
	int NoD;
	vector<bool> bwnum;
	void set_num(char[], int);
	void set_num(wnum1&);
	void set_num(int);
	void negate();
	void inc();
	string wn_to_str();
	//string to_str_10();
	void resize();
	void Lsh(int);
	void Rsh(int);
	bool ZF = false, SF = false;
};

void wnum1::set_num(char num[], int n)
{
	string num_str;
	div_t res;
	int beg = 0;

	if (num[0] == '-')
		++beg;


	do
	{
		num_str += (num[n - 1] - '0') % 2 + '0';
		res.quot = res.rem = 0;

		for (int i = beg; i < n; ++i)
		{
			int a = (num[i] - '0') + res.rem * 10;
			res.quot = a / 2;
			num[i] = res.quot + '0';
			res.rem = a % 2;
		}

	} while (!zero(num, n));

	for (int i = 0 ; i < (int)num_str.size(); i++)
	{
		bwnum.push_back((char)num_str[i] - '0');
	}
	
	if(num[0] == '-')
		negate();
	NoD = bwnum.size();
}

void wnum1::set_num(wnum1& wn)
{
	bwnum = wn.bwnum;
	NoD = wn.NoD;
}

void wnum1:: set_num(int num)
{
	vector<bool> tmp(sizeof(num));
	NoD = sizeof(num);
	for (int i = 0; i < sizeof(num) - 1; i++) tmp[i] = (bool)((num >> i) & 1);
	int i = sizeof(num) - 1;
	while (tmp[i] != 1) { --NoD; --i; }
	tmp.resize(--NoD);
	bwnum = tmp;
	
}

void wnum1::negate()
{
	vector<bool> ;
	bwnum.flip();
	SF = !SF;
	inc();
}

void wnum1::inc()
{
	int sz = bwnum.size();
	vector<bool> res, tmp;
	bool carry = 0;

	tmp.resize(1, 1);
	tmp.resize(sz);
	res.resize(sz);
	for (int i = 0; i < sz; i++)
	{
		res[i] = bwnum[i] ^ tmp[i] ^ carry;
		carry = ((bwnum[i] | tmp[i]) & carry) | (bwnum[i] & tmp[i]) ? 1 : 0;
	}
	//if (carry)
	//{
	//	res.push_back(carry);
	//	carry = 0;
	//}

	bwnum = res;
}

string wnum1::wn_to_str()
{
	string ns;

	if (SF)
	{
		ns = '-';
		negate();
	}

	for (auto v : bwnum) ns += (char)v + '0';

	int NoD = ns.size() - 1;
	for (int i = 0; i < (int)ns.size() / 2; i++)
	{
		char buf = ns[i];
		ns[i] = ns[NoD - i];
		ns[NoD - i] = buf;
	}

	return ns;
}

void wnum1::resize()
{
	NoD = bwnum.size();
	int i = NoD - 1;
	while ((i > 0) && !bwnum[i]){--NoD; --i;}
	ZF = i ? 0 : 1;
	bwnum.resize(NoD);
}

void wnum1::Lsh(int n)
{
	if (!n) return;
	vector<bool> tmp;
	tmp.resize(bwnum.size()+(size_t)n);
	for (int i = n; i < tmp.size(); i++) tmp[i] = bwnum[i - n];
	bwnum = tmp;
}

void wnum1::Rsh(int n)
{
	if (!n) return;
	vector<bool> tmp;
	tmp.resize(bwnum.size() - (size_t)n);
	for (int i = 0; i < tmp.size(); i++) tmp[i] = bwnum[i + n];
	bwnum = tmp;
}

wnum1 add(wnum1 wnumin1, wnum1 wnumin2)
{
	int sz;
	wnum1 res;
	bool carry = 0;
	if (wnumin1.bwnum.size() > wnumin2.bwnum.size())
	{
		sz = wnumin1.bwnum.size();
		if (wnumin2.SF)
			wnumin2.bwnum.resize(sz, 1);
		else
			wnumin2.bwnum.resize(sz);
	}
	else
	{
		sz = wnumin2.bwnum.size();
		if (wnumin1.SF)
			wnumin1.bwnum.resize(sz, 1);
		else
			wnumin1.bwnum.resize(sz);
	}

	res.bwnum.resize(sz);
	for (int i = 0; i < sz; i++)
	{
		res.bwnum[i] = wnumin1.bwnum[i] ^ wnumin2.bwnum[i] ^ carry;
		carry = ((wnumin1.bwnum[i] | wnumin2.bwnum[i]) & carry) | (wnumin1.bwnum[i] & wnumin2.bwnum[i]) ? 1 : 0;
		if(i == sz-1) res.SF = wnumin1.SF ^ wnumin2.SF ^ carry;
	}
	if (carry)
	{
		res.bwnum.push_back(carry);
		carry = 0;
		res.NoD = res.bwnum.size();
	}
	res.resize();
	return res;
}

wnum1 sub(wnum1 wnumin1, wnum1 wnumin2)
{
	wnum1 res/*, tmp*/;
	//if (wnumin2.bwnum.size() < wnumin1.bwnum.size()) tmp.bwnum.resize(wnumin1.bwnum.size());
	wnumin2.negate();
	res = add(wnumin1, /*tmp*/wnumin2);
	//res.bwnum.resize(res.bwnum.size() - 1);
	res.resize();
	return res;
}

wnum1 mul(wnum1 wnumin1, wnum1 wnumin2)
{
	wnum1 sum, tmp[2];

	if (wnumin1.bwnum.size() > wnumin2.bwnum.size())
	{
		tmp[0] = wnumin2; // множитель
		tmp[1] = wnumin1; // множимое
	}
	else
	{
		tmp[0] = wnumin1;
		tmp[1] = wnumin2;
	}

	for (int i = 0; i < tmp[0].bwnum.size(); i++)
	{
		if (tmp[0].bwnum[i])
		{
			sum = add(sum, tmp[1]);
		}
		tmp[1].Lsh(1);
	}

	return sum;
}

//wnum1 div(wnum1 dividend, wnum1 divisor)
//{
//	wnum1 quotient, compl_divr;
//	int k;
//	if (dividend.NoD > divisor.NoD)
//	{
//		k = dividend.NoD - divisor.NoD;
//		divisor.Lsh(k);
//		compl_divr.complementary(divisor);
//	}
//
//}
