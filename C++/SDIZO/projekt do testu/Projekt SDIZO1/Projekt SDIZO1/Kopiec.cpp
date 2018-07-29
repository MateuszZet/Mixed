#include "stdafx.h"
#include "Kopiec.h"
#include "stdafx.h"
#include <iostream>
#include <fstream> 
#include <string>

using namespace std;

//Konstruktor klasy Kopiec. Przypisujemy do ObecnyMaksRozmiar 2 i tworzymy tablice na 2 elementy. Pierwszy wolny indeks to 0, dlatego rozmiar ma wartosc 0
Kopiec::Kopiec()
{
	ObecnyMaksRozmiar = 2;
	rozmiar = 0;
	data = new int[ObecnyMaksRozmiar];
}

//Metoda szukajaca rodzica elementu o wskazanym indeksie
int Kopiec::znajdz_rodzica(int indeks)
{
	if (indeks < rozmiar)
		return (indeks - 1) / 2;
	else
		return -1;
}
//Metoda wyznaczajaca lewe dziecko elementu o podanym indeksie
int Kopiec::znajdz_lewe_dziecko(int indeks)
{
	int lewedziecko = 2 * indeks + 1;
	if (lewedziecko < rozmiar)
		return lewedziecko;
	else
		return -1;
}
//Metoda wyznaczajaca prawe dziecko elementu o podanym indeksie
int Kopiec::znajdz_prawe_dziecko(int indeks)
{
	int prawedziecko = 2 * indeks + 2;
	if (prawedziecko < rozmiar)
		return prawedziecko;
	else
		return -1;
}
//Realokacja pamieci (gdy ilosc elementow w tablicy zrowna sie z maksymalna dopuszczalna iloscia, zwiekszamy pojemnosc tablicy 2 razy)
void Kopiec::realokuj()
{
	ObecnyMaksRozmiar = 2 * ObecnyMaksRozmiar;
	int *tempTab = new int[ObecnyMaksRozmiar];
	for (int i = 0; i < rozmiar; ++i)
		tempTab[i] = data[i];
	delete[] data;
	data = tempTab;
}

void Kopiec::wyczysc()
{
	rozmiar = 0;
	ObecnyMaksRozmiar = 2;
	int *tempTab = new int[ObecnyMaksRozmiar];
	delete[] data;
	data = tempTab;
}
//Metoda naprawiajaca drzewo od dolu (w gore)
int Kopiec::naprawa_gora(int indeks)
{
	int rodzic = znajdz_rodzica(indeks);
	if (rodzic >= 0){
		if (data[rodzic] < data[indeks])
		{
			int change = data[rodzic];
			data[rodzic] = data[indeks];
			data[indeks] = change;
			return rodzic;
		}
		else
			return indeks;
	}
	else
		return -1;
}
//Metoda naprawiajaca drzewo od gory (w dol)
int Kopiec::naprawa_dol(int indeks)
{
	int lewo = znajdz_lewe_dziecko(indeks);
	int prawo = znajdz_prawe_dziecko(indeks);
	int zmien;
	if (data[lewo] > data[prawo])
	{
		zmien = data[lewo];
		data[lewo] = data[indeks];
		data[indeks] = zmien;
		return lewo;
	}
	else {
		zmien = data[prawo];
		data[prawo] = data[indeks];
		data[indeks] = zmien;
		return prawo;
	}
}
//Metoda dodajaca do Kopca (dodajemy na koniec i nastepnie naprawiamy drzewo)
void Kopiec::dodaj(int wartosc)
{
	if (rozmiar >= ObecnyMaksRozmiar)
		realokuj();
	data[rozmiar] = wartosc;
	int indeks = rozmiar;
	rozmiar++;

	while (data[indeks] > data[znajdz_rodzica(indeks)])
	{
		indeks = naprawa_gora(indeks);
	}
}
//Metoda usuwajaca element o podanej wartosci (szukamy elementu, a nastepnie w jego miejsce wstawiamy element o najwiekszym indeksie i naprawiamy fragment drzewa)
void Kopiec::usun(int wartosc)
{
	for (int i = 0; i < rozmiar; i++)
	{
		if (data[i] == wartosc)
		{
			data[i] = data[rozmiar - 1]; // zastepujemy ostatnim elementem kopca i potem naprawiamy w dol
			int indeks = i;
			while (data[indeks] < data[znajdz_lewe_dziecko(indeks)] || data[indeks] < data[znajdz_prawe_dziecko(indeks)])
			{
				indeks = naprawa_dol(indeks);
			}
			rozmiar--;
			return;
		}
	}
}
//Szukanie elementu (liniowe)
bool Kopiec::znajdz(int wartosc)
{
	for (int i = 0; i < rozmiar; ++i)
	{

		if (data[i] == wartosc)
		{
			return true;
		}

	}

	return false;
}
//Wyswietlanie elementow (w porzadku indeksowym)
void Kopiec::wyswietl()
{
	ofstream out("kopiec.txt");
	cout << "rozmiar: " << rozmiar << endl;
	for (int i = 0; i < rozmiar; ++i)
	{
		cout << "["<<i<<"] "<<data[i] << endl;
	}
}
//Wyswietlanie elementow jako drzewo (max 31 wartosci liczby 3-cyfrowe)
void Kopiec::wyswietl2()
{
	ofstream out("kopiec2.txt");
	for (int i = 0; i < rozmiar; ++i)
	{
		if (i == 0) {
			cout << "                                             ";
			cout.width(3);
			cout << data[i];
			cout << "                                             " << "\n\n";
			
		}
		if (0 < i && i < 3){
			cout << "                     ";
			cout.width(3);
			cout << data[i];
			cout << "                        ";
			if (i == 2) { cout << endl << endl; }
		}

		if (2 < i && i < 5) {
			cout << "         ";
			cout.width(3);
			cout << data[i];
			cout << "            ";
		}
		if (4 < i && i < 7){
			cout << "         ";
			cout.width(3);
			cout << data[i];
			cout << "            ";
			if (i == 6) { cout << endl << endl << endl;}
		}
		if (6 < i && i < 15){
			cout << "   ";
			cout.width(3);
			cout << data[i];
			cout << "      ";
			if (i == 14) { cout << endl << endl << endl;}
		}
		if (14 < i && i < 31){
			cout.width(3);
			cout << data[i];
			cout << "   ";
		}
	}
	cout << endl;
}
//Generowanie num elementów o maksymalnej wartoœci : max
void Kopiec::generuj(int max, int num)
{
	wyczysc();
	for (int i = 0; i < num; i++)
		dodaj(rand() % max );
}
//wczytywanie struktury z pliku
void Kopiec::wczytaj(){
	wyczysc();
	int r,ile;
	cout << "Podaj nazwe: " << endl;
	string nazwa;
	cin >> nazwa;
	fstream plik(nazwa);
	plik >> ile;
	for (int i = 0; i < ile; i++)
	{
		plik >> r;
		dodaj(r);
	}
}