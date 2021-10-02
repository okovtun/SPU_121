﻿#include<iostream>
using namespace std;

#define tab "\t"

//Создание структуры:
class Point
{
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}

	double distance(Point other)
	{
		double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance*x_distance + y_distance * y_distance);
		return distance;
	}
};

double distance(Point A, Point B)
{
	/*double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();
	double distance = sqrt(x_distance*x_distance + y_distance * y_distance);
	return distance;*/
	//return sqrt(pow(A.get_x() - B.get_x(), 2) + pow(A.get_y() - B.get_y(), 2));
	return pow(pow(A.get_x() - B.get_x(), 2) + pow(A.get_y() - B.get_y(), 2), .5);
}

//#define STRUCT_POINT

void main()
{
	setlocale(LC_ALL, "Russian");
#ifdef STRUCT_POINT
	int a;		//Объявление переменной 'a' типа 'int'
	Point A;	//Объявление переменной 'A' типа 'Point'
				//Объявление объекта 'A' структуры 'Point'
				//Создание объекта 'A' структуры 'Point'
				//Создание экземпляра структуры 'Point'
	A.x = 2;
	A.y = 3;
	cout << A.x << tab << A.y << endl;

	Point* pA = &A;
	cout << pA->x << tab << pA->y << endl;
	cout << (*pA).x << tab << (*pA).y << endl;
#endif // STRUCT_POINT

	cout << int() << endl;	//Default value for int
	//Seems like we explicitly call default constructor for int

	Point A;
	A.set_x(2);
	A.set_y(3);
	cout << A.get_x() << "\t" << A.get_y() << endl;
	//get-методы
	Point B;
	B.set_x(4);
	B.set_y(5);
	//Метод distance - возвращает расстояние до указанной точки.
	cout << A.distance(B) << endl;
	cout << B.distance(A) << endl;
	cout << distance(A, B) << endl;
	cout << distance(B, A) << endl;
	//Написать функцию distance(), которая возвращает расстояние между двумя точками.
}

/*
.  - Оператор прямого доступа (Point operator)
	 Используется для доступа к членам объекта по имени объекта.
-> - Оператор косвенного доступа (Arrow operator)
	 Используется для доступа к полям (членам) объекта по адресу объекта.
*/

/*
Инкапсуляция - Encapsulation;
Модификаторы доступа:
private:	закрытые поля, доступны только внутри класса.
public:		открытые поля, доступные из любого места.
protected:	используется лишь при наследовании.
			Доступны внутри этого класса, и его дочерних классов.

get/set-методы
get (взять, получить) - открывают доступ к закрытым переменным класса на чтение.
set (задать, установить) -
----------------------------------------
Наследование - Inheritance;
Полиморфизм  - Polymorphism;
*/