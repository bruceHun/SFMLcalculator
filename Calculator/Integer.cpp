#include "Integer.h"
#include "Decimal.h"
#include <cmath>
#include <stdexcept>


namespace  {
	

}

Integer::Integer()
{
	num = "0";
	type = 'i';
	sign = 1;
}
Integer::Integer(long n)
{
	sign = ((n < 0) ? -1 : 1);
	n *= sign;
	num = to_string(n);
	type = 'i';
	
};

Integer::Integer(int n)
{
	sign = ((n < 0) ? -1 : 1);
	n *= sign;
	num = to_string(n);
	type = 'i';
}

Integer::Integer(const string &str)
{
	type = 'i';
	if (str[0] == '-')
	{ 
		num = str.substr(1, string::npos);
		sign = -1;
	}
	else
	{
		num = str;
		sign = 1;
	}
	// eliminating leading 0s
	for (int i = 0;; i++)
	{
		if (num[i] == '0' && i < str.length() - 1)
		{
			num[i] = '\0';
		}
		else
		{
			num = num.substr(i, string::npos);
			break;
		}
	}
}

Integer::~Integer()
{
	//delete this;
	//do nothing
}


Integer& Power(const Integer &b, int p)
{
	Integer base = b; //*(Integer*)(&b);
	Integer *result(new Integer(1));
	
	while(p > 0)
	{
		if(p % 2 == 1)
		{ // Can also use (power & 1) to make code even faster
			*result = (*result * base);// % MOD;
		}
		base = (base * base);// % MOD;
		p = p / 2; // Can also use power >>= 1; to make code even faster
	}
	return *result;
}

Decimal& Power(const Integer &b, double p)
{
	string base = b.num;
	string quotient("");
	Integer dividend, divisor;
	size_t decimal_place = 0;
	// icreases decimal_place every time an extra 0 is being appended
	divisor.num = "";
	dividend.num = ""; // clear the default '0'
	
	
	///--------- 直式開方法 ----------///
	// (a + b)^2 = a^2 + 2ab + b^2
	// (a + b)^2 - a^2 = 2ab + b^2
	// (a + b)^2 - a^2 = b(2a + b)
	int a = 0;
	dividend.num.push_back(base[0]); // push in the first digit of base
	base.erase(0, 1); // erase it from numerator
	if ((b.num.length() % 2) == 0)
	{// if the number of digits of the base is even, the first partition will have two digits
		dividend.num.push_back(base[0]);
		base.erase(0, 1);
	}
	
	while (decimal_place <= 101)
	{
		/////////////////// DIVIDE ////////////////////
		for (a = 1; a <= 10; a++)
		{
			divisor.num.push_back(a + '0');
			if (dividend >= (divisor * a)) // finding the quotient
			{ divisor.num.pop_back(); continue; }
			else
			{
				divisor.num.pop_back(); divisor.num.push_back(--a + '0'); // back to previous 'a'
				dividend = dividend - (divisor * a); // subtraction
				quotient.push_back(a + '0'); // pushing the result into quotient
				break;
			}
		}/// end of DIVIDE
		
		
		if (dividend.num == "0") dividend.num = ""; // the last substraction leaves no remainder
		
		if (base == "") // no more digit left from the original base
		{
			if (!decimal_place) quotient.push_back('.'); // placeing decimal point if it hasn't been done
			if (dividend.num != "") dividend.num = dividend.num + "00"; // appending extra two '0's, allowing the division to proceed
			//else { quotient.pop_back(); break; } // divided evenly
			//decimal_place = decimal_place + 2; // marking down current decimal place
			++decimal_place;
		}
		else
		{// appending next two digit from numerator to dividend
			dividend.num.push_back(base[0]);
			dividend.num.push_back(base[1]);
			base.erase(0, 2);
		}
		
		divisor = divisor + a;
	}
	
	
	Decimal *res = new Decimal(quotient);
	return *res;
}

void Integer::Factorial(Integer &b)
{
	Integer tmp = b;
	if ((b.num.back() - '0') % 2)
	{
		int original = atoi(b.num.c_str());
		for (Integer i = b - 2; i >= 3; i = i - 2)
		{
			tmp = tmp + i;
			b = b * tmp;
		}
		original = round(original / 2.);
		b = b * original;
	}
	else
	{
		for (Integer i = b - 2; i >= 2; i = i - 2)
		{
			tmp = tmp + i;
			b = b * tmp;
		}
	}
	
}


