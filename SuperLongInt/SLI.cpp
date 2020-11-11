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
	void complementary(wnum1);
	void complementary();
	void add(vector<bool>);
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

int main()
{
	string e;

	bool CF = 0;
//	wnum a, b, res;
	wnum1 c, d, res1;
	int n = input(num_str);
//	a.set_num(num_str, n);

//	n = input(num_str);
//	b.set_num(num_str, n);

//	n = input(num_str);
	c.set_num(num_str, n);
	n = input(num_str);
	d.set_num(num_str, n);

	res1 = add(c, d);
	cout << c.wn_to_str() << " + " << d.wn_to_str()  << " = " << res1.wn_to_str() << endl;

	res1 = sub(c, d);
	cout << c.wn_to_str() << " - " << d.wn_to_str()  << " = " << res1.wn_to_str() << endl;

	res1 = mul(c, d);
	cout << c.wn_to_str() << " * " << d.wn_to_str()  << " = " << res1.wn_to_str() << endl;
	cout <<"Length of number " << c.wn_to_str() << " is " << c.wn_to_str().size() << " bit" << endl;

	//res = addwc(a, b, CF);
	//cout << a.bwnum << " + " << b.bwnum << " = " << res.bwnum << " with CF = " << CF << endl;
	//res = sub(a, b);
	//cout << a.bwnum << " - " << b.bwnum << " = " << res.bwnum << endl;


	cin >> e;
	return 0;
}
