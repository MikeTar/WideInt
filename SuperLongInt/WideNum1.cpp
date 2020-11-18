#include <iostream>
#include <vector>
#include <string>


using namespace std;

bool zero(char[], int);

enum num_sys
{
	bin = 2,
	oct = 8,
	dec = 10,
	hex = 16
};


struct wnum1
{
	int NoD;
	vector<bool> bwnum;
	void set_num(char[], int);
	void set_num(wnum1&);
	void set_num(int);
	void negate();
	void altcode();
	void inc();
	string to_str(num_sys);
	//string to_str_10();
	void resize();
	void _Lsh(uint32_t);
	wnum1 Lsh(uint32_t);
	void _Rsh(uint32_t);
	wnum1 Rsh(uint32_t);
	bool ZF = false, SF = false;
	bool isNAN();
};

wnum1 rem;
wnum1 div(wnum1, wnum1);
wnum1 ndiv(wnum1, wnum1);


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
	NoD = (int)bwnum.size();
}

void wnum1::set_num(wnum1& wn)
{
	bwnum = wn.bwnum;
	NoD = wn.NoD;
}

void wnum1:: set_num(int num)
{
	int sz = sizeof(num) * 8;
	vector<bool> tmp(sz);
	NoD = sz;
	if (num < 0)
	{
		SF = 1;
		num = -num;
	}

	int j = sz - 1;
	for (int i = 0; i < j - 1; i++) tmp[i] = (bool)((num >> i) & 1);
	while (tmp[j] != 1) { --NoD; --j; }
	tmp.resize(NoD);
	bwnum = tmp;
	
}

void wnum1::negate()
{
	SF = !SF;
}

void wnum1::altcode()
{
	bwnum.flip();
	inc();
}