/*
Factorial(n)
if n < 2 then return(1) end_if return(Factorial(⌊n/2⌋)2 PrimeSwing(n))

PrimeSwing(n) count ← 0
for prime in Primes(2...n) do q ← n; p ← 1
repeat
q ← ⌊q/prime⌋
if q is odd then p ← p·prime end_if
until q = 0
if p > 1 then FactorList[count++] ← p end_if
end_for
index ← 0 return(Product(FactorList, count))

Product(list, len)
if len = 0 then return(1) end_if
if len = 1 then return(list[index++]) end_if
hlen ← ⌊len/2⌋
return(Product(list, len − hlen) · Product(list, hlen))
*/

////////////// Friend Functions ////////////////

Integer& operator +(const Integer&a, const Integer &b)
{
	Integer *res = NULL;
	
	if (a.sign == -1 && b.sign == 1)
	{// -x + y
		Integer c = a, d = b;
		c.sign = 1, d.sign = 1;
		res = &(d - c);
		
		return *res;
	}
	else if (a.sign == 1 && b.sign == -1)
	{// x + (-y)
		Integer c = a, d = b;
		c.sign = 1, d.sign = 1;
		res = &(c - d);

		return *res;
	}
	
	string n1 = "", n2 = "";
	size_t max = 0, min = 0, lenA = a.num.length(), lenB = b.num.length();
	
	if (lenA > lenB)
	{
		n1 = a.num;
		n2 = b.num;
	}
	else if (lenA == lenB && a.num[0] >= b.num[0])
	{
		n1 = a.num;
		n2 = b.num;
	}
	else
	{
		n1 = b.num;
		n2 = a.num;
	}

	
	///////////////// ADD //////////////////
	max = (int)n1.length();
	min = (int)n2.length();
	
	// ex. {'1','2','4'} + {'7'}
	// ans{'\0', '\0', '\0', '\0'}	(finishing charactors omitted)
	string ans; ans.resize(max + 1, '\0');
	//max = index = 3
	//min = 1
	int index = (int)max;
	// add all
	for (int i = (int)max - 1, j = (int)min - 1; j >= 0;)
	{
		// ans[3] = (n1[2] - '0') + (n2[0] - '0') = 4 + 7 = 11
		ans[index] = (n1[i] - '0') + (n2[j] - '0');
		--index, --i, --j;
		// index = 2,	i = 1,		j = -1
		if (j < 0)
			while (i >= 0)
			{
				// ans[2] = n1[1] - '0' = 2
				// ans[1] = n1[0] - '0' = 1
				ans[index] = n1[i] - '0';
				--index, --i;
			}
		//ans{'\0', 1, 2, 11}
	}
	//carry
	for (int i = (int)max, next = i - 1; next >= 0; i--, next--)
	{
		// i = 3,  next = 2
		// ans[2] = ans[2] + (ans[3] / 10) = 2 + 1 = 3		ans[3] = (ans[3] % 10) + '0' = '1'
		// i = 2,  next = 1
		// ans[1] = ans[1] + (ans[2] / 10) = 1 + 0 = 1		ans[2] = (ans[2] % 10) + '0' = '3'
		// i = 1, next = 0
		// ans[0] = ans[0] + (ans[1] / 10) = 0 + 0 = 0		ans[1] = (ans[1] % 10) + '0' = '1'
		ans[next] = ans[next] + (ans[i] / 10);
		ans[i] = (ans[i] % 10) + '0';
		if (next == 0) ans[next] += '0';
	}
	
	if (ans.at(0) == '0')
	{// eliminating leading 0
		ans = ans.substr(1, string::npos);
	}
	res = new Integer(ans);
	res->sign = a.sign;
	return *res;
}

