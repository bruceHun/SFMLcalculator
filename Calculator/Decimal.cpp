#include "Decimal.h"
#include <cmath>
#include <ctime>
#include <chrono>

namespace
{
#ifdef _WIN32
	double TIME_LIMIT = 1.9;
#else
	int TIME_LIMIT = 1900000;
#endif

	int LengthLimit = 50;
	
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

Decimal::Decimal()
{
	num = "0/1";
	type = 'd';
	sign = 1;
};

Decimal::Decimal(const Integer &n, const Integer &d)
{
	if ((n.sign == 1 && d.sign == 1) || (n.sign == -1 && d.sign == -1))
		sign = 1;
	else sign = -1;
	
	num = n.num + "/" + d.num;
	type = 'd';
	
	//ReductionOfFraction(*this);
}

Decimal::Decimal(int n)
{
	sign = 1;
	if (n < 0)
	{
		sign = -1;
		n *= sign;
	}
	num = to_string(n) + "/1";
	type = 'd';
}

Decimal::Decimal(double d)
{
	num = to_string(d);
	*this = Decimal(num);
	//ReductionOfFraction(*this);
}

Decimal::Decimal(const char *str)
{
	type = 'd';
	string delimiter = ".";
	string tmp = "";
	string arg = str;
	Integer numerator, denominator;
	
	if (arg.find(delimiter) == string::npos)
	{
		if (str[0] == '-') {
			sign = -1;
			arg.erase(0, 1);
		}
		else {
			sign = 1;
		}
		if (arg.find("/") == string::npos)
			num = arg + "/1";
		else num = arg;
	}
	else
	{
		if (str[0] == '-')
		{
			num = arg.substr(1, arg.find(delimiter) - 1); // -1 to get the right position
			sign = -1;
		}
		else
		{
			num = arg.substr(0, arg.find(delimiter));
			sign = 1;
		}
		tmp = arg.erase(0, arg.find(delimiter) + delimiter.length());
		
		
		////Repeating decimal converting
		if (0)//tmp.length() >= 120)
		{// only when the input match or exceed the maximum digits of output do we have to varify if it is repeating
			/*
			int Plen = 0, pos_a = 0;
			vector<short> f;
			for (int i = 0; i < tmp.length(); i++)
			{// find pattern and its starting position (KMP algorithm)
				f = FailureFunction(tmp);
				if (f.back() == -1) tmp.erase(0, 1);
				else break;
				++pos_a;
			}
			for (int i = 0; i < f.size(); i++) // find the length of the pattern
				if (f[i] > -1) { Plen = i; break; }
			
			if (Plen) // pattern found
			{
				// cut the number at the end of the first pattern and substract the non repeating part
				tmp = arg.substr(0, pos_a + Plen);
				if (pos_a > 0) numerator = Integer(tmp) - Integer(tmp.substr(0, pos_a));
				else numerator.num = tmp; // there is no non repeating part
				denominator.num = ""; // there is a redundent '0' generated by the constructor
				for (int i = 0; i < tmp.length(); i++)
					denominator.num.push_back((i < Plen)? '9': '0');
			}
			 */
		////end of Repeating decimal converting
		}
		else
		{// if the decimal is finite (less than 100 decimal places) or non repeating
			denominator.num.resize(arg.length(), '0');
			denominator.num = '1' + denominator.num;
			numerator.num	= arg;
		}
		
		// add the integer part to the fraction
		numerator = Integer(num) * denominator + numerator;
		
		num = numerator.num + "/" + denominator.num;
		if (numerator.num == "0") sign = 1;
		
		//if (denominator.num != "1") ReductionOfFraction(*this);
	}
}

Decimal::Decimal(const string &str)
{
	*this = Decimal(str.c_str());
}



Decimal::Decimal(const Integer& n)
{
	num = n.num + "/1";
	type = 'd';
	sign = n.sign;
};

Decimal::~Decimal()
{
	//do nothing
};

Decimal abs(const Decimal &a)
{
	Decimal tmp = a;
	tmp.sign = 1;
	return tmp;
}

Decimal Power(const Decimal &b, double power)
{
	int p = power;
	string delimiter = "/";
	string d = b.getNum();
	Integer  x1, x2, res1("1"), res2("1");
	Decimal dvd, dvr, result;
	int pwr = p;
	x1 = d.substr(0, d.find(delimiter));
	x2 = d.erase(0, d.find(delimiter) + delimiter.length());

	if ((power - (int)power) != 0)
	{
		if (power != 0.5) throw invalid_argument("Invalid input");
		if (b < 0) throw invalid_argument("Undefined");
		dvd = Power(x1, power);
		dvr = Power(x2, power);
		result = dvd / dvr;
	}
	else
	{
		// initialize TIME_LIMIT
#ifdef _WIN32
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		end = start;
		chrono::duration<double> elapsed_seconds;
#else
		clock_t start = std::clock(), end = std::clock();
#endif

		while (p > 0)
		{
			// exceed the time limit
#ifdef _WIN32
			elapsed_seconds = end - start;
			if (elapsed_seconds.count() > TIME_LIMIT) { throw invalid_argument("Sorry, it'll take forever!"); }
#else
			if (end - start > TIME_LIMIT) { throw invalid_argument("Sorry, it'll take forever!"); }
#endif

			if (p & 1)
			{ // Can also use (power & 1) to make code even faster
				res1 = (res1 * x1);
				res2 = (res2 * x2);
			}
			x1 = (x1 * x1);
			x2 = (x2 * x2);
			p >>= 1; // Can also use power >>= 1; to make code even faster

#ifdef _WIN32
			end = chrono::system_clock::now();
#else
			end = std::clock();
#endif // _WIN32

		}

		result = Decimal(res1, res2);

		if (b.getSign() == -1 && pwr % 2 == 1)
			result.setSign(-1);
		else
			result.setSign(1);
	}
	return result;
}

Decimal operator +(const Decimal &a, const Decimal &b)
{
	string delimiter = "/";
	string dvd = a.num; //augend
	string dvr = b.num; //addend
	Integer  x1, x2, y1, y2;
	
	x1 = dvd.substr(0, dvd.find(delimiter));
	x2 = dvd.erase(0, dvd.find(delimiter) + delimiter.length());
	y1 = dvr.substr(0, dvr.find(delimiter));
	y2 = dvr.erase(0, dvr.find(delimiter) + delimiter.length());
	
	Decimal res;
	
	if (a.sign == -1 && b.sign == 1) {
		Decimal c = a, d = b;
		c.sign = 1, d.sign = 1;
		res = d - c;
		if (res.getNum().length() > LengthLimit) ReductionOfFraction(res);
		return res;
	}
	else if (a.sign == 1 && b.sign == -1) {
		Decimal c = a, d = b;
		c.sign = 1, d.sign = 1;
		res = c - d;
		if (res.getNum().length() > LengthLimit) ReductionOfFraction(res);
		return res;
	}
	else {
		res = Decimal(x1 * y2 + x2 * y1, x2 * y2);
		res.sign = a.sign;
		if (res.getNum().length() > LengthLimit) ReductionOfFraction(res);
		return res;
	}
}

Decimal operator -(const Decimal &a, const Decimal &b)
{
	string delimiter = "/";
	string dvd = a.num; //subtrahend
	string dvr = b.num; //minuend
	Integer  x1, x2, y1, y2;
	
	x1 = dvd.substr(0, dvd.find(delimiter));
	x2 = dvd.erase(0, dvd.find(delimiter) + delimiter.length());
	y1 = dvr.substr(0, dvr.find(delimiter));
	y2 = dvr.erase(0, dvr.find(delimiter) + delimiter.length());
	
	Decimal res;
	
	if ((a.sign == -1 && b.sign == 1) || (a.sign == 1 && b.sign == -1)) { // -x - y, x - (-y)
		Decimal c = a, d = b;
		c.sign = 1, d.sign = 1;
		res = c + d;
		res.sign = a.sign;
		if (res.getNum().length() > LengthLimit) ReductionOfFraction(res);
		return res;
	}
	else { // -x - (-y), x - y
		res = Decimal(x1 * y2 - x2 * y1, x2 * y2);
		
		if (a.sign == 1 && b.sign == 1) {
			res.sign = a >= b ? 1 : -1;
		}
		else {
			res.sign = a > b ? -1 : 1;
		}
		if (res.getNum().length() > LengthLimit) ReductionOfFraction(res);
		return res;
	}
};

Decimal operator *(const Decimal &a, const Decimal &b)
{
	string delimiter = "/";
	string dvd = a.num; //Multiplicand
	string dvr = b.num; //Multiplier
	Integer  x1, x2, y1, y2;
	
	x1 = dvd.substr(0, dvd.find(delimiter));
	x2 = dvd.erase(0, dvd.find(delimiter) + delimiter.length());
	y1 = dvr.substr(0, dvr.find(delimiter));
	y2 = dvr.erase(0, dvr.find(delimiter) + delimiter.length());
	
	Decimal res = Decimal(x1 * y1, x2 * y2);
	res.sign = ((a.sign == 1)&&(b.sign == 1)) || ((a.sign == -1)&&(b.sign == -1))? 1 : -1;
	if (res.getNum().length() > LengthLimit) ReductionOfFraction(res);
	return res;
};

Decimal operator /(const Decimal &a, const Decimal &b)
{
	string delimiter = "/";
	string dvd = a.num; //Dividend
	string dvr = b.num; //Divisor
	Integer  x1, x2, y1, y2;
	
	x1 = dvd.substr(0, dvd.find(delimiter));
	x2 = dvd.erase(0, dvd.find(delimiter) + delimiter.length());
	y1 = dvr.substr(0, dvr.find(delimiter));
	y2 = dvr.erase(0, dvr.find(delimiter) + delimiter.length());
	
	if (y1 == 0) throw invalid_argument("Divisor cannot be 0");
	
	Decimal *res = new Decimal(x1 * y2, x2 * y1);
	res->sign = ((a.sign == 1)&&(b.sign == 1)) || ((a.sign == -1)&&(b.sign == -1))? 1 : -1;
	if (res->getNum().length() > LengthLimit) ReductionOfFraction(*res);
	return *res;
};


void Decimal::operator =(const char *str)
{
	Decimal tmp = Decimal(str);
	num = tmp.num;
	type = tmp.type;
	sign = tmp.sign;
}

Decimal Decimal::operator -()
{
	Decimal tmp = *this;
	if (sign == 1) tmp.setSign(-1);
	else tmp.setSign(1);
	return tmp;
}

bool operator >(const Decimal &a, const Decimal &b)
{
	if (a.sign == 1 && b.sign == -1) return true;
	else if (a.sign == -1 && b.sign == 1) return false;
	else
	{
		string delimiter = "/";
		string dvd = a.num; //
		string dvr = b.num; //
		Integer  x1, x2, y1, y2;
		
		x1 = dvd.substr(0, dvd.find(delimiter));
		x2 = dvd.erase(0, dvd.find(delimiter) + delimiter.length());
		y1 = dvr.substr(0, dvr.find(delimiter));
		y2 = dvr.erase(0, dvr.find(delimiter) + delimiter.length());
		
		Integer c = x1 * y2, d = x2 * y1;
		
		return c > d ? true : false;
	}
}

bool operator >=(const Decimal &a, const Decimal &b)
{
	if (a.sign == 1 && b.sign == -1) return true;
	else if (a.sign == -1 && b.sign == 1) return false;
	else
	{
		string delimiter = "/";
		string dvd = a.num; //
		string dvr = b.num; //
		Integer  x1, x2, y1, y2;
		
		x1 = dvd.substr(0, dvd.find(delimiter));
		x2 = dvd.erase(0, dvd.find(delimiter) + delimiter.length());
		y1 = dvr.substr(0, dvr.find(delimiter));
		y2 = dvr.erase(0, dvr.find(delimiter) + delimiter.length());
		
		Integer c = x1 * y2, d = x2 * y1;
		
		return c >= d ? true : false;
	}
}

bool operator <(const Decimal &a, const Decimal &b)
{
	if (a >= b) return false;
	else return true;
}

bool operator <=(const Decimal &a, const Decimal &b)
{
	if (a > b) return false;
	else return true;
}

bool operator ==(const Decimal &a, const Decimal &b)
{
	if (a.sign != b.sign) return false;
	else
	{
		string delimiter = "/";
		string dvd = a.num; //
		string dvr = b.num; //
		Integer  x1, x2, y1, y2;
		
		x1 = dvd.substr(0, dvd.find(delimiter));
		x2 = dvd.erase(0, dvd.find(delimiter) + delimiter.length());
		y1 = dvr.substr(0, dvr.find(delimiter));
		y2 = dvr.erase(0, dvr.find(delimiter) + delimiter.length());
		
		Integer c = x1 * y2, d = x2 * y1;
		
		return c == d ? true : false;
	}
}

istream& Decimal::input(istream &is)
{
	string input = "";
	is >> input;
	*this = Decimal(input);
	return is;
}

ostream& Decimal::output(ostream &os) const
{
	string str = Divide(*this, 100);
	if (sign < 0) str = "-" + str;
	// word wrapper
	/*
	 for (size_t i = 1, delimiter = 60; i <= (str.length() / 60); i++, delimiter++)
	 {
	 str.insert(delimiter, 1, '\n');
	 delimiter += 60;
	 }
	 */
	os << str;
	return os;
}

string Decimal::Divide(const Decimal &n, int dp) // 
{
	string tmp = n.num;
	string delimiter = "/";
	string numerator = tmp.substr(0, tmp.find(delimiter));
	string denominator = tmp.erase(0, tmp.find(delimiter) + delimiter.length());
	
	string quotient("");
	Integer dividend;
	Integer divisor(denominator);
	
	size_t decimal_place = 0;
	// icreases decimal_place every time an extra 0 is being appended
	dividend.num = ""; // clear the default '0'
	dividend.num.push_back(numerator[0]); // push in the first digit of numerator
	numerator.erase(0, 1); // erase it from numerator
	while (decimal_place <= dp)
	{

		/////////////////// DIVIDE ////////////////////
		for (int i = 1; i <= 10; i++)
		{
			if (dividend >= (divisor * i)) // finding the quotient
				continue;
			else
			{
				dividend = dividend - (divisor * --i); // subtraction
				quotient.push_back(i + '0'); // pushing the result into quotient
				break;
			}
		}/// end of DIVIDE
		
		if (dividend.num == "0") dividend.num = ""; // the last substraction leaves no remainder
		
		if (numerator == "") // no more digit left from the original numerator
		{
			if (!decimal_place) quotient.push_back('.'); // placeing decimal point if it hasn't been done
			if (dividend.num != "") dividend.num.push_back('0'); // appending extra '0', allowing the division to proceed
			//else { quotient.pop_back(); break; } // divided evenly
			++decimal_place; // marking down current decimal place
		}
		else
		{// appending next digit from numerator to dividend
			dividend.num.push_back(numerator[0]);
			numerator.erase(0, 1);
		}
	}
	while (quotient[0] == '0' && quotient[1] != '.')
	{// removing leading '0's
		quotient.erase(0, 1);
	}
	return quotient;
}

vector<short> Decimal::FailureFunction(const string &p)
{
	vector<short> failure;
	failure.resize(p.size(), 0);
	// iterative, bottom-up DP
	for (int i = 1, j = failure[0] = -1; i < p.size(); ++i)
	{
		// 先試 p[0...i-1] 的「次長的相同前綴後綴」，
		// 也就是 p[0...failure[i-1]] = p[0...j]。
		// 再試 p[0...j] 的「次長的相同前綴後綴」，
		// 也就是 p[0...failure[j]]。
		// 再試 p[0...failure[j]] 的「次長的相同前綴後綴」……
		// 直到試成功為止。
		while (j >= 0 && p[j+1] != p[i])
			j = failure[j];
		
		// p[i] 終於有用處了，終於可以加長！
		if (p[j+1] == p[i]) j++;
		
		// 得到了 failure[i] 的值！
		failure[i] = j;
	}
	return failure;
}

