#ifndef WIDEINTTYPE
#define WIDEINTTYPE

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum num_sys
{
	bin = 2,
	oct = 8,
	dec = 10,
	hex = 16
};

class wint
{
public:
	wint();
	wint(int64_t&);
	wint(string);
	string to_str(num_sys);
	wint operator+ (wint&);
	wint operator- (wint&);
	wint operator* (wint&);
	wint operator/ (wint&);
	wint operator% (wint&);

private:
	struct reminder
	{
		int NoD = 0;
		vector<bool> bwint;
		bool ZF = false;
		bool SF = false;
	}rem;
	int NoD;
	vector<bool> bwint;
	void negate();
	void altcode();
	void inc();
	void resize();
	void _Lsh(uint32_t);
	wint Lsh(uint32_t);
	void _Rsh(uint32_t);
	wint Rsh(uint32_t);
	bool ZF = false, SF = false;
	bool isNAN();
	void set_num(wint*);
	void set_num(int64_t);
	void set_num(string);
};

#endif //WIDEINTTYPE
