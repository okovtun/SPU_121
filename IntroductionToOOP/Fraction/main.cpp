#pragma warning(disable:4326)
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------------------------\n"

class Fraction;
Fraction operator*(Fraction left, Fraction right);

class Fraction
{
	int integer;		//Целая часть
	int numerator;		//Числитель
	int denominator;	//Знаменатель
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	//				Constructors
	Fraction()
	{
		integer = numerator = 0;
		denominator = 1;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "1argConstructor:\t" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);	//Когда нужна фильтрация данных, даже внутри класса лучше использовать set-методы
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);	//Когда нужна фильтрация данных, даже внутри класса лучше использовать set-методы
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor\t\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t\t" << this << endl;
	}

	//				Operators
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this*other;
	}

	//				Increment/Decrement
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}

	Fraction& operator()(int integer, int numerator, int denominator)
	{
		set_integer(integer);
		set_numerator(numerator);
		set_denominator(denominator);
		return *this;
	}

	//				Type-cast operators:
	explicit operator int()const
	{
		return integer;
	}
	operator double()const
	{
		return integer + (double)numerator / denominator;
	}

	//				Methods:
	Fraction& to_proper()
	{
		//Выделяет из неправильной дроби целую часть
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction& to_improper()
	{
		//Целую часть интергрирует в числитель
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& inverse()
	{
		to_improper();
		int buffer = numerator;
		numerator = denominator;
		denominator = buffer;
		return *this;
	}

	void print()const
	{
		if (integer)cout << integer;
		if (numerator)
		{
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		if (integer == 0 && numerator == 0)cout << 0;
		cout << endl;
	}

	friend ostream& operator<<(ostream& os, const Fraction& obj);
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	//Fraction result(left.get_numerator()*right.get_numerator(), left.get_denominator()*right.get_denominator());
	//result.set_numerator(left.get_numerator()*right.get_numerator());
	//result.set_denominator(left.get_denominator()*right.get_denominator());
	//result.to_proper();
	//return result;
	return	Fraction
	(
		left.get_numerator()*right.get_numerator(),
		left.get_denominator()*right.get_denominator()
	).to_proper();//Явно вызываем конструктор
//Здесь, мы прямо в return создаем временный безымянный объект типа Fraction, и возвращаем его на место вызова
}
Fraction operator/(Fraction left, Fraction right)
{
	/*left.to_improper();
	right.to_improper();

	return	Fraction
	(
		left.get_numerator()*right.get_denominator(),
		left.get_denominator()*right.get_numerator()
	).to_proper();*/

	return left * right.inverse();
}

Fraction operator+(Fraction left, Fraction right)
{
	left.to_proper();
	right.to_proper();
	return Fraction
	(
		left.get_integer() + right.get_integer(),
		left.get_numerator()*right.get_denominator() + right.get_numerator()*left.get_denominator(),
		left.get_denominator()*right.get_denominator()
	).to_proper();
}

bool operator==(Fraction left, Fraction right)
{
	/*left.to_improper();
	right.to_improper();
	return left.get_numerator()*right.get_denominator() == right.get_numerator()*left.get_denominator();*/
	return
		left.to_improper().get_numerator()*right.get_denominator() ==
		right.to_improper().get_numerator()*left.get_denominator();
	/*if ((double)left == right)return true;
	else return false;*/
	return (double)left == right;
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}
bool operator>(Fraction left, Fraction right)
{
	return
		left.to_improper().get_numerator()*right.get_denominator() >
		right.to_improper().get_numerator()*left.get_denominator();
}
bool operator<(const Fraction& left, const Fraction& right)
{
	return (double)left < right;
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	return left>right || left == right;
}
bool operator<=(const Fraction& left, Fraction& right)
{
	return !(left > right);
}

ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.integer)cout << obj.integer;
	if (obj.numerator)
	{
		if (obj.integer)cout << "(";
		cout << obj.numerator << "/" << obj.denominator;
		if (obj.integer)cout << ")";
	}
	if (obj.integer == 0 && obj.numerator == 0)cout << 0;
	return os;
}
istream& operator>>(istream& is, Fraction& obj)
{
	const int SIZE = 80;
	char sz_buffer[SIZE] = {};
	is.getline(sz_buffer, SIZE);
	char sz_delimiters[] = "/() ";
	//123
	//2/3
	//2(2/3)
	//2 2/3
	char* value[3] = {};
	int n = 0;
	for (char* pch = strtok(sz_buffer, sz_delimiters); pch; pch = strtok(NULL, sz_delimiters))
	{
		//http://cplusplus.com/reference/cstring/strtok/
		value[n++] = pch;
	}
	/*for (int i = 0; i < n; i++)
	{
		cout << values[i] << tab;
	}
	cout << endl;*/
	obj = Fraction();
	switch (n)
	{
	case 1: obj.set_integer(atoi(value[0])); break;
		//atoi(); ASCII-string to integer
		//http://cplusplus.com/reference/cstdlib/atoi/
	case 2: 
		obj.set_numerator(atoi(value[0]));
		obj.set_denominator(atoi(value[1]));
		break;
	case 3:
		obj.set_integer(atoi(value[0]));
		obj.set_numerator(atoi(value[1]));
		obj.set_denominator(atoi(value[2]));
		break;
	}
	return is;
}

