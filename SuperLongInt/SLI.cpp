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

//wnum addwc(wnum&, wnum&, bool&);
wnum1 sub(wnum1, wnum1);
wnum1 add(wnum1, wnum1);
wnum1 mul(wnum1, wnum1);
wnum1 div(wnum1, wnum1);

int main()
{
	string e;

	bool CF = 0;
	wnum1 c, d, res1;
	cout << "First number value " << endl;
	int n = input(num_str);
	c.set_num(num_str, n);
	cout << "Length of number " << c.wn_to_str() << " is " << c.NoD << " bit" << endl;
	c.negate();
	cout << "Negate of number is  " << c.wn_to_str() << endl;
	c.negate();
	cout << "Negate of number again is  " << c.wn_to_str() << endl;
	cout << endl;

	cout << "Second number value " << endl;
	n = input(num_str);
	d.set_num(num_str, n);
	cout << "Length of number " << d.wn_to_str() << " is " << d.NoD << " bit" << endl;
	d.negate();
	cout << "Negate of number is  " << d.wn_to_str() << endl;
	d.negate();
	cout << "Negate of number again is  " << d.wn_to_str() << endl;
	cout << endl;

	cout << "Summation of numbers " << endl;
	res1 = add(c, d);
	cout << c.wn_to_str() << " + " << d.wn_to_str()  << " = " << res1.wn_to_str() << endl;
	cout << "Length of summ " << res1.wn_to_str() << " is " << res1.NoD << " bit" << endl;
	cout << endl;

	cout << "Subtraction of numbers " << endl;
	res1 = sub(c, d);
	cout << c.wn_to_str() << " - " << d.wn_to_str()  << " = " << res1.wn_to_str() << endl;
	cout << "Length of subtract " << res1.wn_to_str() << " is " << res1.NoD << " bit" << endl;
	cout << endl;

	cout << "Multiplication of numbers " << endl;
	res1 = mul(c, d);
	cout << c.wn_to_str() << " * " << d.wn_to_str()  << " = " << res1.wn_to_str() << endl;
	cout << "Length of product " << res1.wn_to_str() << " is " << res1.NoD << " bit" << endl;
	cout << endl;

	cout << "Division of numbers " << endl;
	res1 = div(c, d);
	cout << c.wn_to_str() << " / " << d.wn_to_str()  << " = " << res1.wn_to_str() << endl;
	cout << "Length of quotient " << res1.wn_to_str() << " is " << res1.NoD << " bit" << endl;
	cout << endl;

	cin >> e;
	return 0;
}
