Uruchomienie programów polega na u¿yciu kompilatora as oraz konsolidatora ld.

as plik.s -o plik.o

ld plik.o -o plik

./plik

hello.s  	Program wyœwietla napis „Hello”

hello2.s 	Program wyœwietla podany przez u¿ytkownika ci¹g znaków.

hello3.s 	Program zamienia wszystkie litery ma³e na du¿e. Zamiana dokonywana jest poprzez u¿ycie funkcji logicznej and i zmianê odpowiedniego bitu na 0.

cezar.s		Program przetwarza ci¹g znaków zamieniaj¹c ka¿d¹ literê na inn¹ wed³ug przesuniêcia podanego przez
 u¿ytkownika (0-9). W programie dodatkowo sprawdzane jest czy nie wyszliœmy ponad zakres ma³ych
 lub du¿ych liter.

Kompilacja kodu na maszynie 64-bitowej wymaga u¿ycia opcji --32 kompilatora as oraz -m elf_i386
linkera ld.


as --32 -o plik.o plik.s

ld -m elf_i386 -o plik plik.o
./plik

zamiana.s 	W programie podajemy liczbê, jako ci¹g znaków. Nastêpnie zostaje ona zapisana, jako pojedyncza
	liczba do rejestru poprzez u¿yciu algorytmu Hornera. 
		Na koñcu dokonujemy wypisania zawartoœci
 rejestru dziel¹c liczbê przez zadan¹ podstawê i wypisuj¹c reszty z dzielenia.

silnia.s 	Do wprowadzania i wyœwietlania wyniku zosta³y u¿yte wczeœniej napisane funkcje wpisz i wypisz.
 Funkcja factorial rekurencyjnie oblicza silniê.