//#define CONSTRUCTORS_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK
//#define OPERATORS_CHECK
//#define CONVERSIONS_FROM_OTHER_TO_CLASS
//#define CONVERSION_FROM_CLASS_TO_OTHER
//#define COMPARISON_OPERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	Fraction A;	//Default constructor
	A.print();
	Fraction B = 5;	//Single-argument constructor
	B.print();
	Fraction C(1, 2);
	C.print();
	Fraction D(2, 3, 4);
	D.print();

	Fraction E = D;	//CopyConstrcutor
	E.print();
	Fraction F;
	F = D;		//CopyAssignment
	F.print();
#endif // CONSTRUCTORS_CHECK

#ifdef ARITHMETICAL_OPERATORS_CHECK
	int a = 2;
	int b = 3;
	int c = a * b;

	Fraction A(23, 3);
	A.print();
	Fraction B(8, 4, 5);
	B.print();

	Fraction C = A * B;
	C.print();

	(A / B).print();
	(A + B).print();
	A *= B;
	//A.print();
	cout << A << endl;;
#endif // ARITHMETICAL_OPERATORS_CHECK

#ifdef OPERATORS_CHECK
	/*for (double i = .5; i < 10; i++)
{
	cout << i << "\t";
}
cout << endl;
for (Fraction A(1, 2); A.get_integer() < 10; A++)
{
	cout << A << "\t";
}
cout << endl;*/

	Fraction A(1, 2);
	/*A.set_integer(7);
	A.set_numerator(2);
	A.set_denominator(3);*/
	A(7, 2, 3);
	cout << A << endl;
#endif // OPERATORS_CHECK

#ifdef CONVERSIONS_FROM_OTHER_TO_CLASS
	//(type)value;	//C-like notation
	//type(value);	//Functional notation

//Warning:....possible loss of data

//		l-value = r-value;

	int a = 2;		//No conversions
	double b = 3;	//From less to more
	double c = 2.5;	//No conversion
	int d = b;		//From more to less without data loss
	int e = 4.5;	//From more to less with data loss

	//Single-argument constructor
	//Assignment operator - Copy assignment
	Fraction A(5);	//From int to Fraction (Single-argument constructor)
	cout << A << endl;
	Fraction B;		//Default constucor
	cout << delimiter << endl;
	//B = 8;			//Assignment operator
	B = (Fraction)8;	//C-like notation
	B = Fraction(8);	//Functional notation 
	//(здесь мы явно вызываем конструктор с одним параметром)

	//В этом выражении вызывается конструктор с одним параметром, 
	//и создает временный безымяный объект, для того, 
	//чтобы преобразовать 8 во Fraction.
	//Этот временный безымянный объект будет удален по завершении выражения.
	cout << delimiter << endl;
	cout << B << endl;
#endif // CONVERSIONS_FROM_OTHER_TO_CLASS

#ifdef CONVERSION_FROM_CLASS_TO_OTHER
	//					Type-cast operators
/*
------------------------------------------
operator type() const
{
	...
}
opertor int()const
{
	...
}
------------------------------------------
*/

	Fraction A(5);
	cout << A << endl;
	int a = A;
	cout << a << endl;

	Fraction B(2, 3, 4);
	cout << B << endl;
	double b = (double)B;
	cout << b << endl;
#endif // CONVERSION_FROM_CLASS_TO_OTHER

#ifdef COMPARISON_OPERATORS_CHECK
	cout << (Fraction(2, 1, 2) < Fraction(2, 5, 11)) << endl;
#endif // COMPARISON_OPERATORS_CHECK

	Fraction A(22,33,55);
	cout << delimiter << endl;
	cout << "Введите дробь: "; 
	cin >> A;
	cout << delimiter << endl;
	cout << A << endl;
}