// Decimal_h

#ifndef DECIMAL_H
#define DECIMAL_H

#include "NumberObject.h"
#include "Integer.h"

class Decimal : public NumberObject
{
public:
	friend class Integer;
	Decimal();
	Decimal(const Integer&, const Integer&);
	Decimal(int);
	Decimal(double);
	Decimal(const char*);
	Decimal(const string&);
	Decimal(const Integer&);
	~Decimal();
	
	vector<short> FailureFunction(const string&);
	static string Divide(const Decimal&, int);
	
	void operator =(const char*);
	
	ostream& output(ostream&)const;
	istream& input(istream &is);
	
	Decimal operator -();

	friend Decimal	abs(const Decimal&);
	friend Decimal	Power(const Decimal&, double);
	friend Decimal operator +(const Decimal &a, const Decimal &b);
	friend Decimal operator -(const Decimal &a, const Decimal &b);
	friend Decimal operator *(const Decimal &a, const Decimal &b);
	friend Decimal operator /(const Decimal &a, const Decimal &b);
	friend bool		operator >=(const Decimal &a, const Decimal &b);
	friend bool		operator >(const Decimal &a, const Decimal &b);
	friend bool		operator <(const Decimal &a, const Decimal &b);
	friend bool		operator <=(const Decimal &a, const Decimal &b);
	friend bool		operator ==(const Decimal &a, const Decimal &b);
};



#endif // !DECIMAL_H





