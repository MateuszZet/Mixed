#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <ctime>
/*************************************************************************************/
typedef float point2[2];
int rysuj(point2 p1, point2 p2, point2 p3, point2 p4, int counter)
{
	counter--;
	return 0;
}
// Funkcaja okre�laj�ca, co ma by� rysowane 
// (zawsze wywo�ywana, gdy trzeba przerysowa� scen�)


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym
	
	srand(time(NULL));
	//1
	point2 p1 = { 0 + (rand() % 5) + 1, 0 + (rand() % 5) + 1 };
	point2 p2 = { 0 + (rand() % 5) + 1, 50 + (rand() % 5) + 1 };
	point2 p3 = { 50 + (rand() % 5) + 1, 50 + (rand() % 5) + 1 };
	point2 p4 = { 50 + (rand() % 5) + 1, 0 + (rand() % 5) + 1 };
	//2
	point2 p5 = { 50 + (rand() % 5) + 1, 0 + (rand() % 5) + 1 };
	point2 p6 = { 50 + (rand() % 5) + 1, 50 + (rand() % 5) + 1 };
	point2 p7 = { 100 + (rand() % 5) + 1, 50 + (rand() % 5) + 1 };
	point2 p8 = { 100 + (rand() % 5) + 1, 0 + (rand() % 5) + 1 };
	//3
	point2 p9 = { 100 + (rand() % 5) + 1, 0 + (rand() % 5) + 1 };
	point2 p10 = { 100 + (rand() % 5) + 1, 50 + (rand() % 5) + 1 };
	point2 p11 = { 150 + (rand() % 5) + 1, 50 + (rand() % 5) + 1 };
	point2 p12 = { 150 + (rand() % 5) + 1, 0 + (rand() % 5) + 1 };
	//4
	point2 p13 = { 0 + (rand() % 5) + 1, 50 + (rand() % 5) + 1 };
	point2 p14 = { 0 + (rand() % 5) + 1, 100 + (rand() % 5) + 1 };
	point2 p15 = { 50 + (rand() % 5) + 1, 100 + (rand() % 5) + 1 };
	point2 p16 = { 50 + (rand() % 5) + 1, 50 + (rand() % 5) + 1 };
	//5
	point2 p17 = { 0 + (rand() % 5) + 1, 100 + (rand() % 5) + 1 };
	point2 p18 = { 0 + (rand() % 5) + 1, 150 + (rand() % 5) + 1 };
	point2 p19 = { 50 + (rand() % 5) + 1, 150 + (rand() % 5) + 1 };
	point2 p20 = { 50 + (rand() % 5) + 1, 100 + (rand() % 5) + 1 };
	//6
	point2 p21 = { 50 + (rand() % 5) + 1, 100 + (rand() % 5) + 1 };
	point2 p22 = { 50 + (rand() % 5) + 1, 150 + (rand() % 5) + 1 };
	point2 p23 = { 100 + (rand() % 5) + 1, 150 + (rand() % 5) + 1 };
	point2 p24 = { 100 + (rand() % 5) + 1, 100 + (rand() % 5) + 1 };
	//7
	point2 p25 = { 100 + (rand() % 5) + 1, 100 + (rand() % 5) + 1 };
	point2 p26 = { 100 + (rand() % 5) + 1, 150 + (rand() % 5) + 1 };
	point2 p27 = { 150 + (rand() % 5) + 1, 150 + (rand() % 5) + 1 };
	point2 p28 = { 150 + (rand() % 5) + 1, 100 + (rand() % 5) + 1 };
	//8
	point2 p29 = { 100 + (rand() % 5) + 1, 50 + (rand() % 5) + 1 };
	point2 p30 = { 100 + (rand() % 5) + 1, 100 + (rand() % 5) + 1 };
	point2 p31 = { 150 + (rand() % 5) + 1, 100 + (rand() % 5) + 1 };
	point2 p32 = { 150 + (rand() % 5) + 1, 50 + (rand() % 5) + 1 };
	
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float h = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	// 1 kwadrat
	glBegin(GL_POLYGON);
	glColor3f(r, b, g);
	glVertex2fv(p1);
	glVertex2fv(p2);
	glVertex2fv(p3);
	glVertex2fv(p4);
	glEnd();

	// 2 kwadrat
	glBegin(GL_POLYGON);
	glColor3f(b, g, r);
	glVertex2fv(p5);
	glVertex2fv(p6);
	glVertex2fv(p7);
	glVertex2fv(p8);
	glEnd();


	// 4 kwadrat
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	glVertex2fv(p13);
	glVertex2fv(p14);
	glVertex2fv(p15);
	glVertex2fv(p16);
	glEnd();

	// 3 kwadrat
	glBegin(GL_POLYGON);
	glColor3f(b, r, g);
	glVertex2fv(p9);
	glVertex2fv(p10);
	glVertex2fv(p11);
	glVertex2fv(p12);
	glEnd();

	// 5 kwadrat
	glBegin(GL_POLYGON);
	glColor3f(h, g, b);
	glVertex2fv(p17);
	glVertex2fv(p18);
	glVertex2fv(p19);
	glVertex2fv(p20);
	glEnd();

	// 6 kwadrat
	glBegin(GL_POLYGON);
	glColor3f(h, r, g);
	glVertex2fv(p21);
	glVertex2fv(p22);
	glVertex2fv(p23);
	glVertex2fv(p24);
	glEnd();

	//7 kwadrat
	glBegin(GL_POLYGON);
	glColor3f(h, g, r);
	glVertex2fv(p25);
	glVertex2fv(p26);
	glVertex2fv(p27);
	glVertex2fv(p28);
	glEnd();

	// 8 kwadrat
	glBegin(GL_POLYGON);
	glColor3f(r, h, b);
	glVertex2fv(p29);
	glVertex2fv(p30);
	glVertex2fv(p31);
	glVertex2fv(p32);
	glEnd();

	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania
}
/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania


