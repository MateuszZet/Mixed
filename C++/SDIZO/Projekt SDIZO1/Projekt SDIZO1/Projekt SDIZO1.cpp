// Projekt SDIZO1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include "Tablica.h"
#include "Kopiec.h"
#include "Lista.h"
#include "windows.h"
using namespace std;

unsigned int wybor1, wybor2;
LARGE_INTEGER performanceCountStart, performanceCountEnd, freq;
double tm, t;
//struktury
Lista lista;
Tablica tablica;
Kopiec kopiec;

//menu
void start_menu();
void tablica_menu();
void tablica_menu_dodaj();
void tablica_menu_usun();
void kopiec_menu();
void lista_menu();
void lista_menu_usun();
void lista_menu_dodaj();

//timery
LARGE_INTEGER startTimer();
LARGE_INTEGER endTimer();

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(0));
	start_menu();
	system("Pause");
	return 0;
}




void start_menu()
{

	do{
		cout << "Witaj, dla jakiej struktury chcesz wykonac operacje?" << endl;
		cout << "1. Tablica" << endl << "2. Lista" << endl << "3. Kopiec" << endl << "4. Wyjscie z programu" << endl;
		cin >> wybor1;
	} while (wybor1 == 1 && wybor1 == 2 && wybor1 == 3 && wybor1 == 4);

	switch (wybor1)
	{
	case 1:
		tablica_menu();
		break;
	case 2:
		lista_menu();
		break;
	case 3:
		kopiec_menu();
		break;
	case 4:
		exit(0);
		break;
	default:
		cout << "Zly wybor" << endl;
		start_menu();
	}


}
// ---------------------------tablica--------------------------------
void tablica_menu()
{
	do{
		cout << "1. Generuj" << endl << "2. Dodawanie elementu" << endl << "3. Usuwanie elementow" << endl << "4. Szukanie elementu" << endl << "5. Wyswietl strukture" << endl << "6. Wczytaj strukture z pliku [nazwa.txt]" << endl << "7. Powrot" << endl;
		cin >> wybor2;
	} while (wybor2 == 1 && wybor2 == 2 && wybor2 == 3 && wybor2 == 4 && wybor2 == 5 && wybor2 == 6 && wybor2 == 7);
	switch (wybor2)
	{
	case 1:
		int max, rozmiar;
		cout << "Podaj wartosc maksymalna jaka ma znalezc sie w tablicy" << endl;
		cin >> max;
		cout << "Podaj ilosc elementow tablicy (rozmiar)" << endl;
		cin >> rozmiar;
		tablica.wyczysc();
		tablica.generuj(max, rozmiar);
		tablica_menu();
		break;
	case 2:
		tablica_menu_dodaj();
		tablica_menu();
		break;
	case 3:
		tablica_menu_usun();
		tablica_menu();
		break;
	case 4:
		cout << "Podaj wartosc elementu do wyszukania" << endl;
		int wartosc, result;
		cin >> wartosc;

		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		tablica.znajdz(wartosc);
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		tablica_menu();
		break;
	case 5:
		tablica.pokaz();
		tablica_menu();
		break;
	case 6:
		tablica.wczytaj();
		tablica_menu();
		break;
	case 7:
		start_menu();
		break;
	default:
		cout << "Zly wybor" << endl;
		tablica_menu();
	}

}

void tablica_menu_dodaj()
{


	int index, numer, wybor;
	cout << "Gdzie dodac element?" << endl << "1. Poczatek" << endl << "2. losowo wybrane miejsce" << endl << "3. Koniec" << endl << "4. Powrot" << endl;
	cin >> wybor;
	switch (wybor){
	case 1:
		cout << "Podaj wartosc" << endl;
		cin >> numer;
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		tablica.dodajPoczatek(numer);
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		break;
	case 2:
		cout << "Podaj index" << endl;
		cin >> index;
		cout << "Podaj wartosc" << endl;
		cin >> numer;
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		tablica.dodaj(numer, index);
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		break;
	case 3:
		cout << "Podaj wartosc" << endl;
		cin >> numer;
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		tablica.dodajKoniec(numer);
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		break;
	case 4:
		tablica_menu();
		break;
	default:
		cout << "Zly wybor" << endl;
		tablica_menu_dodaj();

	}
}

void tablica_menu_usun()
{
	int index, numer, wybor;
	cout << "Skad usunac element?" << endl << "1. Poczatek" << endl << "2. Losowo wybrane miejsce" << endl << "3. Koniec" << endl << "4. Powrot"<<endl;
	cin >> wybor;
	switch (wybor){
	case 1:
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		tablica.usunPoczatek();
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		break;
	case 2:
		cout << "Podaj index" << endl;
		cin >> index;
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		tablica.usun(index);
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		break;
	case 3:

		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		tablica.usunKoniec();
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		break;

	case 4:
		tablica_menu();
		break;
	default:
		cout << "Zly wybor" << endl;
		break;
	}
}
// ---------------------------------koniec tablicy--------------------------------

