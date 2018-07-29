//Zalaczenie plikow naglowkowych
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <time.h>

//Definicja typu point3 - punkt w przestrzeni 3D
typedef float point3[3];

//Tablica punktow kontrolnych
GLfloat ctrlPoints[5][5][3] = {
	{ { -4.0, 0.0, 4.0 }, { -2.0, 0.0, 4.0 },
	{ 0.0, 0.0, 4.0 }, { 2.0, 0.0, 4.0 }, { 4.0, 2.0, 4.0 } },

	{ { -4.0, 0.0, 2.0 }, { -2.0, 2.0, 2.0 },
	{ 0.0, 2.0, 2.0 }, { 2.0, 2.0, 2.0 }, { 4.0, 2.0, 2.0 } },

	{ { -4.0, 2.0, 0.0 }, { -2.0, 4.0, 0.0 },
	{ 0.0, 8.0, 0.0 }, { 2.0, 4.0, 0.0 }, { 4.0, 2.0, 0.0 } },

	{ { -4.0, 0.0, -2.0 }, { -2.0, 2.0, -2.0 },
	{ 0.0, 2.0, -2.0 }, { 2.0, 2.0, -2.0 }, { 4.0, 2.0, -2.0 } },

	{ { -4.0, 0.0, -4.0 }, { -2.0, 0.0, -4.0 },
	{ 0.0, 0.0, -4.0 }, { 2.0, 0.0, -4.0 }, { 4.0, 2.0, -4.0 } }
};

//Tablica kolorow dla powierzchni opartej o punkty kontrolne
GLfloat ctrlPointsRGB[5][5][4] = { 0 };

//Czy pokazywac powierzchnie Beziera czy siatke punktow?
bool bezier = false;

//Parametry programu
float uRes = 10.0; //Dokladkosc powierzchni w "poziomie"
float vRes = 15.0; //Dokladkosc powierzchni w "pionie"

// Funkcja rysuj¹ca osie uk³adu wspó³rzêdnych
void Axes(void)
{
	point3  x_min = { -2.0, 0.0, 0.0 };
	point3  x_max = { 2.0, 0.0, 0.0 };
	// pocz¹tek i koniec obrazu osi x

	point3  y_min = { 0.0, -2.0, 0.0 };
	point3  y_max = { 0.0, 2.0, 0.0 };
	// pocz¹tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -2.0 };
	point3  z_max = { 0.0, 0.0, 2.0 };
	//  pocz¹tek i koniec obrazu osi y

	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x
	glVertex3fv(x_min);
	glVertex3fv(x_max);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y
	glVertex3fv(y_min);
	glVertex3fv(y_max);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z
	glVertex3fv(z_min);
	glVertex3fv(z_max);
	glEnd();
}

//Funkcja wysujaca siatke punktow kontrolnych
void Mesh(){
	for (int i = 0; i<5; i++){
		for (int j = 0; j<5; j++){
			
			//*****************Rysowanie punktow***************************

			//Kolor
			glColor3f(1.0, 0.0, 0.0);
			//Konfiguracja rysowania punktow - okragle, grubosc 7
			glEnable(GL_POINT_SMOOTH);
			glPointSize(7.0);
			glBegin(GL_POINTS);
			glVertex3fv(ctrlPoints[i][j]);
			glEnd();
			
			//****************Rysowanie lini*****************************

			//Kolor
			glColor3f(1.0, 1.0, 1.0);
				
			//Pion
			glBegin(GL_LINES);
			glVertex3fv(ctrlPoints[i][j]);
			if (j + 1 == 5)
				glVertex3fv(ctrlPoints[i][j]);
			else
				glVertex3fv(ctrlPoints[i][j + 1]);
			glEnd();
				
			//Poziom
			glBegin(GL_LINES);
			glVertex3fv(ctrlPoints[i][j]);
			if (i + 1 == 5)
				glVertex3fv(ctrlPoints[i][j]);
			else
				glVertex3fv(ctrlPoints[i + 1][j]);
			glEnd();	
		}
	}
	glEnd();
	}


