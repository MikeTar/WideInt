#include"wideint.h"

//std::ostream& operator<<(std::ostream& out, wint &wn)
//{
//	//if(ios::binary) out << wn.to_str(num_sys::bin);
//	if(ios::oct)
//		out << wn.to_str(num_sys::_oct);
//	else if(ios::dec)
//		out << wn.to_str(num_sys::_dec);
//	else if(ios::hex)
//		out << wn.to_str(num_sys::_hex);
//	else
//		out << wn.to_str(num_sys::_bin);
//	return out;
//}

wint div(wint, wint);

wint::wint()
{
	//rem = (reminder*)malloc(sizeof(reminder));
	bwint.push_back(0);
	NoD = ZF = 1;
	SF = 0;
}

//wint::~wint()
//{
//	delete rem;
//}

wint::wint(int64_t num)
{
	if (num != 0)
	{
		int sz = sizeof(num) * 8;
		vector<bool> tmp(sz);
		NoD = sz;
		ZF = 0;
		SF = 0;

		if (num < 0)
		{
			SF = 1;
			num = -num;
		}
		int j = sz - 1;
		for (int i = 0; i < j - 1; i++) tmp[i] = (bool)((num >> i) & 1);
		while (tmp[j] != 1) { --NoD; --j; }
		tmp.resize(NoD);
		bwint = tmp;
	}
	else wint();
	//{
	//	bwint.push_back(0);
	//	NoD = ZF = 1;
	//	SF = 0;
	//}
}

wint::wint(string num_str)
{
	char ch;
	div_t res;
	int beg = 0;
	if (num_str[0] == '-')
	{
		++beg;
		SF = 1;
	}
	int end = num_str.length();

	do
	{
		bwint.push_back((num_str[end - 1] - '0') & 1);

		res.rem = 0;

		if (num_str[0] == '0')
		{
			num_str.erase(0, 1);
			end = num_str.length();
		}

		for (int i = beg; i < end; ++i)
		{
			int a = (num_str[i] - '0') + res.rem * 10;
			res = div(a, 2);
			ch = res.quot + '0';
			num_str.replace(i, 1, 1, ch);
		}
	} while (end);
	resize();
}

//void wint::set_num(string num_str)
//{
//	wint(num_str);
//}

void wint::set_num(wint* wn)
{
	NoD = wn->NoD;
	ZF = wn->ZF;
	SF = wn->SF;
	bwint = wn->bwint;
}

void wint::set_num(int64_t num)
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
	ZF = 0;
	bwint = tmp;

}

wint wint::negate()
{
	wint res = *this;
	res.SF = !SF;
	return res;
}

void wint::altcode()
{
	bwint.flip();
	inc();
}

void wint::inc()
{
	int sz = (int)bwint.size();
	vector<bool> res, tmp;
	bool carry = 0;

	tmp.resize(1, 1);
	tmp.resize(sz);
	res.resize(sz);
	for (int i = 0; i < sz; i++)
	{
		res[i] = bwint[i] ^ tmp[i] ^ carry;
		carry = ((bwint[i] | tmp[i]) & carry) | (bwint[i] & tmp[i]) ? 1 : 0;
	}
	bwint = res;
}

string wint::to_str(num_sys divr)
{
	char ch;
	string ns;
	wint divrin, quot;

	//quot.bwint = bwint;
	//quot.SF = SF;
	//quot.NoD = NoD;

	quot = *this;

	switch (divr)
	{
	case 2:
		if (SF)	ns += ')';
		for (auto v : bwint)
			ns = (char)(v + '0') + ns;
		if (SF) ns = (char)('(') + ((char)('-') + ns);
		ns = 'b' + ns;
		break;

	case 8:
		if (SF)	ns += ')';
		divrin.set_num((int)divr);
		while (!quot.ZF)
		{
			ch = 0;
			quot = quot / divrin;
			if (!quot.rem->ZF)	//The ZF is flag of zero. When ZF = false it means that number not equal to zero, else it means that number is zero.
			{
				for (int i = quot.rem->NoD - 1; i >= 0; i--)
					ch = (ch | quot.rem->bwint[i]) << 1;
				ch >>= 1;
				ns = (char)(ch + '0') + ns;
			}
			else ns = (char)(ch + '0') + ns;
		}
		if (ZF) ns = '0' + ns;
		if (SF) ns = (char)('(') + ((char)('-') + ns);
		ns = '0' + ns;
		break;

	case 10:
		if (SF)	ns += ')';
		divrin.set_num(divr);
		while (!quot.ZF)
		{
			ch = 0;
			quot = quot / divrin;
			if (!quot.rem->ZF)
			{
				for (int i = quot.rem->NoD - 1; i >= 0; i--)
					ch = (ch | quot.rem->bwint[i]) << 1;
				ch >>= 1;
				ns = (char)(ch + '0') + ns;
			}
			else ns = (char)(ch + '0') + ns;
		}
		if (ZF) ns = '0' + ns;
		if (SF) ns = (char)('(') + ((char)('-') + ns);
		break;

	case 16:
		if (SF)	ns += ')';
		divrin.set_num(divr);
		while (!quot.ZF)
		{
			ch = 0;
			quot = quot / divrin;
			if (!quot.rem->ZF)
			{
				for (int i = quot.rem->NoD - 1; i >= 0; i--)
					ch = (ch | quot.rem->bwint[i]) << 1;
				ch >>= 1;
				if (ch >= 10)
					ch = (ch - 10) + 'A';
				else
					ch += '0';
				ns = (char)ch + ns;
			}
			else ns = (char)(ch + '0') + ns;
		}
		if (ZF) ns = '0' + ns;
		if (SF) ns = (char)('(') + ((char)('-') + ns);
		ns = '0' + ('x' + ns);
		break;

	default:
		break;
	}
	return ns;
}

