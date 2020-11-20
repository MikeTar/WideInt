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
	wint(int64_t&);
	wint(string);
	//~wint();
	string to_str(num_sys);
	wint operator+ (wint);
	wint operator- (wint);
	wint operator* (wint);
	wint operator/ (wint);
	wint operator% (wint);
	wint& operator= (wint&);
	wint& operator= (string);
	wint& operator= (int64_t&);
	int size();
	wint negate();
	reminder *rem;
	friend std::ostream& operator<<(std::ostream& out, const wint &wn);

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
	void _Lsh(uint32_t);
	wint Lsh(uint32_t);
	void _Rsh(uint32_t);
	wint Rsh(uint32_t);
	bool ZF = false;	//The ZF is flag of zero. When ZF = false that means the number not equal to zero, else the number is zero.
	bool SF = false;	//The SF is flag of sign number. When SF = false that means the number is positive else the number is negative.
	bool isNAN();
	void set_num(wint*);
	void set_num(int64_t);
};

//std::ostream& operator<<(std::ostream& out, wint &wn)
//{
//	////if(ios::binary) out << wn.to_str(num_sys::bin);
//	//if (ios::oct)
//	//	out << wn.to_str(num_sys::_oct);
//	//else if (ios::dec)
//	//	out << wn.to_str(num_sys::_dec);
//	//else if (ios::hex)
//	//	out << wn.to_str(num_sys::_hex);
//	//else
//		out << wn.to_str(num_sys::_bin);
//	return out;
//}

#endif //WIDEINTTYPE
