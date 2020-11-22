#ifndef WIDEINTTYPE
#define WIDEINTTYPE

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum num_sys
{
	_bin = 2,
	_oct = 8,
	_dec = 10,
	_hex = 16
};

class wint
{
public:
	struct reminder;
	wint();
	wint(int64_t);
	wint(string);
	//~wint();
	string to_str(num_sys);
	wint operator+ (wint);
	wint operator- (wint);
	wint operator- ();
	wint operator* (wint);
	wint operator/ (wint);
	wint operator% (wint);
	wint& operator= (wint&);
	wint& operator= (string);
	wint& operator= (int64_t&);
	wint rem ();
	int size();
	wint negate();
	//reminder *rem;
	friend std::ostream& operator<<(std::ostream& out, const wint &wn);
	friend double ddiv(wint d1, wint d2);

private:
	struct reminder
	{
		int NoD = 0;
		vector<bool> bwint;
		bool ZF = false;
		bool SF = false;
	}r;
	int NoD;
	vector<bool> bwint;
	void altcode();
	void inc();
	void resize();
	//void _Lsh(uint32_t);
	wint& Lsh(uint32_t);
	//void _Rsh(uint32_t);
	wint& Rsh(uint32_t);
	bool ZF = false;	//The ZF is flag of zero. When ZF = false that means the number not equal to zero, else the number is zero.
	bool SF = false;	//The SF is flag of sign number. When SF = false that means the number is positive else the number is negative.
	bool isNAN();
	void set_num(wint*);
	void set_num(int64_t);
};

std::ostream& operator<<(std::ostream& out, wint &wn);
//{
//	auto flags = cout.flags();
//	if(ios::binary) out << wn.to_str(num_sys::bin);
//	if (flags & std::ios::oct)
//		out << wn.to_str(num_sys::_oct);
//	else if (flags & std::ios::dec)
//		out << wn.to_str(num_sys::_dec);
//	else if (flags & std::ios::hex)
//		out << wn.to_str(num_sys::_hex);
//	else
//		out << wn.to_str(num_sys::_bin);
//	return out;
//}

double ddiv(uint64_t d1, uint64_t d2);
#endif //WIDEINTTYPE