void MyInit(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wn�trza okna - ustawiono na szary
}
/*************************************************************************************/

// Funkcja s�u��ca do kontroli zachowania proporcji rysowanych obiekt�w
// niezale�nie od rozmiar�w okna graficznego


void ChangeSize(GLsizei horizontal, GLsizei vertical)
// Parametry horizontal i vertical (szeroko�� i wysoko�� okna) s�
// przekazywane do funkcji za ka�dym razem, gdy zmieni si� rozmiar okna
{
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio okre�laj�cej proporcj� wymiar�w okna

	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0
		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna urz�dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Okre�lenie uk�adu wsp�rz�dnych obserwatora
	glLoadIdentity();
	// Okre�lenie przestrzeni ograniczaj�cej
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika proporcji okna
	// Gdy okno na ekranie nie jest kwadratem wymagane jest 
	// okre�lenie okna obserwatora. 
	// Pozwala to zachowa� w�a�ciwe proporcje rysowanego obiektu
	// Do okre�lenia okna obserwatora s�u�y funkcja glOrtho(...)

	if (horizontal <= vertical)
		glOrtho(-10.0, 160.0, -10.0, 160.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-10.0, 160.0*AspectRatio, -10.0, 160.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okre�lenie uk�adu wsp�rz�dnych     
	glLoadIdentity();
}
/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli


void main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wy�wietlania
	// GLUT_SINGLE - pojedynczy bufor wy�wietlania
	// GLUT_RGBA - model kolor�w RGB

	glutCreateWindow("Dywan Sierpinskiego");
	// Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna

	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn� (callback)
	// Biblioteka GLUT b�dzie wywo�ywa�a t� funkcj� za ka�dym razem, gdy
	// trzeba b�dzie przerysowa� okno


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn� za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy�ej) wykonuje wszelkie  
	// inicjalizacje konieczneprzed przyst�pieniem do renderowania

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}
/*************************************************************************************/