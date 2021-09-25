#include<iostream>
using namespace std;

#define tab "\t"

//Создание структуры:
class Point
{
	double x;
	double y;
public:
};

#define STRUCT_POINT

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