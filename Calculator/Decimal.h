// Decimal_h

#ifndef DECIMAL_H
#define DECIMAL_H

#include "NumberObject.h"
#include "Integer.h"

class Decimal : public NumberBase
{
public:
	friend class Integer;
	Decimal();
	Decimal(const Integer&, const Integer&);
	Decimal(int);
	Decimal(const char*);
	Decimal(const string&);
	Decimal(const Integer&);
	~Decimal();

	NumberBase& Pwr(const NumberBase &p);
	vector<short> FailureFunction(const string&);
	//NumberBase& operator +(const NumberBase & b);
	//NumberBase& operator -(const NumberBase & b);
	//NumberBase& operator *(const NumberBase & b);
	//NumberBase& operator /(const NumberBase & b);
	
	void operator =(const char*);
	
	ostream& output(ostream&)const;

	friend Decimal& operator +(const Decimal &a, const Decimal &b);
	friend Decimal& operator -(const Decimal &a, const Decimal &b);
	friend Decimal& operator *(const Decimal &a, const Decimal &b);
	friend Decimal& operator /(const Decimal &a, const Decimal &b);
	
};



#endif // !DECIMAL_H





