#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <ctime>
#include <cstdio>
#include <chrono> //  для функций из std::chrono
#include "wideint.h"

#ifdef DEBUG
#define mode "Debug mode"
#else
#define mode "Release mode"
#endif // DEBUG

//std::ostream& operator<<(std::ostream& out, wint &wn)
//{
//	auto flags = cout.flags();
//	//if(ios::binary) out << wn.to_str(num_sys::bin);
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


using namespace std;

class Timer
{
private:
	//  Псевдонимы типов используются для удобного доступа к вложенным типам
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

string num_str;

int main()
{
	wint e(25);

	cout << "Binary value of number " << e << " is " << e.to_str(num_sys::_bin) << endl;

	bool CF = 0;
	//wint c, d, res1;
	cout << "First number value " << endl;
	cout << "Input a number:" << endl;
	// Строка должна содержать только цифровые символы '0'...'9' с ведущим знаком '-' для отрицательных чисел.
	// The string must contain only the numeric characters '0'...'9' with the leading sign ' - ' for negative numbers.
	cin >> num_str;
	//int a = stoi(num_str);
	wint c = num_str;
	cout << "Length of number " << c.to_str(num_sys::_bin) << " is " << c.size() << " bit" << endl;	//num_sys::_dec
	cout << "Length of number " << oct << c << " is " << c.size() << " bit" << endl;	//num_sys::_dec
	cout << "Length of number " << dec << c << " is " << c.to_str(num_sys::_dec).size() << " digits" << endl;	//num_sys::_dec
	cout << "Length of number " << hex << c << " is " << c.size() << " bit" << endl;	//num_sys::_dec
	cout << dec;
	c = c.negate();
	cout << "Negate of number is  " << c << endl;
	c = c.negate();
	cout << "Negate of number again is  " << c << endl;
	cout << endl;

	cout << "Second number value " << endl;
	cout << "Input a number:" << endl;
	cin >> num_str;
	//int b = stoi(num_str);
	wint d = num_str;
	cout << "Length of number " << d << " is " << d.size() << " bit" << endl;
	d = d.negate();
	cout << "Negate of number is  " << d << endl;
	d = d.negate();
	cout << "Negate of number again is  " << d << endl;
	cout << endl;

	cout << "Summation of numbers " << endl;
	Timer mt;
	wint res1 = c + d;
	cout << "Time of  Summation = " << mt.elapsed() << " s" << " in " << mode << endl;
	cout << c << " + " << d << " = " << res1 << endl;
	cout << "Length of summ " << res1 << " is " << res1.size() << " bit" << endl;
	cout << endl;

	cout << "Subtraction of numbers " << endl;
	mt.reset();
	res1 = c - d;
	cout << "Time of  Subtraction = " << mt.elapsed() << " s" << " in " << mode << endl;
	cout << c << " - " << d << " = " << res1 << endl;
	cout << "Length of subtract " << res1 << " is " << res1.size() << " bit" << endl;
	cout << endl;

	cout << "Multiplication of numbers " << endl;
	mt.reset();
	res1 = c * d;
	cout << "Time of  Multiplication = " << mt.elapsed() << " s" << " in " << mode << endl;
	cout << c << " * " << d << " = " << res1 << endl;
	cout << "Length of product " << res1 << " is " << res1.size() << " bit" << endl;
	cout << endl;

	cout << "Division of numbers " << endl;
	mt.reset();
	res1 = c / d;
	cout << "Time of  Division = " << mt.elapsed() << " s" << " in " << mode << endl;
	cout << c << " / " << d << " = " << res1 << endl;
	cout << "Length of quotient " << res1 << " is " << res1.size() << " bit" << endl;
	cout << endl;

	cout << "Division of numbers by module " << endl;
	mt.reset();
	res1 = c % d;
	cout << "Time of  Division by module = " << mt.elapsed() << " s" << " in " << mode << endl;
	cout << c << " % " << d << " = " << res1 << endl;
	cout << "Length of remainder " << res1 << " is " << res1.size() << " bit" << endl;
	cout << endl;

	cout << "Real division of wide integer numbers " << endl;
	mt.reset();
	double dres = ddiv(c, d);
	cout << "Time of  Division = " << mt.elapsed() << " s" << " in " << mode << endl;
	cout << c << " // " << d << " = " << setw(15) << scientific << setprecision(14) << dres << endl;
	cout << endl;
	//cout << "Division of numbers " << endl;
	//mt.reset();
	//res1 = ndiv(c, d);
	//cout << "Time of  Division by ndiv() = " << mt.elapsed() << " s" << " in " << mode << endl;
	//cout << c.to_str(num_sys::_bin) << " / " << d.to_str(num_sys::_oct) << " = " << res1.to_str(num_sys::_hex) << endl;
	//cout << "Length of quotient " << res1.to_str(num_sys::_dec) << " is " << res1.size() << " bit" << endl;
	//cout << endl;

	//mt.reset();
	//dres = ddiv(a, b);
	//cout << "Time of  Division = " << mt.elapsed() << " s" << " in " << mode << endl;
	//cout << a << " // " << b << " = " << setw(64) << scientific << setprecision(63) << dres << endl;
	//cout << endl;

	system("pause");
	return 0;
}
