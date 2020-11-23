#ifndef WIDEINTTYPE
#define WIDEINTTYPE

#include <iostream>
#include <vector>
#include <string>

#define out_t double

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
	string to_str(num_sys);
	wint operator+ (wint);
	wint& operator+= (wint);
	wint operator- (wint);
	wint& operator-= (wint);
	wint operator- ();
	wint operator* (wint);
	wint& operator*= (wint);
	wint operator/ (wint);
	wint& operator/= (wint);
	wint operator% (wint);
	wint& operator%= (wint);
	wint& operator= (wint&);
	wint& operator= (string);
	wint& operator= (int64_t&);
	wint& operator++();
	wint& operator--();
	wint operator++(int);
	wint operator--(int);
	wint rem ();
	int size();
	friend std::ostream& operator<<(std::ostream& out, wint &wn);
	friend std::istream& operator>> (std::istream &in, wint &wn);
	friend out_t ddiv(wint d1, wint d2);

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
	wint& Lsh(uint32_t);
	wint& Rsh(uint32_t);
	bool ZF = false;	//The ZF is flag of zero. When ZF = false that means the number not equal to zero, else the number is zero.
	bool SF = false;	//The SF is flag of sign number. When SF = false that means the number is positive else the number is negative.
	bool isNAN();
	void set_num(wint*);
	void set_num(int64_t);
};

std::ostream& operator<<(std::ostream& out, wint &wn);
out_t ddiv(wint d1, wint d2);

#endif //WIDEINTTYPE
