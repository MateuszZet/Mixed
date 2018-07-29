#pragma once
class Tablica
{
public:
	int rozmiar;
	int ObecnyMaksRozmiar;
	int *tab;

public:
	Tablica();
	void pokaz();
	void generuj(int, int);
	void realokuj();
	void dodajKoniec(int);
	void dodajPoczatek(int);
	void dodaj(int, int);
	void usun(int);
	void usunPoczatek();
	void usunKoniec();
	void znajdz(int);
	void wyswietl();
	void wyczysc();
	void wczytaj();
};