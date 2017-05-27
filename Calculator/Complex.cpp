//
//  Complex.cpp
//  Henry
//
//  Created by Henry Lin on 2017/5/25.
//  Copyright © 2017年 Henry Lin. All rights reserved.
//

#include <cmath>
#include "Complex.h"

namespace
{
	
	Integer EuclideanAlgorithm(Integer &lhs, Integer &rhs)
	{
		Integer a = lhs, b = rhs;
		while( a > 0 && b > 0 )
		{
			if( a >= b )
			{
				a = a % b;
			}
			else if( b > a )
			{
				b = b % a;
			}
		}
		if(a >= b)
		{
			return a;
		}
		else
		{
			return b;
		}
	}
	
	void ReductionOfFraction(Decimal &f)
	{
		string tmp = f.getNum();
		string delimiter = "/";
		Integer numerator = tmp.substr(0, tmp.find(delimiter));
		Integer denominator = tmp.erase(0, tmp.find(delimiter) + delimiter.length());
		Integer GCD = EuclideanAlgorithm(numerator, denominator);
		numerator = IntDivide(numerator, GCD);
		denominator = IntDivide(denominator, GCD);
		tmp = numerator.getNum() + "/" + denominator.getNum();
		f.setNum(tmp);
	}
	
}

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
	
	if (arg.find('-') != string::npos || arg.find('+') != string::npos) {
		if (arg.find('-') == string::npos) {
			imagSign = 1;
		}
		else {
			imagSign = -1;
			if (arg.find('+') == string::npos) { // can't find '+'
				arg[arg.find('-')] = '+';
			}
			else {
				arg.erase(arg.find('-'), 1);
			}
		}
		arg.erase(arg.find('i'), 1);
	}
	else {
		arg += "+0";
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
	string delimiter = "+", str = getNum(), real, imag, res = "", rStr, iStr;
	
	real = str.substr(0, str.find(delimiter));
	imag = str.erase(0, str.find(delimiter) + delimiter.length());
	
	Decimal r(real), i(imag);
	
	rStr = r.getNum(), iStr = i.getNum();
	for (int j = 0, cnt = 0; j < rStr.length(); ++j) {
		if (rStr[j] == '/') {
			cnt++;
		}
		if (cnt == 2) {
			rStr.erase(j);
			r.setNum(rStr);
			break;
		}
	}
	
	for (int j = 0, cnt = 0; j < iStr.length(); ++j) {
		if (iStr[j] == '/') {
			cnt++;
		}
		if (cnt == 2) {
			iStr.erase(j);
			i.setNum(iStr);
			break;
		}
	}
	
	res = Decimal::Divide(r, 10);
	res += "+";
	res += Decimal::Divide(i, 10);
	
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
	Decimal  r1, r2, i1, i2, *tmpR, *tmpI;
	
	r1 = aug.substr(0, aug.find(delimiter));
	r1.setSign(a.getSign());
	i1 = aug.erase(0, aug.find(delimiter) + delimiter.length());
	i1.setSign(a.imagSign);
	r2 = add.substr(0, add.find(delimiter));
	r2.setSign(b.getSign());
	i2 = add.erase(0, add.find(delimiter) + delimiter.length());
	i2.setSign(b.imagSign);
	
	Complex *res;
	
	//Real part
	if (a.sign == -1 && b.sign == 1) {
		Decimal c = r1, d = r2;
		c.setSign(1), d.setSign(1);
		tmpR = &(d - c);
		ReductionOfFraction(*tmpR);
		
	}
	else if (a.sign == 1 && b.sign == -1) {
		Decimal c = r1, d = r2;
		c.setSign(1), d.setSign(1);
		tmpR = &(c - d);
		ReductionOfFraction(*tmpR);
	}
	else {
		tmpR = new Decimal;
		*tmpR = r1 +r2;
		tmpR->setSign(a.sign);
		ReductionOfFraction(*tmpR);
	}
	
	//Imag part
	if (a.imagSign == -1 && b.imagSign == 1) {
		Decimal c = i1, d = i2;
		c.setSign(1), d.setSign(1);
		tmpI = &(d - c);
		ReductionOfFraction(*tmpI);
		
	}
	else if (a.imagSign == 1 && b.imagSign == -1) {
		Decimal c = i1, d = i2;
		c.setSign(1), d.setSign(1);
		tmpI = &(c - d);
		ReductionOfFraction(*tmpI);
	}
	else {
		tmpI = new Decimal;
		*tmpI = i1 + i2;
		tmpI->setSign(a.imagSign);
		ReductionOfFraction(*tmpI);
	}
	
	res = new Complex(*tmpR, *tmpI);
	
	return *res;
	
}