void wnum1::inc()
{
	int sz = (int)bwnum.size();
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

string wnum1::to_str(num_sys divr)
{
	char ch;
	string ns;
	wnum1 divrin, quot;

	quot.bwnum = bwnum;
	quot.SF = SF;
	quot.NoD = NoD;


	switch (divr)
	{
	case 2:
		if (SF)	ns += ')';
		for (auto v : bwnum)
			ns = (char)(v + '0') + ns;
		if (SF) ns = (char)('(') + ((char)('-') + ns);
		ns = 'b' + ns;
		break;

	case 8:
		if (SF)	ns += ')';
		divrin.set_num(divr);
		while(!quot.ZF)
		{
			ch = 0;
			quot = div(quot, divrin);
			if (!rem.ZF)
			{
				for (int i = rem.NoD - 1; i >= 0; i--)
					ch = (ch | rem.bwnum[i]) << 1;
				ch >>= 1;
				ns = (char)(ch + '0') + ns;
			}
			else ns = (char)(ch + '0') + ns;
		}
		if (SF) ns = (char)('(')+((char)('-') + ns);
		ns = '0' + ns;
		break;

	case 10:
		if (SF)	ns += ')';
		divrin.set_num(divr);
		while(!quot.ZF)
		{
			ch = 0;
			quot = div(quot, divrin);
			if (!rem.ZF)
			{
				for (int i = rem.NoD - 1; i >= 0; i--)
					ch = (ch | rem.bwnum[i]) << 1;
				ch >>= 1;
				ns = (char)(ch + '0') + ns;
			}
			else ns = (char)(ch + '0') + ns;
		}
		if (SF) ns = (char)('(')+((char)('-') + ns);
		break;

	case 16:
		if (SF)	ns += ')';
		divrin.set_num(divr);
		while (!quot.ZF)
		{
			ch = 0;
			quot = div(quot, divrin);
			if (!rem.ZF)
			{
				for (int i = rem.NoD - 1; i >= 0; i--)
					ch = (ch | rem.bwnum[i]) << 1;
				ch >>= 1;
				if (ch >= 10)
					ch = (ch - 10) + 'A';
				else
					ch += '0';
				ns = (char)ch + ns;
			}
			else ns = (char)(ch + '0') + ns;
		}
		if (SF) ns = (char)('(') + ((char)('-') + ns);
		ns = '0' + ('x' + ns);
		break;

	default:
		break;
	}


	//if (SF)	ns += ')';
	//int i = 0;
	//int prev_i = i;
	//for (auto v : bwnum)
	//{
	//	ns += (char)v + '0';
	//	if ((i - prev_i) == 3)
	//	{
	//		ns += ' ';
	//		prev_i = i + 1;
	//	}
	//	++i;
	//}
	//if (SF) ns = (ns + '-') + '(';

	//int NoD = (int)ns.size() - 1;
	//for (int i = 0; i < (int)ns.size() / 2; i++)
	//{
	//	char buf = ns[i];
	//	ns[i] = ns[NoD - i];
	//	ns[NoD - i] = buf;
	//}

	return ns;
}

void wnum1::resize()
{
	NoD = (int)bwnum.size();
	int i = NoD - 1;
	while ((i > 0) && !bwnum[i]){--NoD; --i;}
	ZF = (i || bwnum[0]) ? 0 : 1;
	bwnum.resize(NoD);
}

void wnum1::_Lsh(uint32_t n)
{
	if (!n) return;
	vector<bool> tmp;
	tmp.resize(bwnum.size()+(size_t)n);
	for (int i = n; i < (int)tmp.size(); i++) tmp[i] = bwnum[i - n];
	bwnum = tmp;
}

wnum1 wnum1::Lsh(uint32_t n)
{
	wnum1 tmp;
	tmp.bwnum = bwnum;
	if (!n) return tmp;
	tmp.bwnum.clear();
	tmp.bwnum.resize(bwnum.size() + (size_t)n);
	for (int i = n; i < (int)tmp.bwnum.size(); i++) tmp.bwnum[i] = bwnum[i - n];
	//bwnum = tmp;
	return tmp;
}

void wnum1::_Rsh(uint32_t n)
{
	if (!n) return;
	vector<bool> tmp;
	tmp.resize(bwnum.size() - (size_t)n);
	for (int i = 0; i < (int)tmp.size(); i++) tmp[i] = bwnum[i + n];
	bwnum = tmp;
}

wnum1 wnum1::Rsh(uint32_t n)
{
	wnum1 tmp;
	tmp.bwnum = bwnum;
	if (!n) return tmp;
	tmp.bwnum.clear();
	tmp.bwnum.resize(bwnum.size() - (size_t)n);
	for (int i = 0; i < (int)tmp.bwnum.size(); i++) tmp.bwnum[i] = bwnum[i + n];
	//bwnum = tmp;
	return tmp;
}

bool wnum1::isNAN()
{
	bool res = bwnum.empty(); /*!(bwnum.size())*/;
	return res;
}

wnum1 add(wnum1 term1, wnum1 term2)
{
	int sz;
	wnum1 res;
	bool carry = 0;

	if (term1.SF & term2.SF)
	{
		term1.SF = term2.SF = 0;
		res.SF = 1;
	}

	if (term1.bwnum.size() > term2.bwnum.size())
	{
		if (term1.SF)
			term1.altcode();
		sz = (int)term1.bwnum.size();
		term2.bwnum.resize(sz);
		if (term2.SF)
			term2.altcode();
	}
	else
	{
		if (term2.SF)
			term2.altcode();
		sz = (int)term2.bwnum.size();
		term1.bwnum.resize(sz);
		if (term1.SF)
			term1.altcode();
	}

	res.bwnum.resize(sz);
	for (int i = 0; i < sz; i++)
	{
		res.bwnum[i] = term1.bwnum[i] ^ term2.bwnum[i] ^ carry;
		carry = ((term1.bwnum[i] | term2.bwnum[i]) & carry) | (term1.bwnum[i] & term2.bwnum[i]) ? 1 : 0;
		if((i == sz-1) && (term1.SF | term2.SF)) res.SF = term1.SF ^ term2.SF ^ carry;
	}
	if (carry & !term1.SF &  !term2.SF)
	{
		res.bwnum.push_back(carry);
		carry = 0;
		res.NoD = (int)res.bwnum.size();
	}
	if (res.SF & (term1.SF ^ term2.SF))
		res.altcode();
	res.resize();
	return res;
}

wnum1 sub(wnum1 minuend, wnum1 subtrahend)
{
	wnum1 res;
	subtrahend.negate();
	res = add(minuend, subtrahend);
	res.resize();
	return res;
}

wnum1 mul(wnum1 wnumin1, wnum1 wnumin2)
{
	wnum1 product, tmp[2];
	bool SF = 0;

	if (wnumin1.SF ^ wnumin2.SF)
		SF = 1;

	wnumin1.SF = wnumin2.SF = 0;

	if (wnumin1.bwnum.size() > wnumin2.bwnum.size())
	{
		tmp[0] = wnumin2; // multiplier
		tmp[1] = wnumin1; // multiplicand
	}
	else
	{
		tmp[0] = wnumin1;
		tmp[1] = wnumin2;
	}

	for (int i = 0; i < (int)tmp[0].bwnum.size(); i++)
	{
		if (tmp[0].bwnum[i])
		{
			product = add(product, tmp[1]);
		}
		tmp[1]._Lsh(1);
	}

	product.SF = SF;
	return product;
}

wnum1 div(wnum1 dividend, wnum1 divisor)
{
	wnum1 quotient, remainder;

	int k= dividend.NoD - divisor.NoD;

	bool SF = false;
	if (dividend.SF ^ divisor.SF)
		SF = 1;
	
	dividend.SF = divisor.SF = 0;

	if (k >= 0)
	{
		quotient.bwnum.resize(k + 1);
		divisor._Lsh(k);
		remainder = sub(dividend, divisor);
		quotient.bwnum[k] = !remainder.SF;
		for (int i = 1; i < k+1; i++)
		{
			remainder._Lsh(1);
			if (!remainder.SF)
				remainder = sub(remainder, divisor);
			else
				remainder = add(remainder, divisor);
			quotient.bwnum[k-i] = !remainder.SF;
		}

		if (remainder.SF)
		{
			remainder = add(remainder, divisor);
		}
		if(((int)remainder.bwnum.size() - k) > 0)
			remainder._Rsh(k);
	}
	else
	{
		remainder = dividend;
		quotient.bwnum.push_back(0);
	}

	if (!remainder.isNAN() && remainder.NoD < 0) remainder.NoD = (int)remainder.bwnum.size();
	remainder.resize();
	rem = remainder;

	if(!quotient.isNAN() && quotient.NoD < 0) quotient.NoD = (int)quotient.bwnum.size();
	quotient.resize();

	quotient.SF = SF;
	return quotient;
} 

wnum1 ndiv(wnum1 dividend, wnum1 divisor)
{
	wnum1 quotient, remainder;
	wnum1 q, r/*, rqq*/;
	wnum1 lq, rq/*, qq*/;

	wnum1 one;
	one.bwnum.resize(1, 1);
	//tmp[0] = tmp[1] = one;

	int k = dividend.NoD - divisor.NoD;

	bool SF = 0;
	if (dividend.SF ^ divisor.SF)
		SF = 1;

	dividend.SF = divisor.SF = 0;
	wnum1 divd = dividend;
	wnum1 divr = divisor;

	if (k >= 0)
	{
		divr._Lsh(k);
		wnum1 end = sub(divr, divd);
		while (end.SF)
		{
			divr._Lsh(1);
			++k;
			end = sub(divr, divd);
		}

		if (k > 0)
		{
			lq = one.Lsh(k + 1);
			rq = one.Lsh(k - 1);
			//rq = 1 << (k - 1);

			wnum1 stop;
			stop.SF = false;
			do
			{
				q = (add(lq, rq)).Rsh(1);
				//qq = (lq + rq)*2/3 /*>> (1)*/;
				//q.set_num(qq);
				divd = mul(divisor, q);
				r = sub(dividend, divd);
				if (!r.SF)
					stop = sub(r, divisor);
				//rqq.set_num(rq);
				wnum1 zero = sub(q, rq);

				if (r.SF && !stop.SF && !zero.ZF)
					lq = q;
				else if (!r.SF && !stop.SF && !zero.ZF)
					rq = q;
				else
				{
					quotient = q;
					rem = remainder = r;
					break;
				}
			} while (true);
		}
		else
		{
			quotient.set_num(1);
			rem = remainder = sub(dividend, divisor);
		}

	}
	else
	{
		remainder = dividend;
		quotient.bwnum.push_back(0);
	}

	if (!remainder.isNAN() && remainder.NoD < 0) remainder.NoD = (int)remainder.bwnum.size();
	remainder.resize();
	rem = remainder;

	if (!quotient.isNAN() && quotient.NoD < 0) quotient.NoD = (int)quotient.bwnum.size();
	quotient.resize();

	quotient.SF = SF;
	return quotient;
}

wnum1 mod(wnum1 divd, wnum1 divr)
{
	wnum1 quot;
	quot = div(divd, divr);
	return rem;
}
