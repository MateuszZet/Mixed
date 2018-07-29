#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <string>
using namespace std;
double PCFreq = 0.0; 											// zmienne do licznika czasu operacji
__int64 CounterStart = 0;
const int MAX_INT = 2147483647;
int m, n, pocz;
int tablica[2000][2000];                        				// Liczba kraw�dzi i wierzcho�k�w w grafie

void StartCounter() 											// funkcja liczaca czas trwania operacji
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double GetCounter() 											// funkcja zwracaja czas zliczony od rozpoczecia licznika
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}
void macierz_sasiedztwa(string nazwa)
{
	int i, j, v1, v2, waga;
	char ** A;
	ifstream dane(nazwa.c_str());
	dane >> n >> m;         // Czytamy liczb� wierzcho�k�w i kraw�dzi

	A = new char *[n];    // Tworzymy tablic� wska�nik�w

	for (i = 0; i < n; i++)
		A[i] = new char[n]; // Tworzymy wiersze

	// Macierz wype�niamy zerami

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) A[i][j] = 0;

	// Odczytujemy kolejne definicje kraw�dzi

	for (i = 0; i < m; i++)
	{
		dane >> v1 >> v2 >> waga;    // Wierzcho�ek startowy i ko�cowy kraw�dzi
		A[v1][v2] = waga;      		// Kraw�d� v1->v2 obecna
		tablica[v1][v2] = waga;
	}

	cout << endl;

	// Wypisujemy zawarto�� macierzy s�siedztwa

	cout << "   ";
	for (i = 0; i < n; i++) cout << setw(3) << i;
	cout << endl << endl;
	for (i = 0; i < n; i++)
	{
		cout << setw(3) << i;
		for (j = 0; j < n; j++) cout << setw(3) << (int)A[i][j];
		cout << endl;
	}

	//Usuwamy macierz

	for (i = 0; i < n; i++) delete[] A[i];
	delete[] A;

	cout << endl;
	dane.close();

}
void macierz_sasiedztwa2(string nazwa)
{
	int i, j, v1, v2, waga;
	char ** A;
	ifstream dane(nazwa.c_str());
	dane >> n >> m >> pocz;         // Czytamy liczb� wierzcho�k�w i kraw�dzi

	A = new char *[n];    // Tworzymy tablic� wska�nik�w

	for (i = 0; i < n; i++)
		A[i] = new char[n]; // Tworzymy wiersze

	// Macierz wype�niamy zerami

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) A[i][j] = 0;

	// Odczytujemy kolejne definicje kraw�dzi

	for (i = 0; i < m; i++)
	{
		dane >> v1 >> v2 >> waga;    // Wierzcho�ek startowy i ko�cowy kraw�dzi
		A[v1][v2] = waga;      		// Kraw�d� v1->v2 obecna
		tablica[v1][v2] = waga;
	}

	cout << endl;

	// Wypisujemy zawarto�� macierzy s�siedztwa

	cout << "   ";
	for (i = 0; i < n; i++) cout << setw(3) << i;
	cout << endl << endl;
	for (i = 0; i < n; i++)
	{
		cout << setw(3) << i;
		for (j = 0; j < n; j++) cout << setw(3) << (int)A[i][j];
		cout << endl;
	}

	//Usuwamy macierz

	for (i = 0; i < n; i++) delete[] A[i];
	delete[] A;

	cout << endl;
	dane.close();

}
void wypisz_macierz()
{
	int i, j;
	cout << "   ";
	for (i = 0; i < n; i++) cout << setw(3) << i;
	cout << endl << endl;
	for (i = 0; i < n; i++)
	{
		cout << setw(3) << i;
		for (j = 0; j < n; j++) cout << setw(3) << (int)tablica[i][j];
		cout << endl;
	}
}

struct slistEl
{
	slistEl * next;
	int v, w;
};


slistEl ** A;                     // Tablica dynamiczna list s�siedztwa
long long * d;                    // Tablica koszt�w doj�cia
int * p;                          // Tablica poprzednik�w


void lista_sasiedztwa(string nazwa)
{
	int i, v1, v2, waga;
	slistEl *p, *r;
	ifstream dane(nazwa.c_str());
	dane >> n >> m;         // Czytamy liczb� wierzcho�k�w i kraw�dzi

	A = new slistEl *[n]; // Tworzymy tablic� list s�siedztwa

	// Tablic� wype�niamy pustymi listami

	for (i = 0; i < n; i++) A[i] = NULL;

	// Odczytujemy kolejne definicje kraw�dzi

	for (i = 0; i < m; i++)
	{
		dane >> v1 >> v2 >> waga;    // Wierzcho�ek startowy i ko�cowy kraw�dzi
		p = new slistEl;    // Tworzymy nowy element
		p->v = v2;          // Numerujemy go jako v2
		p->next = A[v1];    // Dodajemy go na pocz�tek listy A[v1]
		A[v1] = p;
	}

	cout << endl;

	// Wypisujemy zawarto�� tablicy list s�siedztwa

	for (i = 0; i < n; i++)
	{
		cout << "A[" << i << "] =";
		p = A[i];
		while (p)
		{
			cout << setw(3) << p->v;
			p = p->next;
		}
		cout << endl;
	}

	// Usuwamy tablic� list s�siedztwa

	for (i = 0; i < n; i++)
	{
		p = A[i];
		while (p)
		{
			r = p;
			p = p->next;
			delete r;
		}
	}
	delete[] A;

	cout << endl;
	dane.close();
}
void lista_sasiedztwa2(string nazwa)
{
	int i, v1, v2, waga;
	slistEl *p, *r;
	ifstream dane(nazwa.c_str());
	dane >> n >> m >> pocz;         // Czytamy liczb� wierzcho�k�w i kraw�dzi

	A = new slistEl *[n]; // Tworzymy tablic� list s�siedztwa

	// Tablic� wype�niamy pustymi listami

	for (i = 0; i < n; i++) A[i] = NULL;

	// Odczytujemy kolejne definicje kraw�dzi

	for (i = 0; i < m; i++)
	{
		dane >> v1 >> v2 >> waga;    // Wierzcho�ek startowy i ko�cowy kraw�dzi
		p = new slistEl;    // Tworzymy nowy element
		p->v = v2;          // Numerujemy go jako v2
		p->next = A[v1];    // Dodajemy go na pocz�tek listy A[v1]
		A[v1] = p;
	}

	cout << endl;

	// Wypisujemy zawarto�� tablicy list s�siedztwa

	for (i = 0; i < n; i++)
	{
		cout << "A[" << i << "] =";
		p = A[i];
		while (p)
		{
			cout << setw(3) << p->v;
			p = p->next;
		}
		cout << endl;
	}

	// Usuwamy tablic� list s�siedztwa

	for (i = 0; i < n; i++)
	{
		p = A[i];
		while (p)
		{
			r = p;
			p = p->next;
			delete r;
		}
	}
	delete[] A;

	cout << endl;
	dane.close();
}
struct Edge
{
	int v1, v2, weight;               // Wierzcho�ki kraw�dzi, waga kraw�dzi
};

