#include<iostream>
using namespace std;

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
	Fraction(int integer)
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

//#define CONSTRUCTORS_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK

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
}