double wint::double_div(wint divr)
{
	double dres, pdres;
	wint divd, res, srav;
	divd = *this;
	int k = divr.NoD - NoD;

	if (k > 0)
	{
		divd.Lsh(k);
		srav = divd - divr;
		if (srav.SF)
		{
			divd.Lsh(1);
		}
		res = divd / divr;
		dres = 0, pdres;
		for (int i = 0; i < k; i++)
		{
			pdres = dres;
			dres = (dres + (double)res.bwint[i]) / 2;
			if (dres == pdres) break;
		}
	}
	return dres;
}

wint wint::operator+(wint term2)
{
	int sz;
	wint res;
	bool carry = 0;

	if (SF & term2.SF)
	{
		SF = term2.SF = 0;
		res.SF = 1;
	}

	if (bwint.size() > term2.bwint.size())
	{
		if (SF)
			altcode();
		sz = (int)bwint.size();
		term2.bwint.resize(sz);
		if (term2.SF)
			term2.altcode();
	}
	else
	{
		if (term2.SF)
			term2.altcode();
		sz = (int)term2.bwint.size();
		bwint.resize(sz);
		if (SF)
			altcode();
	}

	res.bwint.resize(sz);
	for (int i = 0; i < sz; i++)
	{
		res.bwint[i] = bwint[i] ^ term2.bwint[i] ^ carry;
		carry = ((bwint[i] | term2.bwint[i]) & carry) | (bwint[i] & term2.bwint[i]) ? 1 : 0;
		if ((i == sz - 1) && (SF | term2.SF)) res.SF = SF ^ term2.SF ^ carry;
	}
	if (carry & !SF & !term2.SF)
	{
		res.bwint.push_back(carry);
		carry = 0;
		res.NoD = (int)res.bwint.size();
	}
	if (res.SF & (SF ^ term2.SF))
		res.altcode();
	res.resize();
	return res;
}

wint wint::operator-(wint subtrahend)
{
	wint /*minuend,*/ res;
	/*minuend.set_num(this);*/
	//res = minuend + subtrahend;
	res = *this + subtrahend.negate();
	res.resize();
	return res;
}

wint wint::operator*(wint wnumin2)
{
	wint product, tmp[2];
	bool SF = 0;

	if (this->SF ^ wnumin2.SF)
		SF = 1;

	this->SF = wnumin2.SF = 0;

	if (bwint.size() > wnumin2.bwint.size())
	{
		tmp[0] = wnumin2; // multiplier
		tmp[1] = *this; // multiplicand
	}
	else
	{
		tmp[0] = *this;
		tmp[1] = wnumin2;
	}

	for (int i = 0; i < (int)tmp[0].bwint.size(); i++)
	{
		if (tmp[0].bwint[i])
		{
			product = product + tmp[1];
		}
		tmp[1]._Lsh(1);
	}

	product.SF = SF;
	return product;
}

