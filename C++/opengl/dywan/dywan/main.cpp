//Zalaczenie plikow naglowkowych
#include <windows.h>
#include <stdlib.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <time.h>
#include "Square.h"

//Parametry programu
float verLength = 200.0;	//Dlugosc boku kwadratu
int density = 4;			//Gestosc dywanu(liczba podzialow)
int phaseBase = 30;			//Podstawa fazy(przesuniec)

//Punkt poczatkowy rysowania
point2 startPoint = { (float)-1 * verLength / 2, (float)verLength / 2 };

//Funkcja generujaca i renderujaca dywan sierpinskiego
void RenderCarpet(int density, int phaseBase)
{
	//Obliczenie  nowej dlugosci krawedzi
	verLength = verLength / 3;
	for (int i = 0; i<3; i++) {
		if (density - 1 != 0){
			RenderCarpet(density - 1, phaseBase);
			startPoint[0] = startPoint[0] - verLength;
		}
		else
		{
			Square *qd = new Square(startPoint, verLength, (float)((rand() % 20 + 1) - 10) / phaseBase*verLength);
			qd->Render();
		}
		for (int j = 0; j<2; j++) {
			startPoint[1] = startPoint[1] - verLength;
			if (i != 1 || j != 0){
				if (density - 1 != 0){
					RenderCarpet(density - 1, phaseBase);
					startPoint[0] = startPoint[0] - verLength;
				}
				else
				{
					Square *qd = new Square(startPoint, verLength, (float)((rand() % 20 + 1) - 10) / phaseBase*verLength);
					qd->Render();
				}
			}
		}
		startPoint[0] = startPoint[0] + verLength;
		startPoint[1] = startPoint[1] + 2 * verLength;
	}
	verLength = verLength * 3;
	density = density + 1;
}

//Funkcja okreslajaca, co ma byc rysowane
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	RenderCarpet(density, phaseBase);
	glFlush();

	startPoint[0] = (float)-1 * verLength / 2;
	startPoint[1] = (float)verLength / 2;
}

// Funkcja sluzaca do kontroli zachowania proporcji rysowanych obiektow
//Niezaleznie od rozmiarow okna graficznego
void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	GLfloat AspectRatio; // Deklaracja zmiennej AspectRatio okreœlaj¹cej proporcjê wymiarów okna

	if (vertical == 0) // Zabezpieczenie pzred dzieleniem przez 0
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

	glLoadIdentity(); // Okreœlenie uk³adu wspó³rzêdnych
}

//Funkcja ustalajaca stan renderowania
void MyInit(void)
{
	//Kolor wnêtrza okna
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

//Glowna funkcja programu
void main(void)
{
	//Ziarno losowosci
	srand((unsigned)time(NULL));

	// Ustawienie trybu wyswietlania
	// GLUT_SINGLE - pojedynczy bufor wyswietlania
	// GLUT_RGBA - model kolorów RGB
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	//Ustawienie rozmiaru okna
	glutInitWindowSize(800, 600);

	//Stworzenie okna i nadanie tytulu
	glutCreateWindow("Dywan Sierpiñskiego");

	//Przypisanie glownej funkcji renderowania
	glutDisplayFunc(RenderScene);

	//Przypisanie funkcji wywolywanej przy zmianie rozmiaru okna
	glutReshapeFunc(ChangeSize);

	//Wywolanie funkcji ustalajacej stan renderowania
	MyInit();

	//Wywolanie funkcji uruchamiajacej szkielet biblioteki GLUT
	glutMainLoop();
}