#pragma once

struct element {
	int data;
	element *next, *prev;
};

class Lista
{

public:
	Lista();
	void dodaj(int ind, int num);
	void dodaj_zprzodu(int num);
	void dodaj_ztylu(int num);
	void usun(int ind);
	void usun_zprzodu();
	void usun_ztylu();
	void usun_cala();
	bool znajdz(int num);
	void wyswietl();
	void wyswietl2();
	void generuj(int max, int dlugosc);
	void wczytaj();
private:
	element *head, *tail;
	int dlugosc = 0;
};