class Queue
{
private:
	Edge * Heap;
	int hpos;
public:
	Queue(int n);
	~Queue();
	Edge front();
	void push(Edge e);
	void pop();
};

// Definicja obiektu struktury zbior�w roz��cznych
//------------------------------------------------
struct DSNode
{
	int up, rank;
};

class DSStruct
{
private:
	DSNode * Z;
public:
	DSStruct(int n);
	~DSStruct();
	void MakeSet(int v);
	int FindSet(int v);
	void UnionSets(Edge e);
};

// Definicja obiektu minimalnego drzewa rozpinaj�cego
//---------------------------------------------------
struct TNode
{
	TNode * next;
	int v, weight;
};

class MSTree
{
private:
	TNode ** A;                   // Tablica list s�siedztwa
	int Alen;                     // Liczba kom�rek w tablicy
	int weight;                   // Waga ca�ego drzewa
public:
	MSTree(int n);
	~MSTree();
	void addEdge(Edge e);
	TNode * getAList(int n);
	void print();
};

// Definicje metod obiektu Queue
//------------------------------

// Konstruktor - tworzy n elementow� tablic� heap na kopiec
//---------------------------------------------------------
Queue::Queue(int n)
{
	Heap = new Edge[n];            // Tworzymy tablic�
	hpos = 0;                       // Pozycja w kopcu
}

// Destruktor - usuwa kopiec z pami�ci
//------------------------------------
Queue::~Queue()
{
	delete[] Heap;
}

// Zwraca kraw�d� z pocz�tku kopca
//--------------------------------
Edge Queue::front()
{
	return Heap[0];
}

// Umieszcza w kopcu now� kraw�d� i odtwarza struktur� kopca
//----------------------------------------------------------
void Queue::push(Edge e)
{
	int i, j;

	i = hpos++;                     // i ustawiamy na koniec kopca
	j = (i - 1) >> 1;               // Obliczamy pozycj� rodzica

	// Szukamy miejsca w kopcu dla e

	while (i && (Heap[j].weight > e.weight))
	{
		Heap[i] = Heap[j];
		i = j;
		j = (i - 1) >> 1;
	}

	Heap[i] = e;                    // Kraw�d� e wstawiamy do kopca
}

// Usuwa korze� z kopca i odtwarza jego struktur�
//-----------------------------------------------
void Queue::pop()
{
	int i, j;
	Edge e;

	if (hpos)
	{
		e = Heap[--hpos];

		i = 0;
		j = 1;

		while (j < hpos)
		{
			if ((j + 1 < hpos) && (Heap[j + 1].weight < Heap[j].weight)) j++;
			if (e.weight <= Heap[j].weight) break;
			Heap[i] = Heap[j];
			i = j;
			j = (j << 1) + 1;
		}

		Heap[i] = e;
	}
}

// Definicje metod obiektu DSStruct
//---------------------------------

// Konstruktor
DSStruct::DSStruct(int n)
{
	Z = new DSNode[n];             // Tworzymy tablic� dla element�w zbior�w
}

// Destruktor
//-----------
DSStruct::~DSStruct()
{
	delete[] Z;                    // Usuwamy tablic� ze zbiorami
}

// Tworzy wpis w tablicy Z
//------------------------
void DSStruct::MakeSet(int v)
{
	Z[v].up = v;
	Z[v].rank = 0;
}

// Zwraca indeks reprezentanta zbioru, w kt�rym jest wierzcho�ek v
//----------------------------------------------------------------
int DSStruct::FindSet(int v)
{
	if (Z[v].up != v) Z[v].up = FindSet(Z[v].up);
	return Z[v].up;
}

// ��czy ze sob� zbiory z v i u
//-----------------------------
void DSStruct::UnionSets(Edge e)
{
	int ru, rv;

	ru = FindSet(e.v1);             // Wyznaczamy korze� drzewa z w�z�em u
	rv = FindSet(e.v2);             // Wyznaczamy korze� drzewa z w�z�em v
	if (ru != rv)                    // Korzenie musz� by� r�ne
	{
		if (Z[ru].rank > Z[rv].rank)   // Por�wnujemy rangi drzew
			Z[rv].up = ru;              // ru wi�ksze, do��czamy rv
		else
		{
			Z[ru].up = rv;              // r�wne lub rv wi�ksze, do��czamy ru
			if (Z[ru].rank == Z[rv].rank) Z[rv].rank++;
		}
	}
}

// Definicje metod obiektu MSTree
//-------------------------------

// Konstruktor - tworzy tablic� pustych list s�siedztwa
//-----------------------------------------------------
MSTree::MSTree(int n)
{
	int i;

	A = new TNode *[n];            // Tworzymy tablic� dynamiczn�
	for (i = 0; i < n; i++) A[i] = NULL; // i wype�niamy j� pustymi listami
	Alen = n - 1;                   // Zapami�tujemy d�ugo�� tablicy
	weight = 0;                     // Zerujemy wag� drzewa
}

// Destruktor - usuwa listy oraz tablic� s�siedztwa
//-------------------------------------------------
MSTree::~MSTree()
{
	int i;
	TNode *p, *r;

	for (i = 0; i <= Alen; i++)
	{
		p = A[i];
		while (p)
		{
			r = p;                      // Zapami�tujemy wskazanie
			p = p->next;                // Przesuwamy si� do nast�pnego elementu listy
			delete r;                   // Usuwamy element
		}
	}

	delete[] A;                    // Usuwamy tablic� list s�siedztwa
}

// Dodaje kraw�d� do drzewa
//-------------------------
void MSTree::addEdge(Edge e)
{
	TNode *p;

	weight += e.weight;             // Do wagi drzewa dodajemy wag� kraw�dzi
	p = new TNode;                  // Tworzymy nowy w�ze�
	p->v = e.v2;                    // Wierzcho�ek ko�cowy
	p->weight = e.weight;           // Waga kraw�dzi
	p->next = A[e.v1];              // Dodajemy p do listy wierzcho�ka v1
	A[e.v1] = p;

	p = new TNode;                  // To samo dla kraw�dzi odwrotnej
	p->v = e.v1;                    // Wierzcho�ek ko�cowy
	p->weight = e.weight;           // Waga kraw�dzi
	p->next = A[e.v2];              // Dodajemy p do listy wierzcho�ka v2
	A[e.v2] = p;
}

