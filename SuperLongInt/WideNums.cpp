#include <iostream>
#include <iomanip>
#include "wideint.h"
#include "Timer.h"


#ifdef DEBUG
#define mode "Debug mode"
#else
#define mode "Release mode"
#endif // DEBUG

int os_flags;
#define store_flags os_flags=cout.flags();
#define restore_flags cout.flags(os_flags);

using namespace std;

string num_str;

int main()
{
	wint e(25);

	cout << "Binary value of number " << e << " is " << e.to_str(num_sys::_bin) << endl;

	bool CF = 0;
	wint c/*, d, res1*/;
	cout << "First number value " << endl;
	cout << "Input a number:" << endl;
	// Строка должна содержать только цифровые символы '0'...'9' с ведущим знаком '-' для отрицательных чисел.
	// The string must contain only the numeric characters '0'...'9' with the leading sign ' - ' for negative numbers.
	cin >> c;
	//int a = stoi(num_str);
	//wint c = num_str;
	store_flags
	cout << "Length of number " << c.to_str(num_sys::_bin) << " is " << c.size() << " bit" << endl;	//num_sys::_dec
	cout << "Length of number " << oct << c << " is " << c.size() << " bit" << endl;	//num_sys::_dec
	cout << "Length of number " << dec << c << " is " << c.to_str(num_sys::_dec).size() << " digits" << endl;	//num_sys::_dec
	cout << "Length of number " << hex << c << " is " << c.size() << " bit" << endl;	//num_sys::_dec
	restore_flags
		c = -c;
	cout << "Negate of number is  " << c << endl;
	c = -c;
	cout << "Negate of number again is  " << c << endl;
	++c;
	cout << "Increment of number is  " << c << endl;
	--(--c);
	cout << "Decrement of number is  " << c << endl;
	cout << endl;


	cout << "Second number value " << endl;
	cout << "Input a number:" << endl;
	cin >> num_str;
	//int b = stoi(num_str);
	wint d = num_str;
	cout << "Length of number " << d << " is " << d.size() << " bit" << endl;
	d = -d;
	cout << "Negate of number is  " << d << endl;
	d = -d;
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

	cout << "Remainder of the division of numbers " << endl;
	cout << c << " % " << d << " = " << res1.rem() << endl;
	cout << "Length of remainder " << res1 << " is " << res1.size() << " bit" << endl;
	cout << endl;

	cout << "Division of numbers by module " << endl;
	mt.reset();
	res1 = c % d;
	cout << "Time of  Division by module = " << mt.elapsed() << " s" << " in " << mode << endl;
	cout << c << " % " << d << " = " << res1 << endl;
	cout << "Length of remainder " << res1 << " is " << res1.size() << " bit" << endl;
	cout << endl;

	store_flags
	cout << "Real division of wide integer numbers " << endl;
	mt.reset();
	out_t dres = ddiv(c, d);
	cout << "Time of  Division = " << mt.elapsed() << " s" << " in " << mode << endl;
	cout << c << " // " << d << " = " << setw(16) << scientific << setprecision(15) << dres << endl;
	cout << endl;
	restore_flags

	store_flags
	cout << "Compare " << endl;
	out_t a = 3;
	out_t b = 11;
	cout << a << " // " << b << " = " << setw(16) << scientific << setprecision(15) << a/b << endl;
	cout << endl;
	restore_flags

	system("pause");
	return 0;
}
