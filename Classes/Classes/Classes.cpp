#include <iostream>

using namespace std;

/*
Wielokrotne wielopoziomowe dziedziczenie z bazowa klasa abstrakcyjna.
Umiescic wszystkie obiekty w tej klasie do kontenera, zainicjalizowac i wyswietlic.
W klasie bazowej w polu prywatnym zadeklarowac statyczny adres na zagniezdzona klase.
*/

class A
{
private:
	class B
	{
		friend class A;
		int b = 0;
		void text()
		{
			cout << b << endl;
		}
	};
	static B* var;
public:
	static void mem()
	{
		var = new B;
	}
	static void del()
	{
		delete var;
	}
	static void show()
	{
		B val;
		val.b = 3;
		val.text();
	}
	virtual void get() = 0;

};
A::B* A::var;
class C :public virtual A
{
	int c;
public:
	C(int x = 0)
	{
		this->c = x;
	}
	void get()
	{
		cout << "Klasa C: " << this->c << endl;
	}
};
class D : public virtual A
{
	int d;
public:
	D(int x = 0)
	{
		this->d = x;
	}
	void get()
	{
		cout << "Klasa D: " << this->d << endl;
	}
};
class E : public C, public D
{
	int e;
public:
	E(int x = 0)
	{
		this->e = x;
	}
	void get()
	{
		cout << "Klasa E: " << this->e << endl;
	}
};
void create(A**& tab)
{
	tab = new A * [3];
	for (int i = 0; i < 3; i++)
		tab[i] = NULL;
}
void init(A**& tab)
{
	tab[0] = new C(1);
	tab[1] = new D(2);
	tab[2] = new E(3);
}
void show(A**& tab)
{
	tab[0]->get();
	tab[1]->get();
	tab[2]->get();
}
void remove(A**& tab)
{
	delete[] tab;
}
int main()
{
	A** tab;
	// Tu przydziele pamiec pod wskaznik statyczny w polu prywatnym klasy abstrakcyjnej
	A::mem();
	A::show();
	// Tu przydziele pamiec pod przyszly kontener roznych typow za pomoca funkcji globalnej, ktora nic nie zwraca a przekazuje rozmiar tablicy
	create(tab);
	// Tu inicjalizuje atrybuty obiektow wszystkich klas za pomoca funkcji globalnej, ktora nic nie zwraca
	init(tab);
	// Wyswietlam za pomoca funkcji globalnej funkcji zmienione wartosci
	show(tab);
	// Usuwam wszystkie obiekty z kontenera
	remove(tab);
	// Usuwam pamiec przydzielona pod atrybut statyczny
	A::del();
	system("pause");
	return 0;
}