// Zwraca wska�nik pocz�tku listy s�siad�w wierzcho�ka
//----------------------------------------------------
TNode * MSTree::getAList(int n)
{
	return A[n];
}

// Wy�wietla zawarto�� drzewa oraz jego wag�
//------------------------------------------
void MSTree::print()
{
	int i;
	TNode *p;

	cout << endl;
	for (i = 0; i <= Alen; i++)
	{
		cout << "Wierzcholek " << i << " - ";
		for (p = A[i]; p; p = p->next) cout << p->v << ":" << p->weight << " ";
		cout << endl;
	}
	cout << endl << endl << "Waga Minimalnego Drzewa Rozpinajacego = " << weight << endl << endl;
}
void kruskal_lista(string nazwa_pliku)
{
	Edge e;
	int i;
	ifstream dane(nazwa_pliku.c_str());
	dane >> n >> m;                  // Czytamy liczb� wierzcho�k�w i kraw�dzi

	DSStruct Z(n);                  // Struktura zbior�w roz��cznych
	Queue Q(m);                     // Kolejka priorytetowa oparta na kopcu
	MSTree T(n);                    // Minimalne drzewo rozpinaj�ce

	for (i = 0; i < n; i++)
		Z.MakeSet(i);                 // Dla ka�dego wierzcho�ka tworzymy osobny zbi�r

	for (i = 0; i < m; i++)
	{
		dane >> e.v1 >> e.v2 >> e.weight; // Odczytujemy kolejne kraw�dzie grafu
		Q.push(e);                    // i umieszczamy je w kolejce priorytetowej
	}

	for (i = 1; i < n; i++)          // P�tla wykonuje si� n - 1 razy !!!
	{
		do
		{
			e = Q.front();              // Pobieramy z kolejki kraw�d�
			Q.pop();                    // Kraw�d� usuwamy z kolejki
		} while (Z.FindSet(e.v1) == Z.FindSet(e.v2));
		T.addEdge(e);                 // Dodajemy kraw�d� do drzewa
		Z.UnionSets(e);               // Zbiory z wierzcho�kami ��czymy ze sob�
	}

	// Wy�wietlamy wyniki

	T.print();
	dane.close();
}

void kruskal_macierz()
{
	Edge e;
	int i, j;

	DSStruct Z(n);                  // Struktura zbior�w roz��cznych
	Queue Q(m);                     // Kolejka priorytetowa oparta na kopcu
	MSTree T(n);                    // Minimalne drzewo rozpinaj�ce

	for (i = 0; i < n; i++)
		Z.MakeSet(i);                 // Dla ka�dego wierzcho�ka tworzymy osobny zbi�r

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			if (tablica[i][j] != 0)
			{
				e.v1 = i;
				e.v2 = j;
				e.weight = tablica[i][j];
			}
		Q.push(e);
	}

	for (i = 1; i < n; i++)          // P�tla wykonuje si� n - 1 razy !!!
	{
		do
		{
			e = Q.front();              // Pobieramy z kolejki kraw�d�
			Q.pop();                    // Kraw�d� usuwamy z kolejki
		} while (Z.FindSet(e.v1) == Z.FindSet(e.v2));
		T.addEdge(e);                 // Dodajemy kraw�d� do drzewa
		Z.UnionSets(e);               // Zbiory z wierzcho�kami ��czymy ze sob�
	}

	// Wy�wietlamy wyniki

	T.print();
}