Integer& operator -(const Integer &a, const Integer &b)
{
	Integer *res = NULL;
	if ((a.sign == -1 && b.sign == 1) || (a.sign == 1 && b.sign == -1))
	{// -x - y,	x - (-y)
		Integer c = a, d = b;
		c.sign = 1, d.sign = 1;
		res = &(c + d);
		res->sign = a.sign;
		return *res;
	}

	string n1 = "", n2 = "";
	size_t max = 0, min = 0, lenA = a.num.length(), lenB = b.num.length();
	int index = 0, sign = 1;

	// -x - (-y), x - y
	if (lenA > lenB)
	{
		n1 = a.num;
		n2 = b.num;
		if (a.sign == -1 && b.sign == -1) sign = -1;
	}
	else if (lenA == lenB && a.num.compare(b.num) >= 0)
	{
		n1 = a.num;
		n2 = b.num;
		if (a.sign == -1 && b.sign == -1) sign = -1;
	}
	else
	{
		n1 = b.num;
		n2 = a.num;
		
		if (a.sign == 1 && b.sign == 1) sign = -1;
	}



	/////////////// SUBTRACT /////////////////
	max = (int)n1.length();
	min = (int)n2.length();
	// ex. {'1','2','4'} + {'7'}
	// ans{'\0', '\0', '\0'}	(finishing charactors omitted)
	string ans; ans.resize(max, '\0');
	//max = 3
	//min = 1
	// add all
	for (int i = (int)max - 1, j = (int)min - 1; j >= 0;)
	{
		// ans[3] = (n1[2] - '0') + (n2[0] - '0') = 4 + 7 = 11
		ans[i] = (n1[i]) - (n2[j]);
		--i, --j;
		// index = 2,	i = 1,		j = -1
		if (j < 0)
			while (i >= 0)
			{
				// ans[2] = n1[1] - '0' = 2
				// ans[1] = n1[0] - '0' = 1
				ans[i] = n1[i] - '0';
				--i;
			}
		//ans{'\0', 1, 2, 11}
	}
	//borrow
	for (int i = (int)max - 1, next = i - 1; next >= 0; i--, next--)
	{
		// i = 3,  next = 2
		// ans[2] = ans[2] + (ans[3] / 10) = 2 + 1 = 3		ans[3] = (ans[3] % 10) + '0' = '1'
		// i = 2,  next = 1
		// ans[1] = ans[1] + (ans[2] / 10) = 1 + 0 = 1		ans[2] = (ans[2] % 10) + '0' = '3'
		// i = 1, next = 0
		// ans[0] = ans[0] + (ans[1] / 10) = 0 + 0 = 0		ans[1] = (ans[1] % 10) + '0' = '1'
		if (ans[i] < 0)
		{
			ans[next] = ans[next] - 1;
			ans[i] = (10 + ans[i]) + '0';
		}
		else
			ans[i] += '0';
		if (next == 0) ans[next] += '0';
	}

	while (ans[index] == '0' && index < max - 1)
	{
		ans[index++] = '\0';
	}
	if (max == 1 )
		ans[index] += '0';
	ans = ans.substr(index , string::npos);

	res = new Integer(ans);
	res->sign = sign;
	return *res;

}

Integer& operator *(const Integer &a, const Integer &b)
{
	Integer *res = NULL;
	string n1 = "";
	string n2 = "";
	size_t index = 0, max = 0, min = 0, lenA = a.num.length(), lenB = b.num.length();
	int sign = 1;
	
	if ((a.sign == 1 && b.sign == 1) || (a.sign == -1 && b.sign == -1))
		sign = 1;
	else sign = -1;

	if (lenA > lenB)
	{
		n1 = a.num;
		n2 = b.num;
	}
	else if (lenA == lenB && a.num[0] >= b.num[0])
	{
		n1 = a.num;
		n2 = b.num;
	}
	else
	{
		n1 = b.num;
		n2 = a.num;
	}
	
	
	
	/////////////// MULTIPLY /////////////////
	max = (int)n1.length();
	min = (int)n2.length();
	// ex. {'1','2','4'} * {'7', '1'}
	// ans{'\0', '\0', '\0', '\0', '\0'}	(finishing charactors omitted)
	vector<string> matrix;
	matrix.resize(min + 1);
	for (int i = 0; i < min + 1; i++) matrix[i].resize(max + min , '\0');
	//string ans;
	//ans.resize(max + min, '\0');
	index = max + min;
	//max = 3
	//min = 2
	// add all
	for (int i = 0; i < min; i++)
	{
		for (int j = 1, k = 0; j < index; j++)
		{
			if ((j < i + 1) || k >= max) continue;
			// ans[3] = (n1[2] - '0') + (n2[0] - '0') = 4 + 7 = 11
			matrix[i][j] = (n1[k++] - '0') * (n2[i] - '0');
			// index = 2,	i = 1,		j = -1
			//ans{'\0', 1, 2, 11}
		}
		
	}
	
	// ADD two rows at a time (including carrying)
	for (int i = 0; i < min; i++)
	{
		for (int j = 1; j < index; j++)
		{
			matrix[min][j] += matrix[i][j];
		}
		//carry
		for (int k = (int)index, next = k - 1; next >= 0; k--, next--)
		{
			matrix[min][next] = matrix[min][next] + (matrix[min][k] / 10);
			matrix[min][k] = (matrix[min][k] % 10);
		}
	}
	// CONVERT back to characters
	for (int i = 0; i < index; i++)
	{
		matrix[min][i] += '0';
	}
	// No final carry, eliminating leading 0
	if (matrix[min][0] == '0')
	{
		matrix[min] = matrix[min].substr(1, string::npos);
	}
	
	res = new Integer(matrix[min]);
	res->sign = sign;
	return *res;
}

Decimal& operator /(const Integer &a, const Integer &b)
{// Integer division converts two Integer operands into a Decimal
	if (b.num == "0")
		throw invalid_argument("Denominator cannot be 0");
	Decimal n(a);
	Decimal d(b);
	return n / d;
};

