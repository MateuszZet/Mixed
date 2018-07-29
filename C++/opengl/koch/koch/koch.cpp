//Zalaczenie plikow naglowkowych
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>

//Definicja typu point2
typedef float point2[2];

//Stala - pi
const float PI = 3.14159265;

//Parametry programu
int level = 8;				//Stopieñ zagnie¿d¿enia(ilosc rekurencji)
float verLength = 125;	//Dlugosc krawedzi trojkata rownobocznego
float lineWidth = 2;		//Szerokosc linii

//Punkt poczatkowy rysowania
point2 startPoint = { (float)-1 * verLength / 2, (float)-0.7*verLength / 2 };

//Funkcja renderujaca krzywa Kocha
void KochCurve(float angle, float len, int n)
{
	//Aktualny punktu
	point2 curPoint;

	//Stopnie na radiany
	float angleRad = (float)PI / 180 * angle;
	curPoint[0] = startPoint[0] + len * cos(angleRad);
	curPoint[1] = startPoint[1] + len * sin(angleRad);

	if (n == 0)
	{
		//Rysowanie linii
		glVertex2fv(startPoint);
		glVertex2fv(curPoint);
		startPoint[0] = curPoint[0];
		startPoint[1] = curPoint[1];
	}
	else
	{
		n--;          //Dekrementacja poziomu
		len /= 3.0;   //Zmniejszenie dlugosci
		KochCurve(angle, len, n);

		angle += 60.0;
		KochCurve(angle, len, n);

		angle -= 120.0;
		KochCurve(angle, len, n);

		angle += 60.0;
		KochCurve(angle, len, n);
	}
}

//Funkcja renderujaca platek sniegu Kocha
void RenderKochSnowFlake(int level)
{
	glBegin(GL_LINES);
	//Krzywa pod kontem 60 stopni
	KochCurve(60.0, verLength, level);
	//Przeliczenie wspolrzednych i krzywa
	startPoint[0] = ((float)-1 * verLength / 2) + verLength*0.5;
	startPoint[1] = ((float)-0.7*verLength / 2) + verLength*sqrt(3.0) / 2.0;
	KochCurve(-60.0, verLength, level);
	//Przeliczenie wspolrzednych i krzywa
	//startPoint[0] = ((float)-1 * verLength / 2) + verLength;
	//startPoint[1] = ((float)-0.7*verLength / 2);
	//KochCurve(-180.0, verLength, level);
	glEnd();
}

//Funkcja renderujaca jedna krzywa Kocha
void RenderKochCurve(int level)
{
	glBegin(GL_LINES);
	KochCurve(0.0, verLength, level);
	glEnd();
}

//Funkcja okreslajaca, co ma byc rysowane
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	RenderKochSnowFlake(level);
	glColor3f(1.0f, 1.0f, 1.0f);
	// Ustawienie aktualnego koloru rysowania na bialy

	glRectf(-80.0f, 0.0f, 80.0f, -80.0f);
	glEnd;
	// Narysowanie prostok¹ta
	//RenderKochCurve(level);
	glFlush();
}

// Funkcja sluzaca do kontroli zachowania proporcji rysowanych obiektow
//Niezaleznie od rozmiarow okna graficznego
void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	GLfloat AspectRatio; // Deklaracja zmiennej AspectRatio okreœlaj¹cej proporcjê wymiarów okna

	if (vertical == 0) // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;

	glViewport(0, 0, horizontal, vertical); // Ustawienie wielkoœciokna okna urz¹dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);			// Okreœlenie uk³adu wspó³rzêdnych obserwatora
	glLoadIdentity();						// Okreœlenie przestrzeni ograniczaj¹cej
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;	// Wyznaczenie wspó³czynnika proporcji okna
	// Do okreœlenia okna obserwatora s³u¿y funkcja glOrtho(...)

	if (horizontal <= vertical)
		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity(); //Okreœlenie uk³adu wspó³rzêdnych
}

//Funkcja ustalajaca stan renderowania
void MyInit(void)
{
	//Kolor wnêtrza okna
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glLineWidth(lineWidth);
}

//Glowna funkcja programu
void main(void)
{
	// Ustawienie trybu wyswietlania
	// GLUT_SINGLE - pojedynczy bufor wyswietlania
	// GLUT_RGBA - model kolorów RGB
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	//Ustawienie rozmiaru okna
	glutInitWindowSize(800, 600);

	//Stworzenie okna i nadanie tytulu
	glutCreateWindow("Platek sniegu kocha");

	//Przypisanie glownej funkcji renderowania
	glutDisplayFunc(RenderScene);

	//Przypisanie funkcji wywolywanej przy zmianie rozmiaru okna
	glutReshapeFunc(ChangeSize);

	//Wywolanie funkcji ustalajacej stan renderowania
	MyInit();

	//Wywolanie funkcji uruchamiajacej szkielet biblioteki GLUT
	glutMainLoop();
}