void prim_lista(string nazwa_pliku)
{
	Edge e;
	TNode * p;
	int i, v;
	ifstream dane(nazwa_pliku.c_str());
	dane >> n >> m;                  // Czytamy liczb� wierzcho�k�w i kraw�dzi

	Queue Q(m);                     // Kolejka priorytetowa oparta na kopcu
	MSTree T(n);                    // Minimalne drzewo rozpinaj�ce
	MSTree G(n);                    // Graf
	bool * visited = new bool[n];

	for (i = 0; i < n; i++)
		visited[i] = false;           // Inicjujemy tablic� odwiedzin

	for (i = 0; i < m; i++)
	{
		dane >> e.v1 >> e.v2 >> e.weight; // Odczytujemy kolejne kraw�dzie grafu
		G.addEdge(e);                 // i umieszczamy je w G
	}

	// Tworzymy minimalne drzewo rozpinaj�ce

	v = 0;                          // Wierzcho�ek startowy
	visited[v] = true;              // Oznaczamy go jako odwiedzonego

	for (i = 1; i < n; i++)          // Do drzewa dodamy n - 1 kraw�dzi grafu
	{
		for (p = G.getAList(v); p; p = p->next) // Przegl�damy list� s�siad�w
			if (!visited[p->v])          // Je�li s�siad jest nieodwiedzony,
			{
				e.v1 = v;                 // to tworzymy kraw�d�
				e.v2 = p->v;
				e.weight = p->weight;
				Q.push(e);                // Dodajemy j� do kolejki priorytetowej
			}

		do
		{
			e = Q.front();              // Pobieramy kraw�d� z kolejki
			Q.pop();
		} while (visited[e.v2]);       // Kraw�d� prowadzi poza drzewo?

		T.addEdge(e);                 // Dodajemy kraw�d� do drzewa rozpinaj�cego
		visited[e.v2] = true;         // Oznaczamy drugi wierzcho�ek jako odwiedzony
		v = e.v2;
	}

	// Wy�wietlamy wyniki

	T.print();

	delete[] visited;
	dane.close();
}
void prim_macierz()
{
	Edge e;
	TNode * p;
	int i, j, v;

	Queue Q(m);                     // Kolejka priorytetowa oparta na kopcu
	MSTree T(n);                    // Minimalne drzewo rozpinaj�ce
	MSTree G(n);                    // Graf
	bool * visited = new bool[n];

	for (i = 0; i < n; i++)
		visited[i] = false;           // Inicjujemy tablic� odwiedzin

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			if (tablica[i][j] != 0)
			{
				e.v1 = i;
				e.v2 = j;
				e.weight = tablica[i][j];
			}
		G.addEdge(e);
	}
	// Tworzymy minimalne drzewo rozpinaj�ce

	v = 0;                          // Wierzcho�ek startowy
	visited[v] = true;              // Oznaczamy go jako odwiedzonego

	for (i = 1; i < n; i++)          // Do drzewa dodamy n - 1 kraw�dzi grafu
	{
		for (p = G.getAList(v); p; p = p->next) // Przegl�damy list� s�siad�w
			if (!visited[p->v])          // Je�li s�siad jest nieodwiedzony,
			{
				e.v1 = v;                 // to tworzymy kraw�d�
				e.v2 = p->v;
				e.weight = p->weight;
				Q.push(e);                // Dodajemy j� do kolejki priorytetowej
			}

		do
		{
			e = Q.front();              // Pobieramy kraw�d� z kolejki
			Q.pop();
		} while (visited[e.v2]);       // Kraw�d� prowadzi poza drzewo?

		T.addEdge(e);                 // Dodajemy kraw�d� do drzewa rozpinaj�cego
		visited[e.v2] = true;         // Oznaczamy drugi wierzcho�ek jako odwiedzony
		v = e.v2;
	}

	// Wy�wietlamy wyniki

	T.print();

	delete[] visited;
}
void dijkstra_lista(string nazwa_pliku, int v)
{
	int i, j, u, w, x, y, sptr, *d, *p, *S;
	bool *QS;                       // Zbiory Q i S
	slistEl **graf;                 // Tablica list s�siedztwa
	slistEl *pw, *rw;

	ifstream dane(nazwa_pliku.c_str());
	dane >> n >> m;             //  liczba wierzcho�k�w i kraw�dzi

	// Tworzymy tablice dynamiczne

	d = new int[n];                // Tablica koszt�w doj�cia
	p = new int[n];                // Tablica poprzednik�w
	QS = new bool[n];              // Zbiory Q i S
	graf = new slistEl *[n];       // Tablica list s�siedztwa
	S = new int[n];                // Stos
	sptr = 0;                       // Wska�nik stosu

	// Inicjujemy tablice dynamiczne

	for (i = 0; i < n; i++)
	{
		d[i] = MAX_INT;
		p[i] = -1;
		QS[i] = false;
		graf[i] = NULL;
	}

	// Odczytujemy dane wej�ciowe

	for (i = 0; i < m; i++)
	{
		dane >> x >> y >> w;           // Odczytujemy kraw�d� z wag�
		pw = new slistEl;             // Tworzymy element listy s�siedztwa
		pw->v = y;                    // Wierzcho�ek docelowy kraw�dzi
		pw->w = w;                    // Waga kraw�dzi
		pw->next = graf[x];
		graf[x] = pw;                 // Element do��czamy do listy
	}

	cout << endl;

	d[v] = 0;                       // Koszt doj�cia v jest zerowy

	// Wyznaczamy �cie�ki

	for (i = 0; i < n; i++)
	{
		// Szukamy wierzcho�ka w Q o najmniejszym koszcie d

		for (j = 0; QS[j]; j++);
		for (u = j++; j < n; j++)
			if (!QS[j] && (d[j] < d[u])) u = j;

		// Znaleziony wierzcho�ek przenosimy do S

		QS[u] = true;

		// Modyfikujemy odpowiednio wszystkich s�siad�w u, kt�rzy s� w Q

		for (pw = graf[u]; pw; pw = pw->next)
			if (!QS[pw->v] && (d[pw->v] > d[u] + pw->w))
			{
				d[pw->v] = d[u] + pw->w;
				p[pw->v] = u;
			}
	}

	// Gotowe, wy�wietlamy wyniki

	for (i = 0; i < n; i++)
	{
		cout << i << ": ";

		// �cie�k� przechodzimy od ko�ca ku pocz�tkowi,
		// Zapisuj�c na stosie kolejne wierzcho�ki

		for (j = i; j > -1; j = p[j]) S[sptr++] = j;

		// Wy�wietlamy �cie�k�, pobieraj�c wierzcho�ki ze stosu

		while (sptr) cout << S[--sptr] << " ";

		// Na ko�cu �cie�ki wypisujemy jej koszt

		cout << "$" << d[i] << endl;
	}
	cout << endl;

	// Usuwamy tablice dynamiczne

	delete[] d;
	delete[] p;
	delete[] QS;
	delete[] S;

	for (i = 0; i < n; i++)
	{
		pw = graf[i];
		while (pw)
		{
			rw = pw;
			pw = pw->next;
			delete rw;
		}
	}

	delete[] graf;
	dane.close();
}
void dijkstra_lista2(string nazwa_pliku, int v)
{
	int i, j, u, w, x, y, sptr, *d, *p, *S;
	bool *QS;                       // Zbiory Q i S
	slistEl **graf;                 // Tablica list s�siedztwa
	slistEl *pw, *rw;

	ifstream dane(nazwa_pliku.c_str());
	dane >> n >> m >> pocz;             //  liczba wierzcho�k�w i kraw�dzi

	// Tworzymy tablice dynamiczne

	d = new int[n];                // Tablica koszt�w doj�cia
	p = new int[n];                // Tablica poprzednik�w
	QS = new bool[n];              // Zbiory Q i S
	graf = new slistEl *[n];       // Tablica list s�siedztwa
	S = new int[n];                // Stos
	sptr = 0;                       // Wska�nik stosu

	// Inicjujemy tablice dynamiczne

	for (i = 0; i < n; i++)
	{
		d[i] = MAX_INT;
		p[i] = -1;
		QS[i] = false;
		graf[i] = NULL;
	}

	// Odczytujemy dane wej�ciowe

	for (i = 0; i < m; i++)
	{
		dane >> x >> y >> w;           // Odczytujemy kraw�d� z wag�
		pw = new slistEl;             // Tworzymy element listy s�siedztwa
		pw->v = y;                    // Wierzcho�ek docelowy kraw�dzi
		pw->w = w;                    // Waga kraw�dzi
		pw->next = graf[x];
		graf[x] = pw;                 // Element do��czamy do listy
	}

	cout << endl;

	d[v] = 0;                       // Koszt doj�cia v jest zerowy

	// Wyznaczamy �cie�ki

	for (i = 0; i < n; i++)
	{
		// Szukamy wierzcho�ka w Q o najmniejszym koszcie d

		for (j = 0; QS[j]; j++);
		for (u = j++; j < n; j++)
			if (!QS[j] && (d[j] < d[u])) u = j;

		// Znaleziony wierzcho�ek przenosimy do S

		QS[u] = true;

		// Modyfikujemy odpowiednio wszystkich s�siad�w u, kt�rzy s� w Q

		for (pw = graf[u]; pw; pw = pw->next)
			if (!QS[pw->v] && (d[pw->v] > d[u] + pw->w))
			{
				d[pw->v] = d[u] + pw->w;
				p[pw->v] = u;
			}
	}

	// Gotowe, wy�wietlamy wyniki

	for (i = 0; i < n; i++)
	{
		cout << i << ": ";

		// �cie�k� przechodzimy od ko�ca ku pocz�tkowi,
		// Zapisuj�c na stosie kolejne wierzcho�ki

		for (j = i; j > -1; j = p[j]) S[sptr++] = j;

		// Wy�wietlamy �cie�k�, pobieraj�c wierzcho�ki ze stosu

		while (sptr) cout << S[--sptr] << " ";

		// Na ko�cu �cie�ki wypisujemy jej koszt

		cout << "$" << d[i] << endl;
	}
	cout << endl;

	// Usuwamy tablice dynamiczne

	delete[] d;
	delete[] p;
	delete[] QS;
	delete[] S;

	for (i = 0; i < n; i++)
	{
		pw = graf[i];
		while (pw)
		{
			rw = pw;
			pw = pw->next;
			delete rw;
		}
	}

	delete[] graf;
	dane.close();
}

