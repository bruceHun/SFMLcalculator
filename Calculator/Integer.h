// Integer_h

#ifndef INTEGER_H
#define INTEGER_H

#include "NumberObject.h"


class Decimal;

class Integer : public NumberBase
{
private:
	Integer& PrimeSwing(Integer &n);
	Integer& Product(string list, size_t len);
	Integer& IntDivide(Integer &n) const;
public:
	friend class Decimal;
	//friend class std::basic_ostream<char, std::char_traits<char>>;
	Integer();
	Integer(long ld);
	Integer(int n);
	//Integer(NumberBase &b);
	Integer(const string&);
	~Integer();
	//static NumberBase& Power(const NumberBase &b, int p);
	static void Factorial(Integer&);
	
	//NumberBase& operator +(const NumberBase & b);
	//NumberBase& operator -(const NumberBase & b) ;
	//NumberBase& operator *(const NumberBase & b) ;
	//NumberBase& operator /(const NumberBase & b) ;
	//bool operator == (const NumberBase &b);
	//bool operator >=(const NumberBase &b);
	//bool operator <=(const NumberBase &b);
	
	void operator= (const char*);
	Integer& operator %(Integer&);
	ostream& output(ostream &os) const;
	istream& input(istream &is);
	
	friend Integer& Power(const Integer&, int);
	friend Integer& operator +(const Integer &a, const Integer &b);
	friend Integer& operator -(const Integer &a, const Integer &b);
	friend Integer& operator *(const Integer &a, const Integer &b);
	friend Decimal& operator /(const Integer &a, const Integer &b);
	//friend Integer& operator /(const Integer &a, const Integer &b);
	friend bool operator >=(const Integer &a, const Integer &b);
	friend bool operator >(const Integer &a, const Integer &b);
	//friend bool operator ==(const Integer &a, const Integer &b);
	//friend bool operator <=(const Integer &a, const Integer &b);

};

#endif // !INTEGER_H





