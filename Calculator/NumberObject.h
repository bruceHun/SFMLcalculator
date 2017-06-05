// NumberObject_h

#ifndef NUMBEROBJECT_H
#define NUMBEROBJECT_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>

using namespace std;

class NumberObject
{
protected:
	string num;
	char type;
	int sign;
public:
	NumberObject() {};
	virtual ~NumberObject()
	{
		// cout << "delete " << this << endl;
	};

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

	void setNum(const char *s)
	{
		num = s;
	}

	void setSign(int n)
	{
		sign = n;
	}
	// Pure Virtual Functions
	virtual void operator= (const char*) = 0;
	virtual ostream& output(ostream &os) const = 0;
	virtual istream& input(istream &is) = 0;
	
	

	// Friend Functions
#ifndef FRIEND_OPERATORS
#define FRIEND_OPERATORS

	friend ostream& operator <<(ostream &os, const NumberObject &b)
	{
		//os << ((b.sign == -1) ? "-" : "") << b.num;
		return b.output(os);
	}
 
	friend istream& operator >>(istream &is, NumberObject &b)
	{
		return b.input(is);
	}

#endif // !FRIEND_OPERATORS
	
};

//class Decimal : NumberBase {};
//class Complex : NumberBase {};

#endif /*NUMBEROBJECT_H*/