void dijkstra_macierz(int v)
{
	int i, j, u, w, x, y, sptr, *d, *p, *S;
	bool *QS;                       // Zbiory Q i S
	slistEl **graf;                 // Tablica list s�siedztwa
	slistEl *pw, *rw;

	// Tworzymy tablice dynamiczne

	d = new int[n];                // Tablica koszt�w doj�cia
	p = new int[n];                // Tablica poprzednik�w
	QS = new bool[n];              // Zbiory Q i S
	graf = new slistEl *[n];       // Tablica list s�siedztwa
	S = new int[n];                // Stos
	sptr = 0;                       // Wska�nik stosu

	// Inicjujemy tablice dynamiczne

	for (i = 0; i < n; i++)
	{
		d[i] = MAX_INT;
		p[i] = -1;
		QS[i] = false;
		graf[i] = NULL;
	}

	// Odczytujemy dane wej�ciowe
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			if (tablica[i][j] != 0)
			{
				pw = new slistEl;
				pw->v = j;
				pw->w = tablica[i][j];
				pw->next = graf[i];
				graf[i] = pw;
			}
	}


	cout << endl;

	d[v] = 0;                       // Koszt doj�cia v jest zerowy

	// Wyznaczamy �cie�ki

	for (i = 0; i < n; i++)
	{
		// Szukamy wierzcho�ka w Q o najmniejszym koszcie d

		for (j = 0; QS[j]; j++);
		for (u = j++; j < n; j++)
			if (!QS[j] && (d[j] < d[u])) u = j;

		// Znaleziony wierzcho�ek przenosimy do S

		QS[u] = true;

		// Modyfikujemy odpowiednio wszystkich s�siad�w u, kt�rzy s� w Q

		for (pw = graf[u]; pw; pw = pw->next)
			if (!QS[pw->v] && (d[pw->v] > d[u] + pw->w))
			{
				d[pw->v] = d[u] + pw->w;
				p[pw->v] = u;
			}
	}

	// Gotowe, wy�wietlamy wyniki

	for (i = 0; i < n; i++)
	{
		cout << i << ": ";

		// �cie�k� przechodzimy od ko�ca ku pocz�tkowi,
		// Zapisuj�c na stosie kolejne wierzcho�ki

		for (j = i; j > -1; j = p[j]) S[sptr++] = j;

		// Wy�wietlamy �cie�k�, pobieraj�c wierzcho�ki ze stosu

		while (sptr) cout << S[--sptr] << " ";

		// Na ko�cu �cie�ki wypisujemy jej koszt

		cout << "$" << d[i] << endl;
	}
	cout << endl;

	// Usuwamy tablice dynamiczne

	delete[] d;
	delete[] p;
	delete[] QS;
	delete[] S;

	for (i = 0; i < n; i++)
	{
		pw = graf[i];
		while (pw)
		{
			rw = pw;
			pw = pw->next;
			delete rw;
		}
	}

	delete[] graf;
}
void dijkstra_macierz2(int v)
{
	int i, j, u, w, x, y, sptr, *d, *p, *S;
	bool *QS;                       // Zbiory Q i S
	slistEl **graf;                 // Tablica list s�siedztwa
	slistEl *pw, *rw;

	// Tworzymy tablice dynamiczne

	d = new int[n];                // Tablica koszt�w doj�cia
	p = new int[n];                // Tablica poprzednik�w
	QS = new bool[n];              // Zbiory Q i S
	graf = new slistEl *[n];       // Tablica list s�siedztwa
	S = new int[n];                // Stos
	sptr = 0;                       // Wska�nik stosu

	// Inicjujemy tablice dynamiczne

	for (i = 0; i < n; i++)
	{
		d[i] = MAX_INT;
		p[i] = -1;
		QS[i] = false;
		graf[i] = NULL;
	}

	// Odczytujemy dane wej�ciowe
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			if (tablica[i][j] != 0)
			{
				pw = new slistEl;
				pw->v = j;
				pw->w = tablica[i][j];
				pw->next = graf[i];
				graf[i] = pw;
			}
	}


	cout << endl;

	d[v] = 0;                       // Koszt doj�cia v jest zerowy

	// Wyznaczamy �cie�ki

	for (i = 0; i < n; i++)
	{
		// Szukamy wierzcho�ka w Q o najmniejszym koszcie d

		for (j = 0; QS[j]; j++);
		for (u = j++; j < n; j++)
			if (!QS[j] && (d[j] < d[u])) u = j;

		// Znaleziony wierzcho�ek przenosimy do S

		QS[u] = true;

		// Modyfikujemy odpowiednio wszystkich s�siad�w u, kt�rzy s� w Q

		for (pw = graf[u]; pw; pw = pw->next)
			if (!QS[pw->v] && (d[pw->v] > d[u] + pw->w))
			{
				d[pw->v] = d[u] + pw->w;
				p[pw->v] = u;
			}
	}

	// Gotowe, wy�wietlamy wyniki

	for (i = 0; i < n; i++)
	{
		cout << i << ": ";

		// �cie�k� przechodzimy od ko�ca ku pocz�tkowi,
		// Zapisuj�c na stosie kolejne wierzcho�ki

		for (j = i; j > -1; j = p[j]) S[sptr++] = j;

		// Wy�wietlamy �cie�k�, pobieraj�c wierzcho�ki ze stosu

		while (sptr) cout << S[--sptr] << " ";

		// Na ko�cu �cie�ki wypisujemy jej koszt

		cout << "$" << d[i] << endl;
	}
	cout << endl;

	// Usuwamy tablice dynamiczne

	delete[] d;
	delete[] p;
	delete[] QS;
	delete[] S;

	for (i = 0; i < n; i++)
	{
		pw = graf[i];
		while (pw)
		{
			rw = pw;
			pw = pw->next;
			delete rw;
		}
	}

	delete[] graf;
}


