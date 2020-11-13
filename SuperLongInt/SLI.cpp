#include <iostream>
#include <string>
#include <vector>
#include <bitset>
//#include <cstdlib>

using namespace std;

char num_str[100];
int input(char[]);

//struct wnum
//{
//	int NoD;
//	bitset<512>bwnum;
//	void set_num(char[], int);
//	void set_num(wnum&);
//	void wnum::set_num(int);
//};

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
	void inc();
	string to_str(num_sys);
	void resize();
	void Lsh(int);
	void Rsh(int);
	bool ZF = false, SF = false;
};

//wnum addwc(wnum&, wnum&, bool&);
wnum1 sub(wnum1, wnum1);
wnum1 add(wnum1, wnum1);
wnum1 mul(wnum1, wnum1);
wnum1 div(wnum1, wnum1);
wnum1 mod(wnum1, wnum1);

int main()
{
	string e;

	bool CF = 0;
	wnum1 c, d, res1;
	cout << "First number value " << endl;
	int n = input(num_str);
	c.set_num(num_str, n);
	cout << "Length of number " << c.to_str(num_sys::dec) << " is " << c.NoD << " bit" << endl;
	c.negate();
	cout << "Negate of number is  " << c.to_str(num_sys::dec) << endl;
	c.negate();
	cout << "Negate of number again is  " << c.to_str(num_sys::dec) << endl;
	cout << endl;

	cout << "Second number value " << endl;
	n = input(num_str);
	d.set_num(num_str, n);
	cout << "Length of number " << d.to_str(num_sys::dec) << " is " << d.NoD << " bit" << endl;
	d.negate();
	cout << "Negate of number is  " << d.to_str(num_sys::dec) << endl;
	d.negate();
	cout << "Negate of number again is  " << d.to_str(num_sys::dec) << endl;
	cout << endl;

	cout << "Summation of numbers " << endl;
	res1 = add(c, d);
	cout << c.to_str(num_sys::dec) << " + " << d.to_str(num_sys::dec) << " = " << res1.to_str(num_sys::dec) << endl;
	cout << "Length of summ " << res1.to_str(num_sys::dec) << " is " << res1.NoD << " bit" << endl;
	cout << endl;

	cout << "Subtraction of numbers " << endl;
	res1 = sub(c, d);
	cout << c.to_str(num_sys::dec) << " - " << d.to_str(num_sys::dec)  << " = " << res1.to_str(num_sys::dec) << endl;
	cout << "Length of subtract " << res1.to_str(num_sys::dec) << " is " << res1.NoD << " bit" << endl;
	cout << endl;

	cout << "Multiplication of numbers " << endl;
	res1 = mul(c, d);
	cout << c.to_str(num_sys::dec) << " * " << d.to_str(num_sys::dec)  << " = " << res1.to_str(num_sys::dec) << endl;
	cout << "Length of product " << res1.to_str(num_sys::dec) << " is " << res1.NoD << " bit" << endl;
	cout << endl;

	cout << "Division of numbers " << endl;
	res1 = div(c, d);
	cout << c.to_str(num_sys::dec) << " / " << d.to_str(num_sys::dec)  << " = " << res1.to_str(num_sys::dec) << endl;
	cout << "Length of quotient " << res1.to_str(num_sys::dec) << " is " << res1.NoD << " bit" << endl;
	cout << endl;

	cout << "Division of numbers by module " << endl;
	res1 = mod(c, d);
	cout << c.to_str(num_sys::dec) << " % " << d.to_str(num_sys::dec)  << " = " << res1.to_str(num_sys::dec) << endl;
	cout << "Length of remainder " << res1.to_str(num_sys::dec) << " is " << res1.NoD << " bit" << endl;
	cout << endl;

	cin >> e;
	return 0;
}
