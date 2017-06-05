//
//  Complex.h
//  Henry
//
//  Created by Henry Lin on 2017/5/25.
//  Copyright © 2017年 Henry Lin. All rights reserved.
//

#ifndef Complex_h
#define Complex_h

#include "NumberObject.h"
#include "Decimal.h"
#include "Integer.h"

class Complex : public NumberObject
{
public:
    friend class Integer;
    friend class Decimal;
    Complex();
    Complex(const Decimal&, const Decimal&);
    Complex(const char*);
    Complex(const string&);
    Complex(const Integer&);
    Complex(const Decimal&);
    Complex(const Complex&);
    ~Complex();
	
	int getImagSign();
	
    void operator =(const char*);
    ostream& output(ostream&)const;
    istream& input(istream &is);
    
    friend Complex& operator +(const Complex &a, const Complex &b);
    friend Complex& operator -(const Complex &a, const Complex &b);
    friend Complex& operator *(const Complex &a, const Complex &b);
    friend Complex& operator /(const Complex &a, const Complex &b);
    //friend bool operator >=(const Complex &a, const Complex &b);
    //friend bool operator >(const Complex &a, const Complex &b);
    friend Complex& Power(const Complex&, double);
    
protected:
    int imagSign;
};

#endif /* Complex_h */