bool BF(int v)
{
	int i, x;
	bool test;
	slistEl * pv;

	d[v] = 0;                       // Zerujemy koszt doj�cia do v
	for (i = 1; i < n; i++)          // P�tla relaksacji
	{
		test = true;                  // Oznacza, �e algorytm nie wprowadzi� zmian do d i p
		for (x = 0; x < n; x++)        // Przechodzimy przez kolejne wierzcho�ki grafu
			for (pv = A[x]; pv; pv = pv->next) // Przegl�damy list� s�siad�w wierzcho�ka x
				if (d[pv->v] > d[x] + pv->w) // Sprawdzamy warunek relaksacji
				{
					test = false;           // Jest zmiana w d i p
					d[pv->v] = d[x] + pv->w; // Relaksujemy kraw�d� z x do jego s�siada
					p[pv->v] = x;           // Poprzednikiem s�siada b�dzie x
				}
		if (test) return true;         // Je�li nie by�o zmian, to ko�czymy
	}

	// Sprawdzamy istnienie ujemnego cyklu

	for (x = 0; x < n; x++)
		for (pv = A[x]; pv; pv = pv->next)
			if (d[pv->v] > d[x] + pv->w) return false; // ujemny cykl!!

	return true;
}

void ford_bellman_lista(string nazwa_pliku, int v)
{
	int i, x, y, w, sptr, *S;
	slistEl *rv, *pv;
	ifstream dane(nazwa_pliku.c_str());
	dane >> n >> m;             //  liczba wierzcho�k�w i kraw�dzi

	A = new slistEl *[n];          // Tworzymy tablic� list s�siedztwa
	d = new long long[n];          // Tworzymy tablic� koszt�w doj�cia
	p = new int[n];                // Tworzymy tablice poprzednik�w
	for (i = 0; i < n; i++)          // Inicjujemy struktury danych
	{
		d[i] = MAX_INT;
		p[i] = -1;
		A[i] = NULL;
	}

	for (i = 0; i < m; i++)
	{
		dane >> x >> y >> w;           // Czytamy wierzcho�ki kraw�dzi oraz jej wag�
		pv = new slistEl;             // Tworzymy element listy
		pv->v = y;                    // Inicjujemy go
		pv->w = w;
		pv->next = A[x];              // Dodajemy go na pocz�tek listy s�siad�w wierzcho�ka x
		A[x] = pv;
	}

	cout << endl;

	// Wyznaczamy najkr�tsze �cie�ki algorytmem Bellmana-Forda

	if (BF(v))
	{
		S = new int[n];              // Tworzymy prosty stos
		sptr = 0;

		for (i = 0; i < n; i++)
		{
			cout << i << ": ";
			for (x = i; x != -1; x = p[x]) // Wierzcho�ki �cie�ki umieszczamy na stosie
				S[sptr++] = x;            // w kolejno�ci od ostatniego do pierwszego

			while (sptr)                 // Wierzcho�ki ze stosu drukujemy
				cout << S[--sptr] << " "; // w kolejno�ci od pierwszego do ostatniego

			cout << "$" << d[i] << endl; // Na ko�cu wy�wietlamy koszt
		}
		delete[] S;                  // Usuwamy stos
	}
	else cout << "Negative Cycle found!" << endl;

	cout << endl;
	// Usuwamy struktury dynamiczne

	for (i = 0; i < n; i++)
	{
		pv = A[i];
		while (pv)
		{
			rv = pv;
			pv = pv->next;
			delete rv;
		}
	}

	delete[] A;
	delete[] d;
	delete[] p;

	dane.close();
}
void ford_bellman_lista2(string nazwa_pliku, int v)
{
	int i, x, y, w, sptr, *S;
	slistEl *rv, *pv;
	ifstream dane(nazwa_pliku.c_str());
	dane >> n >> m >> pocz;             //  liczba wierzcho�k�w i kraw�dzi

	A = new slistEl *[n];          // Tworzymy tablic� list s�siedztwa
	d = new long long[n];          // Tworzymy tablic� koszt�w doj�cia
	p = new int[n];                // Tworzymy tablice poprzednik�w
	for (i = 0; i < n; i++)          // Inicjujemy struktury danych
	{
		d[i] = MAX_INT;
		p[i] = -1;
		A[i] = NULL;
	}

	for (i = 0; i < m; i++)
	{
		dane >> x >> y >> w;           // Czytamy wierzcho�ki kraw�dzi oraz jej wag�
		pv = new slistEl;             // Tworzymy element listy
		pv->v = y;                    // Inicjujemy go
		pv->w = w;
		pv->next = A[x];              // Dodajemy go na pocz�tek listy s�siad�w wierzcho�ka x
		A[x] = pv;
	}

	cout << endl;

	// Wyznaczamy najkr�tsze �cie�ki algorytmem Bellmana-Forda

	if (BF(v))
	{
		S = new int[n];              // Tworzymy prosty stos
		sptr = 0;

		for (i = 0; i < n; i++)
		{
			cout << i << ": ";
			for (x = i; x != -1; x = p[x]) // Wierzcho�ki �cie�ki umieszczamy na stosie
				S[sptr++] = x;            // w kolejno�ci od ostatniego do pierwszego

			while (sptr)                 // Wierzcho�ki ze stosu drukujemy
				cout << S[--sptr] << " "; // w kolejno�ci od pierwszego do ostatniego

			cout << "$" << d[i] << endl; // Na ko�cu wy�wietlamy koszt
		}
		delete[] S;                  // Usuwamy stos
	}
	else cout << "Negative Cycle found!" << endl;

	cout << endl;
	// Usuwamy struktury dynamiczne

	for (i = 0; i < n; i++)
	{
		pv = A[i];
		while (pv)
		{
			rv = pv;
			pv = pv->next;
			delete rv;
		}
	}

	delete[] A;
	delete[] d;
	delete[] p;

	dane.close();
}
void ford_bellman_macierz(int v)
{
	int i, j, x, y, w, sptr, *S;
	slistEl *rv, *pv;


	A = new slistEl *[n];          // Tworzymy tablic� list s�siedztwa
	d = new long long[n];          // Tworzymy tablic� koszt�w doj�cia
	p = new int[n];                // Tworzymy tablice poprzednik�w
	for (i = 0; i < n; i++)          // Inicjujemy struktury danych
	{
		d[i] = MAX_INT;
		p[i] = -1;
		A[i] = NULL;
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			if (tablica[i][j] != 0)
			{
				pv = new slistEl;
				pv->v = j;
				pv->w = tablica[i][j];
				pv->next = A[i];
				A[i] = pv;
			}
	}

	cout << endl;

	// Wyznaczamy najkr�tsze �cie�ki algorytmem Bellmana-Forda

	if (BF(v))
	{
		S = new int[n];              // Tworzymy prosty stos
		sptr = 0;

		for (i = 0; i < n; i++)
		{
			cout << i << ": ";
			for (x = i; x != -1; x = p[x]) // Wierzcho�ki �cie�ki umieszczamy na stosie
				S[sptr++] = x;            // w kolejno�ci od ostatniego do pierwszego

			while (sptr)                 // Wierzcho�ki ze stosu drukujemy
				cout << S[--sptr] << " "; // w kolejno�ci od pierwszego do ostatniego

			cout << "$" << d[i] << endl; // Na ko�cu wy�wietlamy koszt
		}
		delete[] S;                  // Usuwamy stos
	}
	else cout << "Znaleziono cykl negatywny!" << endl;

	// Usuwamy struktury dynamiczne

	for (i = 0; i < n; i++)
	{
		pv = A[i];
		while (pv)
		{
			rv = pv;
			pv = pv->next;
			delete rv;
		}
	}

	delete[] A;
	delete[] d;
	delete[] p;

}
void ford_bellman_macierz2(int v)
{
	int i, j, x, y, w, sptr, *S;
	slistEl *rv, *pv;


	A = new slistEl *[n];          // Tworzymy tablic� list s�siedztwa
	d = new long long[n];          // Tworzymy tablic� koszt�w doj�cia
	p = new int[n];                // Tworzymy tablice poprzednik�w
	for (i = 0; i < n; i++)          // Inicjujemy struktury danych
	{
		d[i] = MAX_INT;
		p[i] = -1;
		A[i] = NULL;
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			if (tablica[i][j] != 0)
			{
				pv = new slistEl;
				pv->v = j;
				pv->w = tablica[i][j];
				pv->next = A[i];
				A[i] = pv;
			}
	}

	cout << endl;

	// Wyznaczamy najkr�tsze �cie�ki algorytmem Bellmana-Forda

	if (BF(v))
	{
		S = new int[n];              // Tworzymy prosty stos
		sptr = 0;

		for (i = 0; i < n; i++)
		{
			cout << i << ": ";
			for (x = i; x != -1; x = p[x]) // Wierzcho�ki �cie�ki umieszczamy na stosie
				S[sptr++] = x;            // w kolejno�ci od ostatniego do pierwszego

			while (sptr)                 // Wierzcho�ki ze stosu drukujemy
				cout << S[--sptr] << " "; // w kolejno�ci od pierwszego do ostatniego

			cout << "$" << d[i] << endl; // Na ko�cu wy�wietlamy koszt
		}
		delete[] S;                  // Usuwamy stos
	}
	else cout << "Znaleziono cykl negatywny!" << endl;

	// Usuwamy struktury dynamiczne

	for (i = 0; i < n; i++)
	{
		pv = A[i];
		while (pv)
		{
			rv = pv;
			pv = pv->next;
			delete rv;
		}
	}

	delete[] A;
	delete[] d;
	delete[] p;

}


