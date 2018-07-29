#pragma once
class Kopiec
{
public:
	//Pola klasy: data - wskaznik na tablice do przechowywania danych, rozmiar - indeks wolnego miejsca, ObecnyMaksRozmiar - chwilowa maksymalna ilosc elementow (do realokacji)
	int *data;
	int rozmiar;
	int ObecnyMaksRozmiar;

public:
	Kopiec();
	void realokuj();
	void wyczysc();
	int znajdz_rodzica(int indeks);
	int znajdz_lewe_dziecko(int indeks);
	int znajdz_prawe_dziecko(int indeks);
	void usun(int wartosc);
	int naprawa_gora(int indeks);
	int naprawa_dol(int indeks);
	void dodaj(int wartosc);
	bool znajdz(int wartosc);
	void generuj(int max, int num);
	void wyswietl();
	void wyswietl2();
	void wczytaj();
};