wint wint::operator/(wint divisor)
{
	wint quotient, remainder;

	int k = this->NoD - divisor.NoD;

	bool SF = false;
	if (this->SF ^ divisor.SF)
		SF = 1;

	this->SF = divisor.SF = 0;

	if (k >= 0)
	{
		quotient.bwint.resize(k + 1);
		divisor._Lsh(k);
		remainder = *this - divisor;
		quotient.bwint[k] = !remainder.SF;
		for (int i = 1; i < k + 1; i++)
		{
			remainder._Lsh(1);
			if (!remainder.SF)
				remainder = remainder - divisor;
			else
				remainder = remainder + divisor;
			quotient.bwint[k - i] = !remainder.SF;
		}

		if (remainder.SF)
		{
			remainder = remainder + divisor;
		}
		if (((int)remainder.bwint.size() - k) > 0)
			remainder._Rsh(k);
	}
	else
	{
		remainder = *this;
		quotient.bwint.push_back(0);
	}

	if (!remainder.isNAN() && remainder.NoD < 0)
		remainder.NoD = (int)remainder.bwint.size();
	remainder.resize();
	r.bwint = remainder.bwint;
	r.NoD = remainder.NoD;
	r.SF = remainder.SF;
	r.ZF = remainder.ZF;
	rem = &r;

	if (!quotient.isNAN() && quotient.NoD < 0)
		quotient.NoD = (int)quotient.bwint.size();
	quotient.resize();

	quotient.SF = SF;
	return quotient;
}

wint wint::operator%(wint divr)
{

	wint rem = *this / divr;
	rem.bwint = this->rem->bwint;
	rem.NoD = this->rem->NoD;
	rem.SF = this->rem->SF;
	rem.ZF = this->rem->ZF;

	return rem;
}

wint& wint::operator=(wint &wn)
{
	//*this = wn;
	NoD = wn.NoD;
	bwint = wn.bwint;
	SF = wn.SF;
	ZF = wn.ZF;

	if (wn.rem)
	{
		r.NoD = wn.rem->NoD;
		r.bwint = wn.rem->bwint;
		r.SF = wn.rem->SF;
		r.ZF = wn.rem->ZF;
		rem = &r;
	}
	return *this;
}

wint& wint::operator=(string num_str)
{
	wint res(num_str);
	*this = res;

	return *this;
}

wint& wint::operator=(int64_t &num)
{
	wint res(num);
	*this = res;
	return *this;
}

int wint::size()
{
	return NoD;
}


void wint::resize()
{
	NoD = (int)bwint.size();
	int i = NoD - 1;
	while ((i > 0) && !bwint[i]) { --NoD; --i; }
	ZF = (i || bwint[0]) ? 0 : 1;
	bwint.resize(NoD);
}

void wint::_Lsh(uint32_t n)
{
	if (!n) return;
	vector<bool> tmp;
	tmp.resize(bwint.size() + (size_t)n);
	for (int i = n; i < (int)tmp.size(); i++) tmp[i] = bwint[i - n];
	NoD = tmp.size();
	bwint = tmp;
}

wint wint::Lsh(uint32_t n)
{
	wint tmp;
	tmp.bwint = bwint;
	if (!n) return tmp;
	tmp.bwint.clear();
	tmp.bwint.resize(bwint.size() + (size_t)n);
	for (int i = n; i < (int)tmp.bwint.size(); i++) tmp.bwint[i] = bwint[i - n];
	tmp.resize();
	tmp.NoD = tmp.size();
	return tmp;
}

void wint::_Rsh(uint32_t n)
{
	if (!n) return;
	vector<bool> tmp;
	tmp.resize(bwint.size() - (size_t)n);
	for (int i = 0; i < (int)tmp.size(); i++) tmp[i] = bwint[i + n];
	NoD = tmp.size();
	bwint = tmp;
}

wint wint::Rsh(uint32_t n)
{
	wint tmp;
	tmp.bwint = bwint;
	if (!n) return tmp;
	tmp.bwint.clear();
	tmp.bwint.resize(bwint.size() - (size_t)n);
	for (int i = 0; i < (int)tmp.bwint.size(); i++) tmp.bwint[i] = bwint[i + n];
	tmp.NoD = tmp.size();
	return tmp;
}

bool wint::isNAN()
{
	return bwint.empty();
}

/*
Result of division two wide integer numbers will be correct if first number is lower then second number.
Otherwise result of division will contain only fractional part of result number.
*/
double ddiv(wint d1, wint d2)
{
	wint divd, res;
	int bsize = 128;

	divd = d1.Lsh(bsize);
	res = divd / d2;
	double dres = 0;
	for (int i = 0; i < bsize; i++)
		dres = (dres + (double)res.bwint[i]) / 2;
	return dres;
}

//for verification
double ddiv(uint64_t d1, uint64_t d2)
{
	uint64_t divd, res;
	uint64_t bsize = 32;

	divd = d1 << bsize;
	res = divd / d2;
	double dres = 0;
	for (int i = 0; i < bsize; i++)
	{
		int bit = (res >> i) & 1;
		dres = (dres + bit) / 2;
	}
	return dres;
}
