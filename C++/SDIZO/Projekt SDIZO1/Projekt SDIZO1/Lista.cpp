#include "stdafx.h"
#include "Lista.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Lista::Lista()
{
	head = 0;
	tail = 0;
}



void Lista::dodaj(int ind, int num)
{
	if (ind == 1){          //je¿eli indeks = 1 to dodaje z przodu
		dodaj_zprzodu(num);
	}
	else if (ind <= dlugosc){

		element *temp = head;
		for (int i = 1; i <= ind - 2; i++)
		{
			temp = temp->next;
		}
		element *new_element = new element;
		new_element->data = num;
		new_element->next = temp->next;
		new_element->prev = temp;
		dlugosc++;
		temp->next->prev = new_element;
		temp->next = new_element;
	}
	else { cout << "Nie ma takiego numeru" << endl; }
	
}
	

//dodanie okreœlonej wartoœci z przodu, poprzez wykorzystanie wskaŸnika na element
void Lista::dodaj_zprzodu(int num)
{
	element *new_element = new element;
	new_element->data = num;
	new_element->prev = 0;
	new_element->next = head;
	head = new_element;
	if (new_element->next) {
		new_element->next->prev = new_element;
	}
	else tail=new_element;
	dlugosc++;
}
//dodanie okreœlonej wartoœci z ty³u (koniec listy)
void Lista::dodaj_ztylu(int num)
{
	element *new_element = new element;
	new_element->data = num;
	new_element->prev = tail;
	new_element->next = 0;
	tail = new_element;
	
	if (new_element->prev) { 
		new_element->prev->next = new_element; 
	}
	else head = new_element;
	dlugosc++;
}

//kasuje okreœlony indeks tablicy (w tym wypadku listy)
void Lista::usun(int ind)
{
	
	
	if (ind > dlugosc || ind <=0)
	{
		cout << "Nie ma takiego elementu" << endl;
	}
	else{
		element *temp = head;
		for (int i = 1; i < ind; i++)
		{
			temp = temp->next;
		}
		dlugosc--;
		if (temp->prev) temp->prev->next = temp->next;
		else        head = temp->next;
		if (temp->next) temp->next->prev = temp->prev;
		else        tail = temp->prev;
		delete temp;



	}

}
//kasuje z przodu
void Lista::usun_zprzodu()
{
	usun(1);

}

//kasuje z ty³u
void Lista::usun_ztylu()
{
	usun(dlugosc);
}
//znajdowanie okreœlonego elementu - przez sprecyzowanie klucza - w tym wypadku wartoœci
bool Lista::znajdz(int num)
{
	element *temp = head;
	for (int i = 1; i <= dlugosc; i++){
		if (temp->data == num) {
			cout << "Indeks: [" << i << "]" << endl;
			return true;
		}
		temp = temp->next;
		
	}
	
	return false;								// przelecialo przez cala liste i nie znalazlo to zwroci false
}

//wyœwietlenie struktury
void Lista::wyswietl()
{
	element *temp1 = head;
	cout << "dlugosc: " << dlugosc << endl;
	for (int i = 1; i <= dlugosc; i++){
		
		cout << "[" << i << "]: "<< temp1->data<<endl;
		temp1 = temp1->next;
	}
	
}
void Lista::wyswietl2()
{
	element *temp = tail;
	cout << "dlugosc: " << dlugosc << endl;
	for (int i = 1; i <= dlugosc; i++){
		cout << "[" << dlugosc-i+1 << "]: " << temp->data << endl;
		temp = temp->prev;
	}

}
void Lista::usun_cala(){
	for (int i = 1; i <= dlugosc; i){
		usun(i);
		}
		
	
}
//generowanie listy przez u¿ytkownika -> pierwszy parametr okreœlony jest przez wartoœæ maksymaln¹ w liœcie
// drugi zaœ okreœla d³ugoœæ tej listy (iloœæ elementów)
void Lista::generuj(int max, int dlugosc)
{
	for (int i = 1; i <= dlugosc; i++)
		{
			dodaj_zprzodu(std::rand() % max);
		}
	
}
//wczytywanie struktury z pliku
void Lista::wczytaj(){
	int r, ile;
	cout << "Podaj nazwe: ";
	string nazwa;
	cin >> nazwa;
	fstream plik(nazwa);
	plik >> ile;
	for (int i = 0; i < ile; i++)
	{
		plik >> r;
		dodaj_ztylu(r);
	}
}