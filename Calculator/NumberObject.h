// NumberObject_h

#ifndef NUMBEROBJECT_H
#define NUMBEROBJECT_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>

using namespace std;

class NumberBase
{
protected:
	string num;
	char type;
	int sign;
public:
	NumberBase() {};
	virtual ~NumberBase() {};

	string getNum() const
	{
		return num;
	}

	char getType() const
	{
		return type;
	}
	
	int getSign() const
	{
		return sign;
	}
	
	void setNum(string &s)
	{
		num = s;
	}

	void setSign(int n)
	{
		sign = n;
	}
	// Pure Virtual Functions
	virtual NumberBase& Pwr(const NumberBase &p) = 0;
	virtual void operator= (const char*) = 0;
	virtual ostream& output(ostream &os) const = 0;
	

	// Friend Functions
#ifndef FRIEND_OPERATORS
#define FRIEND_OPERATORS

	friend ostream& operator <<(ostream &os, const NumberBase &b)
	{
		//os << ((b.sign == -1) ? "-" : "") << b.num;
		return b.output(os);
	}
 
	/*
	friend NumberBase& operator +(const NumberBase &a, const NumberBase &b)
	{
		return a + b;
	}
	
	friend NumberBase& operator -(const NumberBase &a, const NumberBase &b)
	{
		return a - b;
	}
	friend NumberBase& operator *(const NumberBase &a, const NumberBase &b)
	{
		return a * b;
	}
	friend NumberBase& operator /(const NumberBase &a, const NumberBase &b)
	{
		return a / b;
	}
	*/
	//friend bool operator ==(const NumberBase &a, const NumberBase &b);
	//friend bool operator >=(const NumberBase &a, const NumberBase &b);
	//friend bool operator <=(const NumberBase &a, const NumberBase &b);

#endif // !FRIEND_OPERATORS
	
};

//class Decimal : NumberBase {};
//class Complex : NumberBase {};

#endif /*NUMBEROBJECT_H*/

