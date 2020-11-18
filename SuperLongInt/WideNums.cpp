#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdio>
#include <chrono> // дл€ функций из std::chrono

using namespace std;

class Timer
{
private:
	// ѕсевдонимы типов используютс€ дл€ удобного доступа к вложенным типам
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

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

//wnum addwc(wnum&, wnum&, bool&);
wnum1 sub(wnum1, wnum1);
wnum1 add(wnum1, wnum1);
wnum1 mul(wnum1, wnum1);
wnum1 div(wnum1, wnum1);
wnum1 ndiv(wnum1, wnum1);
wnum1 mod(wnum1, wnum1);

int main()
{
	string e;

	bool CF = 0;
	wnum1 c, d, res1;
	cout << "First number value " << endl;
	int n = input(num_str);
	c.set_num(num_str, n);
	cout << "Length of number " << c.to_str(num_sys::bin) << " is " << c.NoD << " bit" << endl;	//num_sys::dec
	c.negate();
	cout << "Negate of number is  " << c.to_str(num_sys::oct) << endl;
	c.negate();
	cout << "Negate of number again is  " << c.to_str(num_sys::hex) << endl;
	cout << endl;

	cout << "Second number value " << endl;
	n = input(num_str);
	d.set_num(num_str, n);
	cout << "Length of number " << d.to_str(num_sys::bin) << " is " << d.NoD << " bit" << endl;
	d.negate();
	cout << "Negate of number is  " << d.to_str(num_sys::oct) << endl;
	d.negate();
	cout << "Negate of number again is  " << d.to_str(num_sys::hex) << endl;
	cout << endl;
	
	cout << "Summation of numbers " << endl;
	Timer mt;
	res1 = add(c, d);
	cout << "Time of  Summation = " << mt.elapsed() << " s" << endl;
	cout << c.to_str(num_sys::bin) << " + " << d.to_str(num_sys::oct) << " = " << res1.to_str(num_sys::hex) << endl;
	cout << "Length of summ " << res1.to_str(num_sys::dec) << " is " << res1.NoD << " bit" << endl;
	cout << endl;

	cout << "Subtraction of numbers " << endl;
	mt.reset();
	res1 = sub(c, d);
	cout << "Time of  Subtraction = " << mt.elapsed() << " s" << endl;
	cout << c.to_str(num_sys::bin) << " - " << d.to_str(num_sys::oct)  << " = " << res1.to_str(num_sys::hex) << endl;
	cout << "Length of subtract " << res1.to_str(num_sys::dec) << " is " << res1.NoD << " bit" << endl;
	cout << endl;

	cout << "Multiplication of numbers " << endl;
	mt.reset();
	res1 = mul(c, d);
	cout << "Time of  Multiplication = " << mt.elapsed() << " s" << endl;
	cout << c.to_str(num_sys::bin) << " * " << d.to_str(num_sys::oct)  << " = " << res1.to_str(num_sys::hex) << endl;
	cout << "Length of product " << res1.to_str(num_sys::dec) << " is " << res1.NoD << " bit" << endl;
	cout << endl;

	cout << "Division of numbers " << endl;
	mt.reset();
	res1 = div(c, d);
	cout << "Time of  Division = " << mt.elapsed() << " s" << endl;
	cout << c.to_str(num_sys::bin) << " / " << d.to_str(num_sys::oct)  << " = " << res1.to_str(num_sys::hex) << endl;
	cout << "Length of quotient " << res1.to_str(num_sys::dec) << " is " << res1.NoD << " bit" << endl;
	cout << endl;

	cout << "Division of numbers by module " << endl;
	mt.reset();
	res1 = mod(c, d);
	cout << "Time of  Division by module = " << mt.elapsed() << " s" << endl;
	cout << c.to_str(num_sys::bin) << " % " << d.to_str(num_sys::oct)  << " = " << res1.to_str(num_sys::hex) << endl;
	cout << "Length of remainder " << res1.to_str(num_sys::dec) << " is " << res1.NoD << " bit" << endl;
	cout << endl;

	cout << "Division of numbers " << endl;
	mt.reset();
	res1 = ndiv(c, d);
	cout << "Time of  Division by ndiv() = " << mt.elapsed() << " s" << endl;
	cout << c.to_str(num_sys::bin) << " / " << d.to_str(num_sys::oct) << " = " << res1.to_str(num_sys::hex) << endl;
	cout << "Length of quotient " << res1.to_str(num_sys::dec) << " is " << res1.NoD << " bit" << endl;
	cout << endl;


	system("pause");
	return 0;
}
