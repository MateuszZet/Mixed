#include <iostream>
#include <math.h>
using namespace std;

void rectangle(float a, float b) {
	if ((a > 0) && (b > 0)) {
		float s = a * b;
		float o = 2 * a + 2 * b;

		cout << "Pole prostokata: ";
		cout << s << "\n";
		cout << "Obwod prostokata: ";
		cout << o << "\n\n";
	}
	else cout << "Podano bledne wartosci!\n\n";
		
}

void triangle(float a, float b, float c) {
	//sprawdzenie czy da sie zbudowac trojkat z podanych dlugosci bokow
	if (((a + b) > c) && ((a + c) > b) && ((b + c) > a) && (a > 0) && (b >0) && (c>0)) {

		float o = a + b + c;
		float p = o / 2;

		// wzór Herona
		float x = p*(p - a)*(p - b)*(p - c);
		float s = sqrt(x);

		cout << "Pole trojkata: ";
		cout << s << "\n";
		cout << "Obwod trojkata: ";
		cout << o << "\n\n";
	}
	else cout << "Z podanych dlugosci bokow nie mozna zbudowac trojkata!\n\n";
}

void main()
{
	int k;
	do {
		
		float a = 0, b = 0, c = 0;
		cout << "***Witaj w programi liczacym pole i obwod wybranej figury***\n Wybierz figure:\n1. Prostokat\n2. Trojkat\n3. Wyjscie\n";
		cin >> k;

	
		switch (k) {
		case 1:
			cout << "Podaj dlugosc boku a: ";
			cin >> a;
			cout << "Podaj dlugosc boku b: ";
			cin >> b;
			rectangle(a, b);
			break;
		case 2:
			cout << "Podaj dlugosc boku a: ";
			cin >> a;
			cout << "Podaj dlugosc boku b: ";
			cin >> b;
			cout << "Podaj dlugosc boku c: ";
			cin >> c;
			triangle(a, b, c);
			break;
		default: cout << "Wprowadzono nieprawidlowa wartosc\n\n"; break;
		}
	} while (k != 3);
}	