Complex& operator -(const Complex &a, const Complex &b)
{
	string delimiter = "+";
	string sub = a.num; //subtrahend
	string min = b.num; //minuend
	Decimal  r1, r2, i1, i2, *tmpR, *tmpI;
	
	r1 = sub.substr(0, sub.find(delimiter));
	r1.setSign(a.getSign());
	i1 = sub.erase(0, sub.find(delimiter) + delimiter.length());
	i1.setSign(a.imagSign);
	r2 = min.substr(0, min.find(delimiter));
	r2.setSign(b.getSign());
	i2 = min.erase(0, min.find(delimiter) + delimiter.length());
	i2.setSign(b.imagSign);
	
	Complex *res;
	
	//real
	if ((a.sign == -1 && b.sign == 1) || (a.sign == 1 && b.sign == -1)) { // -x - y, x - (-y)
		Decimal c = r1, d = r2;
		c.setSign(1), d.setSign(1);
		tmpR = &(c + d);
		tmpR->setSign(a.sign);
		ReductionOfFraction(*tmpR);
	}
	else { // -x - (-y), x - y
		tmpR = &(r1-r2);
		
		if (a.sign == 1 && b.sign == 1) {
			tmpR->setSign(r1 >= r2 ? 1 : -1); // change here
		}
		else {
			tmpR->setSign(r1 > r2 ? -1 : 1);
		}
		ReductionOfFraction(*tmpR);
	}
	
	//imag
	if ((a.imagSign == -1 && b.imagSign == 1) || (a.imagSign == 1 && b.imagSign == -1)) { // -x - y, x - (-y)
		Decimal c = i1, d = i2;
		c.setSign(1), d.setSign(1);
		tmpI = &(c + d);
		tmpI->setSign(a.imagSign);
		ReductionOfFraction(*tmpI);
	}
	else { // -x - (-y), x - y
		tmpI = &(i1-i2);
		
		if (a.imagSign == 1 && b.imagSign == 1) {
			tmpI->setSign(i1 >= i2 ? 1 : -1); // change here
		}
		else {
			tmpI->setSign(i1 > i2 ? -1 : 1);
		}
		ReductionOfFraction(*tmpI);
	}
	
	res = new Complex(*tmpR, *tmpI);
	
	return *res;
};

Complex& operator *(const Complex &a, const Complex &b)
{
	string delimiter = "+";
	string multid = a.num; //Multiplicand
	string multir = b.num; //Multiplier
	Decimal  r1, r2, i1, i2, *tmpR, *tmpI;
	
	r1 = multid.substr(0, multid.find(delimiter));
	r1.setSign(a.getSign());
	i1 = multid.erase(0, multid.find(delimiter) + delimiter.length());
	i1.setSign(a.imagSign);
	r2 = multir.substr(0, multir.find(delimiter));
	r2.setSign(b.getSign());
	i2 = multir.erase(0, multir.find(delimiter) + delimiter.length());
	i2.setSign(b.imagSign);
	
	Complex *res;
	
	tmpR = &(r1*r2 - i1*i2);
	tmpI = &(r1*i2 + i1*r2);
	
	res = new Complex(*tmpR, *tmpI);
	res->sign = tmpR->getSign();
	res->imagSign = tmpI->getSign();
	
	return *res;
};

Complex& operator /(const Complex &a, const Complex &b)
{
	string delimiter = "+";
	string dvd = a.num; //Dividend
	string dvr = b.num; //Divisor
	Decimal  r1, r2, i1, i2, *tmpR, *tmpI;
	
	r1 = dvd.substr(0, dvd.find(delimiter));
	r1.setSign(a.getSign());
	i1 = dvd.erase(0, dvd.find(delimiter) + delimiter.length());
	i1.setSign(a.imagSign);
	r2 = dvr.substr(0, dvr.find(delimiter));
	r2.setSign(b.getSign());
	i2 = dvr.erase(0, dvr.find(delimiter) + delimiter.length());
	i2.setSign(b.imagSign);
	
	Complex *res;
	
	tmpR = &((r1 * r2 + i1 * i2) / (r2 * r2 + i2 * i2));
	tmpI = &((i1 * r2 - r1 * i2) / (r2 * r2 + i2 * i2));
	
	res = new Complex(*tmpR, *tmpI);
	res->sign = tmpR->getSign();
	res->imagSign = tmpI->getSign();
	
	return *res;
};

Complex& Power(const Complex &b, double power)
{
	Complex *c = new Complex(b);
	
	for (int i = 0; i < power - 1; ++i) {
		*c = *c * b;
	}
	return *c;
}















