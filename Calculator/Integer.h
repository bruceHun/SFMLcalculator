// Integer_h

#ifndef INTEGER_H
#define INTEGER_H

#include "NumberObject.h"


class Decimal;

class Integer : public NumberObject
{
private:
	Integer& PrimeSwing(Integer &n);
	Integer& Product(string list, size_t len);
	Integer& IntDivide(Integer &n) const;
public:
	friend class Decimal;
	
	Integer();
	Integer(long ld);
	Integer(int n);
	Integer(const string&);
	Integer(const Integer&);
	~Integer();
	
	static void Factorial(Integer&);
	
	ostream& output(ostream &os) const;
	istream& input(istream &is);
	
	void operator= (const char*);
	Integer operator ++();
	Integer operator ++(int);
	
	friend Integer IntDivide(const Integer &a, const Integer &b);
	friend Integer Power(const Integer&, int);
	friend Decimal Power(const Integer&, double);
	friend Integer operator +(const Integer &a, const Integer &b);
	friend Integer operator -(const Integer &a, const Integer &b);
	friend Integer operator *(const Integer &a, const Integer &b);
	friend Decimal operator /(const Integer &a, const Integer &b);
	friend Integer operator %(const Integer &a, const Integer &b);
	friend bool		operator >=(const Integer &a, const Integer &b);
	friend bool		operator >(const Integer &a, const Integer &b);
	friend bool		operator <(const Integer &a, const Integer &b);
	friend bool		operator <=(const Integer &a, const Integer &b);
	friend bool		operator ==(const Integer &a, const Integer &b);
	

};

#endif // !INTEGER_H





