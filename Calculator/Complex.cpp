// Complex.cpp
//
// Name: 林恆毅
// Date: May 25, 2017
// Last Update: June 1, 2017

#include <cmath>
#include "Complex.h"

Complex::Complex() {
	num = "0+0";
	type = 'c';
	sign = 1;
	imagSign = 1;
}

Complex::Complex(const Decimal &n, const Decimal &d) {
	num = n.getNum() + "+" + d.getNum();
	sign = n.getSign();
	imagSign = d.getSign();
	type = 'c';
}

Complex::Complex(const char* str) {
	type = 'c'; // set type
	string arg = str, tmp = "";
	
	//set real sign
	if (str[0] == '-') {
		sign = -1;
		arg.erase(0, 1);
	}
	else {
		sign = 1;
	}
	
	//set imagSign
	if (arg.find('-') != string::npos || arg.find('+') != string::npos) {
		if (arg.find('-') == string::npos) { // can't find '-'
			imagSign = 1;
		}
		else {
			imagSign = -1;
			if (arg.find('+') == string::npos) { // can't find '+'
				arg[arg.find('-')] = '+';
			}
			else {
				arg.erase(arg.find('-'), 1); // ex: 1+-2i -> 1+2i
			}
		}
		arg.erase(arg.find('i'), 1); // erase 'i'
	}
	else {
		arg += "+0"; // enter only real part
		imagSign = 1;
	}
	num = arg;
}

Complex::Complex(const string& str) {
	*this = Complex(str.c_str());
}

Complex::Complex(const Integer& i) {
	num = i.getNum() + "+0";
	type = 'c';
	sign = i.getSign();
	imagSign = 1;
}

Complex::Complex(const Decimal& d) {
	num = d.getNum() + "+0";
	type = 'c';
	sign = d.getSign();
	imagSign = 1;
}

Complex::Complex(const Complex& c) {
	num = c.getNum();
	type = 'c';
	sign = c.getSign();
	imagSign = c.imagSign;
}

Complex::~Complex() {
	
}

int Complex::getImagSign()
{
	return imagSign;
}

void Complex::operator =(const char *str)
{
	Complex tmp = Complex(str);
	num = tmp.num;
	type = tmp.type;
	sign = tmp.sign;
	imagSign = tmp.imagSign;
}

istream& Complex::input(istream &is)
{
	string input = "";
	is >> input;
	*this = Complex(input);
	return is;
}

ostream& Complex::output(ostream &os) const
{
	string delimiter = "+", str = getNum(), real, imag, res = "";
	
	real = str.substr(0, str.find(delimiter));
	imag = str.erase(0, str.find(delimiter) + delimiter.length());
	
	Decimal r(real), i(imag);
	
	res = Decimal::Divide(r, 10); // output real part
	res += "+"; // output '+'
	res += Decimal::Divide(i, 10); // output imag part
	
	if (sign < 0) res = "-" + res;
	
	if (imagSign == -1) res[res.find('+')] = '-';
	
	res += "i";
	
	os << res;
	return os;
}

Complex& operator +(const Complex &a, const Complex &b)
{
	string delimiter = "+";
	string aug = a.num; //augend
	string add = b.num; //addend
	Decimal  r1, r2, i1, i2;
	
	r1 = aug.substr(0, aug.find(delimiter));
	r1.setSign(a.getSign());
	i1 = aug.erase(0, aug.find(delimiter) + delimiter.length());
	i1.setSign(a.imagSign);
	r2 = add.substr(0, add.find(delimiter));
	r2.setSign(b.getSign());
	i2 = add.erase(0, add.find(delimiter) + delimiter.length());
	i2.setSign(b.imagSign);
	
	Complex *res;
	
	res = new Complex(r1 + r2, i1 + i2);
	
	return *res;
	
}

Complex& operator -(const Complex &a, const Complex &b)
{
	string delimiter = "+";
	string sub = a.num; //subtrahend
	string min = b.num; //minuend
	Decimal  r1, r2, i1, i2;
	
	r1 = sub.substr(0, sub.find(delimiter));
	r1.setSign(a.getSign());
	i1 = sub.erase(0, sub.find(delimiter) + delimiter.length());
	i1.setSign(a.imagSign);
	r2 = min.substr(0, min.find(delimiter));
	r2.setSign(b.getSign());
	i2 = min.erase(0, min.find(delimiter) + delimiter.length());
	i2.setSign(b.imagSign);
	
	Complex *res;
	
	res = new Complex(r1 - r2, i1 - i2);
	
	return *res;
};

Complex& operator *(const Complex &a, const Complex &b)
{
	string delimiter = "+";
	string multid = a.num; //Multiplicand
	string multir = b.num; //Multiplier
	Decimal  r1, r2, i1, i2, tmpR, tmpI;
	
	r1 = multid.substr(0, multid.find(delimiter));
	r1.setSign(a.getSign());
	i1 = multid.erase(0, multid.find(delimiter) + delimiter.length());
	i1.setSign(a.imagSign);
	r2 = multir.substr(0, multir.find(delimiter));
	r2.setSign(b.getSign());
	i2 = multir.erase(0, multir.find(delimiter) + delimiter.length());
	i2.setSign(b.imagSign);
	
	Complex *res;
	
	tmpR = r1*r2 - i1*i2; // real part
	tmpI = r1*i2 + i1*r2; // imag part
	
	res = new Complex(tmpR, tmpI);
	
	return *res;
};

Complex& operator /(const Complex &a, const Complex &b)
{
	string delimiter = "+";
	string dvd = a.num; //Dividend
	string dvr = b.num; //Divisor
	Decimal  r1, r2, i1, i2, tmpR, tmpI;
	
	r1 = dvd.substr(0, dvd.find(delimiter));
	r1.setSign(a.getSign());
	i1 = dvd.erase(0, dvd.find(delimiter) + delimiter.length());
	i1.setSign(a.imagSign);
	r2 = dvr.substr(0, dvr.find(delimiter));
	r2.setSign(b.getSign());
	i2 = dvr.erase(0, dvr.find(delimiter) + delimiter.length());
	i2.setSign(b.imagSign);
	
	Complex *res;
	
	tmpR = (r1 * r2 + i1 * i2) / (r2 * r2 + i2 * i2); // real part
	tmpI = (i1 * r2 - r1 * i2) / (r2 * r2 + i2 * i2); // imag part
	
	res = new Complex(tmpR, tmpI);
	
	return *res;
};

Complex& Power(const Complex &b, double power)
{
	
	if (power <= 0 || (power - (int)power) != 0)
		throw invalid_argument("Undefined");
	
	Complex *c = new Complex(b);
	
	for (int i = 0; i < power - 1; ++i) {
		*c = *c * b;
	}
	
	return *c;
}