void Integer::operator =(const char *str)
{
	Integer tmp = Integer(str);
	num = tmp.num;
	type = tmp.type;
	sign = tmp.sign;
}

bool operator >=(const Integer &a, const Integer &b)
{
	if (a.sign == 1 && b.sign == -1) return true;
	else if (a.sign == -1 && b.sign == 1) return false;
	else if (a.num.length() == b.num.length())
	{
		int ans = a.num.compare(b.num);
		if		(ans == 0) return true;	// >=
		else if (ans > 0) return (a.sign == 1) ? true : false ;
		else return  (a.sign == 1) ? false : true;
	}
	else if (a.num.length() > b.num.length())
	{
		return  (a.sign == 1) ? true : false;
	}
	else return  (a.sign == 1) ? false : true;
}

bool operator >(const Integer &a, const Integer &b)
{
	if (a.sign == 1 && b.sign == -1) return true;
	else if (a.sign == -1 && b.sign == 1) return false;
	else if (a.num.length() == b.num.length())
	{
		int ans = a.num.compare(b.num);
		if		(ans == 0) return false;	// >
		else if (ans > 0) 	return (a.sign == 1) ? true : false ;
		else return  (a.sign == 1) ? false : true;
	}
	else if (a.num.length() > b.num.length())
	{
		return  (a.sign == 1) ? true : false;
	}
	else return  (a.sign == 1) ? false : true;
}

bool operator <(const Integer &a, const Integer &b)
{
	if (a >= b) return false;
	else return true;
}

bool operator <=(const Integer &a, const Integer &b)
{
	if (a > b) return false;
	else return true;
}

bool operator ==(const Integer &a, const Integer &b)
{
	if (a.num == b.num && a.sign == b.sign) return true;
	else return false;
}

Integer& operator %(const Integer &a, const Integer &b)
{
	string numerator = a.num;
	string denominator = b.num;
	string empty = "", zero = "0";
	
	string quotient("");
	
	Integer *res = new Integer;
	Integer dividend;
	Integer divisor = b;
	
	dividend.setNum(empty); // clear the default '0'
	
	while (numerator != "")
	{
		if (dividend.getNum() == "0") dividend.setNum(empty); // the last substraction leaves no remainder
		dividend.num.push_back(numerator[0]); // push in the first digit of numerator
		numerator.erase(0, 1); // erase it from numerator
		if (dividend >= divisor)
		{
			/////////////////// DIVIDE ////////////////////
			for (int i = 1; i <= 10; i++)
			{
				if (dividend >= (divisor * i)) // finding the quotient
					continue;
				else
				{
					dividend = dividend - (divisor * (i - 1)); // subtraction
					quotient.push_back(i - 1 + '0'); // pushing the result into quotient
					break;
				}
			}/// end of DIVIDE
		}
		else continue; // the dividend is not big enough to be divided
	}
	if (dividend.getNum() == "") dividend.setNum(zero);

	*res = dividend;
	return *res;
}

Integer& IntDivide(const Integer &a, const Integer &b)
{
	string numerator = a.num;
	string denominator = b.num;
	string empty = "", zero = "0";
	
	string quotient("");
	
	Integer *res = new Integer;
	Integer dividend;
	Integer divisor = b;
	
	dividend.setNum(empty); // clear the default '0'
	
	while (numerator != "")
	{
		if (dividend.getNum() == "0") dividend.setNum(empty); // the last substraction leaves no remainder
		dividend.num.push_back(numerator[0]); // push in the first digit of numerator
		numerator.erase(0, 1); // erase it from numerator
		if (dividend >= divisor)
		{
			/////////////////// DIVIDE ////////////////////
			for (int i = 1; i <= 10; i++)
			{
				if (dividend >= (divisor * i)) // finding the quotient
					continue;
				else
				{
					dividend = dividend - (divisor * (i - 1)); // subtraction
					quotient.push_back(i - 1 + '0'); // pushing the result into quotient
					break;
				}
			}/// end of DIVIDE
		}
		else  { quotient.push_back('0'); continue; } // the dividend is not big enough to be divided
	}
	if (dividend.getNum() == "") dividend.setNum(zero);
	
	*res = quotient;
	return *res;
}

Integer Integer::operator ++()
{
	*this = *this + 1;
	return *this;
}

Integer Integer::operator ++(int)
{
	Integer tmp = *this;
	*this = ++(*this);
	return tmp;
}

istream& Integer::input(istream &is)
{
	string input = "";
	is >> input;
	*this = Integer(input);
	return is;
}

ostream& Integer::output(ostream &os) const
{
	//cout << ((sign < 0) ? "-" : "") << num;
	os << ((sign < 0) ? "-" : "") << num;
	return os;
}

