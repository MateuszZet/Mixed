#include <iostream>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include<string>
using namespace std;
double PCFreq = 0.0; 											// zmienne do licznika czasu operacji
__int64 CounterStart = 0;
const int MAX_INT = 2147483647;

// Zmienne globalne

int n,m,v0,d,dh,sptr,shptr;
bool **A;                         // Macierz s¹siedztwa
int **W;                          // Macierz wag krawêdzi
int *S,*Sh;                       // Stosy w tablicy
bool *visited;                    // Tablica odwiedzin

// Rekurencyjna procedura poszukiwania cyklu Hamiltona
// o najmniejszej sumie wag krawêdzi
// v - wierzcho³ek bie¿¹cy
//----------------------------------------------------
void StartCounter() 											// funkcja liczaca czas trwania operacji
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
	cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter() 											// funkcja zwracaja czas zliczony od rozpoczecia licznika
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}
void TSP(int v)
{
  int u;

  Sh[shptr++] = v;                // zapamiêtujemy na stosie bie¿¹cy wierzcho³ek

  if(shptr < n)                   // jeœli brak œcie¿ki Hamiltona, to jej szukamy
  {
    visited[v] = true;            // Oznaczamy bie¿¹cy wierzcho³ek jako odwiedzony
    for(u = 0; u < n; u++)        // Przegl¹damy s¹siadów wierzcho³ka v
      if(A[v][u] && !visited[u])  // Szukamy nieodwiedzonego jeszcze s¹siada
      {
        dh += W[v][u];            // Dodajemy wagê krawêdzi v-u do sumy
        TSP(u);                   // Rekurencyjnie wywo³ujemy szukanie cyklu Hamiltona
        dh -= W[v][u];            // Usuwamy wagê krawêdzi z sumy
      }
    visited[v] = false;           // Zwalniamy bie¿¹cy wierzcho³ek
  }
  else if(A[v0][v])               // Jeœli znaleziona œcie¿ka jest cyklem Hamiltona
  {
    dh += W[v][v0];               // to sprawdzamy, czy ma najmniejsz¹ sumê wag
    if(dh < d)                    // Jeœli tak,
    {
      d = dh;                     // To zapamiêtujemy tê sumê
      for(u = 0; u < shptr; u++)  // oraz kopiujemy stos Sh do S
        S[u] = Sh[u];
      sptr = shptr;
    }
    dh -= W[v][v0];               // Usuwamy wagê krawêdzi v-v0 z sumy
  }
  shptr--;                        // Usuwamy bie¿¹cy wierzcho³ek ze œcie¿ki
}

void komiwojazerplik()
{
  int i,j,x,y,z;
  string text;
  cout << "Podaj nazwe pliku: " << endl;
  cin >> text;
  ifstream dane(text);
	dane>>n>>m;

  // Tworzymy struktury dynamiczne i inicjujemy je

  S       = new int [n];
  Sh      = new int [n];
  visited = new bool [n];
  A       = new bool * [n];
  W       = new int * [n];
  for(i = 0; i < n; i++)
  {
    A[i] = new bool [n];
    W[i] = new int [n];
    for(j = 0; j < n; j++)
    {
      A[i][j] = false;
      W[i][j] = 0;
    }
    visited[i] = false;
  }
  sptr = shptr = 0;
  

  // Odczytujemy dane wejœciowe

  for(i = 0; i < m; i++)
  {
    dane >> x >> y >> z;
    A[x][y] = A[y][x] = true;     // KrawêdŸ x-y
    W[x][y] = W[y][x] = z;        // Waga krawêdzi x-y
  }

  cout << endl;

  // Rozpoczynamy algorytm

  d  = MAX_INT;
  dh = v0 = 0;
  TSP(v0);
  if(sptr)
  {
    for(i = 0; i < sptr; i++) cout << S[i] << " ";
    cout << v0 << endl;
    cout << "d = " << d << endl;
  }
  else cout << "NO HAMILTONIAN CYCLE" << endl;

  cout << endl;

  // Usuwamy tablice dynamiczne

  delete [] S;
  delete [] Sh;
  delete [] visited;

  for(i = 0; i < n; i++)
  {
    delete [] A[i];
    delete [] W[i];
  }

  delete [] A;
  delete [] W;
	dane.close();
} 