int lista_generacja(int c, double e)
{
	int krawedzie;
	srand(time(NULL));
	krawedzie = ((c*(c - 1)) / 2);
	krawedzie = krawedzie*e;

	int i, v1, v2, v3 = 0, v4 = 0, waga;
	slistEl *p, *r;
	n = c;
	m = krawedzie;
	ofstream random("random.txt");
	random << c << " " << m << endl;

	A = new slistEl *[n]; // Tworzymy tablic� list s�siedztwa

	// Tablic� wype�niamy pustymi listami

	for (i = 0; i < n; i++) A[i] = NULL;

	// Odczytujemy kolejne definicje kraw�dzi
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) tablica[i][j] = 0;

	for (i = 0; i < m; i++)
	{
		v1 = rand() % (c);
		v2 = rand() % (c);
		if (v1 != v2 && tablica[v1][v2] != 1)
		{
			if (v1 != v3 || v2 != v4)
			{
				waga = (rand() % 10) + 1;
				p = new slistEl;    // Tworzymy nowy element
				p->v = v2;          // Numerujemy go jako v2
				p->next = A[v1];    // Dodajemy go na pocz�tek listy A[v1]
				A[v1] = p;
				random << v1 << " " << v2 << " " << waga << endl;
				tablica[v1][v2] = 1;
			}
		}
		else
		{
			i--;
		}
		v3 = v1;
		v4 = v2;
	}

	cout << endl;

	// Wypisujemy zawarto�� tablicy list s�siedztwa

	for (i = 0; i < n; i++)
	{
		cout << "A[" << i << "] =";
		p = A[i];
		while (p)
		{
			cout << setw(3) << p->v;
			p = p->next;
		}
		cout << endl;
	}

	// Usuwamy tablic� list s�siedztwa

	for (i = 0; i < n; i++)
	{
		p = A[i];
		while (p)
		{
			r = p;
			p = p->next;
			delete r;
		}
	}
	delete[] A;
	random.close();
	return 0;
	cout << endl;
}

class stack
{
private:
	slistEl * S;   // lista przechowuj�ca stos

public:
	stack();       // konstruktor
	~stack();      // destruktor
	bool empty(void);
	int  top(void);
	void push(int v);
	void pop(void);
};

//---------------------
// Metody obiektu stack
//---------------------

// Konstruktor
//------------
stack::stack()
{
	S = NULL;
}

// Destruktor - zwalnia tablic� dynamiczn�
//----------------------------------------
stack::~stack()
{
	while (S) pop();
}

// Sprawdza, czy stos jest pusty
//------------------------------
bool stack::empty(void)
{
	return !S;
}

// Zwraca szczyt stosu
//--------------------
int stack::top(void)
{
	return S->v;
}

// Zapisuje na stos
//-----------------
void stack::push(int v)
{
	slistEl * e = new slistEl;
	e->v = v;
	e->next = S;
	S = e;
}

// Usuwa ze stosu
//---------------
void stack::pop(void)
{
	if (S)
	{
		slistEl * e = S;
		S = S->next;
		delete e;
	}
}


