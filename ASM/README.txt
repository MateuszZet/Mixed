Uruchomienie program�w polega na u�yciu kompilatora as oraz konsolidatora ld.

as plik.s -o plik.o

ld plik.o -o plik

./plik

hello.s  	Program wy�wietla napis �Hello�

hello2.s 	Program wy�wietla podany przez u�ytkownika ci�g znak�w.

hello3.s 	Program zamienia wszystkie litery ma�e na du�e. Zamiana dokonywana jest poprzez u�ycie funkcji logicznej and i zmian� odpowiedniego bitu na 0.

cezar.s		Program przetwarza ci�g znak�w zamieniaj�c ka�d� liter� na inn� wed�ug przesuni�cia podanego przez
 u�ytkownika (0-9). W programie dodatkowo sprawdzane jest czy nie wyszli�my ponad zakres ma�ych
 lub du�ych liter.

Kompilacja kodu na maszynie 64-bitowej wymaga u�ycia opcji --32 kompilatora as oraz -m elf_i386
linkera ld.


as --32 -o plik.o plik.s

ld -m elf_i386 -o plik plik.o
./plik

zamiana.s 	W programie podajemy liczb�, jako ci�g znak�w. Nast�pnie zostaje ona zapisana, jako pojedyncza
	liczba do rejestru poprzez u�yciu algorytmu Hornera. 
		Na ko�cu dokonujemy wypisania zawarto�ci
 rejestru dziel�c liczb� przez zadan� podstaw� i wypisuj�c reszty z dzielenia.

silnia.s 	Do wprowadzania i wy�wietlania wyniku zosta�y u�yte wcze�niej napisane funkcje wpisz i wypisz.
 Funkcja factorial rekurencyjnie oblicza silni�.