void komiwojazer()
{
  int i,j,x,y,z,pomoc=0;
  srand( time( NULL ) );
	cout<<"Wprowadz ilosc miast"<<endl;
	cin>>n;
	StartCounter();
	m=n*(n-1)/2;
	

  // Tworzymy struktury dynamiczne i inicjujemy je

  S       = new int [n];
  Sh      = new int [n];
  visited = new bool [n];
  A       = new bool * [n];
  W       = new int * [n];
  for(i = 0; i < n; i++)
  {
    A[i] = new bool [n];
    W[i] = new int [n];
    for(j = 0; j < n; j++)
    {
      A[i][j] = false;
      W[i][j] = 0;
    }
    visited[i] = false;
  }
  sptr = shptr = 0;
    
  for(i=0;i<m;i++)
  {
  	for(j=1+pomoc;j<n;j++)
  	{
  	x=i;
  	y=j;
  	z=(rand() % 10)+1;
  	A[x][y] = A[y][x] = true;     // KrawêdŸ x-y
    W[x][y] = W[y][x] = z;        // Waga krawêdzi x-y
  	}
  	pomoc++;
  }



  cout << endl;

  // Rozpoczynamy algorytm

  d  = MAX_INT;
  dh = v0 = 0;
  TSP(v0);
  if(sptr)
  {
    for(i = 0; i < sptr; i++) cout << S[i] << " ";
    cout << v0 << endl;
    cout << "d = " << d << endl;
  }
  else cout << "NO HAMILTONIAN CYCLE" << endl;

  cout << endl;

  // Usuwamy tablice dynamiczne

  delete [] S;
  delete [] Sh;
  delete [] visited;

  for(i = 0; i < n; i++)
  {
    delete [] A[i];
    delete [] W[i];
  }

  delete [] A;
  delete [] W;
}
void problem_plecakowy_gotowy()
{
int x,i,j,k=0,*orginalny,*wynik,*aktualny,wynikow;
float *waga,*wartosc,*stosunki,tmp=0,maxWaga,maxWartosc=0,plecak=0,limit;
string kkk;
cout << "Podaj nazwe pliku: " << endl;
cin >> plecak;
ifstream plec(kkk);
plec>>limit;
plec>>x;

waga=new float[x];
wartosc=new float[x];
stosunki=new float[x];
wynik=new int[x];
aktualny=new int[x];
orginalny=new int[x];

cout<<endl;

for(i=0;i<x;i++)
{
                plec>>waga[i];
                plec>>wartosc[i];
                stosunki[i]=wartosc[i]/waga[i];
                orginalny[i]=i;
                }

for(i=0;i<x-1;i++)
{
                  for(j=0;j<x-i-1;j++)
                  {
                                      if(stosunki[j]<stosunki[j+1])
                                      {
                                                                   swap(stosunki[j],stosunki[j+1]);
                                                                   swap(waga[j],waga[j+1]);
                                                                   swap(wartosc[j],wartosc[j+1]);
                                                                   swap(orginalny[j],orginalny[j+1]);
                                                                   }
                                      }
                  }

for(i=0;i<x;i++)
{
                  if(waga[i]>limit)
                  continue;
                  plecak=waga[i];
                  tmp=wartosc[i];
                  aktualny[k]=orginalny[i]+1;
                  k++;
                  j=i+1;
                  while(j<x&&plecak+waga[j]<=limit)
                  {
                                                    plecak+=waga[j];
                                                    tmp+=wartosc[j];
                                                    aktualny[k]=orginalny[j]+1;
                                                    k++;
                                                    j++;
                                                    }
                  if(tmp>maxWartosc)
                  {
                                    maxWaga=plecak;
                                    maxWartosc=tmp;
                                    wynikow=k;
                                    while(k>0)
                                    {
                                                   wynik[k-1]=aktualny[k-1];
                                                   k--;
                                                   }
                                    }
                  k=0;
                  }

cout<<"\nWartosc plecaka: "<<maxWartosc<<endl;
cout<<"\nWaga plecaka: "<<maxWaga<<"\nNumery przedmiotow w plecaku: \n";
for(i=0;i<wynikow;i++)
{
                      cout<<wynik[i];
                      if(i<wynikow-1)
                      cout<<",";
                      }

cout<<"\n";
plec.close();
}
void problem_plecakowy()
{
int x,i,j,k=0,*orginalny,*wynik,*aktualny,wynikow;
float *waga,*wartosc,*stosunki,tmp=0,maxWaga,maxWartosc=0,plecak=0,limit;

cout<<"\nPodaj ilosc rzeczy: ";
cin>>x;
cout<<"\nPodaj wielkosc plecaka: ";
cin>>limit;

waga=new float[x];
wartosc=new float[x];
stosunki=new float[x];
wynik=new int[x];
aktualny=new int[x];
orginalny=new int[x];

cout<<endl;

for(i=0;i<x;i++)
{
                cout<<"\nPodaj wage rzeczy nr "<<i+1<<": ";
                cin>>waga[i];
                cout<<"\nPodaj wartosc rzeczy nr "<<i+1<<": ";
                cin>>wartosc[i];
                stosunki[i]=wartosc[i]/waga[i];
                orginalny[i]=i;
                }
StartCounter();
for(i=0;i<x-1;i++)
{
                  for(j=0;j<x-i-1;j++)
                  {
                                      if(stosunki[j]<stosunki[j+1])
                                      {
                                                                   swap(stosunki[j],stosunki[j+1]);
                                                                   swap(waga[j],waga[j+1]);
                                                                   swap(wartosc[j],wartosc[j+1]);
                                                                   swap(orginalny[j],orginalny[j+1]);
                                                                   }
                                      }
                  }

for(i=0;i<x;i++)
{
                  if(waga[i]>limit)
                  continue;
                  plecak=waga[i];
                  tmp=wartosc[i];
                  aktualny[k]=orginalny[i]+1;
                  k++;
                  j=i+1;
                  while(j<x&&plecak+waga[j]<=limit)
                  {
                                                    plecak+=waga[j];
                                                    tmp+=wartosc[j];
                                                    aktualny[k]=orginalny[j]+1;
                                                    k++;
                                                    j++;
                                                    }
                  if(tmp>maxWartosc)
                  {
                                    maxWaga=plecak;
                                    maxWartosc=tmp;
                                    wynikow=k;
                                    while(k>0)
                                    {
                                                   wynik[k-1]=aktualny[k-1];
                                                   k--;
                                                   }
                                    }
                  k=0;
                  }

cout<<"\nWartosc plecaka: "<<maxWartosc<<endl;
cout<<"\nWaga plecaka: "<<maxWaga<<"\nNumery przedmiotow w plecaku: \n";
for(i=0;i<wynikow;i++)
{
                      cout<<wynik[i];
                      if(i<wynikow-1)
                      cout<<",";
                      }

cout<<"\n";
}
void generuj()
{
	srand( time( NULL ) );
	int y,x;
	cout<<"Wprowadz wielkosc plecaka: "<<endl;
	cin>>y;
	cout<<"Wprowadz ilosc przedmiotow: "<<endl;
	cin>>x;
	ofstream plecak("plecak.txt");
	plecak<<y<<" "<<x<<endl;
	for(int i=0;i<x;i++)
	{
		plecak<<(rand() % 20)+1<<" "<<(rand() % 10)+1<<endl;
	}
	plecak.close();
}
int main()
{
	bool f=true;
	int a,b,c;
	while(f==true)
	{
		cout<<"1. Problem Plecakowy\n2. Problem Komiwojazera\n3. Zakoncz"<<endl;
		cin>>a;
		cout<<endl;
		switch(a)
		{
			case 1:
				cout<<"1. Wczytaj z pliku\n2. Wprowadz wartosci\n3. Wygeneruj plecak\n4. Powrot"<<endl;
				cin>>c;
				switch(c)
				{
					case 1:
						StartCounter();
						problem_plecakowy_gotowy();
						cout << "Czas operacji: "<< GetCounter() <<" ms"<<"\n\n";
						break;
					case 2:
						problem_plecakowy();
						cout << "Czas operacji: "<< GetCounter() <<" ms"<<"\n\n";
						break;
					case 3:
						generuj();
						break;
					case 4:
						break;
				}				
				break;
			case 2:
				cout<<"1. Wczytaj z pliku\n2. Wygeneruj\n3. Powrot"<<endl;
				cin>>b;
				switch(b)
				{
					case 1:
						StartCounter();
						komiwojazerplik();
						cout << "Czas operacji: "<< GetCounter() <<" ms"<<"\n\n";
						break;
					case 2:
						komiwojazer();
						cout << "Czas operacji: "<< GetCounter() <<" ms"<<"\n\n";
						break;
					case 3:
						break;
				}
				break;
			case 3:
				f=false;
				break;
		}
	}
}
