// Integer_h

#ifndef INTEGER_H
#define INTEGER_H

#include "NumberObject.h"


class Decimal;

class Integer : public NumberBase
{
	
public:
	friend class Decimal;
	//friend class std::basic_ostream<char, std::char_traits<char>>;
	Integer();
	Integer(long ld);
	Integer(int n);
	//Integer(NumberBase &b);
	Integer(const string&);
	~Integer();
	NumberBase& Pwr(const NumberBase &b);
	static void Factorial(Integer&);
	//NumberBase& operator +(const NumberBase & b);
	//NumberBase& operator -(const NumberBase & b) ;
	//NumberBase& operator *(const NumberBase & b) ;
	//NumberBase& operator /(const NumberBase & b) ;
	//bool operator == (const NumberBase &b);
	//bool operator >=(const NumberBase &b);
	//bool operator <=(const NumberBase &b);
	
	void operator= (const char*);
	
	ostream& output(ostream &os) const;

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





