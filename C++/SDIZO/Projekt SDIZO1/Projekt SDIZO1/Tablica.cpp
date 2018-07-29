#include "stdafx.h"
#include "Tablica.h"
#include <iostream>
#include <fstream> 
#include <string>
using namespace std;


// Konstruktor klasy Kopiec.Przypisujemy do ObecnyMaksRozmiar 2 i tworzymy tablice na 2 elementy.Pierwszy wolny indeks to 0, dlatego rozmiar ma wartosc 0
Tablica::Tablica()
{
	ObecnyMaksRozmiar = 2;
	rozmiar = 0;
	tab = new int[ObecnyMaksRozmiar];
}

//generowanie tablicy, do generowania u¿ywa dodawania na koñcu
void Tablica::generuj(int max, int wielkosc){
	int r;
	for (int i = 0; i < wielkosc; i++){
		r = rand() % max;
		dodajKoniec(r);
	}

}
//wyswietlanie
void Tablica::pokaz(){
	cout << "Dlugosc: " << rozmiar <<endl;
	for (int i = 0; i < rozmiar; i++){
		cout << "[" << i << "]: " << tab[i] << endl;
	}
}

// Metoda realokujaca pamiec
void Tablica::realokuj(){
	ObecnyMaksRozmiar = 2 * ObecnyMaksRozmiar; //2 krotnie zwiekszamy maksymalny rozmiar
	int *tempTab = new int[ObecnyMaksRozmiar]; //tworzymy tymczasow¹ tablice przenosimy do niej elementy z tab, usuwamy tab i przypisujemy tab tymczasow¹ tablicê
	for (int i = 0; i < rozmiar; ++i)			
		tempTab[i] = tab[i];
	delete[] tab;
	tab = tempTab;
}

//Metoda dodajaca element na koniec tablicy 
void Tablica::dodajKoniec(int wartosc){
	if (rozmiar >= ObecnyMaksRozmiar) //je¿eli rozmiar wiêkszy lub równy maksymalnemu to zwiekszamy go 2 krotnie
		realokuj();
	tab[rozmiar] = wartosc;
	rozmiar++;
}


void Tablica::wyczysc() //usuwanie tablicy, przywracanie do stanu poczatkowego
{
	rozmiar = 0;
	ObecnyMaksRozmiar = 2;
	int *tempTab = new int[ObecnyMaksRozmiar];
	delete[] tab;
	tab = tempTab;
}

//wczytywanie struktury z pliku
void Tablica::wczytaj(){
	wyczysc();
	cout << "Podaj nazwe: ";
	string nazwa;
	cin >> nazwa;
	fstream plik(nazwa);
	int r, ile;
	plik >> ile;
	for (int i = 0; i < ile; i++)
	{
		plik >> r;
		dodajKoniec(r);
	}
}

//Metoda dodajaca element na poczatek tablicy, w razie koniecznosci przesuwa cala tablice
void Tablica::dodajPoczatek(int wartosc){
	if (rozmiar >= ObecnyMaksRozmiar)				//je¿eli rozmiar wiêkszy lub równy maksymalnemu to zwiekszamy go 2 krotnie
		realokuj();
	int *tempTab = new int[ObecnyMaksRozmiar]; //tymczasowa tablica
	for (int i = 0; i < rozmiar; i++)
		tempTab[i+1] = tab[i];					//przekopiowujemy elementy z tab na miejsca o 1 dalej
	delete[] tab;
	tab = tempTab;
	tab[0] = wartosc;  //w miejsce o indeksie 0 wstawiamy wartoœæ
	rozmiar++;
}
//Metoda dodajaca element na ustalone miejsce, gdy miejsce jest poza tablica nie dodaje elementu, gdy jest to pierwszy lub ostatni element wykorzystuje
//metody dodajPoczatek i dodajKoniec, w przeciwnym razie rozsuwa tablice i tam wstawia element
void Tablica::dodaj(int wartosc, int index){
	if (index == 0)
		dodajPoczatek(wartosc);
	else if (index == rozmiar-1)
		dodajKoniec(wartosc);
	else if (index>rozmiar || index<0) cout << "Nie ma takiego indeksu" << endl;
	else{
		if (rozmiar >= ObecnyMaksRozmiar)
			realokuj();
		int *tempTab = new int[ObecnyMaksRozmiar];
		for (int i = 0; i < index; i++)
			tempTab[i] = tab[i];			//przekopiowujemy czesc tablicy do indexu bez zmian
		for (int i = index; i < rozmiar; i++)	//od indexu do rozmiaru kopiujemy o 1 pozycje dalej
			tempTab[i + 1] = tab[i];
		delete[] tab;
		tab = tempTab;
		tab[index] = wartosc; // w stawiamy nasza wartosc
		rozmiar++;
	}
	

}
//Usuwanie elementu z poczatku tablicy (przekopiowanie wszystkich innych poza nim)
void Tablica::usunPoczatek(){
	int *tempTab = new int[ObecnyMaksRozmiar];
	for (int i = 0; i < rozmiar; i++)
		tempTab[i] = tab[i+1];
	delete[] tab;
	tab = tempTab;
	rozmiar--;
}
//Usuwanie elementu z konca tablicy (przekopiowanie wszystkich innych poza nim)
void Tablica::usunKoniec(){
	int *tempTab = new int[ObecnyMaksRozmiar];
	for (int i = 0; i < rozmiar-1; i++)
		tempTab[i] = tab[i];
	delete[] tab;
	tab = tempTab;
	rozmiar--;
}
//Usuwanie elementu z  tablicy (przekopiowanie wszystkich innych poza nim)
void Tablica::usun(int index){
	int *tempTab = new int[ObecnyMaksRozmiar];
	if (index == 0)
		usunPoczatek();
	else if (index == rozmiar-1)
		usunKoniec();
	else if (index>rozmiar || index<0) cout << "nie ma takiego indeksu" << endl;
	else {
		
		for (int i = 0; i < index; i++)
			tempTab[i] = tab[i];
		for (int i = index; i < rozmiar; i++)
			tempTab[i] = tab[i+1];
		delete[] tab;
		tab = tempTab;
		rozmiar--;
	}
	
}



//Szukanie elementu w tablicy
void Tablica::znajdz(int wartosc){
	for (int i = 0; i < rozmiar; i++){
		if (tab[i] == wartosc){
			cout <<endl << "Znaleziono element o podanej wartosci. Indeks: " << i << endl;
			return;
		}
	}
	cout << "Nie znaleziono" << endl;
}