void spojnosc()
{
	int n, m;        // Liczba wierzcho�k�w i kraw�dzi
	slistEl ** A;   // Tablica list s�siedztwa grafu
	bool * visited; // Tablica odwiedzin
	stack S;        // Stos
	int i, v, u, vc, waga;
	slistEl *p, *r;
	ifstream random("random.txt");
	random >> n >> m;             // Odczytujemy liczb� wierzcho�k�w i kraw�dzi

	A = new slistEl *[n];     // Tworzymy tablice dynamiczne
	visited = new bool[n];

	// Inicjujemy tablice

	for (i = 0; i < n; i++)
	{
		A[i] = NULL;
		visited[i] = false;
	}

	// Odczytujemy kolejne definicje kraw�dzi.

	for (i = 0; i < m; i++)
	{
		random >> v >> u >> waga;           // Wierzcho�ki tworz�ce kraw�d�
		p = new slistEl;         // Tworzymy nowy element
		p->v = u;                // Numerujemy go jako w
		p->next = A[v];          // Dodajemy go na pocz�tek listy A[v]
		A[v] = p;
		p = new slistEl;         // To samo dla kraw�dzi w drug� stron�
		p->v = v;
		p->next = A[u];
		A[u] = p;
	}

	// Badamy sp�jno�� grafu

	vc = 0;                    // Zerujemy licznik wierzcho�k�w

	S.push(0);                 // Wierzcho�ek startowy na stos
	visited[0] = true;         // Oznaczamy go jako odwiedzony

	while (!S.empty())          // Wykonujemy przej�cie DFS
	{
		v = S.top();             // Pobieramy wierzcho�ek ze stosu
		S.pop();                 // Pobrany wierzcho�ek usuwamy ze stosu
		vc++;                    // Zwi�kszamy licznik wierzcho�k�w
		for (p = A[v]; p; p = p->next) // Przegl�damy s�siad�w
		{
			u = p->v;
			if (!visited[u])        // Szukamy wierzcho�k�w nieodwiedzonych
			{
				visited[u] = true;   // Oznaczamy wierzcho�ek jako odwiedzony
				S.push(u);           // i umieszczamy go na stosie
			}
		}
	}

	// Wy�wietlamy wyniki

	cout << endl;

	if (vc == n) cout << "GRAF SPOJNY"; else cout << "GRAF NIESPOJNY";

	cout << endl;

	// Usuwamy tablice dynamiczne

	for (i = 0; i < n; i++)
	{
		p = A[i];
		while (p)
		{
			r = p;
			p = p->next;
			delete r;
		}
	}

	delete[] A;
	delete[] visited;

}


int main()
{
	bool f = true;
	int a, v;
	int c;
	double e;
	string nazwa_pliku;
	while (f == true)
	{
		cout << "1. Wczytaj z pliku\n2. Wygeneruj losowo\n3. Wyswietl listowo i macierzowo\n4. Algorytm Kruskala (listowo)\n5. Algorytm Kruskala (macierzowo)\n6. Algorytm Prima (listowo)";
		cout << "\n7. Algorytm Prima (macierzowo)\n8. Algorytm Dijkstry (listowo)\n9. Algorytm Dijkstry (macierzowo)\n10. Algorytm Forda-Bellmana (listowo)\n11. Algorytm Forda-Bellmana (macierzowo)\n\n";
		cout << "12. Wczytaj z pliku(wierzcholek pocz) \n13.Algorytm Dijkstry(listowo)(wierzcholek pocz)\n14.Algorytm Dijkstry(macierzowo)(wierzcholek pocz)\n15.Algorytm Forda - Bellmana(listowo)(wierzcholek pocz)\n16.Algorytm Forda - Bellmana(macierzowo)(wierzcholek pocz)\n\n17. Zakoncz" << endl;
		cin >> a;
		cout << endl;
		switch (a)
		{
		case 1:
			cout << "Podaj nazwe pliku" << endl;
			cin >> nazwa_pliku;
			StartCounter();
			macierz_sasiedztwa(nazwa_pliku);
			lista_sasiedztwa(nazwa_pliku);
			cout << "Czas operacji: " << GetCounter() << " ms" << "\n\n";
			break;
		case 2:
			cout << "Podaj liczbe wierzcholkow i gestosc: ";
			cin >> c >> e;
			StartCounter();
			lista_generacja(c, e);
			nazwa_pliku = "random.txt";
			macierz_sasiedztwa(nazwa_pliku);
			cout << "Czas operacji: " << GetCounter() << " ms" << "\n\n";
			spojnosc();
			break;
		case 3:
			if (nazwa_pliku != "")
			{
				wypisz_macierz();
				lista_sasiedztwa(nazwa_pliku);
			}
			break;
		case 4:
			if (nazwa_pliku != "")
			{
				StartCounter();
				kruskal_lista(nazwa_pliku);
				cout << "Czas operacji: " << GetCounter() << " ms" << "\n\n";
			}
			break;
		case 5:
			if (nazwa_pliku != "")
			{
				StartCounter();
				kruskal_macierz();
				cout << "Czas operacji: " << GetCounter() << " ms" << "\n\n";
			}
			break;
		case 6:
			if (nazwa_pliku != "")
			{
				StartCounter();
				prim_lista(nazwa_pliku);
				cout << "Czas operacji: " << GetCounter() << " ms" << "\n\n";
			}
			break;
		case 7:
			if (nazwa_pliku != "")
			{
				StartCounter();
				prim_macierz();
				cout << "Czas operacji: " << GetCounter() << " ms" << "\n\n";
			}
			break;
		case 8:
			if (nazwa_pliku != "")
			{
				cout << "Podaj wezel startowy" << endl;
				cin >> v;
				StartCounter();
				dijkstra_lista(nazwa_pliku, v);
				cout << "Czas operacji: " << GetCounter() << " ms" << "\n\n";
			}
			break;
		case 9:
			if (nazwa_pliku != "")
			{
				cout << "Podaj wezel startowy" << endl;
				cin >> v;
				StartCounter();
				dijkstra_macierz(v);
				cout << "Czas operacji: " << GetCounter() << " ms" << "\n\n";
			}
			break;
		case 10:
			if (nazwa_pliku != "")
			{
				cout << "Podaj wezel startowy" << endl;
				cin >> v;
				StartCounter();
				ford_bellman_lista(nazwa_pliku, v);
				cout << "Czas operacji: " << GetCounter() << " ms" << "\n\n";
			}
			break;
		case 11:
			if (nazwa_pliku != "")
			{
				cout << "Podaj wezel startowy" << endl;
				cin >> v;
				StartCounter();
				ford_bellman_macierz(v);
				cout << "Czas operacji: " << GetCounter() << " ms" << "\n\n";
			}
			break;
		case 17:
			f = false;
			break;
		case 12:
			cout << "Podaj nazwe pliku" << endl;
			cin >> nazwa_pliku;
			StartCounter();
			macierz_sasiedztwa2(nazwa_pliku);
			lista_sasiedztwa2(nazwa_pliku);
			cout << "Czas operacji: " << GetCounter() << " ms" << "\n\n";
			break;
		case 13:
			StartCounter();
			dijkstra_lista2(nazwa_pliku, pocz);
			cout << "Czas operacji: " << GetCounter() << " ms" << "\n\n";
			break;
		case 14:
			StartCounter();
			dijkstra_macierz2(pocz);
			cout << "Czas operacji: " << GetCounter() << " ms" << "\n\n";
			break;
		case 15:
			StartCounter();
			ford_bellman_lista2(nazwa_pliku, pocz);
			cout << "Czas operacji: " << GetCounter() << " ms" << "\n\n";
			break;
		case 16:
			StartCounter();
			ford_bellman_macierz2(pocz);
			cout << "Czas operacji: " << GetCounter() << " ms" << "\n\n";
			break;
		
}
	}
	return 0;
}