// ---------------------------------kopiec----------------------------------------
void kopiec_menu()
{
	int max, ilosc, wartosc;

	do{
		cout << "1. Generuj" << endl << "2. Dodawanie elementow" << endl << "3. Usuwanie elementow" << endl << "4. Szukanie elementu" << endl << "5. Wyswietl strukture" << endl << "6. Wyswietl strukture (drzewo, max 31 elementow 3-cyfrowych)" << endl << "7. Wczytaj strukture z pliku [nazwa.txt]" << endl << "8. Powrot" << endl;
		cin >> wybor2;
	} while (wybor2 == 1 && wybor2 == 2 && wybor2 == 3 && wybor2 == 4 && wybor2 == 5 && wybor2 == 6 && wybor2 == 7);
	switch (wybor2)
	{
	case 1:
		cout << "Podaj wartosc maksymalna jaka ma pojawic sie na kopcu" << endl;
		cin >> max;
		cout << "Podaj ilosc elementow z ktorych ma byc zbudowany kopiec" << endl;
		cin >> ilosc;
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		kopiec.generuj(max, ilosc);
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		break;
	case 2:

		cout << "Podaj wartosc jaka chcesz dodac do kopca" << endl;
		cin >> wartosc;
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		kopiec.dodaj(wartosc);
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		break;
	case 3:
		cout << "Podaj wartosc jaka chcesz usunac z kopca" << endl;
		cin >> wartosc;
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		kopiec.usun(wartosc);
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		break;
	case 4:
		bool result;
		cout << "Podaj wartosc elementu do wyszukania" << endl;
		cin >> wartosc;
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		result = kopiec.znajdz(wartosc);
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Zlozonosc: " << t << endl;
		if (result)
			cout << "Znaleziono podany element" << endl;
		else
			cout << "Nie znaleziono podanego elementu" << endl;

		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		break;
	case 5:
		kopiec.wyswietl();
		break;
	case 6:
		kopiec.wyswietl2();
		break;
	case 7:
		kopiec.wczytaj();
		kopiec_menu();
		break;
	case 8:
		start_menu();
		break;
	default:
		cout << "Zly wybor" << endl;
	}
	kopiec_menu();

}

void lista_menu()
{
	do{

		cout << "1. Generuj" << endl << "2. Dodawanie elementu" << endl << "3. Usuwanie elementow" << endl << "4. Szukanie elementu" << endl << "5. Wyswietl strukture" << endl << "6. Wczytaj strukture z pliku [nazwa.txt]" << endl << "7. Powrot" << endl;
		cin >> wybor2;
	} while (wybor2 == 1 && wybor2 == 8 && wybor2 == 2 && wybor2 == 3 && wybor2 == 4 && wybor2 == 5 && wybor2 == 6 && wybor2 == 7);
	switch (wybor2)
	{
	case 1:
		int max, ile;
		cout << "Podaj wartosc maksymalna jaka ma znalezc sie na liscie" << endl;
		cin >> max;
		cout << "Okresl dlugosc listy (ilosc elementow)" << endl;
		cin >> ile;
		lista.usun_cala();
		lista.generuj(max, ile);
		lista.wyswietl();
		lista_menu();
		break;
	case 2:
		lista_menu_dodaj();
		lista_menu();
		break;
	case 3:
		lista_menu_usun();
		lista_menu();
		break;
	case 4:
		bool result;
		cout << "Podaj wartosc elementu do wyszukania" << endl;
		int wartosc;
		cin >> wartosc;
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		result = lista.znajdz(wartosc);
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;

		if (result)
			cout << "Znaleziono podany element" << endl;
		else
			cout << "Nie znaleziono podanego elementu" << endl;


		lista_menu();
		break;
	case 5:
		lista.wyswietl();
		cout << endl;
		lista.wyswietl2();
		lista_menu();
		break;
	case 6:
		lista.usun_cala();
		lista.wczytaj();
		lista.wyswietl();
		lista_menu();
		break;
	case 7:
		start_menu();
		break;
	default:
		cout << "Zly wybor" << endl;
		lista_menu();
	}
}
void lista_menu_dodaj()
{
	int index, wartosc, wybor;
	cout << "Gdzie dodac element?" << endl << "1. Poczatek" << endl << "2. Wybrane miejsce" << endl << "3. Koniec" << endl << "4. Powrot" << endl;;
	cin >> wybor;
	switch (wybor){
	case 1:
		cout << "Podaj wartosc" << endl;
		cin >> wartosc;
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		lista.dodaj_zprzodu(wartosc);
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		lista.wyswietl();
		break;

	case 2:
		cout << "Podaj index" << endl;
		cin >> index;
		cout << "Podaj wartosc" << endl;
		cin >> wartosc;
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		lista.dodaj(index, wartosc);
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		lista.wyswietl();
		break;
	case 3:
		cout << "Podaj wartosc" << endl;
		cin >> wartosc;
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		lista.dodaj_ztylu(wartosc);
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		lista.wyswietl();
		break;
	case 4:
		lista_menu();
		break;
	default:
		cout << "Zly wybor" << endl;
		break;
	}
}

void lista_menu_usun()
{
	int index, numer, wybor;
	cout << "Skad usunac element?" << endl << "1. Poczatek" << endl << "2. Wybrane miejsce" << endl << "3. Koniec" << endl << "4. Powrot" << endl;
	cin >> wybor;
	switch (wybor){
	case 1:
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		lista.usun_zprzodu();
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		lista.wyswietl();
		break;
	case 2:
		cout << "Podaj index" << endl;
		cin >> index;
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		lista.usun(index);
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		lista.wyswietl();
		break;
	case 3:
		performanceCountStart = startTimer(); //zapamiêtujemy czas pocz¹tkowy
		lista.usun_ztylu();
		performanceCountEnd = endTimer(); //zapamiêtujemy koniec czasu

		QueryPerformanceFrequency(&freq);
		t = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
		tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / ((double)freq.QuadPart / 1000);
		cout << "Wykonano w czasie: " << tm << " [ms]" << endl;
		cout << "Zlozonosc: " << t << endl;
		lista.wyswietl();
		break;
	case 4:
		lista_menu();
		break;
	default:
		cout << "Zly wybor" << endl;
		break;
	}
}

LARGE_INTEGER startTimer()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return start;
}
LARGE_INTEGER endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return stop;
}