// Funkcja okreœlaj¹ca co ma byæ rysowane (zawsze wywo³ywana gdy trzeba 
// przerysowaæ scenê)
void RenderScene(void)
{
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Zapamietanie stanu macierzy
	glPushMatrix();

	//Wyrysowanie osi
	Axes();

	//Rotacja
	glRotatef(45.0, 0.0, 1.0, 0.0);
	glRotatef(30.0, 1.0, 0.0, 1.0);

	//Wyrysowanie siatki lub powierzchni Beziera
	if (!bezier)
		Mesh();
	else
		glEvalMesh2(GL_FILL, 0, uRes, 0, vRes);
	//Przywrocenie stanu mecierzy
	glPopMatrix();
	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania
}

// Funkcja ustalaj¹ca stan renderowania
void MyInit(void)
{
	// Kolor czyszc¹cy (wype³nienia okna) ustawiono na czarny
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//Siatka punktow kontrolnych
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 5, 0, 1, 15, 5, &ctrlPoints[0][0][0]);
	//Siatka kolorow dla powierzchni opartej o punkty
	glMap2f(GL_MAP2_COLOR_4, 0, 1, 4, 5, 0, 1, 20, 5, &ctrlPointsRGB[0][0][0]);
	//Punkty kontrolne maja 3 wspolrzedne
	glEnable(GL_MAP2_VERTEX_3);
	//Kolor - cztery: R, G, B, A
	glEnable(GL_MAP2_COLOR_4);
	//Definicja siatki 20x20
	glMapGrid2f(uRes, 0, 1, vRes, 0, 1);
	//Proste modele
	glShadeModel(GL_FLAT);
}

// Funkcja ma za zadanie utrzymanie sta³ych proporcji rysowanych 
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokoœæ i szerokoœæ okna) s¹ 
// przekazywane do funkcji za ka¿dym razem gdy zmieni siê rozmiar okna.
void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okreœlaj¹cej proporcjê
	// wymiarów okna

	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical) 

	glMatrixMode(GL_PROJECTION);
	// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji

	glLoadIdentity();
	// Czyszcznie macierzy bie¿¹cej           

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wspó³czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okreœlenie tak zwanej
	// przestrzeni ograniczaj¹cej pozwalaj¹cej zachowaæ w³aœciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj¹cej s³u¿y funkcja
	// glOrtho(...)           

	if (horizontal <= vertical)
		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
	else
		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu                                    
	glLoadIdentity();
	// Czyszcenie macierzy bie¿¹cej
}

//Funkcja - callback dla klawiszy
void Keys(unsigned char key, int x, int y)
{
	switch (key) {
		//Zmiana sposobu wyswietlania
	case 'b':
		bezier = !bezier;
		break;
		//Modyfikacja polozenia jednego z pkt kontrolnych
	case 'm':
		if (ctrlPoints[2][2][1] == 8.0)
			ctrlPoints[2][2][1] = -1.0;
		else
			ctrlPoints[2][2][1] = 8.0;
	}
	//Aktualizacja powierzchni i przerysowanie
	MyInit();
	RenderScene();
}

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli
void main(void)
{
	//Ziarno losowosci
	srand((unsigned)time(NULL));

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Powierzchnia Beziera");

	//Losowanie kolorow
	for (int i = 0; i<5; i++){
		for (int j = 0; j<5; j++){
			ctrlPointsRGB[i][j][0] = 1.0;
			ctrlPointsRGB[i][j][1] = 1.0;
			ctrlPointsRGB[i][j][2] = ((float)(rand() % 10) + 1) / 10;
			ctrlPointsRGB[i][j][3] = 1.0;
		}
	}

	glutDisplayFunc(RenderScene);
	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹
	// (callback function).  Bedzie ona wywo³ywana za ka¿dym razem 
	// gdy zajdzie potrzba przeryswania okna

	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹
	// zazmiany rozmiaru okna  
	glutReshapeFunc(ChangeSize);
	MyInit();

	glEnable(GL_DEPTH_TEST);
	// W³¹czenie mechanizmu usuwania powierzchni niewidocznych

	//Rejestracja funkcji zwrotnej dla klawiatury
	glutKeyboardFunc(Keys);

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}